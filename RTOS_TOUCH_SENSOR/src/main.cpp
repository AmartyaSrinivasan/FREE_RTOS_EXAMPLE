#include <Arduino.h>
#include <ArduinoJson.h>

#define TOUCH 23

QueueHandle_t sendreceivingdata;

void TASK1(void *pvParameters)
{
  char send_text[100];
  while (1)
  {
    int touch = digitalRead(TOUCH);
    JsonDocument jsondata;
    jsondata["info"] = touch;
    serializeJson(jsondata, send_text);
    xQueueSend(sendreceivingdata, &send_text, portMAX_DELAY);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void TASK2(void *pvParameters)
{
  char received_data[100];
  while (1)
  {
    int Queuecount = uxQueueMessagesWaiting(sendreceivingdata);
    if (Queuecount > 0)
    {
      if (xQueueReceive(sendreceivingdata, &received_data, portMAX_DELAY) == pdTRUE)
      {
        JsonDocument doc;
        deserializeJson(doc, received_data);
        int data = doc["info"];
        if (data)
        {
          Serial.println("Touch Detected");
        }
      }
    }
  }
}
void setup()
{
  Serial.begin(9600);

  pinMode(TOUCH, INPUT);

  sendreceivingdata = xQueueCreate(10, 30);

  xTaskCreatePinnedToCore(TASK1, "TASK1", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TASK2, "TASK2", 10000, NULL, 2, NULL, 1);
}

void loop()
{
}