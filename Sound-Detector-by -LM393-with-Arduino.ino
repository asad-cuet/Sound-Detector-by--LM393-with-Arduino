const int OUT_PIN = 8;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;

int sound_detected=0;


void setup()
{ 
   Serial.begin(9600);
}
void loop() 
{
   Serial.println(detectSound());
}



int detectSound()
{
  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

   if (digitalRead(OUT_PIN) == LOW) 
   {
      Serial.println("Detected!!!");
      sound_detected=1;
      // Serial.println(sound_detected);
      sampleBufferValue++;
   }
   else
   {
      sound_detected=0;
   }

   if (millisElapsed > SAMPLE_TIME) {
      millisLast = millisCurrent;
   }

   return sound_detected;
}