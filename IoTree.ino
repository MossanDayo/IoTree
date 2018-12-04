#include <Adafruit_NeoPixel.h>

#define LED_COUNT ( 120 )
#define DIGITAL_PIN ( 6 )
#define BUTTON ( 2 )

Adafruit_NeoPixel led = Adafruit_NeoPixel( LED_COUNT,DIGITAL_PIN , NEO_GRB + NEO_KHZ800);


void setup() {
  //初期化処理
  led.begin();
  led.show();
  pinMode(BUTTON, INPUT);
}

void loop() {
  int state = 1;

  switch (state) {
    case 1:
      if (show_1() == true) state++;
      break;
    default:
      break;
  }
}

boolean show_1(){
  for (int i = 0 ; i < LED_COUNT ; i++ ) {
    led.setPixelColor(i-1,led.Color(0,0,0));
    led.setPixelColor(i,led.Color(255,0,0));
    led.show();
    delay(40);

    if (digitalRead(BUTTON) == HIGH) {
      while (digitalRead(BUTTON) == HIGH) {}
      return true;  
    }
  }
  return false;
}
