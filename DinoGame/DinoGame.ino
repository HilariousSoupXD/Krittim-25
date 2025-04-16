#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_PIN 2
#define BUZZER_PIN 10

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int dinoPos = 1;  
int obstaclePos = 15;  
int score = 0;
bool isJumping = false;

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(" Dino Jump Game ");
    delay(2000);
    lcd.clear();
    updateLCD();
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW && !isJumping) {  
        isJumping = true;
        dinoPos = 0;  
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
    }

    moveObstacle();
    checkCollision();
    updateLCD();

    if (isJumping) {
        delay(500);
        dinoPos = 1;  
        isJumping = false;
    }

    delay(400);
}

void moveObstacle() {
    obstaclePos--;
    if (obstaclePos < 0) {
        obstaclePos = 15;  
        score++;
    }
}

void checkCollision() {
    if (obstaclePos == 1 && dinoPos == 1) {  
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("GAME OVER!");
        lcd.setCursor(4, 1);
        lcd.print("Score: ");
        lcd.print(score);
        while (true);  
    }
}

void updateLCD() {
    lcd.clear();
    lcd.setCursor(0, dinoPos);
    lcd.print("D"); 
    lcd.setCursor(obstaclePos, 1);
    lcd.print("#");  
    lcd.setCursor(10, 0);
    lcd.print("Score: ");
    lcd.print(score);
}
