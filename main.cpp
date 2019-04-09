
#include "CImg.h"
#include "RectangleElement.h" 
#include "GamePad.h" 
#include "Brick.h" 
#include "Ball.h" 
#include "Board.h" 
#include "Menu.h" 
using namespace cimg_library;



//
int main()
{
    RectangleElement rectangle; 
    GamePad gamePad;
    Brick brick; 
    Ball ball; 
    Board board(gamePad.width()); 
    Menu menu; 
    CImgDisplay imgDisplay(512/2,896/2, "Tiny Arkanoid", 0); 

   
    imgDisplay.move((CImgDisplay::screen_dimx() - gamePad.width()) / 2, (CImgDisplay::screen_dimy() - gamePad.height()) / 2);

  
    
    for (unsigned int playerScore = 0, bricksScore = 0;
                     !imgDisplay.is_closed && imgDisplay.key != cimg::keyESC && !menu.isExit();)
    {
        
        if (ball.fallDown(gamePad) || playerScore == bricksScore)
        {
            imgDisplay.show_mouse(); 

            
            menu.showMenu(imgDisplay, gamePad, ball, playerScore, bricksScore);

            gamePad.clear(); 
            gamePad.fillRandomBricks(brick);

          
            ball.initialize((float) gamePad.widthHalf(), gamePad.dimY() * rectangle.getSizeY() + ball.height());

           
            bricksScore = (int) gamePad.Sum();
            playerScore = 0;

            imgDisplay.hide_mouse(); 
        }

        gamePad.display(imgDisplay, board, ball); 
        int X = board.getMouseX(imgDisplay, gamePad); 
        board.move(X); 
        ball.move(); 

        
        playerScore = ball.testCollisions(gamePad, brick, board, playerScore,ball);

        
        imgDisplay.set_title("Left : %u", bricksScore - playerScore);
    }
    return 0;
}