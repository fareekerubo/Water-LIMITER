 #include <DS3231.h>


DS3231  rtc(SDA, SCL);
Time t;
int flag=0;
 int full_hour=0; //SET TIME TO ON RELAY (24 HOUR FORMAT)
 int full_min=0;

int empty_hour=0;
int empty_min=0;

//const int OffHour = 18; //SET TIME TO OFF RELAY
//const int OffMin = 47;

int yellow=6;
int blue=7;
int power=4;
int float_Switch=2;
 int check_state;
bool pick_time=true;
void setup() {
  Serial.begin(9600);
  rtc.begin();
  rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
 //rtc.setTime(9, 03, 0);     // Set the time to 12:00:00 (24hr format)
 // rtc.setDate(7, 12, 2021);   // Set the date to January 1st, 2014

pinMode(yellow, OUTPUT);
 pinMode(blue, OUTPUT);
 pinMode(power, OUTPUT);
 pinMode(float_Switch,INPUT_PULLUP);

  Serial.print("closing");
   digitalWrite(power,HIGH);
  digitalWrite(blue,LOW);
  digitalWrite(yellow,LOW);
   delay (3000);
   
   digitalWrite(power,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(yellow,LOW);

  if(digitalRead(float_Switch) == HIGH)
  {
   pick_time=false;
   t = rtc.getTime();
   full_hour=t.hour;
   full_min=t.min;
   Serial.print(full_hour);
   Serial.print(" hour(s), ");
   Serial.print(full_min);
   Serial.print(" minute(s)");
   Serial.println(" ");
   
   
  }

}

void loop() 
{
 float_sensor();
 
 
  if(check_state==0)
  {
    if(pick_time)
    {
    t = rtc.getTime();
    full_hour=t.hour;
    full_min=t.min;
    Serial.print(full_hour);
    Serial.print(" hour(s), ");
    Serial.print(full_min);
    Serial.print(" minute(s)");
    Serial.println(" ");
    Serial.print("closing");
    digitalWrite(power,HIGH);
    digitalWrite(blue,LOW);
    digitalWrite(yellow,LOW);
    delay (3000);
    digitalWrite(power,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(yellow,LOW);
    pick_time=false;
  }
  }
  else if (check_state==1)
  {
    if(!pick_time)
    {
     t = rtc.getTime();
    empty_hour=t.hour;
    empty_min=t.min;
    Serial.print(empty_hour);
    Serial.print(" hour(s), ");
    Serial.print(empty_min);
    Serial.print(" minute(s)");
    Serial.println(" ");
    int diff_hr=empty_hour-full_hour;
    int diff_min=empty_min-full_min;

    if(diff_min==2)
    {
        Serial.print("opening");
  digitalWrite(power,HIGH);
  digitalWrite(blue,HIGH);
  digitalWrite(yellow,HIGH);
   delay (3000);
   digitalWrite(power,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(yellow,LOW);
   delay (1000);
   pick_time=true;
   
    }
  
  }

}
}
