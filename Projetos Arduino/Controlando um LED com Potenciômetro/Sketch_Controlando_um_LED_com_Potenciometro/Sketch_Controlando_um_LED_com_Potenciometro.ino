int led = 11;
int pot = A5;
int valorPot = 0;//Variável responsável pelo armazenamento da leitura bruta do potenciometro
int pwm = 0;//Variável responsável pelo armazenamento do valor convertido pela função map

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);//Inicializa a serial com velocidade de comunicação de 9600.
}

void loop() {
  valorPot = analogRead(pot);
  pwm = map(valorPot, 0, 1023, 0, 255);//Função map() para converter a escala de 0 a 1023 para a escala de 0 a 255
  Serial.println(pwm);//Imprime valorpot na serial
  analogWrite(led, pwm);//Aciona o LED proporcionalmente à leitura analógica
  //delay(500);//Intervalo de 500 milissegundos
}
