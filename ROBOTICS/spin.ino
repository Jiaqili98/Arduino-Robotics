//define inouts
#define LS 1
#define MS 2
#define RS 3

//define outputs
#define LMD 4 //black wire
#define RMD 7 //black wire
#define LMS 5 //red wire
#define RMS 6 //red wire

//threshold definition
#define LTHRESH 100
#define MTHRESH 100
#define RTHRESH 100 
//line tracker
int readingLS = 0;
int readingMS = 0;
int readingRS = 0;

void setup()
{
  pinMode(LS,INPUT);
  pinMode(MS,INPUT);
  pinMode(RS,INPUT);
  pinMode(LMD,OUTPUT);
  pinMode(RMD,OUTPUT);
  pinMode(LMS,OUTPUT);
  pinMode(RMS,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  readingLS = analogRead (1);
  readingMS = analogRead (2);
  readingRS = analogRead (3);


 
if (readingLS >= LTHRESH  || readingMS >= MTHRESH || readingRS >= RTHRESH)
  {
    Serial.println (readingLS);
    Serial.println (readingMS);
    Serial.println (readingRS);
    stop ();
  }
  
else 
  {
    move ();
  }
  
}

void move ()
{
  analogWrite (LMD, HIGH);
  analogWrite (RMD, LOW);
  analogWrite (LMS, 100);
  analogWrite (RMS, 100);
  delay(30);
  }

void stop ()
{
  analogWrite (LMS, 0);
  analogWrite (RMS, 0);
  delay (30);
  }
