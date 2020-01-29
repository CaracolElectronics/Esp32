/*
 * Caracol Electronics 2020
 */
bool bandera = true;

TaskHandle_t Tarea1;
const int led1 = 16;
const int led2 = 27;

void setup()
{
  Serial.begin(115200);
  Serial.print("Setup() se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);

  xTaskCreatePinnedToCore(
      loop_tarea1, /* Funcion de la tarea1 */
      "Tarea1", /* Nombre de la tarea */
      10000,  /* Tamaño de la pila */
      NULL,  /* Parametros de entrada */
      0,  /* Prioridad de la tarea */
      &Tarea1,  /* objeto TaskHandle_t. */
      0); /* Nucleo donde se correra */

}

void loop()
{
  if(bandera)
  {
    Serial.print("Loop() se corre en el nucleo: ");
    Serial.println(xPortGetCoreID());
    bandera = false;
  }
  digitalWrite(led2,HIGH);
  delay(400);
  digitalWrite(led2,LOW);
  delay(400);

}
//////////////////////loop() nucleo0
void loop_tarea1(void * pvParameters)
{
  Serial.print("Tarea1 se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
  while(1)
  {
    digitalWrite(led1,HIGH);
    delay(1000);
    digitalWrite(led1,LOW);
    delay(1000);
  }
}
