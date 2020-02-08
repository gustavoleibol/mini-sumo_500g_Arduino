#define IN1 11 //blue
#define IN2 10 //blue
#define IN3 9 //white
#define IN4 8 //white
#define ENA 6//enable A //green
#define ENB 5//enable B //green
#define SOC 4//sensor de obstaculo central //yellow
#define SOE 3//sensor de obstaculo esquerdo //yellow
#define SOD 2//sensor de obstaculo direito //yellow
int SLE = A0;//sensor de linha esquerdo//pink
int SLD = A1;//sensor de linha direito/pink
#define Line 700//branca < 700 e preta > 700
#define VelocidadeB 160//pwm(pulse width modulation)
#define VelocidadeN 200//pwm(pulse width modulation)
#define VelocidadeA 255///pwm(pulse width modulation)
#define TempoCurva 300 //milisegundos

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(SOC, INPUT_PULLUP);
  pinMode(SOE, INPUT_PULLUP);
  pinMode(SOD, INPUT_PULLUP);
  pinMode(SLE, INPUT);
  pinMode(SLD, INPUT);
  Serial.begin(115200);//inicio da comunicação Serial
  delay(5000);//regra da competição
}
void loop() {
  //se detectar no central e nada nos outros sensores, ele avanca normal
  if(digitalRead(SOC) == 0 && digitalRead(SOD) == 1 && digitalRead(SOE) == 1 && analogRead(SLD) > Line && analogRead(SLE) > Line){
    avancarFrenteNormal();
  }
  //se detectar os dois sensores de linha e nada nos outros sensores, faz a curva
  else if(analogRead(SLD) < Line && analogRead(SLE) < Line){
    avancarEsquerda();
    delay(TempoCurva);
  }
  //se o sensor da esquerda é detectado
  else if(digitalRead(SOE)== 0 && digitalRead(SOC) == 1 && digitalRead(SOD) == 1 && analogRead(SLD) > Line && analogRead(SLE) > Line){
    while(digitalRead(SOC)== 0){//inicia uma repetição de busca que é parada quando detectar o sensor central
      avancarDireita();
    }
  }
  //se o sensor da direita é detectado
  else if(digitalRead(SOD) == 0 && digitalRead(SOC) == 1 && digitalRead(SOD) == 1 && analogRead(SLD) > Line && analogRead(SLE) > Line){
    while(digitalRead(SOC) == 0){//inicia uma repetição de busca que é parada quando detectar o sensor central
      avancarEsquerda();
    }
  }
  //se detectar o sensor de linha direito
  else if(analogRead(SLD) < Line){
      avancarDireita();//irá fazer uma curva para esquerda
      delay(TempoCurva);
  }
  //se detectar o sensor de linha esquerdo
  else if(analogRead(SLE) < Line){
      avancarEsquerda();//irá fazer uma curva para direita
      delay(TempoCurva);
  }
  else{
    avancarFrenteLento();
  }
}
void controlarMotor(int enable, boolean rotacao, int velocidade, int in1, int in2){
  if(rotacao == true){//--frente
    analogWrite(enable, velocidade);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  if(rotacao == false){//--Trás
    analogWrite(enable, velocidade);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}
void travaMotor(int in1, int in2){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
}
void avancarFrenteLento(){
  controlarMotor(ENA,true,VelocidadeB,IN1,IN2);
  controlarMotor(ENB,true,VelocidadeB,IN3,IN4);
}
void avancarFrenteNormal(){
  controlarMotor(ENA,true,VelocidadeN,IN1,IN2);
  controlarMotor(ENB,true,VelocidadeN,IN3,IN4);
}
void avancarFrenteTurbo(){
  controlarMotor(ENA,true,VelocidadeA,IN1,IN2);
  controlarMotor(ENB,true,VelocidadeA,IN3,IN4);
}
void avancarEsquerda(){
  travaMotor(IN3, IN4);
  controlarMotor(ENA,true,VelocidadeN,IN1,IN2);
}
void avancarDireita(){
  travaMotor(IN1, IN2);
  controlarMotor(ENB,true,VelocidadeN,IN3,IN4);
}
