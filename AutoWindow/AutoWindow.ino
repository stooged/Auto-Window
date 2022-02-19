//VE AutoWindow

const int RunTime = 6000; //time to wind window up for (1000 = 1 second)
const int AutoDelay = 800; //how long to hold window up button before auto starts (1000 = 1 second)

const int RelayPin = 4;
const int SwitchOnPin = 6;
const int SwitchOffPin = 7;

int SwitchOnState = HIGH;
int SwitchOffState = HIGH;

unsigned long time;
unsigned long TimeCount;
unsigned long SwitchTime;

bool IsRunning;
bool isSwitchUP;



void setup() {
 pinMode(RelayPin, OUTPUT);
 pinMode(SwitchOnPin, INPUT_PULLUP);
 pinMode(SwitchOffPin, INPUT_PULLUP);
 digitalWrite(RelayPin, LOW);
 IsRunning = false;
 isSwitchUP = false;
 TimeCount = 0;
 SwitchTime = 0;
}



void loop() {
time = millis();

   if (IsRunning == false)
   {
     SwitchOnState = digitalRead(SwitchOnPin); 
      if (SwitchOnState == LOW) {
          digitalWrite(RelayPin, HIGH);
          
            if (isSwitchUP == false)
            {
            SwitchTime = time;
            isSwitchUP = true;
            }
               
            if (time >= (SwitchTime + AutoDelay))
            {
            SwitchTime = 0;
            IsRunning = true;
            isSwitchUP = false;
            TimeCount = time;          
            }           
      }
      else
      { 
            digitalWrite(RelayPin, LOW);
            SwitchTime = 0;
            isSwitchUP = false;
      }
     
   }
   else
   {
     SwitchOffState = digitalRead(SwitchOffPin);
       
      if (SwitchOffState == LOW) {
            digitalWrite(RelayPin, LOW);
            IsRunning = false;
            isSwitchUP = false;
            TimeCount = 0;
            SwitchTime = 0;
            return;
      }  

      if ( time >= (TimeCount + RunTime))
      {
            digitalWrite(RelayPin, LOW); 
            IsRunning = false;
            isSwitchUP = false;
            TimeCount = 0;  
            SwitchTime = 0;   
      }     
   }
}



