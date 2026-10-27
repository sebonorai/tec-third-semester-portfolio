// Red IoT colaborativa - Equipo 3 (TC1004B grupo 503)
// Board support: esp8266 (by ESP8266 Community) version 2.5.2
//
// Cada NodeMCU publica su "temperatura" (potenciometro) en su topico,
// escucha a todos los nodos, promedia y pone el LED RGB:
//   promedio < TEMP_BAJA               -> AZUL
//   TEMP_BAJA <= promedio <= TEMP_ALTA -> VERDE
//   promedio > TEMP_ALTA               -> ROJO

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// ======================= CAMBIA SOLO ESTO =======================
#define MI_ID 5                 // numero de TU nodo (1 a 5). Cada quien el suyo.
#define ANODO_COMUN true        // true = LED de anodo comun (LOW enciende)
                                // false = LED de catodo comun (HIGH enciende)
#define MOSTRAR_MENSAJES false  // true = imprime cada mensaje que llega (muy rapido)
// ================================================================

#include "secrets.h"   // define WIFI_SSID y WIFI_PASSWORD (copia secrets.h.example a secrets.h)

#define SENSOR_A0 A0
#define LED1 D1   // R - Rojo
#define LED2 D0   // G - Verde
#define LED3 D2   // B - Azul

const char *mqtt_server = "broker.hivemq.com";
const char *PREFIJO = "TC1004B.503.Eq3";        // identificador del equipo

// Limites de temperatura
const float TEMP_BAJA = 15.0;   // menos que esto  -> azul
const float TEMP_ALTA = 30.0;   // mas que esto    -> rojo

// El potenciometro (0-1023) se mapea a este rango de temperatura simulada
const float TEMP_MIN_POT = 0.0;
const float TEMP_MAX_POT = 50.0;

const int NUM_NODOS = 5;
float temperaturas[NUM_NODOS + 1];   // indices 1..5 (el 0 no se usa)
bool  recibido[NUM_NODOS + 1];       // true si ya llego algun valor de ese nodo

char topicPub[60];    // TC1004B.503.Eq3/nodoN/temp
char topicSub[60];    // TC1004B.503.Eq3/+/temp

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long tiempoAnterior = 0;
const unsigned long INTERVALO_PUB = 3000;       // publicar cada 3 segundos

unsigned long ultimoCalculo = 0;
const unsigned long INTERVALO_CALCULO = 5000;   // promedio + LED cada 5 segundos

int lecturaPot = 0;   // ultima lectura de mi potenciometro

// ---------- LED RGB ----------
void setColor(bool r, bool g, bool b) {
    int on  = ANODO_COMUN ? LOW  : HIGH;
    int off = ANODO_COMUN ? HIGH : LOW;
    digitalWrite(LED1, r ? on : off);
    digitalWrite(LED2, g ? on : off);
    digitalWrite(LED3, b ? on : off);
}

// ---------- WiFi ----------
void setup_wifi() {
    delay(100);
    Serial.println();
    Serial.print("macAddress: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Conectando WiFi --> ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    randomSeed(micros());
    Serial.println();
    Serial.println("WiFi conectado!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

// ---------- Resumen, promedio y LED ----------
void actualizarLED() {
    float suma = 0;
    int cuantos = 0;

    Serial.println();
    Serial.println("========== RESUMEN ==========");
    Serial.print("Mi potenciometro: ");
    Serial.println(lecturaPot);

    for (int i = 1; i <= NUM_NODOS; i++) {
        Serial.print("Nodo ");
        Serial.print(i);
        if (i == MI_ID) Serial.print(" (yo)");
        if (recibido[i]) {
            Serial.print(": ");
            Serial.println(temperaturas[i], 1);
            suma += temperaturas[i];
            cuantos++;
        } else {
            Serial.println(": sin datos");
        }
    }

    if (cuantos == 0) {
        Serial.println("Todavia no hay datos.");
        return;
    }

    float promedio = suma / cuantos;
    Serial.print("PROMEDIO de ");
    Serial.print(cuantos);
    Serial.print(" nodo(s) = ");
    Serial.println(promedio, 1);

    if (promedio < TEMP_BAJA) {
        Serial.println("LED: AZUL (muy baja)");
        setColor(false, false, true);
    } else if (promedio > TEMP_ALTA) {
        Serial.println("LED: ROJO (alta)");
        setColor(true, false, false);
    } else {
        Serial.println("LED: VERDE (normal)");
        setColor(false, true, false);
    }
    Serial.println("=============================");
}

// ---------- Callback: llega un mensaje MQTT ----------
// Topico esperado: TC1004B.503.Eq3/nodoN/temp   (N = 1..5)
void callback(char* topic, byte* payload, unsigned int length) {
    char texto[32];
    unsigned int n = (length < sizeof(texto) - 1) ? length : sizeof(texto) - 1;
    memcpy(texto, payload, n);
    texto[n] = '\0';

    if (MOSTRAR_MENSAJES) {
        Serial.print("Mensaje [");
        Serial.print(topic);
        Serial.print("] = ");
        Serial.println(texto);
    }

    // Sacar el numero de nodo del topico
    String t = String(topic);
    int pos = t.indexOf("/nodo");
    if (pos < 0) return;
    int id = t.charAt(pos + 5) - '0';
    if (id < 1 || id > NUM_NODOS) return;

    // Validar que el mensaje sea un numero (ignora texto)
    char c = texto[0];
    if (!(c == '-' || c == '.' || (c >= '0' && c <= '9'))) return;

    temperaturas[id] = atof(texto);
    recibido[id] = true;
}

// ---------- MQTT ----------
void reconnect() {
    while (!client.connected()) {
        Serial.print("Intentando conexion MQTT ...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
            Serial.println("Conectado al 'broker' MQTT!!!");
            client.subscribe(topicSub);
            Serial.print("Suscrito a: ");
            Serial.println(topicSub);
        } else {
            Serial.print("Error de conexion, rc=");
            Serial.print(client.state());
            Serial.println(" ... reintentando en 6 seg.");
            delay(6000);
        }
    }
}

void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    Serial.begin(115200);

    // Prueba del LED: rojo, verde, azul
    Serial.println();
    Serial.println("Prueba de LED: rojo, verde, azul");
    setColor(true, false, false);  delay(500);
    setColor(false, true, false);  delay(500);
    setColor(false, false, true);  delay(500);
    setColor(false, false, false);

    for (int i = 0; i <= NUM_NODOS; i++) {
        temperaturas[i] = 0;
        recibido[i] = false;
    }

    snprintf(topicPub, sizeof(topicPub), "%s/nodo%d/temp", PREFIJO, MI_ID);
    snprintf(topicSub, sizeof(topicSub), "%s/+/temp", PREFIJO);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();   // procesa los mensajes que llegan

    unsigned long ahora = millis();

    // --- Publicar mi temperatura ---
    if (ahora - tiempoAnterior >= INTERVALO_PUB) {
        tiempoAnterior = ahora;

        lecturaPot = analogRead(SENSOR_A0);   // 0 - 1023
        float temp = TEMP_MIN_POT + (lecturaPot / 1023.0) * (TEMP_MAX_POT - TEMP_MIN_POT);

        char mensaje[16];
        dtostrf(temp, 1, 1, mensaje);          // ej. "23.4"
        client.publish(topicPub, mensaje);

        // Guardar mi propio valor de inmediato
        temperaturas[MI_ID] = atof(mensaje);
        recibido[MI_ID] = true;
    }

    // --- Calcular promedio y actualizar LED ---
    if (ahora - ultimoCalculo >= INTERVALO_CALCULO) {
        ultimoCalculo = ahora;
        actualizarLED();
    }
}