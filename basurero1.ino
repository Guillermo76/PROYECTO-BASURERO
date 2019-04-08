
//declaracion de pines

#include <Servo.h> 

Servo myservo;
int control=0;

int derA = 10; //motor
int derB = 9; 

int izqA = 6; 
int izqB = 5; 

int vel = 255; // Velocidad 

int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
int Echo = 7;   //Pin digital 3 para el echo del sensor

//variales globales sensor
int t=0;//tiempo
const int dis_tol=10; //centimetros distancia tolerada obstaculo
int distancia;



void alto(){
  analogWrite(derA, 0);  // Detiene los Motores
  analogWrite(izqA, 0); 
  analogWrite(derB, 0);  // Detiene los Motores
  analogWrite(izqB, 0); 
  
}

void adelante(){
    analogWrite(derA, vel);  // Frente 2 segundos
    analogWrite(izqA, vel);
   

}

void reversa(){
    analogWrite(derB, vel);  // Reversa 2 segundos
    analogWrite(izqB, vel);
  
}

void gira_Deracha(){
    analogWrite(derA, vel);  // Derecha 0,5 segundos
    analogWrite(izqA, 0); 
  
}

void gira_Izquierda(){
    analogWrite(derA, 0);    // Izquierda 0,5 segundos
    analogWrite(izqA, vel); 
    
}

int sensores_funcionando(){
  
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
 
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  
  distancia = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(distancia);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);          //Hacemos una pausa de 100ms
  return distancia;//retorna la distancia
  
 
}

int mira_derecha()
{
    myservo.write(30); 
    delay(400);
    int distancia=sensores_funcionando();
    delay(100);
    myservo.write(90); 
    return distancia;
    
}

int mira_izquierda()
{
    myservo.write(160); 
    delay(400);
    int distancia=sensores_funcionando();
    delay(100);
    myservo.write(90);
   return distancia; 
}

void setup()  { 
  
   Serial.begin(115200);
  
  pinMode(derA, OUTPUT);//motor izquiedo
  pinMode(derB, OUTPUT);
  
  pinMode(izqA, OUTPUT);//motor derecho
  pinMode(izqB, OUTPUT);
  
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  delay(500);
   distancia = sensores_funcionando();
   delay(100);
  myservo.attach(11);  
  myservo.write(90); 
  delay(2000);
  
 } 





 
void loop()  { 
  
  
 int distancia_De = 0;
 int distancia_Iz = 0;
 delay(40);
  
  if(distancia <= dis_tol){
      alto();
      delay(100);
      reversa();
      delay(2000);
      alto();
      delay(200);
      distancia_De=mira_derecha();
      delay(200);
      distancia_Iz=mira_izquierda();
      delay(200);
      
      if(distancia_De>=distancia_Iz)
      {
        gira_Deracha();
        delay(1500);
        alto();
        Serial.print("Gira a la derecha");
      }else
      {
        gira_Izquierda();
        delay(1500);
         alto();
         delay(500);
         
         Serial.print("Gira a la izquierda");
      }
      
  }else{
    adelante();
        Serial.print("sigue adelante");
       
  }
       
    distancia = sensores_funcionando();
    
    adelante();
}
      
      

  

