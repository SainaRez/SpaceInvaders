
/************ ECE2049 Garbett Rezvani Lab 1 Code *********/
/**************  11 September 2017   ******************/
/***************************************************/

#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Function Prototypes
void swDelay(char numLoops);

// Declare globals here
unsigned char currKey = 0;

// Main
void main(void){
    //unsigned char ret_val = 0x0F;
    unsigned char dispSz = 3;
    unsigned char dispThree[3];

    // Define some local variables

    unsigned int somethingFun = 0x2121;

    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    // Useful code starts here
    initLeds();

    configDisplay();
    configKeypad();

    // *** Intro Screen ***

    // Draw a box around everything
   // Graphics_Rectangle box = {.xMin = 5, .xMax = 91, .yMin = 5, .yMax = 91 };
   // Graphics_drawRectangle(&g_sContext, &box);

    // We are now done writing to the display.  However, if we stopped here, we would not
    // see any changes on the actual LCD.  This is because we need to send our changes
    // to the LCD, which refreshes the display.
    // Since this is a slow operation, it is best to refresh (or "flush") only after
    // we are done drawing everything we need.

    dispThree[0] = ' ';
    dispThree[2] = ' ';
    int state = 0;
    int substate1 = 0;
    while (1)    // Forever loop
    {
       switch(state){
       case 0:
           Graphics_clearDisplay(&g_sContext); // Clear the display
           Graphics_drawStringCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 50, 50, TRANSPARENT_TEXT);
           Graphics_flushBuffer(&g_sContext);
           //swDelay(10000);

           startGame();     //waits for '*' input to start game
           state++;
           break;
       case 1:                      //Countdown, need to ask in office hours how to make each number show on screen for longer
             Graphics_clearDisplay(&g_sContext); // Clear the display
              Graphics_drawStringCentered(&g_sContext, "...3...", AUTO_STRING_LENGTH, 40, 40, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              Graphics_clearDisplay(&g_sContext); // Clear the display
              Graphics_drawStringCentered(&g_sContext, "...2...", AUTO_STRING_LENGTH, 40, 40, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              Graphics_clearDisplay(&g_sContext); // Clear the display
              Graphics_drawStringCentered(&g_sContext, "...1...", AUTO_STRING_LENGTH, 40, 40, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              state++;
          break;

       case 2:                      //Game
           //switch(substate1){
           //case 0:          //Draw aliens
               drawAliens();
              // substate1++;
               break;
          /* case 1:          //Update screen, moving aliens down and looking for keypad input
               break;
           case 2:         //Level transition, incrementing of number and speed of aliens
               //include level++ at some point
               break;
           }
       case 3:
           display("GAME OVER", 24 48);
           flashLEDs;                   //not sure if this is inclusive of what is needed during a game over, need to check
           soundBuzzer();
           break; */
       // }           //end switch case


    }
}// end while (1)
} // end main
void startGame(){
    while(1){
        currKey = getKey();
        if (currKey == '*'){
                       return;
                   }
    }
}

void drawAliens(){
    int level = 2;
    int rands[level];
    int i, current;
    for(i=0; i<7; i++){
        rands[i] = rand() % 7;  //not sure if I need to make sure the random numbers are new
        current = rands[i];
        if(current == 1){
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 5, 5, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
        if(current == 2){
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 20, 5, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
        if(current == 3){
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 39, 5, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
        if(current == 4){
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 56, 5, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
        if(current == 5){
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "5", AUTO_STRING_LENGTH, 73, 5, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
        if(current == 6){
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "6", AUTO_STRING_LENGTH, 90, 5, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
    }
}










void moveAliens(){

}

void swDelay(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2013

    volatile unsigned int i,j;  // volatile to prevent optimization
                                        // by compiler

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}
