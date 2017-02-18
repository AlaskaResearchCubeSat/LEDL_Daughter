//Kyle Tam
// Feb. 17, 2017
// LEDL gyroscope header

#ifndef _L3G4200_GYRO_H
#define _L3G4200_GYRO_H

//SDO pulled high so SAD= 1101001b
//fall edge triggered

//fixed address bits
#define SAD         0x68
#define READ_SAD    0xD3
#define Write_SAD   0xD2

/////////////////////register addresses////////////////// 
#define WHO_AM_I    0x0F
#define REFERENCE   0X25
#define OUT_TEMP    0x26
#define STATUS_REG  0x27

///Axis Registers
#define OUT_X_LOW   0x28
#define OUT_X_HIGH  0x29
#define OUT_Y_LOW   0x2A
#define OUT_Y_HIGH  0x2B
#define OUT_Z_LOW   0x2C
#define OUT_Z_HIGH  0x2D



#endif