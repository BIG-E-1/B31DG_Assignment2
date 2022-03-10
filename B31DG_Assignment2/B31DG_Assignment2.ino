//B31DG Assignment 2
//Ethan Thomas Hunking H00272332
//The code below is an example of a cyclic executive. It utilises
//a ticker (which acts as a clock) to implement 9 different tasks 
//at different desired frequencies. A counter is linked to the 
//ticker which will implement the desired task if the statement 
//is true. The report attached to this code, explains this functionality. 

//Begin of declaring inputs, outputs and required int/float
#include <Ticker.h>     //Includes the ticker header
Ticker periodicTicker;  //Creates a periodic ticker
int tick_counter = 0;   //counter for ticks.

#define timer_pin 32    //Pin allocation for timer output

#define t1_pin 21       //Pin allocation for Task 1

#define t2_pin 22       //Pin allocation for Task 2
int t2_state = 0;       //Button State for Task 2
int t2_debounce = 0;    //Button debounce

#define t3_pin 13       //Pin allocation for Task 3
float t3_duration1low;  //float counter for time of low
float t3_durationperiod;//float for period of waveform
int t3_frequency;       //integer wavegen frequency

#define t4_pin 14       //Pin allocation for Task 4
int t4_state = 0;       //integer for analogue value read

int t5_sto1 = 0;        //Task 5 Pre-Calc. Avg Storage 1
int t5_sto2 = 0;        //Task 5 Pre-Calc. Avg Storage 2
int t5_sto3 = 0;        //Task 5 Pre-Calc. Avg Storage 3
int t5_sto4 = 0;        //Task 5 Pre-Calc. Avg Storage 4
int t5_avg = 0;         //Task 5 Calculated Average

int error_code = 0;     //Task 7 Error Code

#define t8_pin 15       //Pin allocation for Task 8

//End of required declarations.
//Cyclic Executive Ticker Code
//Main Function. Utilises Ticker.
void periodic4ms(){
    tick_counter++;  //Increments Counter     

    //Task 9 Looks for 0.2Hz
    if((tick_counter % 1250) == 0){
      task9();
      tick_counter =0;  //Resets counter after 5sec
    }
    //Task 3 Looks for 1Hz
    else if((tick_counter % 250) == 0){
      task3();
    }
    //Task 1 Looks for 31.25Hz
    else if((tick_counter % 8) == 0){
      task1();
    }
    //Task 2 Looks for 5Hz
    else if((tick_counter % 50) == 0){
      task2();
    }
    //Task 4&5 Looks for 25Hz 
    else if((tick_counter % 10) == 0){
      task4();
      task5();
    } 
    //Task 6 Looks for 10Hz
    else if((tick_counter % 25) == 0){
      task6();
    }
    //Task 7&8 Looks for 3Hz
    else if((tick_counter % 83) == 0){
      task7();
      task8();
    }
}     //End of Ticker Function

//Functions for each task
//Task1 watchdog 30Hz 
void task1(){
  digitalWrite(t1_pin, HIGH);  //Sets Output High
  delayMicroseconds(50);       //Delays signal by 50us
  digitalWrite(t1_pin, LOW);//Sets Output Low again
}

//Task2 High/Low In 5Hz
void task2(){  
  t2_debounce = t2_state;         //Saves previous status              
  t2_state = digitalRead(t2_pin); //Reads state of button
  delayMicroseconds(250);         //Delays signal by 250us

  //Checking for button bouncing
  if(t2_state != digitalRead(t2_pin)){
    if(t2_state != t2_debounce){
      t2_state = 0;
    }
  }  
}

//Task3 Freq In 1Hz
void task3(){  
   t3_duration1low = pulseIn(t3_pin, LOW);
   t3_durationperiod = t3_duration1low *2;
   t3_frequency = (1 / (t3_durationperiod/1000))*1000;                   
}

//Task4 Poteniotmeter 24Hz (des.) 25Hz (expt.)
void task4(){
  digitalWrite(timer_pin, HIGH);   //High to measure time   
  t4_state = analogRead(t4_pin);//Reads analog input  
  digitalWrite(timer_pin, LOW);    //Low to end measure time            
}

//Task5 Avg 4 Pot. 24Hz (des.) 25Hz (expt.)
void task5(){  
  t5_sto4 = t5_sto3;         //Shifts values by one position
  t5_sto3 = t5_sto2;         //Shifts values by one position         
  t5_sto2 = t5_sto1;         //Shifts values by one position 
  t5_sto1 = t4_state;        //Shifts values by one position

  //Uses 4 values to calculate average
  t5_avg = (t5_sto4 + t5_sto3 + t5_sto2 + t5_sto1)/4;                      
}

//Task6 Volatile 10Hz
void task6(){
  //for loop as defined in lab sheet
  for(int C_Loop = 1; C_Loop == 1000; C_Loop++){  
    __asm__ __volatile__("nop");
  }
}

//Task7 checker 3Hz
void task7(){
  //if statment as defined in lab sheet
  if(t5_avg > (4096/2)){
    error_code = 1; 
  }
  else{
    error_code = 0;
  }
}

//Task8 LED 3Hz
void task8(){
  //Reads error code and sets LED high/low if error_code 1/0
  if(error_code == 1){
    digitalWrite(t8_pin, HIGH);
  }
  else{
    digitalWrite(t8_pin, LOW);
    }
}

//Task9 Print Resuts
void task9(){
  //Prints in serial a csv as defined in lab sheet
  Serial.println("");
  Serial.print(t2_state); //Prints task 2
  Serial.print(" , ");
  Serial.print(t3_frequency); //Prints task 3
  Serial.print(" , ");
  Serial.print(t5_avg); //Prints task 5
}

//End of Functions of tasks
//Setup code
void setup() {
  // put your setup code here, to run once:

  //Creates Serial Port
  Serial.begin(115200);

  //Creates 4ms ticker
  periodicTicker.attach_ms(4, periodic4ms);

  pinMode(t1_pin, OUTPUT);   //Task 1 Watchdog 
  pinMode(t2_pin, INPUT);    //Task 2 Button dig. read
  pinMode(t3_pin, INPUT);    //Task 3 Square wave in.
  pinMode(t4_pin, INPUT);    //Task 4 Analogue input
  pinMode(t8_pin, OUTPUT);   //Task 8 Error LED output
  pinMode(timer_pin, OUTPUT);//Output for time testing
   
}

void loop() {
  //Loop is unused but kept to allow for compiling.
}
