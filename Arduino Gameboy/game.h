#define VRx A0
#include "pitches.h"

unsigned int button_fire = 7;
int deplasare = 1;
int penultima_deplasare = deplasare;
int countA = 0;

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

// LCDWIKI_SPI mylcd(A5, A4, -1);
LCDWIKI_SPI mylcd(ST7735S,A5,A3,-1,A2,A4,A1,A3);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Size: 10W*8H px
const uint16_t red[] PROGMEM =
{
0x0000, 0x0000, 0x0000, 0xe800, 0x0000, 0x0000, 0xe800, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0xe800, 0xe800, 0xe800, 0xe800, 0x0000, 0x0000, 0x0000, 
0xe800, 0x0000, 0xe800, 0xe800, 0xe800, 0xe800, 0xe800, 0xe800, 0x0000, 0xe800, 
0xe800, 0xe800, 0xe800, 0xc764, 0xe800, 0xe800, 0xc764, 0xe800, 0xe800, 0xe800, 
0x0000, 0x0000, 0xe800, 0xe800, 0xe800, 0xe800, 0xe800, 0xe800, 0x0000, 0x0000, 
0x0000, 0x377d, 0xe800, 0xe800, 0xe800, 0xe800, 0xe800, 0xe800, 0x377d, 0x0000, 
0x377d, 0x377d, 0x377d, 0xe800, 0xe800, 0xe800, 0xe800, 0x377d, 0x377d, 0x377d, 
0x377d, 0x377d, 0x0000, 0x0000, 0xe800, 0xe800, 0x0000, 0x0000, 0x377d, 0x377d
};

const uint16_t green[] PROGMEM ={
0x0000, 0x0000, 0x0000, 0x1f60, 0x0000, 0x0000, 0x1f60, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x0000, 0x0000, 0x0000, 
0x1f60, 0x0000, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x0000, 0x1f60, 
0x1f60, 0x1f60, 0x1f60, 0xc764, 0x1f60, 0x1f60, 0xc764, 0x1f60, 0x1f60, 0x1f60, 
0x0000, 0x0000, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x0000, 0x0000, 
0x0000, 0x377d, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x377d, 0x0000, 
0x377d, 0x377d, 0x377d, 0x1f60, 0x1f60, 0x1f60, 0x1f60, 0x377d, 0x377d, 0x377d, 
0x377d, 0x377d, 0x0000, 0x0000, 0x1f60, 0x1f60, 0x0000, 0x0000, 0x377d, 0x377d
};

const uint16_t pink[] PROGMEM ={
0x0000, 0x0000, 0x0000, 0xe957, 0x0000, 0x0000, 0xe957, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0xe957, 0xe957, 0xe957, 0xe957, 0x0000, 0x0000, 0x0000, 
0xe957, 0x0000, 0xe957, 0xe957, 0xe957, 0xe957, 0xe957, 0xe957, 0x0000, 0xe957, 
0xe957, 0xe957, 0xe957, 0xc764, 0xe957, 0xe957, 0xc764, 0xe957, 0xe957, 0xe957, 
0x0000, 0x0000, 0xe957, 0xe957, 0xe957, 0xe957, 0xe957, 0xe957, 0x0000, 0x0000, 
0x0000, 0x377d, 0xe957, 0xe957, 0xe957, 0xe957, 0xe957, 0xe957, 0x377d, 0x0000, 
0x377d, 0x377d, 0x377d, 0xe957, 0xe957, 0xe957, 0xe957, 0x377d, 0x377d, 0x377d, 
0x377d, 0x377d, 0x0000, 0x0000, 0xe957, 0xe957, 0x0000, 0x0000, 0x377d, 0x377d
};

//proj Size: 1W*6H px
const unsigned char proj[] PROGMEM = 
{
0x00,
0xff,
0xff,
0xff,
0xff,
0x00
};

const uint16_t logo[] PROGMEM ={
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2000, 0x2000, 0x1000, 0x1800, 0x1800, 0x1800, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1800, 0x1800, 0x1000, 0x0800, 0x0800, 0x0800, 0x0000, 0x0000, 0x0800, 0x1000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1800, 0x0000, 0x0000, 0x8800, 0xb800, 0x4800, 0xf800, 0xe800, 0x0800, 0x0800, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0x0800, 0x1800, 0x0000, 0x0000, 0x8800, 0xe000, 0xe000, 0xc000, 0x4800, 0xf800, 0xd000, 0x0000, 0x0800, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x8800, 0xe000, 0xd000, 0xd000, 0xd800, 0xc000, 0x4000, 0xf800, 0xb800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0841, 0x0020, 0x0020, 0x1800, 0x0000, 0x0000, 0x8000, 0xe000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd800, 0xb800, 0x4000, 0xf800, 0xf800, 0x0020, 0x0020, 0x0020, 0x0020, 0x0000, 
0x10a2, 0x2104, 0x1082, 0x49a6, 0x0000, 0x0000, 0x8000, 0xe000, 0xd800, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xe800, 0xc000, 0x4000, 0xf800, 0xfaaa, 0x3186, 0x0000, 0x0000, 0x0020, 
0x2965, 0x1082, 0x0000, 0x0000, 0x5800, 0x1800, 0xb800, 0xc800, 0x9000, 0x3800, 0xc000, 0xe000, 0x7800, 0x5000, 0xb000, 0xe000, 0x7000, 0x0000, 0x1800, 0x0020, 0x0000, 0x0000, 0x0000, 
0x2124, 0x0000, 0x0000, 0x94b2, 0x6b4d, 0x0000, 0x3000, 0x3000, 0x0000, 0x1000, 0xb800, 0xe800, 0x7000, 0x0000, 0x2000, 0x3000, 0x2800, 0x0000, 0x9cd3, 0x6b6d, 0xffff, 0xffff, 0x0000, 
0x0000, 0x0000, 0x9cd3, 0xef5d, 0xce79, 0x4a69, 0x4a08, 0x0000, 0x034e, 0x0a8b, 0xc000, 0xe800, 0x6821, 0x0432, 0x0146, 0x07ff, 0x0000, 0x52aa, 0xe71c, 0xce59, 0x528a, 0xffff, 0xffff, 
0x39c7, 0x2124, 0xde9a, 0x126b, 0x9d96, 0x9492, 0xffff, 0x08c3, 0x05fa, 0x0b2e, 0xc000, 0xe800, 0x6820, 0x065c, 0x036f, 0xb7ff, 0x1104, 0xde79, 0x0209, 0x9d96, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd658, 0x028b, 0x8d35, 0x9c92, 0xffff, 0x08a3, 0x0598, 0x0b0d, 0xc000, 0xe800, 0x6820, 0x05fa, 0x032e, 0xafff, 0x2186, 0xd658, 0x02ac, 0x8d55, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0xffff, 0x08c3, 0x0599, 0x0b0d, 0xc000, 0xe800, 0x6820, 0x05fa, 0x032e, 0xffff, 0x2186, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0xffff, 0x08a3, 0x0599, 0x0b0d, 0xc000, 0xe800, 0x6820, 0x05fa, 0x032e, 0xcfff, 0x31e8, 0xcdf7, 0x0209, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d35, 0xa4d3, 0x0000, 0x034e, 0x065c, 0x0aed, 0xc000, 0xe800, 0x6841, 0x05d9, 0x04d5, 0x0125, 0x2124, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d55, 0x9c71, 0x0209, 0x067c, 0x067d, 0x0aed, 0xc000, 0xe800, 0x6841, 0x0578, 0x067d, 0x0517, 0x1145, 0xe6ba, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d35, 0x94d3, 0x0537, 0x0390, 0x05da, 0x0b0d, 0xc000, 0xe800, 0x6821, 0x05fa, 0x03d1, 0x0557, 0x13f1, 0xee58, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x9535, 0x94d3, 0x026b, 0x0861, 0x05d9, 0x0b0d, 0xc000, 0xe800, 0x6820, 0x05fa, 0x030d, 0x0145, 0x12ed, 0xee99, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d55, 0x9471, 0x0000, 0x08c3, 0x0578, 0x0b0d, 0xc800, 0xe000, 0x6820, 0x05da, 0x032e, 0x0000, 0x1924, 0xde79, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0xffff, 0x08a3, 0x05fb, 0x036f, 0xb800, 0xf000, 0x5021, 0x069d, 0x034e, 0xffff, 0x2186, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd659, 0x026b, 0x8d35, 0x9c92, 0xffff, 0x0882, 0x0229, 0x0125, 0x4000, 0x6000, 0x0000, 0x0209, 0x0166, 0x8fff, 0x2145, 0xd659, 0x026b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x39c7, 0x2145, 0xd658, 0x028b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x31a6, 0x2145, 0xd658, 0x028b, 0x8d35, 0x9cb2, 0x0000, 0x0000, 
0x2124, 0x1082, 0xd699, 0x5c31, 0xc679, 0x8430, 0x0000, 0x0000, 0x0000, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x2965, 0x2124, 0x1082, 0xd699, 0x5c31, 0xc679, 0x8430, 0x0000, 0x0000, 
0xffff, 0xffff, 0x5aeb, 0xf7be, 0xb596, 0x0000, 0x0000, 0x39c7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0xffff, 0xffff, 0x5aeb, 0xf7be, 0xb596, 0x0000, 0x0000, 0x3186, 
0x0020, 0x0000, 0xffff, 0x528a, 0x31c7, 0x52aa, 0x31a6, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0xffff, 0x528a, 0x31c7, 0x52aa, 0x31a6, 0x0000, 
0x18c3, 0x1082, 0x2945, 0x0000, 0x0841, 0x18e3, 0x2965, 0x2945, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10a2, 0x18c3, 0x1082, 0x2945, 0x0000, 0x0841, 0x18e3, 0x2965, 0x2945
};

const uint16_t ship[] PROGMEM ={
0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd800, 0xd800, 0xd800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0xd800, 0xd800, 0xd800, 0xd800, 0xd800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0xd800, 0xd800, 0xd800, 0xd800, 0xd800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0xd800, 0x0000, 0xe800, 0x0000, 0xd800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
0x0001, 0x0000, 0xef7d, 0x0000, 0x0000, 0x0000, 0x06bd, 0xe800, 0x06bd, 0x0000, 0x0000, 0x0000, 0xef7d, 0x0000, 0x0001,
0x0001, 0xef7d, 0xef7d, 0xef7d, 0x0000, 0x0000, 0x06bd, 0xe800, 0x06bd, 0x0000, 0x0000, 0xef7d, 0xef7d, 0xef7d, 0x0001,
0x0001, 0xef7d, 0x06fd, 0xef7d, 0x0000, 0x0000, 0x06bd, 0xe800, 0x06bd, 0x0000, 0x0000, 0xef7d, 0x06fd, 0xef7d, 0x0001,
0x0001, 0xef7d, 0x06fd, 0xef7d, 0x0000, 0x06bd, 0x06bd, 0xe800, 0x06bd, 0x06bd, 0x0000, 0xef7d, 0x06fd, 0xef7d, 0x0001,
0x0001, 0xef7d, 0x06fd, 0xef7d, 0x06bd, 0x06bd, 0x06bd, 0xe800, 0x06bd, 0x06bd, 0x06bd, 0xef7d, 0x06fd, 0xef7d, 0x0001,
0x0001, 0xef7d, 0x06fd, 0xef7d, 0x06bd, 0x0000, 0x06bd, 0xe800, 0x06bd, 0x0000, 0x06bd, 0xef7d, 0x06fd, 0xef7d, 0x0001,
0x0001, 0xef7d, 0x06fd, 0xef7d, 0x0000, 0x0000, 0x06bd, 0x0000, 0x06bd, 0x0000, 0x0000, 0xef7d, 0x06fd, 0xef7d, 0x0001,
0x0001, 0xef7d, 0xef7d, 0xef7d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xef7d, 0xef7d, 0xef7d, 0x0001,
0x0001, 0x0000, 0xef7d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xef7d, 0x0000, 0x0001
};

int let_the_games_begin = 0;
#define BUTTON_PIN 4

void deseneaza_logo(int posx, int posy);
void intro()
{
  mylcd.Set_Text_Mode(0);
  
  mylcd.Fill_Screen(BLACK);  
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Galactic Armageddon", 25, 5);
  
  deseneaza_logo(70, 50);

  mylcd.Print_String("Press Fire", 50, 100);
  mylcd.Print_String("to play", 57, 115);
  
  delay(2000);
  // let_the_games_begin = digitalRead(button_fire);
  byte buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == LOW)
  { 
    let_the_games_begin = 1;
  }
  if(let_the_games_begin == 0)
    delay(3000);
}

void premiera()
{
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Text_Size(3);
  mylcd.Print_Number_Int(3, 80, 50, 0, ' ', 10);
  delay(1000);
  mylcd.Print_Number_Int(2, 80, 50, 0, ' ', 10);
  delay(1000);
  mylcd.Print_Number_Int(1, 80, 50, 0, ' ', 10);
  delay(1000);
  mylcd.Set_Text_Size(1);
  mylcd.Fill_Screen(BLACK);
  mylcd.Print_String("Let God sort them out", 18, 62);
  delay(1000);
  mylcd.Fill_Screen(BLACK);
}

void deseneaza_inamic_verde(int xpos, int ypos)
{
  int height = 8 , width = 10, index = 0;
  int i, j;

  for( i = 0; i < height; i++)
  {
    for( j = 0; j < width; j++)
    {
      mylcd.Draw_Pixe(j + xpos, i + ypos, pgm_read_word(green + index));
      index++;
    }
  }
}

void deseneaza_inamic_rosu(int xpos, int ypos)
{
  int height = 8 , width = 10, index = 0;
  int i, j;

  for( i = 0; i < height; i++)
  {
    for( j = 0; j < width; j++)
    {
      mylcd.Draw_Pixe(j + xpos, i + ypos, pgm_read_word(red + index));
      index++;
    }
  }
}

void deseneaza_inamic_roz(int xpos, int ypos)
{
  int height = 8 , width = 10, index = 0;
  int i, j;

  for( i = 0; i < height; i++)
  {
    for( j = 0; j < width; j++)
    {
      mylcd.Draw_Pixe(j + xpos, i + ypos, pgm_read_word(pink + index));
      index++;
    }
  }
}

void deseneaza_inamici()
{
    int n = 8;
    int vx[] = { 10, 28, 46, 64, 82, 100, 118, 136, 154};

    for(int i = 0 ; i < n; i++)
    {
      deseneaza_inamic_rosu(vx[i]+3, 10);
      deseneaza_inamic_verde(vx[i]+3, 25);
      deseneaza_inamic_roz(vx[i]+3, 40);
    }
}

void deseneaza_nava(int cola, int rowa)
{
  int buffidx = 0;
  int w = 15, h = 14;
  for (int row=0; row<h; row++) 
  {
    for (int col=0; col<w; col++) 
    {
      mylcd.Draw_Pixe(col + 70 + cola, row + 110 + rowa, pgm_read_word(ship + buffidx));
      buffidx++;
    }
  }
}


void deseneaza_nava_last(int cola, int rowa)
{
  int buffidx = 0;
  int w = 15, h = 14;
  for (int row=0; row<h; row++) 
  {
    for (int col=0; col<w; col++) 
    {
      mylcd.Draw_Pixe(col + 70 + cola, row + 110 + rowa, BLACK);
      buffidx++;
    }
  }
}
void fill_screen_test()
{
  mylcd.Fill_Screen(BLACK);  
  mylcd.Fill_Screen(RED);
  mylcd.Fill_Screen(GREEN);
  mylcd.Fill_Screen(BLUE);
  mylcd.Fill_Screen(BLACK);
}


void text_test()
{
  mylcd.Set_Text_Mode(0);
  
  mylcd.Fill_Screen(BLACK);  
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Size(1);
  

  
  mylcd.Print_String("Galactic Armageddon", 25, 62);

}

void deseneaza_logo(int posx, int posy)
{
  int h = 26, w = 23, i, j, index = 0;
  for( i = 0; i < h; i++)
  {
    for( j = 0; j < w; j++)
    {
      mylcd.Draw_Pixe( j + posx, i + posy, pgm_read_word(logo + index));
      index++;
    }
  }
}

void deseneaza_stea(int x, int y)
{
  mylcd.Draw_Pixe(x , y, WHITE);
}

void deseneaza_stele()
{
  deseneaza_stea(10, 10);
  deseneaza_stea(30, 10);
  deseneaza_stea(40, 40);
  deseneaza_stea(100, 100);
  deseneaza_stea(50, 50);
  deseneaza_stea(70, 50);
  deseneaza_stea(70, 60);
  deseneaza_stea(65, 85);
  deseneaza_stea(90, 65);
  deseneaza_stea(50, 75);
  deseneaza_stea(40, 60);
  deseneaza_stea(35, 85);
  deseneaza_stea(60, 65);
  deseneaza_stea(30, 75);
  deseneaza_stea(50, 75);
  deseneaza_stea(80, 70);
  deseneaza_stea(100, 85);
  deseneaza_stea(110, 65);
  deseneaza_stea(120, 75);
  deseneaza_stea(15, 70);
  deseneaza_stea(20, 85);
  deseneaza_stea(10, 65);
  deseneaza_stea(12, 75);
  deseneaza_stea(35, 5);
  deseneaza_stea(60, 20);
  deseneaza_stea(30, 25);
  deseneaza_stea(50, 17);
  deseneaza_stea(80, 5);
  deseneaza_stea(100, 20);
  deseneaza_stea(110, 25);
  deseneaza_stea(120, 11);
  deseneaza_stea(15, 17);
  deseneaza_stea(20, 8);
  deseneaza_stea(10, 19);
  deseneaza_stea(12, 30);
  deseneaza_stea(100, 47);
  deseneaza_stea(90, 38);
  deseneaza_stea(104, 29);
  deseneaza_stea(120, 55);
  deseneaza_stea(120, 3);
  deseneaza_stea(70, 3);
  deseneaza_stea(110, 120);
  deseneaza_stea(130, 110);
  deseneaza_stea(140, 90);
  deseneaza_stea(140, 45);
  deseneaza_stea(135, 22);
  deseneaza_stea(150, 10);
  deseneaza_stea(10, 110);
  deseneaza_stea(23, 113);
  deseneaza_stea(29, 95);
  deseneaza_stea(50, 80);
  deseneaza_stea(30, 92);
  deseneaza_stea(47, 101);
  deseneaza_stea(25, 98);

}

int melody[] = {


  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4

};


// note durations: 4 = quarter note, 8 = eighth note, etc.:

int noteDurations[] = {


  4, 8, 8, 4, 4, 4, 4, 4

};

// w = 15, h = 14; coord { column = 70, row = 110 }
void coloreaza_pixeli_jos(int cola, int rowa)
{
  int buffidx = 0;
  int w = 15, h = 14;
  for (int row=0; row<h; row++) 
  {
    for (int col=0; col<w; col++) 
    {
      mylcd.Draw_Pixe(col + 70 + cola, row + 110 + rowa, BLACK);
      buffidx++;
    }
  }
}

void canta_ceva()
{
  for (int thisNote = 0; thisNote < 8; thisNote++) {


    // to calculate the note duration, take one second divided by the note type.


    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.


    int noteDuration = 1000 / noteDurations[thisNote];


    tone(8, melody[thisNote], noteDuration);


    // to distinguish the notes, set a minimum time between them.


    // the note's duration + 30% seems to work well:


    int pauseBetweenNotes = noteDuration * 1.30;


    delay(pauseBetweenNotes);


    // stop the tone playing:


    noTone(8);


  }
}