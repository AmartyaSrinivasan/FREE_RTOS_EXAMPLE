#include <Arduino.h>
#include "PinConfig.h"

QueueHandle_t sendreceivingdata;


void TASK1(void *pvParameters)
{
  while(1)
  {
    int motionread=digitalRead(MOTION);
    events event = (motionread == HIGH) ? ETS_MOTION_DETECTOR : ETS_NO_MOTION;
    xQueueSend(sendreceivingdata, &event, portMAX_DELAY);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }

}

void TASK2(void *pvParameters)
{
  while(1)
  {
    int receive;
    int Queuecount = uxQueueMessagesWaiting(sendreceivingdata);
    if (Queuecount > 0)
    {
      if (xQueueReceive(sendreceivingdata, &receive, portMAX_DELAY) == pdTRUE)
      {
        switch(receive)
        {
          case  ETS_NO_MOTION:
            Serial.println("No motion");
            digitalWrite(BUZZER,LOW);
            break;
          case ETS_MOTION_DETECTOR:
            Serial.println("Motion detector");
            digitalWrite(BUZZER,HIGH);
            break;
        }
      }
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(MOTION, INPUT);
  pinMode(BUZZER, OUTPUT);
  sendreceivingdata = xQueueCreate(10, 1);
  xTaskCreatePinnedToCore(TASK1, "TASK1", 1000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TASK2, "TASK2", 1000, NULL, 2, NULL, 1);
}

void loop()
{

}