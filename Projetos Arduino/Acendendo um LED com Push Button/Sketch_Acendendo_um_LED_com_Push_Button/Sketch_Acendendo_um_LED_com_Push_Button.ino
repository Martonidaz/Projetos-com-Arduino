int botao = 7;
int led = 11;
int status = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(botao,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  status = digitalRead(botao);
  if (status == HIGH){
    digitalWrite(led, HIGH);
    delay(100);
  }
  else{
    digitalWrite(led, LOW);
    //delay(100);
  }
}
