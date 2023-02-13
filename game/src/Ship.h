#pragma once

class Ship {

    short currentSpeed;
    short health;

    Texture2D img;

    Vector2 currentPos;

public:
    Ship() {
        currentSpeed = 10;
        health = 100;
        currentPos.x = 0;
        currentPos.y = 100;
    };
    Ship(short pCurrentSpeed, short pHealth, Texture2D pImg, Vector2 pCurrentPos) {
        currentSpeed = pCurrentSpeed;
        health = pHealth;
        img = pImg;
        currentPos = pCurrentPos;
    }

    short getCurrentSpeed() { return currentSpeed; }
    void setCurrentSpeed(short pSpeed) { currentSpeed = pSpeed; };

    short getHealth() { return health; }
    void setHealth(short pDamage) { health = health - pDamage; };

    Texture2D getImg() { return img; };
    void setImg(Texture2D pImg) { img = pImg; };

    Vector2 getCurrentPosition() { return currentPos; };
    void setCurrentPosition(Vector2 pPosition) { currentPos = pPosition; }

    void Move(Vector2 delta) {
        currentPos.x = currentPos.x + (delta.x * currentSpeed);
        currentPos.y = currentPos.y + (delta.y * currentSpeed);
    }
};