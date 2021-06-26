#define BLYNK_PRINT Serial
#include <DM02A.h>  //Inclui a biblioteca para comunicar com o dimmer DM02A
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

int valor_slider1;
int valor_slider2;

Servo servo_porta;
Servo servo_janela;

//Cria um novo objeto do tipo Dimmer
DM02A dimmer(D1, D2);//SIG, CH, EN - Se não usar o EN, deixar sem informar

char auth[] = "xxxxxxxxxxxxxxxxxxxx";
char ssid[] = "xxxxxx";
char pass[] = "xxxxxxxxxxx";

BLYNK_WRITE(V1) {
  valor_slider1 = param.asInt();
}
BLYNK_WRITE(V2) {
  servo_porta.write(90);
}
BLYNK_WRITE(V3) {
  servo_porta.write(180);
}
BLYNK_WRITE(V4) {
  servo_janela.write(90);
}
BLYNK_WRITE(V5) {
  servo_janela.write(180);
}
BLYNK_WRITE(V6) {
  valor_slider2 = param.asInt();
}
void setup() {
  
  //Força os dois canais iniciarem desligados
  dimmer.EnviaNivel(0, 0);
  dimmer.EnviaNivel(0, 1);
 
  Blynk.begin(auth, ssid, pass);

  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);

//liga os relés
  digitalWrite(D5, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D3, LOW);

  servo_porta.attach(D6); // NodeMCU D6 pin
  servo_janela.attach(D7); // NodeMCU D7 pin
}

void loop() {

  Blynk.run();
  dimmer.EnviaNivel(valor_slider1, 0);
  dimmer.EnviaNivel(valor_slider2, 1);

}
