
#ifndef MAIN_H
#define MAIN_H
//FUNCTIONS
void set_time(void);
int dec_to_hex(int num);
void date_time(void);
void read_time(void);
void bottle_count(void);
void bottle_count1(void);
void bottle_count2(void);
void bottle_count3(void);
void bottle_count4(void);
void bottle_time(void);
void standby(void);
void operation(void);
void operationend(void);
void emergencystop(void);
void servo_rotate0(int degree);
void servo_rotate1(int degree);
void read_colorsensor(void);
uint8_t eeprom_readbyte(uint16_t);
void eeprom_writebyte(uint16_t, uint8_t);
void savedata(void);
//VARIABLES
int i;
int j;
const char keys[] = "123A456B789C*0#D";
const char timeset[7] = { 0x30, //Seconds 
144
 0x19, //Minutes
 0x13, //Hour, 24 hour mode
 0x02, //Day of the week, Monday = 1
 0x11, //Day/Date
 0x04, //Month
 0x17};//Year, last two digits
enum state {
 STANDBY,
 EMERGENCYSTOP,
 OPERATION,
 OPERATIONEND,
 DATETIME,
 BOTTLECOUNT,
 BOTTLECOUNT1,
 BOTTLECOUNT2,
 BOTTLECOUNT3,
 BOTTLECOUNT4,
 BOTTLETIME
 };
enum state curr_state;
unsigned char time[7];
unsigned char start_time[2];
unsigned char end_time[2];
int stime;
int etime;
int operation_time;
int temp;
145
//For bottle count
//0 = Total
//1 = YOP + CAP
//2 = YOP - CAP
//3 = ESKA + CAP
//4 = ESKA - CAP
int bottle_count_disp[5] = -1; //Data for bottle display screen
int bottle_count_array[5];
int operation_disp = 0; //Data for operation running animation
int operation_timeout = 0;
unsigned int color[4]; //Stores TCS data in form clear, red, green, blue
unsigned int colorprev[4];
unsigned char color_low[4]; //For reading colors
unsigned char color_high[4];
int servo0_timer; //1250 = 1ms
int servo1_timer;
char servo0_flag;
char servo1_flag;
//Bottle Detection Logic
int flag_bottle;
int flag_bottle_high;
int flag_top_read;
int flag_yopNC;
int flag_picbug;
int flag_eskaC;
146
int bottle_read_top;
int bottle_read_bot;
float r, b, r_p, b_p;
//CONSTANTS
#define MAINPOLLINGDELAYMS 10
#define AMBIENTTCSCLEAR 18
#define TCSBOTTLEHIGH 30
#define NOCAPDISTINGUISH 130
#endif /* MAIN_H */