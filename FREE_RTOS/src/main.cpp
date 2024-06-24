#include "Arduino.h"
/* mutexes or semaphores*/


void TASK1(void *pvParameters)
{
      while (1)
      {
            Serial.println("i am task1");
            vTaskDelay(1000/portTICK_PERIOD_MS);       
      }
}

void TASK2(void *pvParameters)
{
     while(1)
     {
          Serial.println("i am task2");
          vTaskDelay(1000/portTICK_PERIOD_MS);
     }
}


void setup()
{
      Serial.begin(9600);
      /*************************************RTOS task********************************************/
       //task function                 taskname  ram size       priority  task handle , cpu
       xTaskCreatePinnedToCore(TASK1 , "TASK1" , 1000   , NULL , 1      , NULL ,0);
       xTaskCreatePinnedToCore(TASK2 , "TASK2" , 1000   , NULL , 2      , NULL ,1);
      /******************************************************************************************/
}

void loop()
{
      
}