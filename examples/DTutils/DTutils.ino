#include <DTutils.h>
#include <Time.h>

int TimeZone = +1; //Zeitzone vorgeben
dtElements dt_to_int;
dtElements int_to_dt;
tmElements_t tm;

void setup() {
  // put your setup code here, to run once:
  // Setup Serial connection
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("--- Start ---");
  Serial.print("Day of Week: ");
  Serial.println(DayOfWeek(2014,06,17));

  Serial.print("Start Date DaylightSaving: ");
  Serial.println(StartDateDaylightSaving(2014));

  Serial.print("End Date DaylightSaving: ");
  Serial.println(EndDateDaylightSaving(2014));

  dt_to_int.Year = 2014;
  dt_to_int.Month = 6;
  dt_to_int.Day = 17;
  dt_to_int.Hour = 14;
  dt_to_int.Minute = 15;
  dt_to_int.Second = 16;
  uint32_t SecUnix;
  Serial.print("DT To Int: (1403014516) - ");
  DTToInt(dt_to_int, SecUnix);
  Serial.println(SecUnix);
  
  Serial.println("Int To DT: (1403014516)");
  IntToDT(1403014516, int_to_dt);
  Serial.print("Year:");
  Serial.println(int_to_dt.Year);
  Serial.print("Month:");
  Serial.println(int_to_dt.Month);
  Serial.print("Day:");
  Serial.println(int_to_dt.Day);
  Serial.print("Hour:");
  Serial.println(int_to_dt.Hour);
  Serial.print("Minute:");
  Serial.println(int_to_dt.Minute);
  Serial.print("Second:");
  Serial.println(int_to_dt.Second);   

  Serial.println("--- End ---");  
  delay(1000); 
}
