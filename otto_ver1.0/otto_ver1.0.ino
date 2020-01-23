/* Дата: 23.01.2020
 * Автор: NickGeek
 * Проект: Otto с управлением по BT, 3 сенсорами и ультразвуковым дачтиком
 * 
 * Доделать
 * 1)Научить Отто говорить
 */

#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>

Otto Otto;  //Начальная инициализация

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
     Otto.sing(S_connection); 

     switch(val){
     //Движения в стороны
      case('F'):
        Otto.walk(4,500,1);
        Otto.home();
        break;
      case('B'):
        Otto.walk(4,500,-1);
        Otto.home();
        break;
      case('L'):
        Otto.turn(4,500,LEFT);
        Otto.home();
        break;
      case('R'):
        Otto.turn(4,500,RIGHT);
        Otto.home();
        break;
        
      //Прочие движения
      case('0'):    
        Otto.jump(4,500);
        Otto.home();
        break;
      case('1'):
        Otto.bend(2,500,LEFT);
        Otto.bend(2,500,RIGHT);
        Otto.home();
        break;
      case('2'):
        Otto.shakeLeg(2,500,RIGHT);
        Otto.shakeLeg(2,500,LEFT);
        Otto.home();
        break;
      case('3'):
        Otto.updown(4,500,40);
        Otto.home();
        break;
      case('4'):
        Otto.swing(4,500,40);
        Otto.home();
        break;
      case('5'):
        Otto.tiptoeSwing(4,500,40);
        Otto.home();
        break;
      case('6'):
        Otto.jitter(4,500,40);
        Otto.home();
        break;
      case('7'):
        Otto.ascendingTurn(4,500,40);
        Otto.home();
        break;

      //Танцы
      case('Q'):
        Otto.moonwalker(6,500,40,RIGHT);   
        Otto.home();
        break;
      case('W'):
        Otto.crusaito(4,500,20,RIGHT);
        Otto.home();
        break;
      case('E'):
        Otto.flapping(4,500,20,FORWARD);
        Otto.home();
        break;
        
      case('X'):
        Otto.moonwalker(6,500,40,LEFT);   
        Otto.home();
        break;
      case('Y'):
        Otto.crusaito(4,500,20,LEFT);
        Otto.home();
        break;
      case('Z'):
        Otto.flapping(4,500,20,BACKWARD);
        Otto.home();
        break;
      default:
        Otto.sing(S_fart1); 
        Otto.home();
        break;
     }
    Otto.sing(S_disconnection); 
  }      

  //Верхний сенсор
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
 
    motion = motion + 1;
    if (motion == 14)
    {
      motion = 1;             
    }
   }

  //Левый сенсор
  if (digitalRead(sensorLeft)){
    Otto.sing(S_superHappy);
    Otto.flapping(4,500,20,BACKWARD);
    Otto.home();
  }

  //Правый сенсор
  if (digitalRead(sensorRight)){
    Otto.sing(S_surprise);
    Otto.flapping(4,500,20,FORWARD); 
    Otto.home();
  }

    //Обработка обнаружения движения
  
  if(obstacleDetected){ 
    Otto.sing(S_fart1);  
    Otto.walk(1,500,-1); 
    Otto.tiptoeSwing(2,500,40); 
    Otto.home(); 
    Otto.sing(S_fart3);   
    obstacleDetector(); 
  }        
  else{ 
    obstacleDetector(); 
  }  

}

//////////////////////////////////////////////////////////////////////////
//-- Функция для считывания датчика расстояния и для обновления переменной
void obstacleDetector(){

  int sum = 0;
  int attempts = 50;  //Количество замеров для вычисления среднего. Если уменьшить - будет работать быстрее
  int distance = 0;
  int cm;

  //Фильтр помех. Вычисляем среднее (пока такой, потом надо переписать)
  for (int i = 0; i < attempts; i++) {
    distance = Otto.getDistance();
    sum += distance;
  }
  cm = sum/attempts;
  Serial.println(cm);


  if(cm < 20){
    obstacleDetected = 1;
  }
  else{
    obstacleDetected = 0;
  }
}
