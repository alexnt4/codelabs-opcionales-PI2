#include <Arduino.h>
#include <WiFi.h>

const char * ssid = "virus5";
const char * password = "12345678";

WiFiServer server(80);

void conectarRedWifi(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Conectado a la red WiFi");
}
void setup() { // Conexion serial a 115200 baudos: 9600, 19200, 38400, 57600, 115200
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  conectarRedWifi();
  Serial.print("IP Local: "); // Imprime la direccion IP asignada por el router
  Serial.println(WiFi.localIP());
  server.begin(); // Inicia el servidor en el puerto 80
}

void loop() {
   // Maneja las peticiones al servidor y controla el LED
   WiFiClient cliente = server.available();
   if(cliente){
      String mensaje="";
      Serial.println("Llego un nuevo cliente");
      while(cliente.connected()){
        if(cliente.available()){
          char letra = cliente.read();
          Serial.write(letra);
          if(letra=='\n'){  //Es un caracter enter?
             if(mensaje.length()==0){  //La longitud de la linea es 0 ?
                  cliente.println("HTTP/1.1 200 OK");
                  cliente.println("Content-type:text/html");
                  cliente.println();  //Indicamos que terminamos de enviar la cabecera HTTP
                  cliente.println("<br>Clic <a href=\"H\">aqui</a> para encender la lampara<br>");
                  cliente.println("Clic <a href=\"L\">aqui</a> para apagar la lampara");
                  cliente.println();
                  break;
             } else
                  mensaje="";
          } else if (letra != '\r'){
            mensaje+=letra;
          }
          if(mensaje.endsWith("GET /H")){
            digitalWrite(2, HIGH);
          }
          if(mensaje.endsWith("GET /L")){
            digitalWrite(2,LOW);
          }
        }
      }
      Serial.println("Fin de conexion");
      cliente.stop();
   }
}