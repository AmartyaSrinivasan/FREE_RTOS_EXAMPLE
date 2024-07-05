#include "Arduino.h"
#define led1 13
#define led2 12
void TASK1(void *pvParameters)
{
      while (1)
      {
            digitalWrite(led1,1);
            vTaskDelay(1000/portTICK_PERIOD_MS); 
            digitalWrite(led1,0);
            vTaskDelay(1000/portTICK_PERIOD_MS); 
      }
}

void TASK2(void *pvParameters)
{
     while(1)
     {
          digitalWrite(led2,1);
          vTaskDelay(1000/portTICK_PERIOD_MS);
          digitalWrite(led2,0);
          vTaskDelay(1000/portTICK_PERIOD_MS); 
     }
}


void setup()
{
      Serial.begin(9600);
      pinMode(led1,OUTPUT);
      pinMode(led2,OUTPUT);
      /*************************************RTOS task********************************************/
       //task function                 taskname  ram size       priority  task handle , cpu
       xTaskCreatePinnedToCore(TASK1 , "TASK1" , 1000   , NULL , 1      , NULL ,0);
       xTaskCreatePinnedToCore(TASK2 , "TASK2" , 1000   , NULL , 2      , NULL ,1);
      /******************************************************************************************/

      
}

void loop()
{
      
}