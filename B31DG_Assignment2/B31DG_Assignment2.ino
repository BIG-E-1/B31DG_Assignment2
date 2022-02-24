#include <Ticker.h>

Ticker periodicTicker;
Ticker onceTicker;

void periodicPrint(){
  Serial.println("printing in periodic function");
}

void oncePrint(){
  Serial.println("printing in once function");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  periodicTicker.attach_ms(5000, periodicPrint);
  onceTicker.once_ms(10000, oncePrint);
}

void loop() {
  // put your main code here, to run repeatedly:

}
