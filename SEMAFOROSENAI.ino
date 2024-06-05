#include <EEPROM.h>

#define LED_VM1 11  
#define LED_AM1 12  
#define LED_VD1 13 
#define LED_VM2 2  
#define LED_AM2 3  
#define LED_VD2 4  

// Endereços na EEPROM para armazenar os tempos dos semáforos 1 e 2
#define ADDR_TEMPO_VERDE1 0
#define ADDR_TEMPO_AMARELO1 4
#define ADDR_TEMPO_VERMELHO1 8
#define ADDR_TEMPO_VERDE2 12
#define ADDR_TEMPO_AMARELO2 16
#define ADDR_TEMPO_VERMELHO2 20

// Variáveis para armazenar os tempos dos semáforos
long tempoVerde1, tempoAmarelo1, tempoVermelho1;
long tempoVerde2, tempoAmarelo2, tempoVermelho2;


// Variáveis para armazenar o tempo
long int tempoAntigo = 0;
const long intervaloVerde = 1500;  // Tempo em que o LED Verde fica ligado (5 segundos)
const long intervaloAmarelo = 300; // Tempo em que o LED Amarelo fica ligado (2 segundos)
const long intervaloVermelho = 1500;    // Tempo em que o LED Vermelho fica ligado (5 segundos)

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
  
  // Ler os tempos da EEPROM
  EEPROM.get(ADDR_TEMPO_VERDE1, tempoVerde1);
  EEPROM.get(ADDR_TEMPO_AMARELO1, tempoAmarelo1);
  EEPROM.get(ADDR_TEMPO_VERMELHO1, tempoVermelho1);
  EEPROM.get(ADDR_TEMPO_VERDE2, tempoVerde2);
  EEPROM.get(ADDR_TEMPO_AMARELO2, tempoAmarelo2);
  EEPROM.get(ADDR_TEMPO_VERMELHO2, tempoVermelho2);
  EEPROM.get(0,contador);

  // Se os valores lidos da EEPROM forem inválidos, inicializar com valores padrão
  if (tempoVerde1 <= 0 || tempoVerde1 > 60000) tempoVerde1 = 15000;
  if (tempoAmarelo1 <= 0 || tempoAmarelo1 > 60000) tempoAmarelo1 = 3000;
  if (tempoVermelho1 <= 0 || tempoVermelho1 > 60000) tempoVermelho1 = 15000;

  if (tempoVerde2 <= 0 || tempoVerde2 > 60000) tempoVerde2 = 15000;
  if (tempoAmarelo2 <= 0 || tempoAmarelo2 > 60000) tempoAmarelo2 = 3000;
  if (tempoVermelho2 <= 0 || tempoVermelho2 > 60000) tempoVermelho2 = 15000;
}
 void loop()
 {
    // Ler comandos da serial
  if (Serial.available()) {
    String comando = Serial.readString();
    if (comando.startsWith("setVerde1")) {
      tempoVerde1 = comando.substring(9).toInt();
      EEPROM.put(ADDR_TEMPO_VERDE1, tempoVerde1);
      Serial.print("Tempo Verde 1 atualizado para: ");
      Serial.println(tempoVerde1);
    } else if (comando.startsWith("setAmarelo1")) {
      tempoAmarelo1 = comando.substring(11).toInt();
      EEPROM.put(ADDR_TEMPO_AMARELO1, tempoAmarelo1);
      Serial.print("Tempo Amarelo 1 atualizado para: ");
      Serial.println(tempoAmarelo1);
    } else if (comando.startsWith("setVermelho1")) {
      tempoVermelho1 = comando.substring(12).toInt();
      EEPROM.put(ADDR_TEMPO_VERMELHO1, tempoVermelho1);
      Serial.print("Tempo Vermelho 1 atualizado para: ");
      Serial.println(tempoVermelho1);
    } else if (comando.startsWith("setVerde2")) {
      tempoVerde2 = comando.substring(9).toInt();
      EEPROM.put(ADDR_TEMPO_VERDE2, tempoVerde2);
      Serial.print("Tempo Verde 2 atualizado para: ");
      Serial.println(tempoVerde2);
    } else if (comando.startsWith("setAmarelo2")) {
      tempoAmarelo2 = comando.substring(11).toInt();
      EEPROM.put(ADDR_TEMPO_AMARELO2, tempoAmarelo2);
      Serial.print("Tempo Amarelo 2 atualizado para: ");
      Serial.println(tempoAmarelo2);
    } else if (comando.startsWith("setVermelho2")) {
      tempoVermelho2 = comando.substring(12).toInt();
      EEPROM.put(ADDR_TEMPO_VERMELHO2, tempoVermelho2);
      Serial.print("Tempo Vermelho 2 atualizado para: ");
      Serial.println(tempoVermelho2);
    } else if (comando == "transito") {
      contador = 0;
      if (contador <= 15) {
        digitalWrite(LED_AM1, LOW);
        digitalWrite(LED_VM1, LOW);
        digitalWrite(LED_VD1, HIGH);
        digitalWrite(LED_VD2, LOW);
        digitalWrite(LED_AM2, LOW);
        digitalWrite(LED_VM2, HIGH);
      }
    }
  }
   long tempoAtual = millis();
  if (tempoAtual - tempoAntigo >= 1000) {
    tempoAntigo = tempoAtual;
    contador++;
  }

  // Lógica do semáforo
  if (contador <= 15) {
    digitalWrite(LED_VD1, HIGH);
    digitalWrite(LED_VM2, HIGH);
    digitalWrite(LED_VM1, LOW);
    digitalWrite(LED_AM1, LOW);
    digitalWrite(LED_VD2, LOW);
    digitalWrite(LED_AM2, LOW);
    Serial.println("ligou led verde1 e vermelho2");
  } else if (contador > 15 && contador <= 18) {
    digitalWrite(LED_VD1, LOW);
    digitalWrite(LED_AM1, HIGH);
    Serial.println("ligou led amarelo");
  } else if (contador > 18 && contador <= 33) {
    digitalWrite(LED_AM1, LOW);
    digitalWrite(LED_VM2, LOW);
    digitalWrite(LED_VD2, HIGH);
    digitalWrite(LED_VM1, HIGH);
    Serial.println("ligou led verde 2 E vm 1");
  } else if (contador > 33 && contador <= 35) {
    digitalWrite(LED_VD2, LOW);
    digitalWrite(LED_AM2, HIGH);
    Serial.println("ligou led verde am 2");
  } else {
    EEPROM.put(0,contador);
    contador = 0;
  }
}