/* ------------- MOVIMENTO PATAS VERSAO 2.3.6 ------------- 
 *  Desenvolvedores: Daniel Lopes / Enrique Emanuel
 *  ETEC Martin Luther King
 *  Sao Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  enriqueemanuelcontato@gmail.com
 *  
 *  CORE HEXPOD: V2.35
 *  CONTROLE HEXPOD: V1.3
 *  
 *  =========Log de atualizacoes=============
 *  CONTEUDO NOVO:
 *  - Portas Ponte H
 * CONTEUDO MODIFICADO: 
 * - Controle dos servos trocado pela Ponte H
 * CONTEUDO EXCLUIDO:
 * - Qualquer coisa envolvida com os servos
 * 
 */
//Bibliotecas
#include <VirtualWire.h>
#include <VirtualWire_Config.h>

//Porta das Pontes H
  //Motor 1
  #define IN1  22
  #define IN2  23
  //Motor 2
  #define IN3  24
  #define IN4  25
  //Motor 3
  #define IN5  26
  #define IN6  27
  //Motor 4
  #define IN7  28
  #define IN8  29
  //Motor 5
  #define IN9  30
  #define IN10 31
  //Motor 6
  #define IN11 32
  #define IN12 33
//Porta dos Sensores
uint8_t motores[6] = {2, 3, 4, 5, 6, 7 }; //array que define os pinos dos motores
#define sensorA 2
#define sensorB 3
#define sensorC 4
#define sensorD 5
#define sensorE 6
#define sensorF 7
#define pinRF  12
boolean LED = 0;
boolean CAMERA = 0;
struct tipoPacote {
  char valor1;
};
tipoPacote pacote; 
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

//Delays para movimento das patas
  #define delay1 650 //Delay para iniciar o lado B
  #define delay2 100 //Delay para parar o lado A
  
//Declarando Funções que serão utilizadas:
void front_auto();
int  graus(int x);
void front();
void right();  
void left();
void parado();
void controle();
void test();

void setup() {

  for(int i = 22; i<34; i++) pinMode(i , OUTPUT);//Portas para controlar Ponte H
  for(int i = 0; i<7; i++) pinMode(motores[i] , INPUT_PULLUP); //Portas 2 - 8 como entradas com resistor Pullup
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  vw_set_rx_pin(pinRF);
  vw_setup(2000);   
  vw_rx_start();
  
}

void loop() {
  controle();
}

void controle(){
  if (vw_have_message()){
   vw_get_message(buf, &buflen);   
   memcpy(&pacote,&buf,buflen);
    switch (pacote.valor1) {
          case 'W':
            front();
          break;

          case 'S':
            front_auto();
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
            digitalWrite(8, LED);
          break;

          case'B':
            CAMERA = !CAMERA;
            digitalWrite(9, CAMERA);
          break; 
    }
  }
}

void test(){
  front();
}
void front(){     //Funcao que faz o Hexpod andar para frente
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Motor 5(oposto) Frente robo:
  digitalWrite(IN10, HIGH);
  digitalWrite(IN9, LOW);
  //Motor 3 Frente robo:
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
    delay(delay1);//Delay para iniciar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
    delay(delay2);//Delay para parar o lado A
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  //Motor 5 Frente robo:
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10,HIGH);
  //Motor 3 Frente robo:
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
    int a = delay1 - delay2;
    delay(a);//Delay para parar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, HIGH);
    parado(0);//Chama a funaao parado que sincroniza as patas ao chao, com sentido para frente do robo
}

void right(){
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Motor 5(oposto) Frente robo:
  digitalWrite(IN10, HIGH);
  digitalWrite(IN9, LOW);
  //Motor 3 Frente robo:
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
    delay(delay1);//Delay para iniciar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
    delay(delay2);//Delay para parar o lado A
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  //Motor 5 Frente robo:
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10,HIGH);
  //Motor 3 Frente robo:
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
    int a = delay1 - delay2;
    delay(a);//Delay para parar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, HIGH);
  parado(0);                        //Chama a funaao parado que sincroniza as patas ao chao, com sentido para direita do robo
}

void left(){     //Funcao que faz o Hexpod andar para a esquerda
  //Motor 1 Frente robo:
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Motor 5(oposto) Frente robo:
  digitalWrite(IN10,LOW);
  digitalWrite(IN9, HIGH);
  //Motor 3 Frente robo:
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
    delay(delay1);//Delay para iniciar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
    delay(delay2);//Delay para parar o lado A
  //Motor 1 parado:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  //Motor 5 parado:
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10,HIGH);
  //Motor 3 parado:
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
    int a = delay1 - delay2;
    delay(a);//Delay para parar o lado B
  //Motor 4 parado:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //Motor 2 parado:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  //Motor 6 parado:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, HIGH);
  parado(0); //Chama a funcao parado que sincroniza as patas ao chao, com sentido para esquerda do robo
}

void parado(int sentido){       //Funcao que sincroniza as patas no chao, recebe valor: sentido de rotacao, para sincronizar
  if(sentido == 0) {                    //Se sentido for 0, sincroniza as patas para tras do robo


      //Sincronizar Motor 2:  
      if(!digitalRead(sensorB)){    //Se o sensor B, localizado na porta 3, estiver ativado
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
          }while(digitalRead(sensorB));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorB)){//Se o sensor B, localizado na porta 3, estiver ativado
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
          }                         //
      }                             //

      //Sincronizar Motor 5:
      if(!digitalRead(sensorE)){
        digitalWrite(IN9, HIGH);
        digitalWrite(IN10,HIGH);
      } else {
          do{
            digitalWrite(IN9, HIGH);
            digitalWrite(IN10,LOW);
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            digitalWrite(IN9, HIGH);
            digitalWrite(IN10,HIGH);
          }
      }

      //Sincronizar Motor 6:
      if(!digitalRead(sensorF)){
        digitalWrite(IN11, HIGH);
        digitalWrite(IN12, HIGH);
      } else {
          do{
            digitalWrite(IN11, HIGH);
            digitalWrite(IN12, LOW);
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            digitalWrite(IN11, HIGH);
            digitalWrite(IN12, HIGH);
          }
      }
      
      //Sincronizar Motor 3:
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        digitalWrite(IN5, HIGH);
        digitalWrite(IN6, HIGH);
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            digitalWrite(IN5, HIGH);
            digitalWrite(IN6, LOW);
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            digitalWrite(IN5, HIGH);
            digitalWrite(IN6, HIGH);
          }                         //
      }                             //


      
    //Sincronizar Motor 1:
      if(!digitalRead(sensorA)){    //Se o sensor A, localizado na porta 2, estiver ativado
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW); 
          } while(digitalRead(sensorA));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor A, localizado na porta 2, estiver ativado
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
          }                         //
      }                             //


      
    //Sincronizar Motor 4:               
      if(!digitalRead(sensorD)){
        digitalWrite(IN7, HIGH);
        digitalWrite(IN8, HIGH);
      } else {
          do{
            digitalWrite(IN7, HIGH);
            digitalWrite(IN8, LOW);
          }while(digitalRead(sensorD));
          if(!digitalRead(sensorD)){
            digitalWrite(IN7, HIGH);
            digitalWrite(IN8, LOW);
          }
      }
  }//end if
  /*
  if(sentido == 1) {                    //Se sentido for 1, sincroniza as patas para direita do robo


    //Sincronizar Motor 2:
      if(!digitalRead(sensorB)){    //Se o sensor B, localizado na porta 3, estiver ativado
        pwm.setPWM(1, 0, graus(51));//Motor 1 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(1, 0, graus(0));//Motor 1 gira com sentido para tras no robo 
          }while(digitalRead(sensorB));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorB)){//Se o sensor B, localizado na porta 3, estiver ativado
            pwm.setPWM(1, 0, graus(51));//Motor 1 parado
          }                         //
      }                             //


      //Sincronizar Motor 5:
      if(!digitalRead(sensorE)){
        pwm.setPWM(4, 0, graus(51));
      } else {
          do{
            pwm.setPWM(4, 0, graus(0));
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            pwm.setPWM(4, 0, graus(51));
          }
      }


      //Sincronizar Motor 6:
      if(!digitalRead(sensorF)){
        pwm.setPWM(5, 0, graus(51));
      } else {
          do{
            pwm.setPWM(5, 0, graus(180));
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            pwm.setPWM(5, 0, graus(51));
          }
      }


      //Sincronizar Motor 3:
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        pwm.setPWM(2, 0, graus(51));//Motor 2 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(2, 0, graus(180));//Motor 2 gira com sentido para frente no robo
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            pwm.setPWM(2, 0, graus(51));//Motor 2 parado
          }                         //
      }                             //


      
    //Sincronizar Motor 1:
      if(!digitalRead(sensorA)){    //Se o sensor A, localizado na porta 2, estiver ativado
        pwm.setPWM(0, 0, graus(51));//Motor 0 parado
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(0, 0, graus(180));//Motor 0 gira com sentido para frente no robo 
          } while(digitalRead(sensorA));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor A, localizado na porta 2, estiver ativado
            pwm.setPWM(0, 0, graus(51));//Motor 0 parado
          }                         //
      }                             //

      
      
    //Sincronizar Motor 4:
      if(!digitalRead(sensorD)){
        pwm.setPWM(3, 0, graus(51));
      } else {
          do{
            pwm.setPWM(3, 0, graus(180));
          }while(digitalRead(sensorD));
          if(!digitalRead(sensorD)){
            pwm.setPWM(3, 0, graus(51));
          }
      }
  }//end if
  
  if(sentido == 3) {                    //Se sentido for 0, sincroniza as patas para esquerda do robo


    //Sincronizar Motor 2:
      if(!digitalRead(sensorB)){    //Se o sensor B, localizado na porta 3, estiver ativado
        pwm.setPWM(1, 0, graus(51));//Motor 1 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(1, 0, graus(180));//Motor 1 gira com sentido para frente no robo 
          }while(digitalRead(sensorB));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorB)){//Se o sensor B, localizado na porta 3, estiver ativado
            pwm.setPWM(1, 0, graus(51));//Motor 1 parado
          }                         //
      }                             //


      //Sincronizar Motor 5:
      if(!digitalRead(sensorE)){
        pwm.setPWM(4, 0, graus(51));
      } else {
          do{
            pwm.setPWM(4, 0, graus(180));
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            pwm.setPWM(4, 0, graus(51));
          }
      }


      //Sincronizar Motor 6:
      if(!digitalRead(sensorF)){
        pwm.setPWM(5, 0, graus(51));
      } else {
          do{
            pwm.setPWM(5, 0, graus(0));
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            pwm.setPWM(5, 0, graus(51));
          }
      }



  //Sincronizar Motor 3:
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        pwm.setPWM(2, 0, graus(51));//Motor 2 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(2, 0, graus(0));//Motor 2 gira com sentido para tras no robo
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            pwm.setPWM(2, 0, graus(51));//Motor 2 parado
          }                         //
      }                             //



    //Sincronizar Motor 1:
      if(!digitalRead(sensorA)){    //Se o sensor A, localizado na porta 2, estiver ativado
        pwm.setPWM(0, 0, graus(51));//Motor 0 parado
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(0, 0, graus(0));//Motor 0 gira com sentido para tras no robo 
          } while(digitalRead(sensorA));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor A, localizado na porta 2, estiver ativado
            pwm.setPWM(0, 0, graus(51));//Motor 0 parado
          }                         //
      }                             //


      
    //Sincronizar Motor 4:
      if(!digitalRead(sensorD)){
        pwm.setPWM(3, 0, graus(51));
      } else {
          do{
            pwm.setPWM(3, 0, graus(0));
          }while(digitalRead(sensorD));
          if(!digitalRead(sensorD)){
            pwm.setPWM(3, 0, graus(51));
          }
      }
  }//end if
  */
}//end void parado

/*
int graus(int x) { //Funçao 'graus' que recebe um valor Inteiro armazenado em 'x'                                                            
  int graus = x; //Variavel inteira 'graus' recebe o valor de 'x'
  graus = map(graus, 0, 180, SERVOMIN, SERVOMAX); //Regra de 3, para converter graus no valor do PWM
  
  return graus; //Retorna como resultado da funcao, o valor da variavel 'graus'
}
*/

void front_auto(){
  
}
