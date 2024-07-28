#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <LiquidCrystal.h>

// LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Semaphore for serial output
SemaphoreHandle_t xSerialSemaphore;

char* characters[] = { " ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

// Array of test strings
String testArrLog[] = { "TESTING", "ARRAY", "LISTS", "VALUES" };
volatile int arrPointer = 0;
bool editMode = false;

// Function prototypes
void BaseTask(void *pvParameters);
void LoopThroughArrayList(void *pvParameters);
void ChangeEditMode(void *pvParameters);
void DefaultLCD();

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  DefaultLCD();

  // Create the serial semaphore
  if (xSerialSemaphore == NULL) {
    xSerialSemaphore = xSemaphoreCreateMutex();
    if (xSerialSemaphore != NULL) {
      xSemaphoreGive(xSerialSemaphore);
    }
  }

  // Create the task to read analog input
  xTaskCreate(BaseTask, "MainTask", 128, NULL, 1, NULL);
}

void loop() {
  // Empty. Things are done in Tasks.
}

// Task to read analog input
void BaseTask(void *pvParameters) {
  for (;;) {
    int buttonValue = analogRead(A0);

    if (buttonValue >= 1020 && buttonValue <= 1025) {
      xTaskCreate(LoopThroughArrayList, "ShowNextValue", 128, NULL, 2, NULL);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    if (buttonValue >= 840 && buttonValue <= 850) {
      if (!editMode) {
        xTaskCreate(ChangeEditMode, "ChangeEditMode", 128, NULL, 3, NULL);
        vTaskDelay(500 / portTICK_PERIOD_MS);
      }
    }

    // Use semaphore to print the button value
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t) 5) == pdTRUE) {
      Serial.println(buttonValue);
      xSemaphoreGive(xSerialSemaphore);
    }
  }
}

void ChangeEditMode(void *pvParameters) {
  editMode = !editMode;
  if (editMode) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(testArrLog[arrPointer]);
    xTaskCreate(EditValue, "EditValues", 128, NULL, 2, NULL);
  } else {
    DefaultLCD();
  }
  vTaskDelete(NULL);
}

void EditValue(void *pvParameters) {
  int curPosInArr = 0;
  int curPosInLCD = 0;
  String currentText = testArrLog[arrPointer];
  lcd.setCursor(0, 0);
  lcd.print(currentText);

  for (;;) {
    int buttonValue = analogRead(A0);

    for(int i = 0; i <= sizeof(characters); i++) {
      if (characters[i] == currentText[curPosInLCD]) {
        curPosInArr = i;
        break;
      }
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
 
    if (buttonValue >= 910 && buttonValue <= 920) {
      curPosInArr++;
      if (curPosInArr > sizeof(characters)) {
        curPosInArr = 0;
      }
      currentText[curPosInArr] = characters[curPosInArr];
      lcd.print(currentText);
      Serial.println(currentText);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    if (buttonValue >= 840 && buttonValue <= 850) {
      curPosInArr--;
      if (curPosInArr < 0) {
        curPosInArr = sizeof(characters);
      }
      currentText[curPosInArr] = characters[curPosInArr];
      lcd.print(currentText);
      Serial.println(currentText);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    if (buttonValue >= 1 && buttonValue <= 5 && curPosInLCD > 0) {
      curPosInLCD--;
      lcd.setCursor(curPosInLCD, 0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    if (buttonValue >= 975 && buttonValue <= 980 && curPosInLCD < 16) {
      curPosInLCD++;
      lcd.setCursor(curPosInLCD, 0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    if (buttonValue >= 1020 && buttonValue <= 1025) {
      xTaskCreate(ChangeEditMode, "ChangeEditMode", 128, NULL, 3, NULL);
      vTaskDelete(NULL);
    }
  }
}

void LoopThroughArrayList(void *pvParameters) {
  arrPointer++;
  if (arrPointer >= (sizeof(testArrLog) / sizeof(testArrLog[0]))) {
    arrPointer = 0;
  }

  int nextPointer = arrPointer + 1;
  if (nextPointer >= (sizeof(testArrLog) / sizeof(testArrLog[0]))) {
    nextPointer = 0;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(testArrLog[arrPointer]);
  lcd.setCursor(0, 1);
  lcd.print(testArrLog[nextPointer]);

  vTaskDelete(NULL);
}

void DefaultLCD() {
  arrPointer = 0;
  lcd.clear();
  lcd.print(testArrLog[0]);
  lcd.setCursor(0, 1);
  lcd.print(testArrLog[1]);
}
