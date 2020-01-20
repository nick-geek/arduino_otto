/* Дата: 31.07.2019
 * Otto с управлением по BT, 3 сенсорами и ультразвуковым дачтиком
 * 1) Сделать управление по БТ, чтобы можно было ходить в стороны и петь песни
 * 2) Без БТ работа в обычном режиме, при поглаживании по шее идти в сторону поглаживания
 * 3) Перепечатать голову
 * 4) Скачал гитхаб десктоп
 */

#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>



Otto Otto;  //This is Otto!

//---------------------------------------------------------
//-- Подключение сервоприводов и датчиков
/*
           ----/\----     <== Touch Sensor 1 - Pin 12
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
Senson 2 ---------------  <== Touch Sensor 3 - Pin 10
  Pin 11     ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
         Buzzer - pin 13
*/
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]
  const int sensorLeft = 11;
  const int sensorRight = 10;
  const int sensorTop = 12;
  
  
///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
//-- Инициализация движения
int motion = 1;
//---------------------------------------------------------
bool obstacleDetected = false;

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
    //Set the servo pins
    Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true, -1, 13, 8, 9);
    Serial.begin(9600);
    pinMode(sensorLeft, INPUT);
    pinMode(sensorRight, INPUT);
    pinMode(sensorTop, INPUT);
    Otto.home();
    Otto.sing(S_happy); // Отто счастлив, что его включили :)
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  //Работа по БТ
  if (Serial.available()){
    int val = Serial.read();
    //Serial.println(val);
    /*Режимы работы
     * Вперёд: F
     * Назад: B
     * Влево: L
     * Вправо: R 
     * Songs:
     * ...
     * ...
     * ...
     */

     switch(val){
      case('F'):
        Otto.sing(S_OhOoh);
        Otto.walk(4,500,1);
        Otto.home();
        break;
      case('B'):
        Otto.sing(S_OhOoh);
        Otto.walk(4,500,-1);
        Otto.home();
        break;
      //case('L'):

      //case('R'):
      
     }
     
  }

  //При обнаружении препятствия отто ругается
  if(obstacleDetected){ 
    Otto.sing(S_fart1);  
    Otto.walk(3,500,-1); 
    Otto.tiptoeSwing(2,500,40); 
    Otto.home(); 
    Otto.sing(S_fart3);   
    delay(50); 
    obstacleDetector(); 
  }        
  else{ 
    obstacleDetector(); 
  }           
  

  if (digitalRead(sensorLeft)){
    Otto.sing(S_happy);
    Otto.turn(8, 500, LEFT);
    Otto.home();
  }

  if (digitalRead(sensorRight)){
    Otto.sing(S_happy);
    Otto.turn(8, 500, RIGHT);
    Otto.home();
  }
   
  int state = digitalRead(sensorTop);
 
   if (state == HIGH)
   {
    if (motion == 1)
    {
      Otto.sing(S_surprise);
      Otto.walk(3,1300,1); 
      Otto.home();      
    }
    if (motion == 2)
    {
      Otto.sing(S_OhOoh);
      Otto.moonwalker(3,1000,30,1); 
      Otto.home();
    }
    if (motion == 3)
    {
      Otto.sing(S_happy);
      Otto.crusaito(3,3000,40,1); 
      Otto.home();
    }
    if (motion == 4)
    {
      Otto.sing(S_superHappy);
      Otto.shakeLeg(3,1000,1); 
      Otto.home();
    }
    if (motion == 5)
    {
      Otto.sing(S_fart1);
      Otto.flapping(3,500,40,1); 
      Otto.home();
    }  
    if (motion == 6)
    {
      Otto.sing(S_confused);
      Otto.tiptoeSwing(3,1000,30); 
      Otto.home();
    }
    if (motion == 7)
    {
      Otto.sing(S_connection);
      Otto.swing(3,500,40); 
      Otto.home();
    }
    if (motion == 8)
    {
      Otto.sing(S_disconnection);
      Otto.updown(3,1000,30); 
      Otto.home();
    }
    if (motion == 9)
    {
      Otto.sing(S_buttonPushed);
      Otto.jitter(10,500,40); 
      Otto.home();
    }
    if (motion == 10)
    {
      Otto.sing(S_fart3);      
      Otto.ascendingTurn(3,500,50); 
      Otto.home();
    }                
    if (motion == 11)
    {
      Otto.sing(S_sad);      
      Otto.jump(3,500); 
      Otto.home();
    }                
    if (motion == 12)
    {
      Otto.sing(S_cuddly);      
      Otto.turn(3,1000,1); 
      Otto.home();
    }
    if (motion == 13)
    {
      Otto.sing(S_superHappy);      
      Otto.bend(3,1000,1); 
      Otto.home();
    }    
 
    motion = motion +1;
    if (motion == 14)
    {
      motion = 1;             
    }
   }
}

///////////////////////////////////////////////////////////////////
//-- Функция для считывания датчика расстояния и для обновления переменной
void obstacleDetector(){
   int distance = Otto.getDistance();
        if(distance<15){
          obstacleDetected = true;
        }
        else{
          obstacleDetected = false;
        }
}
