#include "game.h"



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(button_fire, INPUT);
  mylcd.Init_LCD();

  uint8_t var = 1;
  mylcd.Set_Rotation(var);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  // text_test();

  if( let_the_games_begin == 0 )
  {
    intro();
    if(let_the_games_begin)
    {
      premiera();
      canta_ceva();
      mylcd.Fill_Screen(BLACK);
    }
  }
  else
  {
   
    deseneaza_stele();
    deseneaza_inamici();
    int val = analogRead(VRx);
    int old = deplasare;
    if( val >= 0 && val < 300)
      deplasare += 15;
    if( val > 724 && val <= 1024 )
      deplasare -= 15;
    delay(100);
    deseneaza_nava_last(old, 0);
    deseneaza_nava(deplasare, 0);
    delay(200);
  }

  // de aici in jos stanga, dreapta
  // dreapta =  0
  // stanga = 1024
  

   
}
