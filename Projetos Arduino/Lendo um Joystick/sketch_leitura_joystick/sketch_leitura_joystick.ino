int x = A5;
int y = A4;
int botao = 2;

void setup() {
  pinMode(botao, INPUT_PULLUP); // Configura botão com resistor pull-up interno
  Serial.begin(9600);          // Inicializa comunicação serial
}

void loop() {
  // Lê os valores dos eixos X e Y
  int leituraX = analogRead(x);
  int leituraY = analogRead(y);

  // Lê o estado do botão
  int estadoBotao = digitalRead(botao);

  // Exibe os valores no monitor serial
  Serial.print("Eixo X: ");
  Serial.print(leituraX);
  Serial.print(" | Eixo Y: ");
  Serial.print(leituraY);
  Serial.print(" | Botão: ");
  Serial.println(estadoBotao);

  delay(500); // Pausa para leitura
}
