#pragma once
//
#include <iostream>
#include "CImg.h"
#include "RectangleElement.h"
using namespace cimg_library;

class Ball : public RectangleElement
{
  private:
    int ballXsize;
    int ballYsize;

    CImg<unsigned char> gameBall;

    float SpeedVertical = 3 * 2;
    float SpeedHorisontal = 3 * 2;

    float X = 0,
          Y = 0;

    float Xo = 0,
          Yo = 0;

    float xVector = 0,
          yVector = 0;

    static const int RGB = 3;

  public:
    Ball() : RectangleElement()
    {

        ballXsize = 5 * 4;
        ballYsize = 5 * 4;

        unsigned char white[RGB] = {255, 255, 255};

        gameBall = CImg<unsigned char>(ballXsize, ballYsize, 1, RGB, 0);
        gameBall.draw_circle(ballXsize / 2, ballYsize / 2, ballXsize / 2 - 1, white);
    }

    //
    void move()
    {

        Xo = X;
        Yo = Y;

        X += xVector;
        Y += yVector;
    }

    //
    template <typename T1, typename T2>
    void initialize(T1 xO, T2 yO)
    {

        Xo = xO;
        Yo = yO;
        X = Xo;
        Y = Yo;

        xVector = SpeedVertical;
        yVector = SpeedHorisontal;
    }

    template <class T>
    bool fallDown(T &gamePad) { return (Y > gamePad.height()); }

    template <class T1, class T2, class T3, typename T4, class T5>
    unsigned int testCollisions(T1 &gamePad, T2 &brick, T3 board, T4 playerScore, T5 ball)
    {

        if ((X >= gamePad.width() - widthHalf()) ||
            (X < widthHalf()))
        {
           
            X -= xVector;
            Y -= yVector;
            xVector = -xVector;
        }

        if (Y < heightHalf())
        {
            Y = (float)heightHalf();
            yVector = -yVector;
        }

        if (Y >= gamePad.height() - board.height() - ballXsize - heightHalf() &&
            Y < gamePad.height() - ballYsize - heightHalf() &&
            board.X() - board.widthHalf() <= X &&
            board.X() + board.widthHalf() >= X)
        {
            X = Xo;
            Y = gamePad.height() - board.height() - (float)ballXsize - heightHalf();

            yVector = -yVector;
            xVector += (board.X() - board.Xo()) / heightHalf();
            if (cimg::abs(xVector) > ballXsize)
                xVector *= ballXsize / cimg::abs(xVector);
        }

        if (Y < gamePad.dimY() * sizeY)
        {  
           
            int X = (int)getX() / sizeX,
                Y = (int)getY() / sizeY;

            if (gamePad.getGamePadValue(X, Y))
            {

                playerScore++;
                float x0 = X * brick.getX(),
                      y0 = Y * brick.getY(),
                      x1 = (X + 1) * brick.getX(),
                      y1 = (Y + 1) * brick.getY();

                float R = ballXsize / 2;

                if ((ball.getY() + R > y0) && (ball.getY() + R < y1) && (ball.getX() < y1))
                {
                    xVector = -xVector;
                }
                else if ((ball.getY() + R > y0) && (ball.getY() + R < y1) && (ball.getX() + R > y0))
                {
                    xVector = -xVector;
                }
                else if (((ball.getX() + R) - x0 > 0) && ((ball.getX() + R) - x1 < 0) && (ball.getY() - y1 < 0))
                {
                    yVector = -yVector;
                }
                else if (((ball.getX() + R) - x0 > 0) && ((ball.getX() + R) - x1 < 0) && (ball.getY() - y1 > 0))
                {
                    yVector = -yVector;
                }

                else if ((ball.getX() < x1) && (y1 > ball.getY() > y0) && (ball.getX() - x1 > y1 - ball.getY()))
                {
                    yVector = -yVector;
                }
                else if ((ball.getX() < x1) && (y1 > ball.getY() > y0) && (ball.getX() - x1 < y1 - ball.getY()))
                {
                    xVector = -xVector;
                }
                else if ((ball.getX() < x1) && (ball.getY() < y0) && (ball.getY() + 2 * R - y0 > x1 - ball.getX()))
                {
                    xVector = -xVector;
                }
                else if ((ball.getX() < x1) && (ball.getY() < y0) && (ball.getY() + 2 * R - y0 < x1 - ball.getX()))
                {
                    yVector = -yVector;
                }
                else if ((ball.getX() + 2 * R > x0) && (ball.getY() + 2 * R > y0) && (ball.getY() + 2 * R - y0 > ball.getX() - x0))
                {
                    yVector = -yVector;
                }
                else if ((ball.getX() + 2 * R > x0) && (ball.getY() + 2 * R > y0) && (ball.getY() + 2 * R - y0 > ball.getX() - x0))
                {
                    xVector = -xVector;
                }
                else if ((ball.getX() < x0) && (ball.getY() > y0) && (ball.getY() < y1) && (ball.getX() + 2 * R - x0 > y1 - ball.getY()))
                {
                    yVector = -yVector;
                }
                else if ((ball.getX() < x0) && (ball.getY() > y0) && (ball.getY() < y1) && (ball.getX() + 2 * R - x0 < y1 - ball.getY()))
                {
                    xVector = -xVector;
                }
                else
                {
                    yVector = -yVector;
                }

                gamePad.killBrick(X, Y, brick);
            }
        }
        return playerScore;
    }

    CImg<unsigned char> getImage() { return gameBall; }

    float getX() { return X; }
    float getY() { return Y; }

    int width() { return gameBall.dimx(); }
    int height() { return gameBall.dimy(); }

    int widthHalf() { return width() / 2; }
    int heightHalf() { return height() / 2; }
};