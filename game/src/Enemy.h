#pragma once


class Enemy :public Ship {

    short powerFire;
    Rectangle rectColision;

public:
    Enemy() {};
    Enemy(short pPowerFire, Rectangle pRectColision, Texture2D pImg, Vector2 pCurrentPosition, short pCurrentSpeed) {
        powerFire = pPowerFire;
        rectColision = pRectColision;
        setImg(pImg);
        setCurrentPosition(pCurrentPosition);
        setCurrentSpeed(pCurrentSpeed);
    }

    short getPowerFire() { return powerFire; }
    void setPowerFire(short pPowerFire) { powerFire = pPowerFire; }

    Rectangle getRectColision() { return rectColision; }
    void setRectColision(Rectangle pRectColision) { rectColision = pRectColision; };

};