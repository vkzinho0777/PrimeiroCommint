
#define LED_VM1 D12 
#define LED_AM1 D11  
#define LED_VD1 D13 
#define LED_VM2 D8 
#define LED_AM2 D9  
#define LED_VD2 D10  


// Variáveis para armazenar o tempo
long int tempoAntigo = 0;
const long intervaloVerde = 1500;  // Tempo em que o LED Verde fica ligado (15 segundos)
const long intervaloAmarelo = 300; // Tempo em que o LED Amarelo fica ligado (3 segundos)
const long intervaloVermelho = 1500;    // Tempo em que o LED Vermelho fica ligado (15 segundos)

// Estado inicial do semáforo
int estado = 0;

long int contador = 0;

void setup() {
 
  Serial.begin(9600);
  pinMode(LED_VM1, OUTPUT);
  pinMode(LED_AM1, OUTPUT);
  pinMode(LED_VD1, OUTPUT);
  pinMode(LED_VM2, OUTPUT);
  pinMode(LED_AM2, OUTPUT);
  pinMode(LED_VD2, OUTPUT);
}
 void loop()
 {
   String serial = Serial.readString();
   serial.trim();
   long int tempoAtual = millis();
   if(tempoAtual - tempoAntigo > 1000){
   tempoAntigo = millis();
   contador++;
 }

Serial.println(contador);
   
    if( serial == "transito"){
      contador = 0;
     if(contador <= 15)
     digitalWrite(LED_AM1, LOW);
     digitalWrite(LED_VM1, LOW);
     digitalWrite(LED_VD1, HIGH);
     
     digitalWrite(LED_VD2, LOW);
     digitalWrite(LED_AM2, LOW);
     digitalWrite(LED_VM2, HIGH);
      }
   
if(contador <= 15){
 digitalWrite(LED_VD1, HIGH); 
 digitalWrite(LED_VM2, HIGH);
 digitalWrite(LED_VM1, LOW);
 digitalWrite(LED_AM1, LOW);
 digitalWrite(LED_VD2, LOW);
 digitalWrite(LED_AM2, LOW);
 
  
 Serial.println("ligou led verde1 e vermelho2"); 
}   
else if(contador > 15 && contador <= 18 ){
 digitalWrite(LED_VD1, LOW); 
 digitalWrite(LED_AM1, HIGH);  
 Serial.println("ligou led amarelo"); 
}
else if(contador > 18 && contador  <=33 ){
digitalWrite(LED_AM1, LOW);
digitalWrite(LED_VM2, LOW); 
digitalWrite(LED_VD2, HIGH);  
digitalWrite(LED_VM1, HIGH);  
 Serial.println("ligou led verde 2 E vm 1");    
}
   else if(contador > 33 && contador <= 35){
digitalWrite(LED_VD2, LOW);
digitalWrite(LED_AM2, HIGH);       
 Serial.println("ligou led verde am 2 ");   
   }
   else{
   contador = 0;
   }
}
   
