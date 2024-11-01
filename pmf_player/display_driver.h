/*
    Driver for the ITM2M display, a soviet 4x4 plasma display
*/

#include <Arduino.h>

//                 \/PORT\/
#define X0  1<<4        //D 
#define X1  1<<7        //D 
#define X2  1<<2   //B  
#define X3  1<<0   //B  
#define Y0  1<<3   //B    
#define Y1  1<<5        //D   
#define Y2  1<<1   //B    
#define Y3  1<<6        //D   

#define RST 1<<4        //D

#define TC_RES   22     //350us reset time 
#define TC_UPD   156    //100Hz operation with 4 brightness levels means 2.5ms update rate

// 4 by 4 pixel array, 0 = off, 1 = 25% brightness, 2 = 50% brightness, >2 = 100% brightness
extern uint8_t pixels[4][4];

void setup_disp();
