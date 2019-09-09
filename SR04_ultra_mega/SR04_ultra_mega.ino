#define PIN_TRIG 12
#define PIN_ECO  13
 
void setup() {
  // Inicializacion de la comunicacion serial
  Serial.begin (9600);
  // Inicializacion de pines digitales
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT);
}
 
void loop() {
  long duracion, distancia;  // Variables
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;
  /* Imprimir resultados a la terminal serial */
  if (distancia >= 500 || distancia <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distancia);
    Serial.println(" cm");
  }  
  // Retardo para disminuir la frecuencia de las lecturas
  delay(500);  
}
