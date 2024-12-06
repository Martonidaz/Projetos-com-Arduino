int x = A5; // Pino do eixo X do joystick
int y = A4; // Pino do eixo Y do joystick
int botao = 2; // Pino do botão
int ledVerde = 11; // LED Verde
int ledAmarelo = 10; // LED Amarelo

bool travado = false; // Estado inicial: LEDs liberados
int intensidadeVerde = 0; // Intensidade inicial do LED Verde
int intensidadeAmarelo = 0; // Intensidade inicial do LED Amarelo
bool botaoPressionado = false; // Estado para evitar múltiplas leituras do mesmo clique

void setup() {
  pinMode(ledVerde, OUTPUT); // Configura LED Verde como saída
  pinMode(ledAmarelo, OUTPUT); // Configura LED Amarelo como saída
  pinMode(botao, INPUT_PULLUP); // Configura botão com resistor pull-up interno
  Serial.begin(9600); // Inicializa comunicação serial

  // Garante que os LEDs iniciem apagados
  analogWrite(ledVerde, 0);
  analogWrite(ledAmarelo, 0);
}

void loop() {
  // Verifica se o botão foi pressionado
  if (digitalRead(botao) == LOW) { // Botão pressionado
    if (!botaoPressionado) { // Evita múltiplas leituras do mesmo clique
      travado = !travado; // Alterna entre travado e liberado
      botaoPressionado = true; // Marca como pressionado
      Serial.print("Estado: ");
      Serial.println(travado ? "Travado" : "Liberado");
    }
  } else {
    botaoPressionado = false; // Redefine o estado do botão
  }

  if (!travado) {
    // Lê os valores do joystick apenas se estiver liberado
    int leituraX = analogRead(x);
    int leituraY = analogRead(y);

    // Garante que leituras inválidas não afetem os LEDs
    if (leituraX >= 0 && leituraX <= 1023) {
      intensidadeVerde = map(leituraX, 0, 1023, 255, 0); // Eixo X controla LED Verde
    } else {
      intensidadeVerde = 0; // Apaga LED Verde se leitura for inválida
    }

    if (leituraY >= 0 && leituraY <= 1023) {
      intensidadeAmarelo = map(leituraY, 0, 1023, 255, 0); // Eixo Y controla LED Amarelo
    } else {
      intensidadeAmarelo = 0; // Apaga LED Amarelo se leitura for inválida
    }
  }

  // Aplica as intensidades aos LEDs
  analogWrite(ledVerde, intensidadeVerde);
  analogWrite(ledAmarelo, intensidadeAmarelo);

  // Exibe os valores no monitor serial para diagnóstico
  Serial.print("Eixo X (Verde): ");
  Serial.print(intensidadeVerde);
  Serial.print(" | Eixo Y (Amarelo): ");
  Serial.print(intensidadeAmarelo);
  Serial.print(" | Estado: ");
  Serial.println(travado ? "Travado" : "Liberado");

  delay(100); // Pequena pausa para evitar poluição no monitor serial
}
