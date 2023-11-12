#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int adc_key_in  = 0;
int lcd_key = 5;
int hour = 0;
int minute = 0;
int second = 0;
int s = 0;
int mm = 1;
int dd = 1;
int secondSinceStart = 0;
int m = 1;
int temperature = 0;
float sensorTemp = 0;

//bool set_date_y = false;
bool set_time= false;
bool set_date_m = false;
bool set_date_d = false;
bool set_date = false;
bool set_time_h = false;
bool set_time_m = false;
bool time = true;
bool date = false;
bool temp = false;
bool minus = false;
bool dots = false;
bool slash = false;
bool dg = false;
bool refreshMinute = true;
bool refreshHour = true;
bool refreshDay = true;
bool refreshMonth = true;
bool refreshTemp = true;
bool firstDate = true;
bool firstTime = true;
bool firstTemp = true;

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 /*
 if (adc_key_in > 1500) return btnNONE; 
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 500)  return btnLEFT; 
 if (adc_key_in < 700)  return btnSELECT;  
*/
 if (adc_key_in < 60) return btnRIGHT;
  else if (adc_key_in < 200) return btnUP;
  else if (adc_key_in < 400) return btnDOWN;
  else if (adc_key_in < 600) return btnLEFT;
   if (adc_key_in < 800) return btnSELECT;
 return btnNONE;
}

byte left[8] = { B01111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B01111, };

byte left_up[8] = { B11111,
B01111,
B00000,
B00000,
B00000,
B00000,
B00111,
B01111, };

byte middle[8] = { B11111,
B11111,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000, };

byte middle_1[8] = { B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111, };

byte middle_2[8] = { B11111,
B11111,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111, };

byte right[8] = { B11110,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11110, };

byte right_up[8] = { B11111,
B11110,
B00000,
B00000,
B00000,
B00000,
B11100,
B11110, };

byte dot[8] = { B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B11000,
B11000, };




void setup()
{
lcd.begin(16, 2);
lcd.createChar(0, right);
lcd.createChar(1, right_up);
lcd.createChar(2, left);
lcd.createChar(3, left_up);
lcd.createChar(4, middle);
lcd.createChar(5, middle_1);
lcd.createChar(6, middle_2);
lcd.createChar(7, dot);
Serial.begin(9600);
sensors.begin();
}

void zero(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos, 1);
  lcd.write((byte)2);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)4);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void one(int pos) {
  lcd.setCursor(pos, 0);
  lcd.print(" ");
  lcd.setCursor(pos, 1);
  lcd.print(" ");
  lcd.setCursor(pos + 1, 0);
  lcd.print(" ");
  lcd.setCursor(pos + 1, 1);
  lcd.print(" ");
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)2);
  lcd.rightToLeft();
}

void two(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)3);
  lcd.setCursor(pos, 1);
  lcd.write((byte)2);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)6);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)5);
}

void three(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)3);
  lcd.setCursor(pos, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)6);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void four(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos, 1);
  lcd.print(" ");
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)5);
  lcd.setCursor(pos + 1, 1);
  lcd.print(" ");
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void five(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)6);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)1);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void six(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos, 1);
  lcd.write((byte)2);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)6);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)1);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void seven(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)4);
  lcd.setCursor(pos, 1);
  lcd.print(" ");
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)4);
  lcd.setCursor(pos + 1, 1);
  lcd.print(" ");
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void eight(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos, 1);
  lcd.write((byte)2);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)6);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void nine(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write((byte)2);
  lcd.setCursor(pos, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 1, 0);
  lcd.write((byte)6);
  lcd.setCursor(pos + 1, 1);
  lcd.write((byte)5);
  lcd.setCursor(pos + 2, 0);
  lcd.write((byte)0x00);
  lcd.setCursor(pos + 2, 1);
  lcd.write((byte)0x00);
}

void dotsCr() {
  lcd.setCursor(6, 0);
  lcd.write((byte)7);
  lcd.setCursor(6, 1);
  lcd.write((byte)7);
}

void slashCr() {
  lcd.setCursor(7, 1);
  lcd.write((byte)2);
  lcd.setCursor(8, 0);
  lcd.write((byte)2);
  lcd.setCursor(8, 1);
  lcd.write((byte)4);
}


void displayDigits(int digit, int pos) {
  switch(digit) {
    case 0:
    {
      zero(pos);
       break;
    }
    case 1:
    {
      one(pos);
       break;
    }
    case 2:
    {
      two(pos);
       break;
    }
    case 3:
    {
      three(pos);
       break;
    }
    case 4:
    {
      four(pos);
       break;
    }
    case 5:
    {
      five(pos);
       break;
    }
    case 6:
    {
      six(pos);
       break;
    }
    case 7:
    {
      seven(pos);
       break;
    }
    case 8:
    {
      eight(pos);
       break;
    }
    case 9:
    {
      nine(pos);
       break;
    }
  }
}

void clearDigit(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write(" ");
  lcd.setCursor(pos, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 1, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 1, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 2, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 2, 1);
  lcd.write(" ");
}

void clearSlash() {
  lcd.setCursor(7, 1);
  lcd.write(" ");
  lcd.setCursor(8, 0);
  lcd.write(" ");
  lcd.setCursor(8, 1);
  lcd.write(" ");
}


void clearDots() {
  lcd.setCursor(6, 0);
  lcd.write(" ");
  lcd.setCursor(6, 1);
  lcd.write(" ");
}

void clearSecDg() {
  lcd.setCursor(14, 1);
  lcd.write(" ");
  lcd.setCursor(15, 1);
  lcd.write(" ");
}

void clear(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write(" ");
  lcd.setCursor(pos, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 1, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 1, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 2, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 2, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 3, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 3, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 4, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 4, 1);
  lcd.write(" ");
  lcd.setCursor(pos + 5, 0);
  lcd.write(" ");
  lcd.setCursor(pos + 5, 1);
  lcd.write(" ");
}

void blink(int pos) {
  delay(200);
  clear(pos);
  delay(80);
  if (pos == 0) refreshHour = true;
  if (pos == 7) refreshMinute = true;
  
  
}

void blinkDate(int pos) {
  delay(200);
  clear(pos);
  delay(70);
  if (pos == 10) refreshDay = true;
  if (pos == 0) refreshMonth = true;
}


void checkTime() {
  if (time) {
    if (slash) {
      slash = false;
      clear(0);
      clear(10);
      clearSlash();
  }
  if (dg) {

      clear(0);
      clear(7);
      clearSecDg();
      dg = false;

      lcd.setCursor(13, 0);
      lcd.print(" ");
      lcd.setCursor(13, 1);
      lcd.print(" ");
    }
  if (!dots) {
      dotsCr();
      dots = true;
    }
  

  if(hour < 10 && refreshHour) {
    clearDigit(3);
    displayDigits(0, 0);
    displayDigits(hour, 3);
    refreshHour = false;
  } else if (refreshHour){
    clearDigit(0);
    clearDigit(3);
    displayDigits(hour/10, 0);
    displayDigits(hour%10, 3);
    refreshHour = false;
  }

  
  if(minute < 10 && refreshMinute) {
    clearDigit(10);
    displayDigits(0, 7);
    displayDigits(minute, 10);
    refreshMinute = false;
  } else if (refreshMinute) {
      clearDigit(7);
      clearDigit(10);
      displayDigits(minute/10, 7);
      displayDigits(minute%10, 10);
      refreshMinute = false;
    }
    
      lcd.setCursor(14, 1);
      lcd.print(second/10);
      lcd.setCursor(15, 1);
      lcd.print(second%10);
  }
  if (hour >= 60) {
    hour = 0;
    dd++;
    refreshHour = true;
    refreshDay = true;
  }

  if (minute >= 60) {
    minute = 0;
    hour++;
    refreshMinute = true;
    refreshHour = true;
  }
  delay(200);
}


void checkDate() {
  if(date) {
    if (dots) {
      clearDots();
      clear(0);
      clear(7);
      clearSecDg();
      dots = false;
    }
    if (dg) {
      clear(0);
      clear(7);
      clearSecDg();
      dg = false;

      lcd.setCursor(6, 0);
      lcd.print(" ");
      lcd.setCursor(6, 1);
      lcd.print(" ");
    }
    if (!slash) {
      slashCr();
      slash = true;
    }
    
  

  if(mm < 10 && refreshMonth) {
    clearDigit(3);
    displayDigits(0, 0);
    displayDigits(mm, 3);
    refreshMonth = false;
  } else if (refreshMonth){
    clearDigit(0);
    clearDigit(3);
    displayDigits(mm/10, 0);
    displayDigits(mm%10, 3);
    refreshMonth = false;
  }

  if(dd < 10 && refreshDay) {
    clearDigit(10);
    displayDigits(0, 10);
    displayDigits(dd, 13);
    refreshDay = false;
  } else if(refreshDay) {
    clearDigit(10);
    clearDigit(13);
    displayDigits(dd/10, 10);
    displayDigits(dd%10, 13);
    refreshDay = false;
  }
  }

   if (mm >= 13) {
    mm = 1;
    dd = 1;
    refreshMonth = true;
    refreshDay = true;
  }

  if (dd >= 32) {
    dd = 1;
    mm++;
    refreshMonth = true;
    refreshDay = true;
  } 

  delay(200);
}

void checkTemp(float t) {
  temperature = t * 100;
  if (temp) {
     if (dots) {
      clearDots();
      clear(0);
      clear(7);
      clearSecDg();
      dots = false;
    }
    if (slash) {
      slash = false;
      clear(0);
      clear(10);
      clearSlash();
    }
    if (!dg) {
      lcd.setCursor(14, 1);
      lcd.print((char)223);
      lcd.setCursor(15, 1);
      lcd.print("C");
      dg = true;
    }
    if (refreshTemp) {
      if (temperature < 10 && temperature > -10) {
        displayDigits(0, 1);
        displayDigits(temperature/100, 4);
        displayDigits(temperature%100/10, 8);
        displayDigits(temperature%10, 11);
        lcd.setCursor(6, 1);
        lcd.write((byte)7);
      } else {
        displayDigits(temperature/1000, 1);
        displayDigits(temperature/100%10, 4);
        displayDigits(temperature%100/10, 8);
        displayDigits(temperature%10, 11);
        lcd.setCursor(7, 1);
        lcd.write((byte)7);
      }
      if (temperature < 0) {
        lcd.setCursor(0, 1);
        lcd.write((byte)4);
        minus = true;
      }
      else {
        lcd.setCursor(0, 1);
        lcd.print(" ");
        minus = false;
      }
    }
  }
  
}


void loop() {
  sensors.requestTemperatures(); 
  lcd_key = read_LCD_buttons();
  sensorTemp = sensors.getTempCByIndex(0);
  Serial.println(sensorTemp);
  Serial.print("C");
  Serial.println();
  if (!set_time) {
    checkTime();
    if (!set_time_h) {
      blink(0);
    } else if (!set_time_m) {
      blink(7);
    }
    switch (lcd_key)
    {
    case btnRIGHT:
     {
        if (!set_time_h) {
          set_time_h = true;
        } else if (!set_time_m) {
          set_time_m = true;
          set_time = true;
          time = false;
          date = true;
        }
     break;
     }
   case btnLEFT:
     {
     if (!set_time_m) {
          set_time_h = false;
        }
     break;
     }
   case btnUP:
     {
        if (!set_time_h) {
          hour++;
        } else if (!set_time_m) {
          minute++;
        }
        
     break;
     }
   case btnDOWN:
     {
        if (!set_time_h) {
          hour--;
        } else if (!set_time_m) {
          minute--;
        }
     break;
     
    }
    }
  } else if (!set_date) {
    checkDate();
    if (!set_date_m) {
      blinkDate(0);
    } else if (!set_date_d) {
      blinkDate(10);
    }

      switch (lcd_key) 
    {
    case btnRIGHT:
     {
      if (!set_date_m) {
          set_date_m = true;
        } else if (!set_date_d) {
          set_date_d = true;
          set_date = true;
          time = true;
          refreshHour = true;
          refreshMinute = true;
          secondSinceStart = millis() % 60;
        }
     break;
     }
   case btnLEFT:
     {
     if (!set_date_d) {
          set_date_m = false;
      }
     break;
     }
   case btnUP:
     {
     if (!set_date_m) {
          mm++;
        } else if (!set_date_d) {
          dd++;
        }
     break;
     }
   case btnDOWN:
     {
      if (!set_date_m) {
          mm--;
        } else if (!set_date_d) {
          dd--;
        }
     break;
     }
  }
 } else {
  second  = ((millis() - secondSinceStart) / 1000) % 60;

  if (firstTime) {
    refreshHour = true;
    refreshMinute = true;
    firstTime = false;
    
  }
  if (firstDate) {
    refreshDay = true;
    refreshMonth = true;
    firstDate = false;
  }
  if (firstTemp) {
    refreshTemp = true;
  }
  if (time) {
    checkTime();
  } else if(date) {
    checkDate();
  } else if(temp) {
    checkTemp(sensorTemp);
  }

  if (second == 59) {
    minute++;
    delay(800);
    refreshMinute = true;
  }
  switch (lcd_key)
    {
    case btnRIGHT:
     {
     if (time) {
        time = false;
        date = true;
        refreshDay = true;
        refreshMonth = true;
      } else if (date) {
        date = false;
        temp = true;
        refreshTemp = true;
      } else if (temp){
        temp = false;
        time = true;
        refreshMinute = true;
        refreshHour = true;
        
      }
     break;
     }
   case btnLEFT:
     {
      if (time) {
        time = false;
        temp = true;
        refreshTemp = true;
      } else if (temp) {
        temp = false;
        date = true;
        refreshDay = true;
        refreshMonth = true;
      } else if (date) {
        date = false;
        time = true;
        refreshMinute = true;
        refreshHour = true;
      }

     break;
     }
  }
  
  /*Serial.print("Hour: "); Serial.println(hour);
  Serial.print("Minutes: "); Serial.println(minute);
  Serial.print("Seconds: "); Serial.println(second);*/
  delay(100);

 }
}