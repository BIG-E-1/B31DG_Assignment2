#include <Ticker.h>

Ticker periodicTicker;
Ticker onceTicker;
int tick = 0;

#define task2_pin 22
int task2_state = 0;

#define task4_pin 23    // select the input pin for the potentiometer
int task4_state = 0; 

int task5_sto1 = 0;
int task5_sto2 = 0;
int task5_sto3 = 0;
int task5_sto4 = 0;
int task5_avg = 0;

void periodicPrint(){
  Serial.println("printing in periodic function");
  tick++;
}

void oncePrint(){
  Serial.println("printing in once function");
}

//Task2 High/Low In 5Hz
void task2(){                        
  task2_state = digitalRead(task2_pin);
}

//Task3 Freq In 1Hz
void task3(){                        
}

//Task4 Poteniotmeter 24Hz
void task4(){     
  task4_state = analogRead(task4_pin);                   
}

//Task5 Avg 4 Pot 1Hz
void task5(){  
  task5_sto4 = task5_sto3;
  task5_sto3 = task5_sto2;
  task5_sto2 = task5_sto1; 
  task5_sto1 = task4_state;
  task5_avg = (task5_sto4 + task5_sto3 + task5_sto2 + task5_sto1)/4;                      
}

//Task6 Volatile 3Hz
void task6(){
  for(int C_Loop = 0; C_Loop == 1000; C_Loop++){  
    __asm__ __volatile__("nop");
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //periodicTicker.attach_ms(0.1, periodicPrint);
  
  pinMode(task2_pin, INPUT);    //Button Digital
  pinMode(task4_pin, INPUT);
   
  
}

void loop() {
  // put your main code here, to run repeatedly:

 // Serial.println(tick);

 while(1){
 task4();
 Serial.println(task4_state);
 delay(1000);
 }


  
  
}
