#include "motrain.lib.h"

#define TIMER_SHORT 0x8D
#define TIMER_LONG 0x1B
#define OneMessage 58
#define ZeroMessage 116

#define TrainNumber 36
#define Pin 6

void sendBit(Byte bitval){
    if((bitval & (1 << 0)) > 0){
      //Serial.print(1);
      digitalWrite(Pin, HIGH);
      delayMicroseconds(getDelay(1));
      digitalWrite(Pin, LOW);
      delayMicroseconds(getDelay(1));
    }
    else{
      //Serial.print(0);
      digitalWrite(Pin, HIGH);
      delayMicroseconds(getDelay(0));
      digitalWrite(Pin, LOW);
      delayMicroseconds(getDelay(0));
    }
}

void sendByte(Byte byteval){
    for(int i = 7; i >= 0; i--){
        if((byteval & (1 << i)) > 0){
          sendBit(1);
        } else{
          sendBit(0);
        }
    }
}

void sendMessage(Message msg) {
  //Serial.println("sending message");
    // PREAMBLE
    for(int i = 0; i < 14; i++){
        sendBit(1);
    }
    sendBit(0);
    // BYTES
    for(int i = 0; i < msg.len; i++){
      //Serial.println("");
      //Serial.println(msg.data[i]);
        sendByte(msg.data[i]);
        if(i == msg.len-1){
            sendBit(1);
        } else {
            sendBit(0);
        }
    }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Pin, OUTPUT);
  pinMode(13, OUTPUT);
//  SetupTimer2();
  Message msg = Message({TrainNumber, 100, 100, 0,0,0,0});
  msg.data[2] = msg.data[1] ^ TrainNumber;
  msg.len = 3;
  sendMessage(msg);
}

void loop() {
  // put your main code here, to run repeatedly:
  Message msg = Message({TrainNumber, 100, 100, 0,0,0,0});
  msg.data[2] = msg.data[1] ^ TrainNumber;
  msg.len = 3;
  sendMessage(msg);
  /*
  delay(10000);
  msg = Message({TrainNumber, 65, 65, 0,0,0,0});
  msg.data[2] = msg.data[1] ^ TrainNumber;
  msg.len = 3;
  sendMessage(msg);
  delay(10000);
  */
}



/*

void SetupTimer2() {
  TCCR2A = 0;
  TCCR2B = 7;

  TIMSK2 = 1 << TOIE2;
  TCNT2 = TIMER_SHORT;
}

ISR(TIMER2_OVF_vect){
  Serial.println(millis());
}

*/
