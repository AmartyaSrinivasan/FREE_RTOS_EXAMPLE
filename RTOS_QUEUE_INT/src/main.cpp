#include "Arduino.h"

QueueHandle_t sendreceivingdata; // Declare a queue to pass client status
int count = 0;

void TASK1(void *pvParameters)
{
  while (1)
  {
    count++;
    Serial.println("i am task1");
    xQueueSend(sendreceivingdata, &count, portMAX_DELAY);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void TASK2(void *pvParameters)
{

  while (1)
  {
    int receivedNumber;
    int Queuecount = uxQueueMessagesWaiting(sendreceivingdata); // for stored Queue count
    if (Queuecount > 0)
    {
      if (xQueueReceive(sendreceivingdata, &receivedNumber, portMAX_DELAY) == pdTRUE)
      {
        Serial.print("Received Number: ");
        Serial.println(receivedNumber);
      }
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup()
{

  Serial.begin(9600);

  sendreceivingdata = xQueueCreate(2, 1); 

  /*************************************RTOS task********************************************/
  // task function                 taskname  ram size       priority  task handle , cpu core
  xTaskCreatePinnedToCore(TASK1, "TASK1", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TASK2, "TASK2", 10000, NULL, 2, NULL, 1);
  /******************************************************************************************/
}

void loop()
{
}