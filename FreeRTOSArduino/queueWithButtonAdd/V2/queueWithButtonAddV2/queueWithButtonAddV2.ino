#include <Arduino_FreeRTOS.h>
#include <queue.h>

typedef void (*TaskFunction)(void*);

typedef struct {
  TaskFunction function;
  void *parameters;
} TaskItem;

QueueHandle_t xTaskQueue;
const int buttonPin = 2;

// Function prototypes
void receiverTask(void *pvParameters);
void idleTask(void *pvParameters);
void showSpecificLed(int port);
void showLed11(void *pvParameters);
void showLed10(void *pvParameters);
void handleButtonInterrupt();

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Create a queue that can hold 5 TaskItems
  xTaskQueue = xQueueCreate(5, sizeof(TaskItem));

  // Create the receiver task with reduced stack size
  xTaskCreate(receiverTask, "ReceiverTask", 128, NULL, 2, NULL);

  // Create the idle task with reduced stack size
  xTaskCreate(idleTask, "IdleTask", 128, NULL, 0, NULL);

  // Create interrupt
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);

  vTaskStartScheduler();
}

void loop() {
  // Empty loop as required by Arduino framework when using FreeRTOS
}

void receiverTask(void *pvParameters) {
  TaskItem receivedItem;
  for (;;) {
    // Wait indefinitely for data to arrive on the queue
    if (xQueueReceive(xTaskQueue, &receivedItem, portMAX_DELAY) == pdPASS) {
      // Call the function pointer with its parameters
      receivedItem.function(receivedItem.parameters);
      vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for demonstration
    }
    taskYIELD();
  }
}

void idleTask(void *pvParameters) {
  for (;;) {
    showSpecificLed(13);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    showSpecificLed(12);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void showSpecificLed(int port) {
  for (int i = 10; i < 14; i++) {
    if (i == port) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

void showLed11(void *pvParameters) {
  showSpecificLed(11);
}

void showLed10(void *pvParameters) {
  showSpecificLed(10);
}

void handleButtonInterrupt() {
  if (uxQueueSpacesAvailable(xTaskQueue) < 1) {
    return;
  } else if (uxQueueSpacesAvailable(xTaskQueue) == 1) {
    TaskItem item = { showLed10, NULL };
    xQueueSendToFrontFromISR(xTaskQueue, &item, portMAX_DELAY);
  } else {
    TaskItem item = { showLed10, NULL };
    xQueueSendFromISR(xTaskQueue, &item, portMAX_DELAY);
  }
}
