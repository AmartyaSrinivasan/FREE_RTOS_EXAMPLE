#include <Arduino.h>

QueueHandle_t sendreceivingdata;


void TASK1(void *pvParameters)
{
  while(1)
  {
    char text[100] = "Helloworld";
    xQueueSend(sendreceivingdata, &text, portMAX_DELAY);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void TASK2(void *pvParameters)
{
  while(1)
  {
    char received_text[100];
    int Queuecount=uxQueueMessagesWaiting(sendreceivingdata);
    if (Queuecount>0)
    {
      if  (xQueueReceive(sendreceivingdata, &received_text, portMAX_DELAY) == pdTRUE)
      {
        Serial.println(received_text);
      }
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  sendreceivingdata = xQueueCreate(10,15);

  xTaskCreatePinnedToCore(TASK1, "TASK1", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TASK2, "TASK2", 10000, NULL, 2, NULL, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}

