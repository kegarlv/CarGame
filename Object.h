#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include "exception.h"

class Object {
  public:
    enum ShapeType { RECTANGLE,
                     POLYGON,
                     CIRCLE };

    Object();
    virtual ~Object();
    int getPropertyInt(std::string name);
    float getPropertyFloat(std::string name);
    std::string getPropertyString(std::string name);

    ShapeType getShapeType() const;
    std::string getName() const;
    std::string getType() const;
    sf::Rect<int> getRect() const;
    b2BodyType getBodyType() const;
    b2BodyDef getBodyDef();
    b2FixtureDef *getFixtureDef();
    b2Body *getBody() const;
    b2Vec2 getPosition() const;
    sf::Sprite getSprite() const;

    void setPosition(const b2Vec2 &value);
    void setShapeType(const ShapeType &value);
    void setProperty(std::string name, std::string property);
    void setName(const std::string &value);
    void setType(const std::string &value);
    void setObjectRect(const sf::Rect<int> &rect);
    void setSprite(const sf::Sprite &value);

    virtual b2Fixture *build(b2World *world, const sf::Vector2i &tileSize) = 0;
    virtual void draw(sf::RenderWindow &window);


    friend std::ostream &operator<<(std::ostream &os, Object &obj) {
        os << "Object sf::Rect: " << std::endl
           << "\tTop " << obj.getRect().top << std::endl
           << "\tLeft " << obj.getRect().left << std::endl
           << "\tWidth " << obj.getRect().width << std::endl
           << "\tHeight " << obj.getRect().height << std::endl;

        os << std::endl;

//        os << "b2Position: " << std::endl
//           << "\tx: " << obj.getBody()->GetPosition().x << std::endl
//           << "\ty: " << obj.getBody()->GetPosition().y << std::endl;

        os << std::endl;
        return os;
    }


protected:
    std::map<std::string, std::string> prop;
    std::string name, type;
    ShapeType shapeType;
    sf::Rect<int> rect;
    sf::Sprite sprite;
    bool isSprite = false;

    b2Vec2 position;

    b2BodyType bodyType;
    b2BodyDef bodyDef;
    b2Body *body;
    b2FixtureDef *fixtureDef;
};

#include "circleobject.h"
#include "polygonobject.h"
#include "rectangleobject.h"

#endif // OBJECT_H
