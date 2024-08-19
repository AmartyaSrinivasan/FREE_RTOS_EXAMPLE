#include <Arduino.h>
#include <ArduinoJson.h>

QueueHandle_t sendreceivingdata;

void TASK1(void *pvParameters)
{
  char send_text[100];
  while (1)
  {
    JsonDocument jsondata;
    jsondata["info"] = "hello world";
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
        String data = doc["info"];
        Serial.println(data);
      }
    }
  }
}
void setup()
{
  Serial.begin(9600);

  sendreceivingdata = xQueueCreate(10, 30);

  xTaskCreatePinnedToCore(TASK1, "TASK1", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TASK2, "TASK2", 10000, NULL, 2, NULL, 1);
}

void loop()
{
}
