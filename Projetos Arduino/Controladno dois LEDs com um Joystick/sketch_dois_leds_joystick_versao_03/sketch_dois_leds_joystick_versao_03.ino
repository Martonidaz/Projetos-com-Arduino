int x = A5; // Pino do eixo X do joystick
int y = A4; // Pino do eixo Y do joystick
int botaoExterno = 3; // Pino do pushbutton externo
int ledVerde = 11; // LED Verde
int ledAmarelo = 10; // LED Amarelo

// Estados de travamento para os LEDs
bool travadoVerde = false;
bool travadoAmarelo = false;

// Intensidades para os LEDs
int intensidadeVerde = 0;
int intensidadeAmarelo = 0;

// Intensidades travadas
int intensidadeTravadaVerde = 0;
int intensidadeTravadaAmarelo = 0;

int estadoBotao = 0; // Estado cíclico do botão (0 = ambos destravados, 1 = verde travado, 2 = amarelo travado, 3 = ambos travados)
bool botaoPressionado = false;

void setup() {
  pinMode(ledVerde, OUTPUT); // Configura LED Verde como saída
  pinMode(ledAmarelo, OUTPUT); // Configura LED Amarelo como saída
  pinMode(botaoExterno, INPUT_PULLUP); // Configura o pushbutton externo com resistor pull-up interno
  Serial.begin(9600); // Inicializa comunicação serial

  // Garante que os LEDs iniciem apagados
  analogWrite(ledVerde, 0);
  analogWrite(ledAmarelo, 0);
}

void loop() {
  // Verifica se o pushbutton externo foi pressionado
  if (digitalRead(botaoExterno) == LOW) {
    if (!botaoPressionado) { // Evita múltiplas leituras do mesmo clique
      estadoBotao = (estadoBotao + 1) % 4; // Alterna entre 4 estados: 0, 1, 2, 3

      // Atualiza o estado de travamento com base no estado atual do botão
      switch (estadoBotao) {
        case 0: // Ambos os LEDs destravados
          travadoVerde = false;
          travadoAmarelo = false;
          Serial.println("Ambos os LEDs destravados.");
          break;
        case 1: // Apenas o LED Verde travado
          travadoVerde = true;
          intensidadeTravadaVerde = intensidadeVerde; // Salva intensidade do verde
          Serial.println("LED Verde TRAVADO.");
          break;
        case 2: // Apenas o LED Amarelo travado
          travadoAmarelo = true;
          intensidadeTravadaAmarelo = intensidadeAmarelo; // Salva intensidade do amarelo
          Serial.println("LED Amarelo TRAVADO.");
          break;
        case 3: // Ambos os LEDs travados
          travadoVerde = true;
          travadoAmarelo = true;
          Serial.println("Ambos os LEDs TRAVADOS.");
          break;
      }

      botaoPressionado = true; // Marca como pressionado
      delay(300); // Delay para evitar múltiplos cliques rápidos
    }
  } else {
    botaoPressionado = false; // Redefine o estado do botão
  }

  // Atualiza as intensidades dos LEDs se não estiverem travados
  if (!travadoVerde) {
    int leituraX = analogRead(x);
    intensidadeVerde = map(leituraX, 0, 1023, 255, 0); // Controla a intensidade do LED verde
  }

  if (!travadoAmarelo) {
    int leituraY = analogRead(y);
    intensidadeAmarelo = map(leituraY, 0, 1023, 255, 0); // Controla a intensidade do LED amarelo
  }

  // Define as intensidades aplicadas
  int intensidadeAtualVerde = travadoVerde ? intensidadeTravadaVerde : intensidadeVerde;
  int intensidadeAtualAmarelo = travadoAmarelo ? intensidadeTravadaAmarelo : intensidadeAmarelo;

  // Aplica as intensidades aos LEDs
  analogWrite(ledVerde, intensidadeAtualVerde);
  analogWrite(ledAmarelo, intensidadeAtualAmarelo);

  // Exibe valores no monitor serial
  Serial.print("Verde: ");
  Serial.print(intensidadeAtualVerde);
  Serial.print(" (");
  Serial.print(travadoVerde ? "TRAVADO" : "LIBERADO");
  Serial.print(") | Amarelo: ");
  Serial.print(intensidadeAtualAmarelo);
  Serial.print(" (");
  Serial.print(travadoAmarelo ? "TRAVADO" : "LIBERADO");
  Serial.println(")");

  delay(100); // Pausa para evitar leituras rápidas demais
}
