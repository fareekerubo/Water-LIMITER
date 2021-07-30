void float_sensor()
{
  Serial.print("Tank status: " );
  Serial.println(digitalRead(float_Switch));
  
  if(digitalRead(float_Switch) == LOW)//empty
  {
    check_state=0;//FULL
     
  }
 else
 {
  check_state=1;//EMPTY
 }
}
