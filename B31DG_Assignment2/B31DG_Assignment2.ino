#include <Ticker.h>

#define timer_pin 32

Ticker periodicTicker;
int tick = 0;

#define task1_pin 21

#define task2_pin 22
int task2_state = 0;

#define task3_pin 13
float task3_duration1low;
float task3_durationperiod;
int task3_frequency;

#define task4_pin 14    // select the input pin for the potentiometer
int task4_state = 0; 

int task5_sto1 = 0;
int task5_sto2 = 0;
int task5_sto3 = 0;
int task5_sto4 = 0;
int task5_avg = 0;

int error_code = 0;

#define task8_pin 15

void periodicPrint(){
  //Serial.println(tick);
  tick++;
    if((tick % 2500) == 0){
    task9();
    tick = 0;
  }
  
   if((tick % 500) == 0){
    task3();
  }

     if((tick % 16) == 0){
    task1();
  }

     if((tick % 100) == 0){
    task2();
  }

//rounded 
  if((tick % 21) == 0){
    task4();
    task5();
  } 

  if((tick % 50) == 0){
    task6();
  }

//rounded
  if((tick % 167) == 0){
    task7();
    task8();
  }
}


//Task1 watchdog 30Hz 
void task1(){
  digitalWrite(task1_pin, HIGH);
  delayMicroseconds(50);
  digitalWrite(task1_pin, LOW);
}

//Task2 High/Low In 5Hz
void task2(){                        
  task2_state = digitalRead(task2_pin);
}

//Task3 Freq In 1Hz
void task3(){  
 //  task3_duration1low = pulseIn(task3_pin, LOW);
 //  task3_durationperiod = task3_duration1low *2;
 //  task3_frequency = (1 / (task3_durationperiod/1000))*1000;                   
}

//Task4 Poteniotmeter 24Hz
void task4(){
  digitalWrite(timer_pin, HIGH);     
  task4_state = analogRead(task4_pin);  
  digitalWrite(timer_pin, LOW);                  
}

//Task5 Avg 4 Pot 1Hz
void task5(){  
  task5_sto4 = task5_sto3;
  task5_sto3 = task5_sto2;
  task5_sto2 = task5_sto1; 
  task5_sto1 = task4_state;
  task5_avg = (task5_sto4 + task5_sto3 + task5_sto2 + task5_sto1)/4;                      
}

//Task6 Volatile 10Hz
void task6(){
  for(int C_Loop = 1; C_Loop == 1000; C_Loop++){  
    __asm__ __volatile__("nop");
  }
}

//Task7 checker 3Hz
void task7(){
  if(task5_avg > (4096/2)){
    error_code = 1; 
  }
  else{
    error_code = 0;
  }
}

//Task8 LED 3Hz
void task8(){
  if(error_code == 1){
    digitalWrite(task8_pin, HIGH);
  }
  else{
    digitalWrite(task8_pin, LOW);
    }
}

//Task9 Print Resuts
void task9(){
  Serial.println("");
  Serial.print("[ ");
  Serial.print(task2_state);
  Serial.print(" , ");
  Serial.print(task3_frequency);
  Serial.print(" , ");
  Serial.print(task5_avg);
  Serial.print(" ]");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  periodicTicker.attach_ms(2, periodicPrint);

  pinMode(task1_pin, OUTPUT);
  pinMode(task2_pin, INPUT);    //Button Digital
  pinMode(task3_pin, INPUT);
  pinMode(task4_pin, INPUT);
  pinMode(task8_pin, OUTPUT);
  pinMode(timer_pin, OUTPUT);
   
}

void loop() {
  // put your main code here, to run repeatedly:


}
