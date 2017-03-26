#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ctl.h>
#include <terminal.h>
#include <commandLib.h>
#include <ARCbus.h>
#include <stdlib.h>
#include <i2c.h>
#include "pins.h"
#include "temp.h"
#include "L3G4200_GYRO.h"


int example_command(char **argv,unsigned short argc){
  int i,j;
  printf("This is an example command that shows how arguments are passed to commands.\r\n""The values in the argv array are as follows : \r\n");
  for(i=0;i<=argc;i++){
    printf("argv[%i] = 0x%p\r\n\t""string = \"%s\"\r\n",i,argv[i],argv[i]);
    //print out the string as an array of hex values
    j=0;
    printf("\t""hex = {");
    do{
      //check if this is the first element
      if(j!='\0'){
        //print a space and a comma
        printf(", ");
      }
      //print out value
      printf("0x%02hhX",argv[i][j]);
    }while(argv[i][j++]!='\0');
    //print a closing bracket and couple of newlines
    printf("}\r\n\r\n");
  }
  return 0;
}

int getRotation(char **argv, unsigned short argc){
  unsigned int port =4;
  unsigned int sda  =1;
  unsigned int scl  =0;
  unsigned short addr[1]={CTRL_REG3};
  unsigned char DRDY[1]={0x08};
  int ret;
  initI2C( port,sda,scl); 
//initalize I2C
  ret = i2c_tx(Write_SAD,addr,1);
 printf("i2ctx return %i \r\n\t",ret);
 ret = i2c_tx(CTRL_REG3,DRDY,1);
 printf("i2ctx return %i \r\n\t",ret);

} 







//this function works
/*
int getRotation(char **argv, unsigned short argc){
 unsigned int port =4;
  unsigned int sda  =1;
  unsigned int scl  =0;
   short ret;
   unsigned short busSize=1;
  unsigned char *dat;
  
  unsigned short addr[1]= {WHO_AM_I};
  initI2C( port,sda,scl); 
  ret= i2c_tx(0x69,addr,busSize);
    printf("tx return %i \r\n\t",ret);
    printf("dat stored %s \r\n\t",*dat);
  ret=i2c_rx(0x69,dat,1);
       printf("rx return %i \r\n\t",ret);
    printf("dat stored %x \r\n\t",*dat);

  //ret = i2c_txrx(0x69,addr,busSize,dat,busSize);
 // ret = i2c_rx(addr, dat , busSize);
 

  
} */

/*
int getRotation(char **argv, unsigned short argc){
   short ret;
   unsigned short busSize=2;
  unsigned char *dat;
  unsigned short addr[1]= {WHO_AM_I};
  ret = i2c_rx(0x69,addr,busSize);
 // ret = i2c_rx(addr, dat , busSize);
 
  printf("rx return %i \r\n\t",ret);
  printf("addr holds %i \r\n\t",addr[1]);
} 
*/
int temp(char **argv,unsigned short argc)
{
  unsigned char reg[1] = {TEMP_VAL};
  unsigned char addr = 0x48; // all low (0x48); (0x4A A2 low, A1 High, A0 low); (0x49 A2 low, A1 low, A0 high); (0x4C A2 High, A1 low, A0 low); (0x4E A2 High, A1 High, A0 low); (0x4D A2 High, A1 Low, A0 High); (0x4F A2 High, A1 High, A0 High);
  unsigned char aptr, *temp;
  int ret;
  ret = i2c_tx(addr, reg ,1);
  printf("I2C TX return %i \r\n\t", ret);
  if(ret==1){
  ret = i2c_rx(addr,temp, 2); 
  printf("I2C RX return %i \r\n\t", ret);
  printf("%i.%02u \r\n\t",(short)((char)temp[0]),25*(temp[1]>>6));
  }
}

//table of commands with help
const CMD_SPEC cmd_tbl[]={{"help"," [command]",helpCmd},
                   {"ex","[arg1] [arg2] ...\r\n\t""Example command to show how arguments are passed",example_command},
                   {"temp", "Takes Temperature",temp},
                   {"gyro", "experimental",getRotation},
                   ARC_COMMANDS,CTL_COMMANDS,ERROR_COMMANDS,
                   //end of list
                   {NULL,NULL,NULL}};

