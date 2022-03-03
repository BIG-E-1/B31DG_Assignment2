#include <Ticker.h>

Ticker periodicTicker;
Ticker onceTicker;
int tick = 0;

#define task2_pin 22
int task2_state = 0;
int task4_pin = A0;    // select the input pin for the potentiometer
int task4_state = 0; 

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

//Task4 Peteniotmeter 24Hz
void task4(){     
  task4_state = analogRead(task4_pin);                   
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //periodicTicker.attach_ms(0.1, periodicPrint);
  
  pinMode(task2_pin, INPUT);    //Button Digital
   
  
}

void loop() {
  // put your main code here, to run repeatedly:

 // Serial.println(tick);

 while(1){
 task2();
 Serial.println(task2_state);
 delay(1000);
 }


  
  
}
