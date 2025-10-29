#include <LiquidCrystal.h>
#include <SPI.h>

const int rs = 3, en = 2, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char buff [100];
volatile byte indx;
volatile boolean process;
char ambient_temp [100];
char light_state [100];
char fan_state [100];
int cnt = 0;
String light;
String fan;
 
void setup (void) {
   Serial.begin (115200);
   // LCD setup
   lcd.begin(16,2);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}
 
ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   byte c = SPDR; // read byte from SPI Data Register
   
   if (indx < sizeof(buff)) {
      buff[indx++] = c; // save data in the next index in the array buff
      if (c == '\n') { 
        buff[indx - 1] = 0; // replace newline ('\n') with end of string (0)
        process = true;
      }
  }
} 



void loop (void) {
  if (process) {
    process = false; //reset the process
        
    Serial.println (buff); //print the array on serial monitor    
  //transmitted_values[i] = buff;    
    if(cnt == 0){
      for(int i = 0; i < sizeof(buff); ++i){
        ambient_temp[i] = buff[i];
      }
    Serial.println(atoi(ambient_temp));     
    }
    else if(cnt == 1){
      for(int i = 0; i < sizeof(buff); ++i){
        light_state[i] = buff[i];        
      }
      Serial.println(atoi(light_state)); 
    }


    else if(cnt == 2){
      for(int i = 0; i < sizeof(buff); ++i){
        fan_state[i] = buff[i];        
      }
      Serial.println(atoi(fan_state)); 
    }
    if (cnt < 2){
      ++cnt;
    }
    else{
      cnt = 0;
    }
      
    if(atoi(light_state) == 0){
      light = "Off";
    }
    if(atoi(light_state) != 0){
      light = "On";
    }
    if(atoi(fan_state) == 0){
      fan = "Off";
    }
    if(atoi(fan_state) != 0){
      fan = "On";
    }
    indx= 0; //reset button to zero
}

// int size = sizeof(light_state) / sizeof(char);
// String s_a = convertToString(light_state, size);
// Serial.println(s_a);


lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temp:");
lcd.print(ambient_temp);
lcd.print(" Fan:");
lcd.print(fan);
lcd.setCursor(0,1);
lcd.print("Light:");     
lcd.print(light);
//  lcd.print("/");
//  lcd.print("red");
delay(100);
}
