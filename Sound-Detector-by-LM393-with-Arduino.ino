const int OUT_PIN = 8;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;

int sound_detected=0;

//heart calculation

int lastState = 0;      // Previous state of beat detection
unsigned long lastBeatTime = 0; // Time of the last beat detection
int beats = 0;  


void setup()
{ 
   Serial.begin(9600);
}
void loop() 
{
   calculateHeartBeat();
}



int detectHeartBeat()
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

void calculateHeartBeat()
{
      // Replace this with your function that returns 1 on beat detection, 0 otherwise
  int currentState = detectHeartBeat();
  Serial.println("currentState: " + String(currentState));

  // If there's a transition from no beat to beat (rising edge)
  if (currentState == 1 && lastState == 0) {
    unsigned long currentTime = millis();
    unsigned long timeSinceLastBeat = currentTime - lastBeatTime;

    // Avoid division by zero and very fast beats
    if (timeSinceLastBeat > 0 && timeSinceLastBeat < 3000) {
      float heartRate = 60000.0 / timeSinceLastBeat; // Convert to beats per minute
      Serial.println("Heart Rate: " + String(heartRate) + " BPM");
    }

    lastBeatTime = currentTime;
    beats++;
  }

  lastState = currentState;
}