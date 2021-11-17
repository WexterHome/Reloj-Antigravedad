
#define DRV_1 6      //Primer pin de control del Electroimán
#define DRV_2 7      //Segundo pin de control del Electroimán
#define DRV_LEDS 5   //Pin de control de los LEDs

#define EXPO 600   // Tiempo en el que los leds estan encendidos (poner entre 400 y 600) 
#define PERIOD 5000 // El periodo de vibración
#define DEF_OFFSET -200 //Modificar este valor para cambiar de efecto [-250:250]

boolean flashState, motorState;
uint8_t valColor;
uint16_t flashDelay, lightTimer;
uint32_t lightPrev, motorPrev;

void setup() {
  pinMode(DRV_1, OUTPUT);
  pinMode(DRV_2, OUTPUT);
  pinMode(DRV_LEDS, OUTPUT);
  delay(500);
  bitWrite(PORTD, DRV_LEDS, 1);
  flashDelay = PERIOD * 2 + DEF_OFFSET;
  delay( 3000 ); 
}

void loop() {

  if (micros() - lightPrev >= lightTimer) {
    lightPrev = micros();
    flashState = !flashState;
    bitWrite(PORTD, DRV_LEDS, flashState);
    if (flashState) lightTimer = EXPO;
    else lightTimer = flashDelay - EXPO;
  }

  if (micros() - motorPrev >= PERIOD){
    motorPrev = micros();
    motorState = !motorState;
    bitWrite(PORTD, DRV_1, motorState);
    bitWrite(PORTD, DRV_2, !motorState);
  }
}
