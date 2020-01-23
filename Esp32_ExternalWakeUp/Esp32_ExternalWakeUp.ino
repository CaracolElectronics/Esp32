
#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex

RTC_DATA_ATTR int bootNum = 0;

void setup(){
  Serial.begin(115200);
  delay(10);
  
  //incrementa cada vez que se depierta
  bootNum++;
  Serial.println("numero de boot: " + String(bootNum));

  // imprime razon pro la cual se despertó...
  print_porque_desperte(); 

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low

  //EXT1 ESP_EXT1_WAKEUP_ANY_HIGH or ESP_EXT1_WAKEUP_ALL_LOW
  
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);

  Serial.println("A dormir........................ ");
  Serial.flush(); 
  esp_deep_sleep_start();

  Serial.println("Esto nunca se imprime");
}

void loop(){
  //This is not going to be called
}
///////////////////////////////////////////
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
