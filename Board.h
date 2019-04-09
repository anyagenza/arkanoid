#pragma once
#include "CImg.h"
#include "RectangleElement.h"
#include <iostream>
#include <iostream>
using namespace cimg_library;

class Board : public RectangleElement
{
  private:
    int boardXsize;
    int boardYsize;

    CImg<unsigned char> gameBoard;

    int boardWidth,
        boardHeight,
        boardWidthHalf;

    float boardX,
        boardXo;

    static const int RGB = 3;

  public:
    Board(int width) : RectangleElement()
    {

        boardXsize = sizeX * 2;
        boardYsize = sizeY / 2;

        gameBoard = CImg<unsigned char>(boardXsize, boardYsize, 1, RGB, 235);

        boardWidth = gameBoard.dimx();

        std::cout << gameBoard.dimx();
        boardHeight = gameBoard.dimy();
        boardWidthHalf = boardWidth / 2;

        boardX = (float)(width - boardWidthHalf);
        boardXo = (float)boardX;
    }

    void move(int x)
    {
        boardXo = boardX;
        boardX = (float)x;
    }

    template <class T1, class T2>
    int getMouseX(T1 &imgDisplay, T2 &gamePad)
    {
        int X = (int)boardX;

        float coef = 2.0f;
        imgDisplay.show_mouse();

        X = imgDisplay.mouse_x * coef;
        if (X < boardWidthHalf)
        {
            X = boardWidthHalf;
        }

        if (X >= gamePad.width() - boardWidthHalf)
        {
            X = gamePad.width() - boardWidthHalf - 1;
        }
        return X;
    }

    CImg<unsigned char> getGameBoard() { return gameBoard; };

    int height() { return boardHeight; }
    int widthHalf() { return boardWidthHalf; }

    float X() { return boardX; }
    float Xo() { return boardXo; }
};