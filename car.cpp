#include "car.h"

Car::Car(b2World *world, b2Vec2 position) {

    carWheel1 = new CircleObject(b2_dynamicBody, 10);
    carWheel2 = new CircleObject(b2_dynamicBody, 10);

    sf::Rect<int> rect;
    rect.top = position.y;
    rect.left = position.x;
    rect.width = 16;
    rect.height = 16;

    carWheel1->setObjectRect(rect);
    b2CarWheel1Fixture = carWheel1->build(world, sf::Vector2i(16, 16));

    rect.top = position.y + 20;
    rect.left = position.x;

    carWheel2->setObjectRect(rect);
    b2CarWheel2Fixture = carWheel2->build(world, sf::Vector2i(16, 16));

    carBody = new RectangleObject(b2_dynamicBody);
    rect.width = 16 * 3;
    carBody->setObjectRect(rect);
    carBody->setWidth(16 * 3);
    carBody->setHeight(16);

    b2CarFixture = carBody->build(world, sf::Vector2i(16, 16));

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = carBody->getBody();
    jointDef.bodyB = carWheel1->getBody();
    jointDef.localAnchorB.Set(0, 0);
    jointDef.localAnchorA.Set(-25, 10);
    //    jointDef.enableMotor = true;
    //    jointDef.maxMotorTorque = 100;
    //    jointDef.motorSpeed = 90 * 3.14/180;

    joint1 = (b2RevoluteJoint *)world->CreateJoint(&jointDef);

    jointDef.bodyB = carWheel2->getBody();
    jointDef.localAnchorB.Set(0, 0);
    jointDef.localAnchorA.Set(25, 10);

    joint2 = (b2RevoluteJoint *)world->CreateJoint(&jointDef);
}

Car::~Car() {
    delete carWheel1;
    delete carWheel2;
    delete carBody;
}

void Car::draw(sf::RenderWindow &window) {
    carWheel1->draw(window);
    carWheel2->draw(window);
    carBody->draw(window);
}

void Car::moveRight() {
    //    carWheel1->getBody()->SetAngularVelocity(5);
    carWheel2->getBody()->SetAngularVelocity(5);
}

void Car::moveLeft() {
    carWheel1->getBody()->SetAngularVelocity(-5);
    //    carWheel2->getBody()->SetAngularVelocity(-5);
}

sf::Vector2f Car::getCenter() {
    return sf::Vector2f(carBody->getBody()->GetPosition().x, carBody->getBody()->GetPosition().y);
}
