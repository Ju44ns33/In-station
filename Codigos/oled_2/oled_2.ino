#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>

int valor=0;
int pinsensor=A1;
unsigned long tiempoSonido = 0;

Servo s;
dht DHT;
#define DHT11_PIN 2


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
void setup() {
  Serial.begin(9600);

  pinMode(5,OUTPUT);
  pinMode(pinsensor,INPUT);

  s.attach(3);


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.clearDisplay();
  
   s.write(70);

}


void loop()
 {
  
  valor=analogRead(pinsensor);

  Serial.print("Lluvia = ");
  Serial.println(valor);

   DHT.read11(DHT11_PIN);

  //TEMPERATURA//
  Serial.print("Temperatura = ");
  Serial.print(DHT.temperature);
  Serial.println(" C");



  //HUMEDAD RELATIVA//
  Serial.print("Humedad = ");
  Serial.print(DHT.humidity);
  Serial.println(" %");
  delay(1000);

  display.setCursor(0,0);             
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.println("Humedad");
  display.display();
  display.setCursor(0,30);           
  display.setTextSize(2);        
  display.setTextColor(SSD1306_WHITE);
  display.println(DHT.humidity);
  display.display();
   display.setCursor(64,22);            
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.println("%");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,2);             
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.println("Temper");
  display.display();
  display.setCursor(0,30);             
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.println(DHT.temperature);
  display.display();
  display.setCursor(64,22);             
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE); 
  display.println("C");
  display.display();
  delay(2000);
  display.clearDisplay();
  unsigned long tiempoActual = millis(); // Tiempo actual



  if (valor < 499) {
    if (tiempoActual - tiempoSonido >= 700) {
      tiempoSonido = tiempoActual; 
      if (tiempoSonido % 1400 < 700) {
        tone(4, 523, 1000);
      } else {
        tone(4, 0, 1000); 
        s.write(0);
      }
    }
  } else if (valor > 499) {
    tone(4, 0, 1000);
    s.write(70);
    
  }
  if (DHT.temperature < 34) {
   
   digitalWrite(5,HIGH);
  }
  else if (DHT.temperature > 34) {
    digitalWrite(5,LOW);
    
  }
}