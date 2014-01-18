int x, y, z, mag;
int xPrev, yPrev, zPrev;
double xAvg, yAvg, zAvg;

boolean flags[] = {0, 0, 0, 0};

const int xPin = 1;
const int yPin = 2;
const int zPin = 3;

const double calCount = 100;

// Pins for note switching
const int a = 8;
const int b = 9;
const int c = 10;
const int d = 11;

const int vcc = A5;
const int gnd = A4;
// Constant for Low Pass filter
const double k = 0.8f;

void setup() {
  Serial.begin(9600);

  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);

  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(c, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  
  // Initialize variables
  x = 0;
  y = 0;
  z = 0;
  xPrev = 0;
  yPrev = 0;
  zPrev = 0;
  
  delay(1000);
  calibrate();
}

void loop() {
  // Apply a Low Pass Filter on the raw signal
  x = k*xPrev + (1-k)*(analogRead(xPin) - xAvg);
  y = k*yPrev + (1-k)*(analogRead(yPin) - yAvg);
  z = k*zPrev + (1-k)*(analogRead(zPin) - zAvg);
  
  mag = (int) sqrt(x*x + y*y + z*z);
  
  if(digitalRead(a) == LOW) flags[0] = 1;
  else flags[0] = 0;
  if(digitalRead(b) == LOW) flags[1] = 1;
  else flags[1] = 0;
  if(digitalRead(c) == LOW) flags[2] = 1;
  else flags[2] = 0;
  if(digitalRead(d) == LOW) flags[3] = 1;
  else flags[3] = 0;
  
  for(int i = 0; i < 4; i++) Serial.print(flags[i]);
  Serial.print("#");
  Serial.print(mag);
  Serial.print("\n");
  

  // Update values for next iteration
  xPrev = x;
  yPrev = y;
  zPrev = z;
}

// Function to re-zero the acceleremeter, finds an average
void calibrate() {
  int i;
  xAvg = 0;
  yAvg = 0;
  zAvg = 0;
  
  for(i = 0; i < calCount; i++) {
    // Read in the raw unclean data sset
    xAvg += analogRead(xPin);
    yAvg += analogRead(yPin);
    zAvg += analogRead(zPin);
  }

  xAvg = xAvg / calCount;
  yAvg = yAvg / calCount;
  zAvg = zAvg / calCount;
  
  delay(100);
}



