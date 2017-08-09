
#include <xc.h>
#include "I2C.h"
#include "configBits.h"
#include "constants.h"
void I2C_Master_Init(const unsigned long c)
{
 // See Datasheet pg171, I2C mode configuration
 SSPSTAT = 0b00000000;
 SSPCON1 = 0b00101000;
 SSPCON2 = 0b00000000;
 SSPADD = (_XTAL_FREQ/(4*c))-1;
 TRISC3 = 1; //Setting as input as given in datasheet
 TRISC4 = 1; //Setting as input as given in datasheet
}
void I2C_Master_Wait()
{
 while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
148
void I2C_Master_Start()
{
 I2C_Master_Wait();
 SEN = 1;
}
void I2C_Master_RepeatedStart()
{
 I2C_Master_Wait();
 RSEN = 1;
}
void I2C_Master_Stop()
{
 I2C_Master_Wait();
 PEN = 1;
}
void I2C_Master_Write(unsigned d)
{
 I2C_Master_Wait();
 SSPBUF = d;
}
void I2C_ColorSens_Init(void){
 I2C_Master_Start(); //Write Start condition
 I2C_Master_Write(0b01010010); //7bit address for TCS (0x29) + Write
 I2C_Master_Write(0b10000000); //Write to cmdreg + access enable reg
 I2C_Master_Write(0b00000001); //Start POWER
149
 I2C_Master_Stop();

 __delay_ms(3); //TCS requires 2.4ms delay before other actions

 I2C_Master_Start(); //Write Start condition
 I2C_Master_Write(0b01010010); //7bit address for TCS (0x29) + Write
 I2C_Master_Write(0b10000000); //Write to cmdreg + access enable reg
 I2C_Master_Write(0b00000011); //Start RGBC
 I2C_Master_Stop();

 I2C_Master_Start(); //Write Start condition
 I2C_Master_Write(0b01010010); //7bit address for TCS (0x29) + Write
 I2C_Master_Write(0b10001111); //Write to cmdreg + access control reg
 I2C_Master_Write(0b00000010); //Set analog gain to 16
 I2C_Master_Stop();

 I2C_Master_Start(); //Write Start condition
 I2C_Master_Write(0b01010010); //7bit address for TCS (0x29) + Write
 I2C_Master_Write(0b10000001); //Write to cmdreg + access RGBC timing register
 I2C_Master_Write(0b11111111); //Set RGBC timing register
 I2C_Master_Stop();

 I2C_Master_Start(); //Initializing for reading
 I2C_Master_Write(0b01010010); //7bit address 0x29 + Write
 I2C_Master_Write(0b10110100); //Write to cmdreg + access&increment clear low reg
 I2C_Master_Stop();
}
void I2C_ColorSens_ClearInt(void){
 I2C_Master_Start(); //Write Start condition
150
 I2C_Master_Write(0b01010010); //7bit address for TCS (0x29) + Write
 I2C_Master_Write(0b11100110); //Write to cmdreg + special func clear int
 I2C_Master_Write(0b11100110); //TESTING -- works but not sure if needed
 I2C_Master_Stop();
}
unsigned char I2C_Master_Read(unsigned char a)
{
 unsigned char temp;
 I2C_Master_Wait();
 RCEN = 1;
 I2C_Master_Wait();
 temp = SSPBUF;
 I2C_Master_Wait();
 ACKDT = (a)?0:1;
 ACKEN = 1;
 return temp;
}
void delay_10ms(unsigned char n) {
 while (n-- != 0) {
 __delay_ms(5);
 }
}
151
I2c.h
void I2C_Master_Init(con