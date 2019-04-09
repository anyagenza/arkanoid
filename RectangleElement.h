#pragma once

//#ifndef RECTANGLEELEMENT_H
//#define RECTANGLEELEMENT_H
struct RectangleElement {
protected:
    
    int sizeX;
    int sizeY;

public:
    
    RectangleElement() {
        
        sizeX = 64;
        sizeY = 32;
    }

    int getSizeX() const { return sizeX; }
    int getSizeY() const { return sizeY; }
};

////#endif