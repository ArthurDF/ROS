#include <ros.h>
#include <std_msgs/Int32.h>

#include <Ultrasonic.h>
#include <Servo.h>
#define TRIGGER_PIN  12
#define ECHO_PIN     10

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo myservo;

ros::NodeHandle nodo;

std_msgs::Int32 ValorUltraSom;

int valorServo;

ros::Publisher UltraSom("UltraSom", &ValorUltraSom);

void Callback(const std_msgs::Int32& msg){
  valorServo=msg.data;
  valorServo=map(valorServo,0,1023,0,180);
  myservo.write(valorServo); //escreve valor do angulo no servo
}

ros::Subscriber<std_msgs::Int32> sub("Servo", Callback); //cria o subscriver sub que se inscreve no tópico Servo

void setup() {
  nodo.initNode(); //Inicia No do ultra som
  nodo.advertise(UltraSom); //Divulga para o Ros o Topico UltraSom
  nodo.subscribe(sub); // inicia a inscrição do subscriber sub
  myservo.attach(9); //Inicia o servo no pino 9

}


void loop() {
  // put your main code here, to run repeatedly:
  
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  ValorUltraSom.data=cmMsec;
  
  UltraSom.publish(&ValorUltraSom); // Publica Valor do Ultra som no tópico UltraSom
  
  nodo.spinOnce(); // Coloca para o Ros Reconhecer o ciclo
  
  //delay(1000);

}
