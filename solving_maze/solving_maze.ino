#define echoPin 10 //on
#define trigPin 11 //on
#define echoPin2 A5 //sol
#define trigPin2 A2//sol
#define echoPin3 A0 //sag
#define trigPin3 A1 //sag
#define MotorL1 13 //in1
#define MotorL2 12 //in2
#define MotorLE 3//enb
#define MotorR1 8//in3
#define MotorR2 7//in4
#define MotorRE 6//ena
#define PWM 200

const int maxrange = 50;
const int avaragerange = 30;
const int minrange = 30;

long sure,sure2,sure3,onmesafe,sagmesafe,solmesafe;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
Main:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH); 
  onmesafe = sure / 29.1 / 2; 
  
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW); 
  sure2 = pulseIn(echoPin2, HIGH);
  solmesafe = sure2 / 29.1 / 2;
  
  digitalWrite(trigPin3, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW); 
  sure3 = pulseIn(echoPin3, HIGH);
  sagmesafe = sure3 / 29.1 / 2;
  
  
  Serial.print("SAĞ MESAFE = ");Serial.println(solmesafe);
  

    
    if(sagmesafe >= maxrange && onmesafe >= maxrange){
    sag();
    goto Main;
    }
    if (sagmesafe >= maxrange && (onmesafe < maxrange && onmesafe >= minrange)){
    hafifsag();
    goto Main;
    }
    if (sagmesafe >= maxrange && onmesafe < minrange){
    sag();
    goto Main;
    }
    if ((sagmesafe < maxrange && sagmesafe >= minrange) && onmesafe >= maxrange){
    sag();
    goto Main;
    }  
    if((sagmesafe < maxrange && sagmesafe >= minrange) && (onmesafe < maxrange && onmesafe >= minrange)){
    sag();
    goto Main;
  }
  if((sagmesafe < maxrange && sagmesafe >= minrange) && onmesafe < minrange){
    sol();
    goto Main;
  }
  if(sagmesafe < minrange && onmesafe >= maxrange){
    ileri();    
    goto Main;
  }
  if(sagmesafe < minrange && (onmesafe < maxrange && onmesafe >= minrange)){
    sol();
    goto  Main;
  }
  if(sagmesafe < minrange && onmesafe < minrange){

    sol();
    goto Main;
  }
}
void ileri(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, PWM);
}
void geri(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, PWM);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, PWM);
}
void dur(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 0);
}
void sol(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, 50); 
}
void sag(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 50);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, PWM); 
}
void hafifsol(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM+25);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 0);
}
void hafifsag(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, PWM+25);
}
