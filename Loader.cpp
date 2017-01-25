#include "Loader.h"

Loader::Loader() {
}

Loader::~Loader() {
    for (auto x : objects)
        delete x;
}

bool Loader::loadFromFile(std::string filename) {
    TiXmlDocument levelFile(filename.c_str());
    if (!levelFile.LoadFile()) {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    //get root element
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    //get basic info
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileSize.x = atoi(map->Attribute("tilewidth"));
    tileSize.y = atoi(map->Attribute("tileheight"));

    std::cout << "width"
              << "\t" << width << "\n"
              << "height"
              << "\t" << height << "\n"
              << "tSize"
              << "\t" << tileSize.x << "x" << tileSize.y << std::endl
              << std::endl;

    //get tileset info
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileId = atoi(tilesetElement->Attribute("firstgid"));

    TiXmlElement *imageElement;
    imageElement = tilesetElement->FirstChildElement("image");
    std::string imagepath = imageElement->Attribute("source");

    sf::Image image;

    if (!image.loadFromFile(imagepath)) {
        std::cout << "Failed to load " << imagepath << std::endl;
        return false;
    }
    tilesetImage.loadFromImage(image);
    tilesetImage.setSmooth(false);

    int columns = tilesetImage.getSize().x / tileSize.x;
    int rows = tilesetImage.getSize().y / tileSize.y;

    std::vector<sf::Rect<int>> subRects;

    //generate field
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * tileSize.y;
            rect.height = tileSize.y;
            rect.left = x * tileSize.x;
            rect.width = tileSize.x;

            subRects.push_back(rect);
        }

    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");

    //for every layer
    std::cout << "Processing layers..." << std::endl;
    while (layerElement) {
        Layer layer;

        //get name
        if (layerElement->Attribute("name") != NULL)
            layer.name = layerElement->Attribute("name");

        std::cout << "\t " << layer.name << std::endl;

        //get opacity
        if (layerElement->Attribute("opacity") != NULL)
            layer.opacity = 255 * strtod(layerElement->Attribute("opacity"), NULL);
        else
            layer.opacity = 255;

        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL) {
            std::cout << "No layer information found" << std::endl;
            //            return false;
        }

        //process tiles
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL) {
            std::cout << "No tile information found" << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileId;

            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileSize.x, y * tileSize.y);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y + 1 >= height ? y = 0 : y++;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    std::cout << "Done processing layers" << std::endl
              << std::endl;
    TiXmlElement *objectGroupElement;

    //if map contains objectGroups
    if (map->FirstChildElement("objectgroup") != NULL) {
        std::cout << "Processing objectgpoups..." << std::endl;

        //for every object
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            std::cout << "\t" << objectGroupElement->Attribute("name") << std::endl;
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                //get type and name
                std::string objectType;
                std::string objectName;
                if (objectElement->Attribute("type") != NULL) {
                    objectType = objectElement->Attribute("type");
                }
                if (objectElement->Attribute("name") != NULL) {
                    objectName = objectElement->Attribute("name");
                }

                //TODO cleanup this

                Object *object;

                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                sf::Rect<int> objectRect;
                objectRect.top = y;
                objectRect.left = x;

                if (objectElement->Attribute("width") != NULL) {
                    float height = atof(objectElement->Attribute("height"));
                    float width = atof(objectElement->Attribute("width"));
                    object = new RectangleObject(b2_staticBody,width, height);
                    RectangleObject *rObj = dynamic_cast<RectangleObject *>(object);
                    rObj->setPosition(b2Vec2((x + width )/ 2, (y + height) / 2));

                    objectRect.width = rObj->getWidth();
                    objectRect.height = rObj->getHeight();

                } else if (TiXmlElement *el = objectElement->FirstChildElement("polygon")) {
                    object = new PolygonObject();
                    PolygonObject *pObj = dynamic_cast<PolygonObject *>(object);
                    pObj->setPoints(el->Attribute("points"));

                    objectRect.width = 32;
                    objectRect.height = 32;

                    pObj->setPosition(b2Vec2(x, y));

                } else {
                    object = new RectangleObject(b2_staticBody);
                    RectangleObject *rObj = dynamic_cast<RectangleObject *>(object);
                    int height = subRects[atoi(objectElement->Attribute("gid")) - firstTileId].height;
                    int width = subRects[atoi(objectElement->Attribute("gid")) - firstTileId].width;

                    rObj->setHeight(height);
                    rObj->setWidth(width);
                    //                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileId]);
                }

                object->setName(objectName);
                object->setType(objectType);
                object->setObjectRect(objectRect);

                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object->setProperty(propertyName, propertyValue);

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);
                objLayers[objectGroupElement->Attribute("name")].push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
        std::cout << "Done processing objectgroups" << std::endl
                  << std::endl;
    } else {
        std::cout << "No object layers found" << std::endl
                  << std::endl;
    }

    return true;
}

Object *Loader::getObject(std::string name) {
    for (auto obj : objects)
        if (obj->getName() == name)
            return obj;
}

void Loader::draw(sf::RenderWindow &window) {
    for (auto layer : layers)
        for (auto tile : layer.tiles)
            window.draw(tile);
}

std::vector<Object *> &Loader::getObjects(std::string name) {
    std::vector<Object *> res;
    for (auto obj : objects)
        if (obj->getName() == name)
            res.push_back(obj);
    return res;
}

const sf::Vector2i &Loader::getTileSize() const { return tileSize; }

std::vector<Object *> &Loader::getObjLayers(std::string name) {
    return objLayers[name];
}
