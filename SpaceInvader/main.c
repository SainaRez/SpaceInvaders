
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Function Prototypes
void swDelay(char numLoops);
void startGame();
void makeArray();
void drawAliens();
void moveAliens();

// Declare globals here
unsigned char currKey = 0;
int level = 1;
int randArray[6] = {};
int location = 8;
int locationArray[10] = {8,17,26,35,44,53,62,71,80,89};

// Main
void main(void){
    //unsigned char ret_val = 0x0F;

    unsigned char dispSz = 3;
    unsigned char dispThree[3];
    time_t t;
    int isEmpty = 5;
    int f = 0;
    int e = 0;
    int c = 0;

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
    srand((unsigned) time(&t));
    while (1)    // Forever loop
    {
       switch(state){
       case 0:
           Graphics_clearDisplay(&g_sContext); // Clear the display
           Graphics_drawStringCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 50, 50, TRANSPARENT_TEXT);
           Graphics_flushBuffer(&g_sContext);
           startGame(); //waits for '*' input to start game
           state++;
           break;
       case 1:
              Graphics_clearDisplay(&g_sContext); // Clear the display
              Graphics_drawStringCentered(&g_sContext, "3!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              swDelay(1);
              Graphics_clearDisplay(&g_sContext); // Clear the display
              Graphics_drawStringCentered(&g_sContext, "2!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              swDelay(1);
              Graphics_clearDisplay(&g_sContext); // Clear the display
              Graphics_drawStringCentered(&g_sContext, "1!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              swDelay(1);
              Graphics_clearDisplay(&g_sContext); // Clear the displays
              state++;
          break;
       case 2:          //Draw aliens
           for (f = 0; f < 6; f++) {
                randArray[f] = 0;
           }
           location = 8;
           makeArray();
           unsigned int k = 0;
           /*
           while (k <= 3) {
           drawAliens();
           k = k+1;
           }*/
           drawAliens();
           while(k <= 50000) {
               k++;
           }
           state++;
           break;
       case 3:      //Update screen, moving aliens down and looking for keypad input
           moveAliens();
           for (e = 0; e < 6; e++) {
               if (randArray[e] != 0) {
                isEmpty = 0;   //array is not all zero
                break;
               }
               else {
                   isEmpty = 1; //array is all zero
               }
           }
           if (location == 89 && isEmpty == 0) {
               state++;
           }
           else if (location == 89 && isEmpty == 1) {
               if (level < 6) {

                   Graphics_clearDisplay(&g_sContext);
                   Graphics_drawStringCentered(&g_sContext, "Next Level!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(3);
                   Graphics_clearDisplay(&g_sContext);
                   level++;
                   state = 2;
               }
               else {
                   BuzzerOn();
                   setLeds(15);
                   Graphics_clearDisplay(&g_sContext);
                   Graphics_drawStringCentered(&g_sContext, "YOU WON!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(3);
                   Graphics_clearDisplay(&g_sContext);
                   BuzzerOff();
                   LedOff();
                   level = 1;
                   state = 0;
               }
           }
           break;
       case 4:
           Graphics_clearDisplay(&g_sContext); // Clear the display
           k = 0;
           while (k < 10) {
               setLeds(15);
               BuzzerOn();
               Graphics_drawStringCentered(&g_sContext, "You Suck", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
               Graphics_flushBuffer(&g_sContext);
               k++;
           }
           for (c = 0; c < 6; c++) {
               randArray[c] = 0;
          }
           location = 8;
           BuzzerOff();
           LedOff();
           state = 0;
           level = 1;
           break;
    }
}// end while (1)

   //This is test code

    /*while (1)    // Forever loop
        {
           switch(state){
           case 0:
               Graphics_clearDisplay(&g_sContext); // Clear the display
               Graphics_drawStringCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 50, 50, TRANSPARENT_TEXT);
               Graphics_flushBuffer(&g_sContext);
               startGame(); //waits for '*' input to start game
               state++;
               break;
           case 1:
                  Graphics_clearDisplay(&g_sContext); // Clear the display
                  Graphics_drawStringCentered(&g_sContext, "3!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                  Graphics_flushBuffer(&g_sContext);
                  swDelay(1);
                  Graphics_clearDisplay(&g_sContext); // Clear the display
                  Graphics_drawStringCentered(&g_sContext, "2!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                  Graphics_flushBuffer(&g_sContext);
                  swDelay(1);
                  Graphics_clearDisplay(&g_sContext); // Clear the display
                  Graphics_drawStringCentered(&g_sContext, "1!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                  Graphics_flushBuffer(&g_sContext);
                  swDelay(1);
                  Graphics_clearDisplay(&g_sContext); // Clear the displays
                  state++;
              break;
           case 2:          //Draw aliens
               for (f = 0; f < 6; f++) {
                    randArray[f] = 0;
               }
               unsigned int k = 0;
               int l = 0;
               for (l = 0; l < 10; l++) {
               int location = locationArray[l];
               makeArray();
               while (k <= 3) {
               drawAliens();
               k++;
               }
             //Update screen, moving aliens down and looking for keypad input
               moveAliens();
               for (e = 0; e < 6; e++) {
                   if (randArray[e] != 0) {
                    isEmpty = 0;   //array is not all zero
                    break;
                   }
                   else {
                       isEmpty = 1; //array is all zero
                   }
               }
               if (location == 89 && isEmpty == 0) {
                   state++;
               }
               else if (location == 89 && isEmpty == 1) {
                   if (level < 6) {

                       Graphics_clearDisplay(&g_sContext);
                       Graphics_drawStringCentered(&g_sContext, "Next Level!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                       Graphics_flushBuffer(&g_sContext);
                       swDelay(3);
                       Graphics_clearDisplay(&g_sContext);
                       level++;
                       state = 2;
                       break;
                   }
                   else {
                       BuzzerOn();
                       setLeds(15);
                       Graphics_clearDisplay(&g_sContext);
                       Graphics_drawStringCentered(&g_sContext, "YOU WON!", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                       Graphics_flushBuffer(&g_sContext);
                       swDelay(3);
                       Graphics_clearDisplay(&g_sContext);
                       BuzzerOff();
                       LedOff();
                       level = 1;
                       state = 0;
                   }
               }
               }
               break;
           case 3:
               Graphics_clearDisplay(&g_sContext); // Clear the display
               k = 0;
               while (k < 10) {
                   setLeds(15);
                   BuzzerOn();
                   Graphics_drawStringCentered(&g_sContext, "You Suck", AUTO_STRING_LENGTH, 48, 40, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   k++;
               }
               for (c = 0; c < 6; c++) {
                   randArray[c] = 0;
              }
               location = 8;
               BuzzerOff();
               LedOff();
               state = 0;
               level = 1;
               break;
        }
    }// end while (1) */




} // end main

void startGame(){
    while(1){
        currKey = getKey();
        if (currKey == '*'){
            return;
        }
    }
}

void makeArray() {
    int j;
    for(j = 0; j < level; j++) {
        int n1;
        n1 = (rand() % 6) + 1;
        int k;
        int cond;
        cond = 1;
        while (cond != 0){
            cond = 0;
            for (k = 0; k < j; k++){
                cond = cond + (n1 == randArray[k]);
            }
            if (cond != 0)
                n1 = (rand() % 6) + 1;
        }
        randArray[j] = n1;
    }
    return;
}

void drawAliens(){

    int i, current = 0;
    for(i = 0; i < level; i++){
        //randArray[i] = (rand() % 6) + 1;
        current = randArray[i];
        if(current == 1){
            //Graphics_drawCircle(&g_sContext, 5, location, 6);
            Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 5, location, TRANSPARENT_TEXT);
            //Graphics_flushBuffer(&g_sContext);
        }
        if(current == 2){
            //Graphics_drawCircle(&g_sContext, 5, location, 6);
            Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 20, location, TRANSPARENT_TEXT);
            //Graphics_flushBuffer(&g_sContext);
        }
        if(current == 3){
            //Graphics_drawCircle(&g_sContext, 5, location, 6);
            Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 39, location, TRANSPARENT_TEXT);
            //Graphics_flushBuffer(&g_sContext);
        }
        if(current == 4){
            //Graphics_drawCircle(&g_sContext, 56, location, 6);
            Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 56, location, TRANSPARENT_TEXT);
            //Graphics_flushBuffer(&g_sContext);
        }
        if(current == 5){
            //Graphics_drawCircle(&g_sContext, 5, location, 6);
            Graphics_drawStringCentered(&g_sContext, "5", AUTO_STRING_LENGTH, 73, location, TRANSPARENT_TEXT);
            //Graphics_flushBuffer(&g_sContext);
        }
        if(current == 6){
            //Graphics_drawCircle(&g_sContext, 5, location, 6);
            Graphics_drawStringCentered(&g_sContext, "6", AUTO_STRING_LENGTH, 90, location, TRANSPARENT_TEXT);
            //Graphics_flushBuffer(&g_sContext);
        }
        Graphics_flushBuffer(&g_sContext);
    }
    return;
}

void moveAliens(){
    int row = 0;
    int newArray[6] = {};
    char key[1];
    while (row < 9) {
        location = location + 9;
        Graphics_clearDisplay(&g_sContext);
        //drawAliens();
        //int rate = 11;
        unsigned int k = 0;
        //while (k <= rate) {
        int rate = 6  - level;
        for (k = 0; k <= rate*10; k++) {
            drawAliens();
            char key[1];
            key[0] = getKey();
            unsigned int keyPressed = atoi(key);
            int x = 0;
            int n;
            for (n = 0; n < level; n++) {
                if (randArray[n] != keyPressed) {
                    newArray[x] = randArray[n];
                    x++;
                }
            }
            int c;
           for (c = 0; c < 6; c++) {
               randArray[c] = newArray[c];
               newArray[c] = 0;
           }
            //k = k+1;
            //rate = rate - 2;
        }
        /*drawAliens();
        key[0] = getKey();
        unsigned int keyPressed = atoi(key);
        int x = 0;
        int n;
        for (n = 0; n < level; n++) {
            if (randArray[n] != keyPressed) {
                newArray[x] = randArray[n];
                    x++;
            }
        }
        int c;
        for (c = 0; c < 6; c++) {
            randArray[c] = newArray[c];
            newArray[c] = 0;
        }
        int dRate = 50 * level;
        while (k <= (1200 - dRate)) {
            k = k+1;
            key[0] = getKey();
        }*/
        row++;
    }
    return;
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
