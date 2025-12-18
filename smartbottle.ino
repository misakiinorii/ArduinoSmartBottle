#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <millisDelay.h>

//diferent pins indicating different water levels
int a;
int b;
int c;
int d;
int z = 10;
int drank;
int level;
millisDelay drinkdelay;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  lcd.init();
  lcd.backlight();
  drinkdelay.start(60000);
  level = 4;
}

void loop()
{

  a = analogRead(A0);
  b = analogRead(A1);
  c = analogRead(A2);
  d = analogRead(A3);


  if (d > z && c > z && b > z && a > z )
  {
    lcd.setCursor(1, 1);
    lcd.print("600ml FULL");
    level = 4;

  }
  else
  {
    if (d > z && c > z && b > z && a < z )
    {
      lcd.setCursor(1, 1);
      lcd.print("480ml FULL");

      if (level != 3)
      {
        drank = drank + 120;
        level = 3;
      }

    }
    else
    {
      if (d > z && c > z && b < z && a < z )
      {
        lcd.setCursor(1, 1);
        lcd.print("360ml FULL");
        if (level != 2)
        {
        drank = drank + 120;
        level = 2;
        }

      }
      else
      {
        if (d > z && c < z && b < z && a < z )
        {

          lcd.setCursor(2, 1);
          lcd.print("240ml FULL");
          if (level != 1)
           {
          drank = drank + 120;
          level = 1;
           }


        }
        else if (d < z && c < z && b < z && a < z )
        {

          lcd.setCursor(1, 1);
          lcd.print("EMPTY");
          if (level != 0)
           {
          drank = drank + 240;
          level = 0;
           }

        }
      }
    }
  }
  {
    lcd.setCursor(1, 0);
    lcd.print(drank);
    delay(500);
    lcd.clear();
  }
  if (drinkdelay.justFinished())
  {
    if (drank <= 1000)
    {
      lcd.setCursor(0,0);
      lcd.print("Drink more water!");
      delay(5000);
      lcd.clear();
    }
    drank = 0;
    drinkdelay.start(60000);
  }
  else
  {
    if (drank >= 1000)
    {
      lcd.setCursor(0,0);
      lcd.print("Too much water!");
      lcd.setCursor(0,1);
      lcd.print("Stop drinking!");
      delay(5000);
      lcd.clear();
      drank = 0;
    }
  }
}
