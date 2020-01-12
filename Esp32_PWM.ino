///////////////////////////
/// Caracol Electronics ///
///////////////////////////
/// Ejemplo PWM con ESP32//
///////////////////////////

/* GPIO al cual iran asignados las señales PWM */
const int ledGPIO = 18; 
const int ledGPIO1 = 16;
const int ledGPIO2 = 17;

//propiedades señal PWM//////////
const int canalPWM = 0;
const int canalPWM1 = 1;
const int canalPWM2 = 2;// 0-15

const int frecuencia = 10000; // en Hz
const int resolucion = 8; // 8-16 bits de resolución.
/////////////////////////////////

void setup() 
{
  // 1) configura señal PWM
  ledcSetup(canalPWM, frecuencia, resolucion);
  ledcSetup(canalPWM1, frecuencia, resolucion);
  ledcSetup(canalPWM2, frecuencia, resolucion);

  // 2) asigna la señal creada al GPIO de su elección 
  ledcAttachPin(ledGPIO, canalPWM);
  ledcAttachPin(ledGPIO1, canalPWM1);
  ledcAttachPin(ledGPIO2, canalPWM2);

}

void loop() 
{
  // prendiendo
  int CT = 0; //ciclo de trabajo
  while(CT < 255)
  {
    ledcWrite(canalPWM, CT);
    delay(5);
    CT++;
  }
  CT = 0;
  while(CT < 255)
  {
    ledcWrite(canalPWM1, CT);
    delay(5);
    CT++;
  }
  CT = 0;
  while(CT < 255)
  {
    ledcWrite(canalPWM2, CT);
    delay(5);
    CT++;
  }
  
  
  
  
  /// apagando ! 
  CT = 255; //ciclo de trabajo
  while(CT > 0)
  {
    ledcWrite(canalPWM, CT);
    delay(5);
    CT--;
  }
  CT = 255;
  while(CT > 0)
  {
    ledcWrite(canalPWM1, CT);
    delay(5);
    CT--;
  }
  CT = 255;
  while(CT > 0)
  {
    ledcWrite(canalPWM2, CT);
    delay(5);
    CT--;
  }

  CT=0;
}
