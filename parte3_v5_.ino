/*
Sistemas Embebidos TP1 Parte 3-Matriz de LEDs
Trabalho realizado por:
  Cláudio Coelho a22106474
  Lucas Martins a22103318
Trabalho realizado com base em:
  https://projecthub.arduino.cc/natalmakers/arduino-pedestrian-crossing-traffic-lights-1c534d
*/
#define red1 2
#define yellow1 3
#define green1 4 
#define green2 5
#define yellow2 6
#define red2 7
#define crosswalkGo2_1 8
#define crosswalkGo2_2 9
#define crosswalkGo1_1 10
#define crosswalkGo1_2 11
#define crosswalkStop2_1 12
#define crosswalkStop2_2 13
#define crosswalkStop1_1 A4
#define crosswalkStop1_2 A5
const int crosswalk2_1 = A0;
const int crosswalk2_2 = A1;
const int crosswalk1_1 = A2;
const int crosswalk1_2 = A3;

void setup() {
  pinMode(red1,OUTPUT);
  pinMode(yellow1,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(yellow2,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(crosswalkGo2_2,OUTPUT);
  pinMode(crosswalkGo2_1,OUTPUT);
  pinMode(crosswalkGo1_1,OUTPUT);
  pinMode(crosswalkGo1_2,OUTPUT);
  pinMode(crosswalkStop2_1,OUTPUT);
  pinMode(crosswalkStop2_2,OUTPUT);
  pinMode(crosswalkStop1_1,OUTPUT);
  pinMode(crosswalkStop1_2,OUTPUT);
  pinMode(crosswalk1_1,INPUT_PULLUP); //Coloca o pin A2 a realizar input
  pinMode(crosswalk1_2,INPUT_PULLUP); //Coloca o pin A3 a realizar input
  pinMode(crosswalk2_1,INPUT_PULLUP); //Coloca o pin A0 a realizar input.
  pinMode(crosswalk2_2,INPUT_PULLUP); //Coloca o pin A1 a realizar input
}

int time = 0; //Auxilia a determinar quando determinados LEDs devem acender.
bool stCross1 = true; //Determina se a estrada 1 está a ser atravessada por veículos, por defeito está.
bool stCross2 = false; //Determina se a estrada 2 está a ser atravessada por veículos, por defeito não está.
bool crossing = false; //Determina se o botão foi pressionado.
int crossingTime = 0; //Auxilia a determinar se um botão pode ser pressionado.
int state1_1 = 0; //Determina o estado atual do botão 2 (associado ao pino A2).
int state1_2 = 0; //Determina o estado atual do botão 2 (associado ao pino A3).
int state2_1 = 0; //Determina o estado atual do botão 2 (associado ao pino A0).
int state2_2 = 0; //Determina o estado atual do botão 2 (associado ao pino A1).
void loop() {
  if(crossingTime>=4000){ //Depois de carregar num botão, os botões não terão efeito ao serem carregados enquanto a variável crossingTime fôr menor que 4000.
    crossingTime = 0; //Quando crossingTime fôr igual ou superior a 4000, os valores de crossingTime e crossing regressam aos seus valores originais 0 e false, respetivamente.
    crossing = false;
  }
  state1_1 = digitalRead(crosswalk1_1);
    if(!state1_1 && digitalRead(green1) == 1 && !crossing){ //Verifica se alguém carregou no botão, se o semáforo dos veículos associado à estrada da passadeira está verde e se já hà alguma travessia a ocorrer.
        time = 6000; //Faz com que o semáforo da estrada associada à passadeira passe a amarelo.
        crossing = true; //Indica que está a ocorrer uma travessia por causa de alguém ter carregado num botão.
    }

  state1_2 = digitalRead(crosswalk1_2);
  if(!state1_2 && digitalRead(green1) == 1 && !crossing){ //Verifica se alguém carregou no botão, se o semáforo dos veículos associado à estrada da passadeira está verde e se já hà alguma travessia a ocorrer.
      time = 6000; //Faz com que o semáforo da estrada associada à passadeira passe a amarelo.
      crossing = true; //Indica que está a ocorrer uma travessia por causa de alguém ter carregado num botão.
  }

  state2_1 = digitalRead(crosswalk2_1);
  if(!state2_1 && digitalRead(green2) == 1 && !crossing){ //Verifica se alguém carregou no botão, se o semáforo dos veículos associado à estrada da passadeira está verde e se já hà alguma travessia a ocorrer.
      time = 6000; //Faz com que o semáforo da estrada associada à passadeira passe a amarelo.
      crossing = true; //Indica que está a ocorrer uma travessia por causa de alguém ter carregado num botão.
  }

  state2_2 = digitalRead(crosswalk2_2);
  if(!state2_2 && digitalRead(green2) == 1 && !crossing){ //Verifica se alguém carregou no botão, se o semáforo dos veículos associado à estrada da passadeira está verde e se já hà alguma travessia a ocorrer.
      time = 6000; //Faz com que o semáforo da estrada associada à passadeira passe a amarelo.
      crossing = true; //Indica que está a ocorrer uma travessia por causa de alguém ter carregado num botão.
  }

  if(time<5000){ //Quando time é inferior a 5000 a estrada na qual cirulam veículos terá os LEDs verdes ligados e a outra terá os LEDs vermelhos ligados.
    if(stCross1){greenLight1();}
    else{redLight1();}
    if(stCross2){greenLight2();}
    else{redLight2();}
  }
  if(time>=5000 && time<7000){ //Quando time é inferior a 8000 e igual ou superior a 5000 a estrada na qual transitam veículos terá os LEDs amarelos ligados.
    if(stCross1){yellowLight1();}
    if(stCross2){yellowLight2();}
  }

  if(digitalRead(red1) == 1){ //Quando os LEDs vermelhos dos semáforos da estrada 1 estão acesos os LEDs verdes das passadeiras dessa estrada estão acessos.
    if(digitalRead(yellow2) == 0){ //Verifica se os LEDs amarelos dos semáforos da estrada 2 estão acesos.
    digitalWrite(crosswalkGo1_1,HIGH);
    digitalWrite(crosswalkStop1_1,LOW);
    digitalWrite(crosswalkGo1_2,HIGH);
    digitalWrite(crosswalkStop1_2,LOW);}
    else{ //Caso os LEDs amarelos dos semáforos da estrada 2 estejam acesos os LEDs verdes das passadeiras da estrada 1 começam a piscar.
      if(time>=5000 && time<5200){digitalWrite(crosswalkGo1_1,HIGH);digitalWrite(crosswalkGo1_2,HIGH);}
      if(time>=5200 && time<5400){digitalWrite(crosswalkGo1_1,LOW);digitalWrite(crosswalkGo1_2,LOW);}
      if(time>=5400 && time<5600){digitalWrite(crosswalkGo1_1,HIGH);digitalWrite(crosswalkGo1_2,HIGH);}
      if(time>=5600 && time<5800){digitalWrite(crosswalkGo1_1,LOW);digitalWrite(crosswalkGo1_2,LOW);}
      if(time>=5800 && time<6000){digitalWrite(crosswalkGo1_1,HIGH);digitalWrite(crosswalkGo1_2,HIGH);}
      if(time>=6000 && time<6200){digitalWrite(crosswalkGo1_1,LOW);digitalWrite(crosswalkGo1_2,LOW);}
      if(time>=6200 && time<6400){digitalWrite(crosswalkGo1_1,HIGH);digitalWrite(crosswalkGo1_2,HIGH);}
      if(time>=6400 && time<6600){digitalWrite(crosswalkGo1_1,LOW);digitalWrite(crosswalkGo1_2,LOW);}
      if(time>=6600 && time<6800){digitalWrite(crosswalkGo1_1,HIGH);digitalWrite(crosswalkGo1_2,HIGH);}
      if(time>=6800 && time<7000){digitalWrite(crosswalkGo1_1,LOW);digitalWrite(crosswalkGo1_2,LOW);}
    }
  }
  if(digitalRead(green1) == 1 || digitalRead(yellow1) == 1){ //Quando os LEDs verdes ou amarelos dos semáforos da estrada 1 estão acesos os LEDs vermelhos das passadeiras dessa estrada estão acessos.
    digitalWrite(crosswalkGo1_1,LOW);
    digitalWrite(crosswalkStop1_1,HIGH);
    digitalWrite(crosswalkGo1_2,LOW);
    digitalWrite(crosswalkStop1_2,HIGH);
  }

  if(digitalRead(red2) == 1){ //Quando os LEDs vermelhos dos semáforos da estrada 2 estão acesos os LEDs verdes das passadeiras dessa estrada estão acessos.
    if(digitalRead(yellow1) == 0){ //Verifica se os LEDs amarelos dos semáforos da estrada 1 estão acesos.
      digitalWrite(crosswalkGo2_1,HIGH);
      digitalWrite(crosswalkStop2_1,LOW);
      digitalWrite(crosswalkGo2_2,HIGH);
      digitalWrite(crosswalkStop2_2,LOW);
    }
    else{ //Caso os LEDs amarelos dos semáforos da estrada 1 estejam acesos os LEDs verdes das passadeiras da estrada 2 começam a piscar.
      if(time>=5000 && time<5200){digitalWrite(crosswalkGo2_1,HIGH);digitalWrite(crosswalkGo2_2,HIGH);}
      if(time>=5200 && time<5400){digitalWrite(crosswalkGo2_1,LOW);digitalWrite(crosswalkGo2_2,LOW);}
      if(time>=5400 && time<5600){digitalWrite(crosswalkGo2_1,HIGH);digitalWrite(crosswalkGo2_2,HIGH);}
      if(time>=5600 && time<5800){digitalWrite(crosswalkGo2_1,LOW);digitalWrite(crosswalkGo2_2,LOW);}
      if(time>=5800 && time<6000){digitalWrite(crosswalkGo2_1,HIGH);digitalWrite(crosswalkGo2_2,HIGH);}
      if(time>=6000 && time<6200){digitalWrite(crosswalkGo2_1,LOW);digitalWrite(crosswalkGo2_2,LOW);}
      if(time>=6200 && time<6400){digitalWrite(crosswalkGo2_1,HIGH);digitalWrite(crosswalkGo2_2,HIGH);}
      if(time>=6400 && time<6600){digitalWrite(crosswalkGo2_1,LOW);digitalWrite(crosswalkGo2_2,LOW);}
      if(time>=6600 && time<6800){digitalWrite(crosswalkGo2_1,HIGH);digitalWrite(crosswalkGo2_2,HIGH);}
      if(time>=6800 && time<7000){digitalWrite(crosswalkGo2_1,LOW);digitalWrite(crosswalkGo2_2,LOW);}
    }
  }
  if(digitalRead(green2) == 1 || digitalRead(yellow2) == 1){ //Quando os LEDs verdes ou amarelos dos semáforos da estrada 2 estão acesos os LEDs vermelhos das passadeiras dessa estrada estão acessos.
    digitalWrite(crosswalkGo2_1,LOW);
    digitalWrite(crosswalkStop2_1,HIGH);
    digitalWrite(crosswalkGo2_2,LOW);
    digitalWrite(crosswalkStop2_2,HIGH);
  }

  if(time>=7000){ //Quando time fôr maior ou igual a 7000, o estado de cada estrada é invertido e o time é igualado a 0.
    time = 0; //Iguala time a 0.
    stCross1 = !stCross1; //Inverte o estado da estrada 1.
    stCross2 = !stCross2; //Inverte o estado da estrada 2.
  }
  delay(2);
  time += 2; //Incrementa time em 2.
  crossingTime += 2; //Incrementa crossingTime em 2.
}

void deactivateAll1(){  //Desativa todos os LEDs da estrada 1.
  for(byte i=2;i<=4;i++){digitalWrite(i,LOW);}
}

void greenLight1(){ //Ativa os LEDs verdes da estrada 1.
  deactivateAll1();
  digitalWrite(green1,HIGH);
}

void yellowLight1(){ //Ativa os LEDs amarelos da estrada 1.
  deactivateAll1();
  digitalWrite(yellow1,HIGH);
}

void redLight1(){ //Ativa os LEDs vermelhos da estrada 1.
  deactivateAll1();
  digitalWrite(red1,HIGH);
}

void deactivateAll2(){ //Desativa todos os LEDs da estrada 2.
  for(byte i=5;i<=7;i++){digitalWrite(i,LOW);}
}

void greenLight2(){ //Ativa os LEDs verdes da estrada 2.
  deactivateAll2();
  digitalWrite(green2,HIGH);
}

void yellowLight2(){ //Ativa os LEDs amarelos da estrada 2.
  deactivateAll2();
  digitalWrite(yellow2,HIGH);
}

void redLight2(){ //Ativa os LEDs vermelhos da estrada 2.
  deactivateAll2();
  digitalWrite(red2,HIGH);
}