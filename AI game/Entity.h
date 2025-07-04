#pragma once
#include <d2d1.h>
#include "AI.h"

class Entity {
public:
    Entity(float X, float Y);

    virtual void Think();
    virtual void Think(float playerPosX, float playerPosY);

    void Physics();
    void Left();
    void Right();
    void Up();

    D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Gray);
    float width = 0.8f;
    float height = 1.8f;

    float posX;
    float posY;
    float velX;
    float velY;

private:
    const float acceleration = 0.03f;
    const float friction = 0.02f;
};

class Player : public Entity {
public:
    Player(float x, float y) : Entity(x, y)
    {
        color = D2D1::ColorF(D2D1::ColorF::Green);
    }

    void Think() override;

    void ForceUp();
};

class TestEnemy : public Entity {
public:
    TestEnemy(float x, float y, fann* brain) : Entity(x, y)
    //TestEnemy(float x, float y) : Entity(x, y)
    {
        color = D2D1::ColorF(D2D1::ColorF::Maroon);
        width = 1.1f;
        height = 1.1f;
        //CopyBrain(brain, indBrain);
        indBrain = fann_create_standard(3, 3, 6, 3);
        fann_set_learning_rate(indBrain, 0.7f);
        return;
    }

    fann* indBrain;
    void Think(float playerPosX, float playerPosY) override;
};