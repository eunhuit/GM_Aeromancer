#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal.h>

// 설정값
#define DHTPIN 2        // DHT 센서 핀
#define DHTTYPE DHT22   // DHT22 사용

#define BMP_SDA 4        // BMP 센서 SDA 핀
#define BMP_SCL 5        // BMP 센서 SCL 핀

DHT_Unified dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;   // BMP280 센서 객체

// LCD 디스플레이 설정
LiquidCrystal lcd(12, 11, 6, 7, 8, 9);

void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600);

  // DHT 센서 초기화
  dht.begin();

  // BMP 센서 초기화
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // LCD 초기화
  lcd.begin(16, 2);

  // 화면에 초기 메시지 출력
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
}

void loop() {
  // 센서 데이터 읽기
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temperature = event.temperature;
  dht.humidity().getEvent(&event);
  float humidity = event.relative_humidity;

  float pressure = bmp.readPressure() / 100.0F; // 대기압 (hPa)로 변환

  // 결과 출력
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // LCD에 날씨 데이터 출력
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(5000); // 5초마다 측정
}
