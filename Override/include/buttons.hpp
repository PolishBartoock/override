#include "Functions.hpp"

void onButtonAPress() 
{
   
}

void onButtonBPress() 
{
    while(Controller.ButtonB.pressing())
    {
        
    }
    
}

void onButtonXPress() 
{
    while(Controller.ButtonX.pressing())
    {
    
    }
}

void onButtonYPress() 
{
           
             toggleLoader();
}

void onButtonL1Press() 
{
        while(Controller.ButtonL1.pressing())
    {
        scoreOben();
    }
    intakeStop();
}

void onButtonL2Press() 
{
 
}

void onButtonR1Press() 
{
        while(Controller.ButtonR1.pressing())
    {
        Intaken();

    }
    intakeStop();
}

void onButtonR2Press() 
{
       while(Controller.ButtonR2.pressing())
    {
        Outtaken();
    }
    intakeStop();
}

void onButtonUpPress() 
{
    while(Controller.ButtonUp.pressing())
    {
    
    }
}

void onButtonDownPress() 
{

}

int Auton = 0;
void onButtonLeftPress()
{
  while (Controller.ButtonLeft.pressing())
    {
        Auton++;

        if (Auton > 2)
            Auton = 0;

        wait(200, msec);
    }
}

void onButtonRightPress() 
{
      toggleDescorer();
}