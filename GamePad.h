#pragma once

#include "CImg.h"
#include "RectangleElement.h"
#include "D:/uroki/New/labka3/proekt/jpeg-9c/jpeglib.h"
#include <iostream>

using namespace cimg_library;
class GamePad : public RectangleElement
{
  private:
    static const int gamePadXsize = 8;
    static const int gamePadYsize = 8;

    CImg<unsigned char> gamePad;

    CImg<unsigned char> background;

    CImg<unsigned char> frameBuffer,
        frame;

    int widthFull,
        heightFull,

        WidthHalf,
        HeightHalf;

  public:
    GamePad() : RectangleElement()
    {

        gamePad = CImg<unsigned char>(gamePadXsize, gamePadYsize, 1, 3, 0);

        background = CImg<unsigned char>(512, 896, 1, 3, 1);

        frameBuffer = CImg<unsigned char>(background);

        frame = CImg<unsigned char>(frameBuffer);

        widthFull = 512;
        heightFull = 896;

        WidthHalf = widthFull / 2,
        HeightHalf = heightFull / 2;
    }

    //
    void clear()
    {

        gamePad.fill(0);
        frameBuffer = background;
    }

    //
    template <class T>
    void fillRandomBricks(T brick)
    {

        cimg_forXY(gamePad, x, y)

            if (0.1 + cimg::crand() >= 0)
        {

            CImg<> cbrick = CImg<double>::vector(100 + cimg::rand() * 155,
                                                 100 + cimg::rand() * 155,
                                                 100 + cimg::rand() * 155)
                                .unroll('v')
                                .resize(brick.getX(), brick.getY());

            //cimg_forV(cbrick, k) (cbrick.get_shared_channel(k).mul(brick.getBrick())) /= 255;

            frameBuffer.draw_image(cbrick, x * sizeX, y * sizeY);

            gamePad(x, y) = 1;
        }
    }

    //
    template <typename T1, typename T2, class T3>
    void killBrick(T1 X, T2 Y, T3 brick)
    {

        gamePad(X, Y) = 0;

        int x0 = X * brick.getX(),
            y0 = Y * brick.getY(),

            x1 = (X + 1) * brick.getX(),
            y1 = (Y + 1) * brick.getY();

        
        frameBuffer.draw_image(background.get_crop(x0, y0, x1, y1), x0, y0);
    }

    template <class T1, class T2, class T3>
    void display(T1 &imgDisplay, T2 board, T3 ball)
    {

        imgDisplay.display((frame = frameBuffer)

                               .draw_image(board.getGameBoard(), (int)(board.X() - board.widthHalf()), height() - board.height() - ball.height())

                               .draw_image(ball.getImage(), (int)(ball.getX() - ball.widthHalf()), (int)(ball.getY() - ball.heightHalf())));

        if (imgDisplay.wait(20).is_resized)
            imgDisplay.resize(imgDisplay);
    }

    int width() const { return widthFull; }
    int height() const { return heightFull; }
    int widthHalf() const { return WidthHalf; }
    int heightHalf() const { return HeightHalf; }

    int dimY() { return gamePad.dimy(); }
    double Sum() { return gamePad.sum(); }

    bool getGamePadValue(int x, int y) { return gamePad(x, y); }

    CImg<unsigned char> getFrame() { return frame; }
};