
#include <iostream>
#include "CImg.h"
#include "RectangleElement.h"
#include "Ball.h"
using namespace cimg_library;

class GamePad;
Ball::Ball() : RectangleElement()

{

    ballXsize = 5 * 2;
    ballYsize = 5 * 2;

    unsigned char white[RGB] = {255, 255, 255};

    gameBall = CImg<unsigned char>(ballXsize, ballYsize, 1, RGB, 0);
    gameBall.draw_circle(ballXsize / 2, ballYsize / 2, ballXsize / 2 - 1, white);
};

void Ball::move()

{

    Xo = X;
    Yo = Y;

    X += xVector;
    Y += yVector;
};

void Ball::initialize(float xO, int yO)
{

    Xo = xO;
    Yo = yO;
    X = Xo;
    Y = Yo;

    xVector = SpeedVertical;
    yVector = SpeedHorisontal;
}


bool Ball::fallDown(GamePad& gamePad)
{
    return (Y > gamePad.height());
}
