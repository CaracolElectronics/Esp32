/*
 * Caracol Electronics 2020
 */

#define Sensibilidad 40 /* Entre más grande el valor, más sensible */
RTC_DATA_ATTR int bootNum = 0;
touch_pad_t touchPin;

void setup()
{
  Serial.begin(115200);
  delay(10);

  //incrementa cada vez que se depierta
  bootNum++;
  Serial.println("numero de boot: " + String(bootNum));

  // imprime razon pro la cual se despertó...
  print_porque_desperte();
  print_quePin(); 
   
  Serial.println("Se configura para despertar con el touchPad ");
  touchAttachInterrupt(T3, callbackT3, Sensibilidad);
  esp_sleep_enable_touchpad_wakeup();

 
  Serial.println("A dormir........................ ");
  Serial.flush(); 
  esp_deep_sleep_start();
  
  
  Serial.println("Esto nunca se imprime");
}

void loop()
{
  //El programa nunca llega hasta aqui
}

void callbackT3()
{
  
}
void print_porque_desperte()
{
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Me desperte por una senal externa usando RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Me desperte por una senal externa usando RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Me desperte por el timer!"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Me desperte por el touchpad"); break;   
  }
}

void print_quePin()
{
  touchPin = esp_sleep_get_touchpad_wakeup_status();

  switch(touchPin)
  {
    case 0  : Serial.println("Contacto en el GPIO 4"); break;
    case 1  : Serial.println("Contacto en el GPIO 0"); break;
    case 2  : Serial.println("Contacto en el GPIO 2"); break;
    case 3  : Serial.println("Contacto en el GPIO 15"); break;
    case 4  : Serial.println("Contacto en el GPIO 13"); break;
    case 5  : Serial.println("Contacto en el GPIO 12"); break;
    case 6  : Serial.println("Contacto en el GPIO 14"); break;
    case 7  : Serial.println("Contacto en el GPIO 27"); break;
    case 8  : Serial.println("Contacto en el GPIO 33"); break;
    case 9  : Serial.println("Contacto en el GPIO 32"); break;
  }
}
