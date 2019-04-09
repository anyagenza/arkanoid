#pragma once
//
#include "CImg.h"
#include "RectangleElement.h" 
using namespace cimg_library;

class Brick : public RectangleElement {
private:
  
    int brickXsize;
    int brickYsize;

    CImg<unsigned char> gameBrick;

public:

    Brick() : RectangleElement() {
        brickXsize = sizeX / 2;
        brickYsize = sizeY;
        

    
        gameBrick = CImg<unsigned char> (brickXsize, brickYsize, 1, 1, 200);
        gameBrick.resize(sizeX - 1, sizeY - 1, 1, 1, 1);
        gameBrick.resize(sizeX, sizeY, 1, 1, 0);
    }

    CImg<unsigned char> getBrick() { return gameBrick; }

    int getX() const { return gameBrick.dimx(); }
    int getY() const { return gameBrick.dimy(); }
};