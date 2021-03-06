/* ------------- MOVIMENTO PATAS VERSAO 2.4.3 -------------  
 *  Desenvolvedores: Daniel Lopes / Enrique Emanuel
 *  ETEC Martin Luther King
 *  Sao Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  enriqueemanuelcontato@gmail.com
 *  
 *  CORE HEXPOD: V2.431
 *  CONTROLE HEXPOD: V1.3
 *  
 *  =========Log de atualizacoes=============
 *  CONTEUDO NOVO:
 *  Trocados todas as variáveis do tipo int para uint8_t
 *  Definido o delayUM como 500ms
 *  Definido porta X para executar ligação da câmera
 * 
 * CONTEUDO MODIFICADO: 
 * 
 * CONTEUDO EXCLUIDO:
 * 
 * ============INFORMAÇÕES ÚTEIS=============
 * 
 *  
 * 
 * 
 * 
 * 
 * 
 * 
 */

boolean sync1 = 0;
boolean sync2 = 0;
boolean sync3 = 0;
boolean sync4 = 0;
boolean sync5 = 0;
boolean sync6 = 0;

#define luz 7
#define base 46  
#define delayUM 500
uint8_t delay2;
uint8_t delay3;
       
//Bibliotecas
#include <VirtualWire.h>
#include <VirtualWire_Config.h>

//Porta das Pontes H
  //Motor 1
  #define IN1  12
  #define IN2  11
  //Motor 2
  #define IN3  15
  #define IN4  16
  //Motor 3
  #define IN5  51
  #define IN6  53
  //Motor 4
  #define IN7  24
  #define IN8  26
  //Motor 5
  #define IN9  19
  #define IN10 18
  //Motor 6
  #define IN11 43
  #define IN12 41

//Porta dos Sensores
//sensorA = Motor 1
#define sensorA 13
//sensorB = Motor 2 
#define sensorB 14
//sensorC = Motor 3 
#define sensorC 52
//sensorD = Motor 4
#define sensorD 19
//sensorE = Motor 5
#define sensorE 21
//sensorF = Motor 6
#define sensorF 42

//Portas de modulos
#define pinRF  33 //Pino antena RF 433MHz
#define trigPin A0 //Pino TRIG do sensor no pino analógico A0
#define echoPin A1 //Pino ECHO do sensor no pino analógico A1

//Variaveis de controle
boolean LED = 0;
boolean CAMERA = 0;

struct tipoPacote {
  char valor1;
};

tipoPacote pacote; 
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

uint8_t TempoGirar = 1;//Tempo de giro autonomo
uint8_t distanciaObstaculo = 30; //Distancia para o robo identificar obstaculos 

  
//Declarando Funções que serão utilizadas:
void front_auto();
int  graus(int x);
void front();
void right();  
void left();
void back();
void parado(int l);
void controle();
void test();
void giro(int num_motor, char sentido);
int lerSonar();
int calcularDistanciaCentro();
int calcularDistanciaDireita();
int calcularDistanciaEsquerda();
char calculaMelhorDistancia();
void posicionaCarroMelhorCaminho();
void reposicionaServoSonar();
void rotacao_Parado();
void rotacao_Frente();
void rotacao_Re();
void rotacao_Direita();
void rotacao_Esquerda();
void test2();

//Variaveis  para o sensor ultrassonico
long duracao;
long distancia_cm=0;
uint8_t minimumRange=5; //tempo de resposta do sensor
uint8_t maximumRange=200;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(IN9, OUTPUT);
  pinMode(IN10, OUTPUT);
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(base, OUTPUT);  

  pinMode(sensorA, INPUT_PULLUP);
  pinMode(sensorB, INPUT_PULLUP);
  pinMode(sensorC, INPUT_PULLUP);
  pinMode(sensorD, INPUT_PULLUP);
  pinMode(sensorE, INPUT_PULLUP);
  pinMode(sensorF, INPUT_PULLUP);

// Declaração do pino do LED
  pinMode(luz, OUTPUT);

// Declaração do pino do Transistor
  pinMode(base, OUTPUT);

  pinMode(trigPin, OUTPUT); //define o pino TRIG como saida
  pinMode(echoPin, INPUT);  //define o pino ECHO como entrada 

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  vw_set_rx_pin(pinRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000);   
  vw_rx_start();
  
}

void loop() {
  controle();
}                   


void giro(int num_motor, char sentido){

  // p = Parado
  if (sentido == 'p'){
    if (num_motor == 1){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
    }
    
    if (num_motor == 2){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
    }
    
    if (num_motor == 3){
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, HIGH);
    }
    
    if (num_motor == 4){
      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, HIGH);
    }
    
    if (num_motor == 5){
      digitalWrite(IN9, HIGH);
      digitalWrite(IN10, HIGH);
    }
    
    if (num_motor == 6){
      digitalWrite(IN11, HIGH);
      digitalWrite(IN12, HIGH);
    }
  }
  
  // f = Giro para a Frente do robô
  if (sentido == 'f'){
  
    if (num_motor == 1){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    
    if (num_motor == 2){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    
    if (num_motor == 3){
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
    }
    
    if (num_motor == 4){
      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, LOW);
    }
    
    if (num_motor == 5){
      digitalWrite(IN9, HIGH);
      digitalWrite(IN10, LOW);
    }
    
    if (num_motor == 6){
      digitalWrite(IN11, LOW);
      digitalWrite(IN12, HIGH);
    }
  }
  
  // t = Giro para Trás do robô
  if (sentido == 't'){
  
    if (num_motor == 1){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    
    if (num_motor == 2){
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    
    if (num_motor == 3){
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);
    }
    
    if (num_motor == 4){
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);
    }
    
    if (num_motor == 5){
      digitalWrite(IN9, LOW);
      digitalWrite(IN10, HIGH);
    }
    
    if (num_motor == 6){
      digitalWrite(IN11, HIGH);
      digitalWrite(IN12, LOW);
    }
  }

}

void back(){
  
}

void controle(){

  if ( vw_have_message() ) {
   
    vw_get_message(buf, &buflen);
    memcpy(&pacote,&buf,buflen);
    
    switch (pacote.valor1) {
          case 'W':
            front();
          break;

          case 'S':
            for(int n=0; n<20; n++){ 
            front_auto();
            }
          break;
          
          case 'A':
            left();
          break;
  
          case 'D':
            right();
          break;
  
          case 'C':
            parado(0);
          break;
          
          case'G':
            LED = !LED;
            digitalWrite(luz, LED);
          break;

          case'B':
            CAMERA = !CAMERA;
            digitalWrite(base, CAMERA);
          break;
          
    } 
  } else {
      parado(3);
    } 

}


void front(){     //Funcao que faz o Hexpod andar para frente
  giro ( 1, 'f');
  giro ( 5, 'f');
  giro ( 3, 'f');
  delay(delayUM);
  parado(0);
  giro (2, 'f');
  giro (4, 'f');
  giro (6, 'f');
  delay(delayUM);
  parado(0);
}

void right(){
  giro (1, 'f');
  giro (3, 't');
  giro (5, 'f');
  delay(delayUM);
  for (int hj = 0; hj< 15; hj++){
  parado(1);
  sync6 = 0;
  sync5 = 0;
  sync4 = 0;
  sync3 = 0;
  sync2 = 0;
  sync1 = 0;
  }
  giro (4, 't');
  giro (2, 'f');
  giro (6, 'f');
  delay(delayUM);
  for (int hj = 0; hj< 15; hj++){
  parado(1);
  sync6 = 0;
  sync5 = 0;
  sync4 = 0;
  sync3 = 0;
  sync2 = 0;
  sync1 = 0;
  }
}

void left(){     //Funcao que faz o Hexpod andar para a esquerda
  //Giro do lado A
  giro (1, 't');
  giro (3, 'f');
  giro (5, 't');
  delay(delayUM);
  for (int hj = 0; hj< 15; hj++){
  parado(2);
  sync6 = 0;
  sync5 = 0;
  sync4 = 0;
  sync3 = 0;
  sync2 = 0;
  sync1 = 0;
  }
  giro (4, 'f');
  giro (2, 't');
  giro (6, 'f');
  delay(delayUM);
  for (int hj = 0; hj< 15; hj++){
  parado(2);
  sync6 = 0;
  sync5 = 0;
  sync4 = 0;
  sync3 = 0;
  sync2 = 0;
  sync1 = 0;
  }
}

void parado(int sentido){       //Funcao que sincroniza as patas no chao, recebe valor: sentido de rotacao, para sincronizar
  if(sentido == 0) {
    
  boolean ok = 0;
  syncLeg:
  for(int g = 0; g <20; g++){
    int pont = 0;
    if(digitalRead(sensorA) && sync1 == 0){
      giro ( 1, 'f');
      Serial.write("girando motor 1");
      pont--;
    }
    if(digitalRead(sensorB) && sync2 == 0){
      giro ( 2, 'f');
      Serial.write("girando motor 2");
      pont--;
    }
    if(digitalRead(sensorC) && sync3 == 0){
      giro ( 3, 'f');
      Serial.write("girando motor 3");
      pont--;
    }
    if(digitalRead(sensorD) && sync4 == 0){
      giro ( 4, 'f');
      Serial.write("girando motor 4");
      pont--;
    }
    if(digitalRead(sensorE) && sync5 == 0){
      giro ( 5, 'f');
      
      pont--;
    }
    if(digitalRead(sensorF) && sync6 == 0){
      giro ( 6, 'f');
      
      pont--;
    }
    
    delay(1);
    if(!digitalRead(sensorA)){
      giro ( 1, 'p');
      pont++;
      sync1 = 1;
    }
    if(!digitalRead(sensorB)){
      giro ( 2, 'p');      
      pont++;
      sync2 = 1;
    }
    if(!digitalRead(sensorC)){
      giro ( 3, 'p');
      pont++;      
      sync3 = 1;
    }
    if(!digitalRead(sensorD)){
      giro ( 4, 'p');      
      pont++;
      sync4 = 1;
    }
    if(!digitalRead(sensorE)){
      giro ( 5, 'p');      
      pont++;
      sync5 = 1;
    }

    if(!digitalRead(sensorF)){
      giro ( 6, 'p');      
      pont++;
      sync6 = 1;
    }
    delay(1);

    if(pont > 5){      
      giro ( 1, 'p');
      giro ( 2, 'p');
      giro ( 3, 'p');
      giro ( 4, 'p');
      giro ( 5, 'p');
      giro ( 6, 'p');
      ok = 1;
      break;
    }

    if(pont < 5){
      sync1 = 0;
      sync2 = 0;
      sync3 = 0;
      sync4 = 0;
      sync5 = 0;
      sync6 = 0;
      goto syncLeg;
    }
  }

  if(!ok) {
    goto syncLeg;
  }
  sync1 = 0;
  sync2 = 0;
  sync3 = 0;
  sync4 = 0;
  sync5 = 0;
  sync6 = 0;
 }
  
  //Sincronização do movimento para direita
  if(sentido == 1) {
  
  boolean ok = 0;
  int tries = 0;
  syncLegR:
  if(tries > 3){
    giro ( 1, 'f');
    giro ( 2, 'f');
    giro ( 3, 'f');
    giro ( 4, 'f');
    giro ( 5, 'f');
    giro ( 6, 'f');
  }
  for(int g = 0; g <20; g++){
    int pont = 0;
    if(digitalRead(sensorA) && sync1 == 0){
      giro ( 1, 'f');
      pont--;
    }
    if(digitalRead(sensorB) && sync2 == 0){
      giro ( 2, 'f');
      pont--;
    }
    if(digitalRead(sensorC) && sync3 == 0){
      giro ( 3, 't');     
      pont--;
    }
    if(digitalRead(sensorD) && sync4 == 0){
      giro ( 4, 't');
      pont--;
    }
    if(digitalRead(sensorE) && sync5 == 0){
      giro ( 5, 'f');
      pont--;
    }
    if(digitalRead(sensorF) && sync6 == 0){
      giro ( 6, 'f');
      pont--;
    }
    
    delay(1);
    if(!digitalRead(sensorA)){
      giro ( 1, 'p');
      pont++;
      sync1 = 1;
    }
    if(!digitalRead(sensorB)){
      giro ( 2, 'p');
      pont++;
      sync2 = 1;
    }
    if(!digitalRead(sensorC)){
      giro ( 3, 'p');
      pont++;
      sync3 = 1;
    }
    if(!digitalRead(sensorD)){
      giro ( 4, 'p');
      pont++;
      sync4 = 1;
    }
    if(!digitalRead(sensorE)){
      giro ( 5, 'p');
      pont++;
      sync5 = 1;
    }
    if(!digitalRead(sensorF)){
      giro ( 6, 'p');
      pont++;
      sync6 = 1;
    }
    delay(1);
    if(pont >= 5){
      giro ( 1, 'p');
      giro ( 2, 'p');
      giro ( 3, 'p');
      giro ( 4, 'p');
      giro ( 5, 'p');
      giro ( 6, 'p');
      ok = 1;
      break;
    }
    if(pont < 5){
      sync1 = 0;
      sync2 = 0;
      sync3 = 0;
      sync4 = 0;
      sync5 = 0;
      sync6 = 0;
      goto syncLegR;
    }
  }
  if(!ok) {
    goto syncLegR;
  }
  sync1 = 0;
  sync2 = 0;
  sync3 = 0;
  sync4 = 0;
  sync5 = 0;
  sync6 = 0;
 }

  //Sincronização do movimento para esquerda
  if(sentido == 2) {
  boolean ok = 0;
  syncLegL:
  for(int g = 0; g <20; g++){
    int pont = 0;
    if(digitalRead(sensorA) && sync1 == 0){
      giro ( 1, 't');
      
      pont--;
    }
    if(digitalRead(sensorB) && sync2 == 0){
      giro ( 2, 't');
      
      pont--;
    }
    if(digitalRead(sensorC) && sync3 == 0){
      giro ( 3, 'f');
      
      pont--;
    }
    if(digitalRead(sensorD) && sync4 == 0){
      giro ( 4, 'f');
      
      pont--;
    }
    if(digitalRead(sensorE) && sync5 == 0){
      giro ( 5, 't');
      
      pont--;
    }
    if(digitalRead(sensorF) && sync6 == 0){
      giro ( 6, 't');
      
      pont--;
    }
    
    delay(1);
    if(!digitalRead(sensorA)){
      giro ( 1, 'p');
      Serial.println(g);
      pont++;
      sync1 = 1;
    }
    if(!digitalRead(sensorB)){
      giro ( 2, 'p');
      Serial.println(g);
      pont++;
      sync2 = 1;
    }
    if(!digitalRead(sensorC)){
      giro ( 3, 'p');
      pont++;
      Serial.println(g);
      sync3 = 1;
    }
    if(!digitalRead(sensorD)){
      giro ( 4, 'p');
      Serial.println(g);
      pont++;
      sync4 = 1;
    }
    if(!digitalRead(sensorE)){
      giro ( 5, 'p');
      Serial.println(g);
      pont++;
      sync5 = 1;
    }
    if(!digitalRead(sensorF)){
      giro ( 6, 'p');
      Serial.println(g);
      pont++;
      sync6 = 1;
    }
    delay(1);
    if(pont >= 5){
      Serial.println("OK!");
      giro ( 1, 'p');
      giro ( 2, 'p');
      giro ( 3, 'p');
      giro ( 4, 'p');
      giro ( 5, 'p');
      giro ( 6, 'p');
      ok = 1;
      break;
    }
    if(pont < 5){
      sync1 = 0;
      sync2 = 0;
      sync3 = 0;
      sync4 = 0;
      sync5 = 0;
      sync6 = 0;
      goto syncLegL;
    }
  }
  if(!ok) {
    goto syncLegL;
  }
  sync1 = 0;
  sync2 = 0;
  sync3 = 0;
  sync4 = 0;
  sync5 = 0;
  sync6 = 0;
 
 }
  
  if(sentido == 3) {
    
  boolean ok = 0;
  syncLegP:
  for(int g = 0; g <20; g++){
    int pont = 0;
    if(digitalRead(sensorA) && sync1 == 0){
      giro ( 1, 't');
      pont--;
    }
    if(digitalRead(sensorB) && sync2 == 0){
      giro ( 2, 'f');
      
      pont--;
    }
    if(digitalRead(sensorC) && sync3 == 0){
      giro ( 3, 't');
      
      pont--;
    }
    if(digitalRead(sensorD) && sync4 == 0){
      giro ( 4, 'f');
      
      pont--;
    }
    if(digitalRead(sensorE) && sync5 == 0){
      giro ( 5, 't');
      
      pont--;
    }
    if(digitalRead(sensorF) && sync6 == 0){
      giro ( 6, 'f');
      
      pont--;
    }
    
    delay(1);
    if(!digitalRead(sensorA)){
      giro ( 1, 'p');
      
      pont++;
      sync1 = 1;
    }
    if(!digitalRead(sensorB)){
      giro ( 2, 'p');
      
      pont++;
      sync2 = 1;
    }
    if(!digitalRead(sensorC)){
       giro ( 3, 'p');
      pont++;
      
      sync3 = 1;
    }
    if(!digitalRead(sensorD)){
      giro ( 4, 'p');
      
      pont++;
      sync4 = 1;
    }
    if(!digitalRead(sensorE)){
      giro ( 5, 'p');
      
      pont++;
      sync5 = 1;
    }
    if(!digitalRead(sensorF)){
      giro ( 6, 'p');
      
      pont++;
      sync6 = 1;
    }
    delay(1);
    if(pont > 5){
      
      giro ( 1, 'p');
      giro ( 2, 'p');
      giro ( 3, 'p');
      giro ( 4, 'p');
      giro ( 5, 'p');
      giro ( 6, 'p');
      ok = 1;
      break;
    }
    if(pont < 5){
      sync1 = 0;
      sync2 = 0;
      sync3 = 0;
      sync4 = 0;
      sync5 = 0;
      sync6 = 0;
      goto syncLegP;
    }
  }
  if(!ok) {
    goto syncLegP;
  }
  sync1 = 0;
  sync2 = 0;
  sync3 = 0;
  sync4 = 0;
  sync5 = 0;
  sync6 = 0;
 }

}

void front_auto(){

  int distancia = lerSonar(); // Ler o sensor de distancia  
    if (distancia > distanciaObstaculo) {  // Se a distancia for maior que 20 cm  
      rotacao_Frente(); //robo anda para frente   
    } else {   
    rotacao_Parado();  //para o robo  
    posicionaCarroMelhorCaminho(); //calcula o melhor caminho    
    front_auto();    
    }

}

// Funcao para ler e calcular a distancia do sensor ultrassonico    
int lerSonar(){    
  digitalWrite(trigPin, LOW); //nao envia som
    delayMicroseconds(2);
  digitalWrite(trigPin,HIGH); //envia som 
    delayMicroseconds(10);
  digitalWrite(trigPin,LOW); //nao envia o som e espera o retorno do som enviado
      duracao = pulseIn(echoPin,HIGH); //Captura a duracao em tempo do retorno do som.
      distancia_cm = duracao/56; //Calcula a distancia
  delay(30);  
return distancia_cm;             // Retorna a distancia  
}
   
// Funcao para calcular a distancia do centro    
int calcularDistanciaCentro(){    
  parado(0);    
    delay(20);   
  int leituraDoSonar = lerSonar();// Ler sensor de distância  
    delay(500);   
  leituraDoSonar = lerSonar();   
    delay(500);   
return leituraDoSonar;// Retorna a distancia  
}
    
// Funcao para calcular a distancia da direita    
int calcularDistanciaDireita(){    
  right();   
   delay(200);  
  int leituraDoSonar = lerSonar();   
    delay(500);   
  leituraDoSonar = lerSonar();   
    delay(500);   
return leituraDoSonar;    
}
    
// Funcao para calcular a distancia da esquerda    
int calcularDistanciaEsquerda(){    
  left();   
    delay(200);  
  int leituraDoSonar = lerSonar();   
    delay(500);   
  leituraDoSonar = lerSonar();   
    delay(500);   
return leituraDoSonar;    
}
    
// Funcao para captar as distancias lidas e calcular a melhor distancia    
char calculaMelhorDistancia(){    
  int esquerda = calcularDistanciaEsquerda();    
  int centro = calcularDistanciaCentro();    
  int direita = calcularDistanciaDireita();    
    reposicionaServoSonar();    
  int maiorDistancia = 0;   
  char melhorDistancia = '0';     
    if (centro > direita && centro > esquerda){    
      melhorDistancia = 'c';    
      maiorDistancia = centro;    
    }else   
    if (direita > centro && direita > esquerda){    
      melhorDistancia = 'd';    
      maiorDistancia = direita;    
    }else  
    if (esquerda > centro && esquerda > direita){    
      melhorDistancia = 'e';    
      maiorDistancia = esquerda;    
    }    
    if (maiorDistancia <= distanciaObstaculo) { //distancia limite para parar o robo   
      rotacao_Re();    
      posicionaCarroMelhorCaminho();    
    }    
    reposicionaServoSonar();  
return melhorDistancia;    
} 
   
// Funcao para colocar o carrinho na melhor distancia    
void posicionaCarroMelhorCaminho(){    
  char melhorDist = calculaMelhorDistancia();     
  if (melhorDist == 'c'){    
    front_auto();    
  }else if (melhorDist == 'd'){    
    rotacao_Direita();    
  }else if (melhorDist == 'e'){    
    rotacao_Esquerda();     
  }else{    
    rotacao_Re();    
  }    
  reposicionaServoSonar();    
} 
   
// Funcao para deixar o sensor do robo no centro    
void reposicionaServoSonar(){
  parado(0);   
  delay(200);   
}    

// Funcao para fazer o robo parar    
void rotacao_Parado(){    
  parado(0); 
}    

// Funcao para fazer o robo andar para frente    
void rotacao_Frente(){    
  front();    
}    

// Funcao que faz o robo andar para tras    
void rotacao_Re(){
    back();
}    
    
void rotacao_Direita(){
  right();    
}    
// Função que faz o robô virar à esquerda    
void rotacao_Esquerda(){    
  left();
} 
