int eixo_X = A0; //PINO REFERENTE A LIGAÇÃO DO EIXO X
int eixo_Y = A1; //PINO REFERENTE A LIGAÇÃO DO EIXO Y
int botao = 2; //PINO REFERENTE A LIGAÇÃO NO PINO KEY (EIXO Z)
int pinoR = 11; //PINO DIGITAL EM QUE O TERMINAL 'R' ESTÁ CONECTADO
int pinoG = 10; //PINO DIGITAL EM QUE O TERMINAL 'G' ESTÁ CONECTADO
int pinoB = 9; //PINO DIGITAL EM QUE O TERMINAL 'B' ESTÁ CONECTADO

//COMENTE A LINHA ABAIXO SE O LED RGB QUE ESTÁ UTILIZANDO É CATODO COMUM
#define COMMON_ANODE 

void setup()
{
  pinMode (botao, INPUT_PULLUP); //DEFINE A PORTA COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  Serial.begin (9600); //INICIALIZA O MONITOR SERIAL
  pinMode(pinoR, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoG, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoB, OUTPUT); //DEFINE O PINO COMO SAÍDA 
}
void loop()
{

    if((analogRead(eixo_X)) == 1023)
    { //SE LEITURA FOR IGUAL A 0, FAZ
        Serial.println("PARA CIMA"); //IMPRIME O TEXTO NO MONITOR SERIAL
        setColor(255, 0, 0); //PARÂMETROS PARA PRODUZIR A COR VERMELHA
    }
    else
    {
          if((analogRead(eixo_X)) == 0)
          { //SE LEITURA FOR IGUAL A 1023, FAZ
              Serial.println("PARA BAIXO"); //IMPRIME O TEXTO NO MONITOR SERIAL
              setColor(0, 255, 0); //PARÂMETROS PARA PRODUZIR A COR VERDE
          }
          else
          {
                if((analogRead(eixo_Y)) == 1023)
                { //SE LEITURA FOR IGUAL A 0, FAZ
                  Serial.println("DIREITA"); //IMPRIME O TEXTO NO MONITOR SERIAL
                   setColor(0, 0, 255); //PARÂMETROS PARA PRODUZIR A COR AZUL
                }
                else
                {
                      if((analogRead(eixo_Y)) == 0)
                      { //SE LEITURA FOR IGUAL A 1023, FAZ
                          Serial.println("ESQUERDA"); //IMPRIME O TEXTO NO MONITOR SERIAL
                           setColor(80, 0, 80); //PARÂMETROS PARA PRODUZIR A COR VIOLETA
                      }
                      else
                      {
                            if(digitalRead(botao) == LOW)
                            { //SE LEITURA FOR IGUAL A HIGH, FAZ
                               Serial.println("BOTAO PRESSIONADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
                               setColor(255, 255, 255); //PARÂMETROS PARA PRODUZIR A COR BRANCA        }  
                            }
                      }
                }
          }
      }
} 
//FUNÇÃO QUE PRODUZ O BRILHO DE CADA UM DOS LEDS DE ACORDO COM OS PARÂMETROS INFORMADOS
void setColor(int vermelho, int verde, int azul)
{  
  #ifdef COMMON_ANODE //SE O LED RGB FOR DEFINIDO COMO ANODO COMUM, FAZ
    vermelho = 255 - vermelho; //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (vermelho) INFORMADO' NA CHAMADA DA FUNÇÃO
    verde = 255 - verde; //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (verde) INFORMADO' NA CHAMADA DA FUNÇÃO
    azul = 255 - azul; //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (azul) INFORMADO' NA CHAMADA DA FUNÇÃO
  #endif
  analogWrite(pinoR, vermelho); //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'vermelho'
  analogWrite(pinoG, verde); //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'verde'
  analogWrite(pinoB, azul); //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'azul'
}