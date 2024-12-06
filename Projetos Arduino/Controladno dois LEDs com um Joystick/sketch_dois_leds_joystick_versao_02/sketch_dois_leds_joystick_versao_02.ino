int x = A5; // Pino do eixo X do joystick
int y = A4; // Pino do eixo Y do joystick
int botao = 2; // Pino do botão principal
int botaoTrava = 3; // Novo botão para travar/destravar intensidade
int ledVerde = 11; // LED Verde
int ledAmarelo = 10; // LED Amarelo

bool travado = false; // Estado geral: travado ou liberado
bool intensidadeTravada = false; // Estado: intensidade travada ou liberada
int intensidadeVerde = 0; // Intensidade inicial do LED Verde
int intensidadeAmarelo = 0; // Intensidade inicial do LED Amarelo
int intensidadeTravadaVerde = 0; // Armazena a intensidade travada do LED Verde
int intensidadeTravadaAmarelo = 0; // Armazena a intensidade travada do LED Amarelo
bool botaoPressionado = false; // Estado do botão principal
bool botaoTravaPressionado = false; // Estado do botão de travar

void setup() {
  pinMode(ledVerde, OUTPUT); // Configura LED Verde como saída
  pinMode(ledAmarelo, OUTPUT); // Configura LED Amarelo como saída
  pinMode(botao, INPUT_PULLUP); // Configura botão principal com resistor pull-up interno
  pinMode(botaoTrava, INPUT_PULLUP); // Configura botão de travar com resistor pull-up interno
  Serial.begin(9600); // Inicializa comunicação serial

  // Garante que os LEDs iniciem apagados
  analogWrite(ledVerde, 0);
  analogWrite(ledAmarelo, 0);
}

void loop() {
  // Verifica se o botão de travar/destravar foi pressionado
  if (digitalRead(botaoTrava) == LOW) {
    if (!botaoTravaPressionado) { // Evita múltiplas leituras do mesmo clique
      intensidadeTravada = !intensidadeTravada; // Alterna o estado de travar/destravar

      if (intensidadeTravada) {
        // Salva as intensidades atuais ao travar
        intensidadeTravadaVerde = intensidadeVerde;
        intensidadeTravadaAmarelo = intensidadeAmarelo;
        Serial.println("Intensidades TRAVADAS.");
      } else {
        Serial.println("Intensidades LIBERADAS.");
      }

      botaoTravaPressionado = true; // Marca como pressionado
    }
  } else {
    botaoTravaPressionado = false; // Redefine o estado do botão de travar
  }

  // Verifica se o botão principal foi pressionado
  if (digitalRead(botao) == LOW) {
    if (!botaoPressionado) {
      travado = !travado; // Alterna entre travado e liberado
      botaoPressionado = true; // Marca como pressionado
      Serial.print("Estado geral: ");
      Serial.println(travado ? "Travado" : "Liberado");
    }
  } else {
    botaoPressionado = false; // Redefine o estado do botão principal
  }

  if (!travado && !intensidadeTravada) {
    // Lê os valores do joystick apenas se estiver liberado e não travado
    int leituraX = analogRead(x);
    int leituraY = analogRead(y);

    // Valida leituras para evitar ruído
    if (leituraX >= 0 && leituraX <= 1023) {
      intensidadeVerde = map(leituraX, 0, 1023, 255, 0); // Eixo X controla LED Verde
    } else {
      intensidadeVerde = 0;
    }

    if (leituraY >= 0 && leituraY <= 1023) {
      intensidadeAmarelo = map(leituraY, 0, 1023, 255, 0); // Eixo Y controla LED Amarelo
    } else {
      intensidadeAmarelo = 0;
    }
  }

  // Define as intensidades a serem aplicadas
  int intensidadeAtualVerde = intensidadeTravada ? intensidadeTravadaVerde : intensidadeVerde;
  int intensidadeAtualAmarelo = intensidadeTravada ? intensidadeTravadaAmarelo : intensidadeAmarelo;

  // Aplica as intensidades aos LEDs
  analogWrite(ledVerde, intensidadeAtualVerde);
  analogWrite(ledAmarelo, intensidadeAtualAmarelo);

  // Exibe valores no monitor serial
  Serial.print("Eixo X (Verde): ");
  Serial.print(intensidadeVerde);
  Serial.print(" | Eixo Y (Amarelo): ");
  Serial.print(intensidadeAmarelo);
  Serial.print(" | Estado geral: ");
  Serial.print(travado ? "Travado" : "Liberado");
  Serial.print(" | Intensidade: ");
  Serial.println(intensidadeTravada ? "Travada" : "Liberada");

  delay(100); // Pequena pausa para evitar poluição no monitor serial
}
