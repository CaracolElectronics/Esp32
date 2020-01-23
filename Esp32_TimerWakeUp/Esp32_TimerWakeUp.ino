/*
 * Caracol Electronics 2020
 */
#define uS_a_S_FACTOR 1000000  /* x 1'000'000 para tener segundos */
#define TIME  6        /* Tiempo que duerme en Segundos */

RTC_DATA_ATTR int bootNum = 0;

void setup()
{
  Serial.begin(115200);
  delay(100);

  //incrementa cada vez que se depierta
  bootNum++;
  Serial.println("numero de boot: " + String(bootNum));

  // imprime razon pro la cual se despertó...
  print_porque_desperte(); 

  /*
    Lo primero es configurar las razones que lo despiertan
    le indicamos que se derpierte cada 6 segundos
  */
  esp_sleep_enable_timer_wakeup(TIME * uS_a_S_FACTOR); 
  Serial.println("Se configura para despertar en " + String(TIME) +
  " segundos");

 
  Serial.println("A dormir........................ ");
  Serial.flush(); 
  esp_deep_sleep_start();

  
  Serial.println("Esto nunca se imprime");
}

void loop()
{
  //El programa nunca llega hasta aqui
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
