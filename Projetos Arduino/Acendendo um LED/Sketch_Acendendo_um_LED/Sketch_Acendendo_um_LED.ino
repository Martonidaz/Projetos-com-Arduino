void setup() {
  // DEfinição da porta nesse caso porta digital número 11 como função de saída
  pinMode(11, OUTPUT);
}

void loop() {
  // Chamada da função de escrita digitalWrite para acender o led como parÂmetro a sua porta e o seu estado
  digitalWrite(11, HIGH);
  //Atraso milisegundos como parâmetro a quantidade de milisegundos de um estado para o outro
  delay(1000);
  //Novamente a chamada a função digitalWrite mas dessa vez mudando o seu estado 
  digitalWrite(11, LOW);
  // Outra ves a chamada a função delay para que ocorra por completo o efeito de pisca-pisca
  delay(1000);
  
}
