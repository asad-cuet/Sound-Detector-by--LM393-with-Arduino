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


//gsr_avg
const int GSR = A0;
int sensorValue = 0;
int gsr_avg = 0;


//logic var
int heart_rate_measured=0;


void setup()
{ 
   Serial.begin(9600);
}
void loop() 
{
   while(!heart_rate_measured)
   {
      calculateHeartBeat();
   }
   heart_rate_measured=0;

   readGSR();

   delay(5000);
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
      heart_rate_measured=1;
      Serial.println("Heart Rate: " + String(heartRate) + " BPM");
    }

    lastBeatTime = currentTime;
    beats++;
  }

  lastState = currentState;
}

void readGSR()
{
  long sum = 0;
  for (int i = 0; i < 10; i++)

  {

    sensorValue = analogRead(GSR);

    sum += sensorValue;

    delay(100);

  }

  gsr_avg = sum / 10;
  Serial.print("gsr_avg=");
  Serial.println(gsr_avg);
}