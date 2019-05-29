#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "SPIFFS.h"
#include "FS.h"

WebServer Server;
AutoConnect Portal(Server);
AutoConnectConfig Config;
WiFiUDP ntpUDP;
//Cria um objeto "NTP" com as configurações.utilizada no Brasil
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -3 * 3600, 60000);

#define output27 27
#define output26 26

void handleRoot() {
  
  String output27State;
  String output26State;

  String HoraT1Liga;
  String MinutoT1Liga;
  String HoraT1Desliga;
  String MinutoT1Desliga;
  String HoraT2Liga;
  String MinutoT2Liga;
  String HoraT2Desliga;
  String MinutoT2Desliga;

  String T1Domingo;
  String T1Segunda;
  String T1Terca;
  String T1Quarta;
  String T1Quinta;
  String T1Sexta;
  String T1Sabado;

  String T2Domingo;
  String T2Segunda;
  String T2Terca;
  String T2Quarta;
  String T2Quinta;
  String T2Sexta;
  String T2Sabado;

  String page = PSTR(
"<html>"
"<head>"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
  "<style type=\"text/css\">"
    "html {"
    "font-family: Helvetica;"
    "display: inline-block;"
    "margin: 0px auto;" 
    "text-align: center;"
    "}"
    ".menu > a:link {"
    "position: absolute;"
    "display: inline-block;"
    "right: 12px;"
    "padding: 0 6px;"
    "text-decoration: none;"
    "}"
    ".button {" 
    "background-color: none;"
    "border: none;"
    "color: white;"
    "padding: 16px 40px;"
    "text-decoration: none;"
    "font-size: 30px;"
    "margin: 10px 2px;"
    "cursor: pointer;"
    "}  "
    ".button2 {" 
    "background-color: none;"
    "border: none;"
    "color: white;"
    "padding: 6px 8px;"
    "text-decoration: none;"
    "font-size: 15px;"
    "margin: 2px 4px;"
    "cursor: pointer;"
    "}"
    "#number {"
    "width: 4em;"
    "}"
  "</style>"
  "<div class=\"menu\">" AUTOCONNECT_LINK(COG_32) "</div>"
"</head>"
"<body>" 
  "<h1>InteLight</h1><br>"
  "Tomada 1 : ");

  File F_output27State = SPIFFS.open("/output27State.txt", FILE_READ);
  output27State = F_output27State.readString();
  F_output27State.close();

  page += String(F("<span style=\"font-weight:bold;color:"));
  page += String(output27State) == "OFF" ? String("DarkRed\">DESLIGADA") : String("DarkBlue\">LIGADA");
  page += String(F("</span>"));
  
  page += String(F("<p><a class=\"button\""));
  page += String(output27State) == "OFF" ? String(F("style=\"background-color:DarkRed\"href=\"/io?v27=low\">LIGAR")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?v27=high\">DESLIGAR"));
  page += String(F("</a></p><br>"));

  File F_T1Domingo = SPIFFS.open("/fT1Domingo.txt", FILE_READ);
  T1Domingo = F_T1Domingo.readString();
  F_T1Domingo.close();

  File F_T1Segunda = SPIFFS.open("/fT1Segunda.txt", FILE_READ);
  T1Segunda = F_T1Segunda.readString();
  F_T1Segunda.close();

  File F_T1Terca = SPIFFS.open("/fT1Terca.txt", FILE_READ);
  T1Terca = F_T1Terca.readString();
  F_T1Terca.close();

  File F_T1Quarta = SPIFFS.open("/fT1Quarta.txt", FILE_READ);
  T1Quarta = F_T1Quarta.readString();
  F_T1Quarta.close();

  File F_T1Quinta = SPIFFS.open("/fT1Quinta.txt", FILE_READ);
  T1Quinta = F_T1Quinta.readString();
  F_T1Quinta.close();

  File F_T1Sexta = SPIFFS.open("/fT1Sexta.txt", FILE_READ);
  T1Sexta = F_T1Sexta.readString();
  F_T1Sexta.close();

  File F_T1Sabado = SPIFFS.open("/fT1Sabado.txt", FILE_READ);
  T1Sabado = F_T1Sabado.readString();
  F_T1Sabado.close();

  page += String(F("<p>"));

  page += String(F("<a class=\"button2\""));
  page += String(T1Domingo) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Domingo=ON\">D</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Domingo=OFF\">D</a>"));
  
  page += String(F("<a class=\"button2\""));
  page += String(T1Segunda) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Segunda=ON\">S</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Segunda=OFF\">S</a>"));
  
  page += String(F("<a class=\"button2\""));
  page += String(T1Terca) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Terca=ON\">T</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Terca=OFF\">T</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T1Quarta) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Quarta=ON\">Q</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Quarta=OFF\">Q</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T1Quinta) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Quinta=ON\">Q</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Quinta=OFF\">Q</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T1Sexta) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Sexta=ON\">S</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Sexta=OFF\">S</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T1Sabado) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT1Sabado=ON\">S</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT1Sabado=OFF\">S</a>"));

  page += String(F("</p>"));

  page += String(F("<FORM action=\"/io\" method=\"post\">"));
  page += String(F("<P>Ligar <input type=\"number\" name=\"horaT1Liga\" min=\"0\" max=\"23\" id=\"number\">H <input type=\"number\" name=\"minutoT1Liga\" min=\"0\" max=\"59\" id=\"number\">Min </P>"));
  page += String(F("<P>Desligar <input type=\"number\" name=\"horaT1Desliga\" min=\"0\" max=\"23\" id=\"number\">H <input type=\"number\" name=\"minutoT1Desliga\" min=\"0\" max=\"59\" id=\"number\">Min <INPUT type=\"submit\" value=\"Salvar\"> </P>"));
  page += String(F("</FORM>"));

  File F_HoraT1Liga = SPIFFS.open("/vHoraT1Liga.txt", FILE_READ);
  HoraT1Liga = F_HoraT1Liga.readString();
  F_HoraT1Liga.close();

  File F_MinutoT1Liga = SPIFFS.open("/vMinutoT1Liga.txt", FILE_READ);
  MinutoT1Liga = F_MinutoT1Liga.readString();
  F_MinutoT1Liga.close();

  File F_HoraT1Desliga = SPIFFS.open("/vHoraT1Desliga.txt", FILE_READ);
  HoraT1Desliga = F_HoraT1Desliga.readString();
  F_HoraT1Desliga.close();

  File F_MinutoT1Desliga = SPIFFS.open("/vMinutoT1Desliga.txt", FILE_READ);
  MinutoT1Desliga = F_MinutoT1Desliga.readString();
  F_MinutoT1Desliga.close();

  page += String(F("<p>Liga "));
  page += String(HoraT1Liga);
  page += String(" : ");
  page += String(MinutoT1Liga);
  page += String(F("</p>"));

  page += String(F("<p>Desliga "));
  page += String(HoraT1Desliga);
  page += String(" : ");
  page += String(MinutoT1Desliga);
  page += String(F("</p>"));
  
  
  page += String("Tomada 2 : ");
  
  File F_output26State = SPIFFS.open("/output26State.txt", FILE_READ);
  output26State = F_output26State.readString();
  F_output26State.close();

  page += String(F("<span style=\"font-weight:bold;color:"));
  page += String(output26State) == "OFF" ? String("DarkRed\">DESLIGADA") : String("DarkBlue\">LIGADA");
  page += String(F("</span>"));
  
  page += String(F("<p><a class=\"button\""));
  page += String(output26State) == "OFF" ? String(F("style=\"background-color:DarkRed\"href=\"/io?v26=low\">LIGAR")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?v26=high\">DESLIGAR"));
  page += String(F("</a></p><br>"));

  File F_T2Domingo = SPIFFS.open("/fT2Domingo.txt", FILE_READ);
  T2Domingo = F_T2Domingo.readString();
  F_T2Domingo.close();

  File F_T2Segunda = SPIFFS.open("/fT2Segunda.txt", FILE_READ);
  T2Segunda = F_T2Segunda.readString();
  F_T2Segunda.close();

  File F_T2Terca = SPIFFS.open("/fT2Terca.txt", FILE_READ);
  T2Terca = F_T2Terca.readString();
  F_T2Terca.close();

  File F_T2Quarta = SPIFFS.open("/fT2Quarta.txt", FILE_READ);
  T2Quarta = F_T2Quarta.readString();
  F_T2Quarta.close();

  File F_T2Quinta = SPIFFS.open("/fT2Quinta.txt", FILE_READ);
  T2Quinta = F_T2Quinta.readString();
  F_T2Quinta.close();

  File F_T2Sexta = SPIFFS.open("/fT2Sexta.txt", FILE_READ);
  T2Sexta = F_T2Sexta.readString();
  F_T2Sexta.close();

  File F_T2Sabado = SPIFFS.open("/fT2Sabado.txt", FILE_READ);
  T2Sabado = F_T2Sabado.readString();
  F_T2Sabado.close();

  page += String(F("<p>"));

  page += String(F("<a class=\"button2\""));
  page += String(T2Domingo) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Domingo=ON\">D</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Domingo=OFF\">D</a>"));
  
  page += String(F("<a class=\"button2\""));
  page += String(T2Segunda) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Segunda=ON\">S</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Segunda=OFF\">S</a>"));
  
  page += String(F("<a class=\"button2\""));
  page += String(T2Terca) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Terca=ON\">T</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Terca=OFF\">T</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T2Quarta) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Quarta=ON\">Q</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Quarta=OFF\">Q</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T2Quinta) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Quinta=ON\">Q</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Quinta=OFF\">Q</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T2Sexta) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Sexta=ON\">S</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Sexta=OFF\">S</a>"));

  page += String(F("<a class=\"button2\""));
  page += String(T2Sabado) == "9" ? String(F("style=\"background-color:LightGrey\"href=\"/io?vT2Sabado=ON\">S</a>")) : String(F("style=\"background-color:DarkBlue\"href=\"/io?vT2Sabado=OFF\">S</a>"));

  page += String(F("</p>"));

  page += String(F("<FORM action=\"/io\" method=\"post\">"));
  page += String(F("<P>Ligar <input type=\"number\" name=\"horaT2Liga\" min=\"0\" max=\"23\" id=\"number\">H <input type=\"number\" name=\"minutoT2Liga\" min=\"0\" max=\"59\" id=\"number\">Min </P>"));
  page += String(F("<P>Desligar <input type=\"number\" name=\"horaT2Desliga\" min=\"0\" max=\"23\" id=\"number\">H <input type=\"number\" name=\"minutoT2Desliga\" min=\"0\" max=\"59\" id=\"number\">Min <INPUT type=\"submit\" value=\"Salvar\"> </P>"));
  page += String(F("</FORM>"));

  File F_HoraT2Liga = SPIFFS.open("/vHoraT2Liga.txt", FILE_READ);
  HoraT2Liga = F_HoraT2Liga.readString();
  F_HoraT2Liga.close();

  File F_MinutoT2Liga = SPIFFS.open("/vMinutoT2Liga.txt", FILE_READ);
  MinutoT2Liga = F_MinutoT2Liga.readString();
  F_MinutoT2Liga.close();

  File F_HoraT2Desliga = SPIFFS.open("/vHoraT2Desliga.txt", FILE_READ);
  HoraT2Desliga = F_HoraT2Desliga.readString();
  F_HoraT2Desliga.close();

  File F_MinutoT2Desliga = SPIFFS.open("/vMinutoT2Desliga.txt", FILE_READ);
  MinutoT2Desliga = F_MinutoT2Desliga.readString();
  F_MinutoT2Desliga.close();


  page += String(F("<p>Liga "));
  page += String(HoraT2Liga);
  page += String(" : ");
  page += String(MinutoT2Liga);
  page += String(F("</p>"));

  page += String(F("<p>Desliga "));
  page += String(HoraT2Desliga);
  page += String(" : ");
  page += String(MinutoT2Desliga);
  page += String(F("</p>"));
  
  page += String(F("</body>"));
  page += String(F("</html>"));
 Server.send(200, "text/html", page);
}

void sendRedirect(String uri) {
  Server.sendHeader("Location", uri, true);
  Server.send(302, "text/plain", "");
  Server.client().stop();
}

void handleGPIO() {

  String HoraT1Liga;
  String MinutoT1Liga;
  String HoraT1Desliga;
  String MinutoT1Desliga;
  String HoraT2Liga;
  String MinutoT2Liga;
  String HoraT2Desliga;
  String MinutoT2Desliga;

  if (Server.arg("v27") == "low"){
    digitalWrite(output27, LOW);
    File F_output27State = SPIFFS.open("/output27State.txt", FILE_WRITE);
    F_output27State.print("ON");
    F_output27State.close();
    }
  else if (Server.arg("v27") == "high"){
    digitalWrite(output27, HIGH);
    File F_output27State = SPIFFS.open("/output27State.txt", FILE_WRITE);
    F_output27State.print("OFF");
    F_output27State.close();
    }
  
  if (Server.arg("v26") == "low"){
    digitalWrite(output26, LOW);
    File F_output26State = SPIFFS.open("/output26State.txt", FILE_WRITE);
    F_output26State.print("ON");
    F_output26State.close();
    }
  else if (Server.arg("v26") == "high"){
    digitalWrite(output26, HIGH);
    File F_output26State = SPIFFS.open("/output26State.txt", FILE_WRITE);
    F_output26State.print("OFF");
    F_output26State.close();
    }

  if (Server.arg("horaT1Liga")!= NULL){
    HoraT1Liga = Server.arg("horaT1Liga");
    File F_HoraT1Liga = SPIFFS.open("/vHoraT1Liga.txt", FILE_WRITE);
    F_HoraT1Liga.print(HoraT1Liga);
    F_HoraT1Liga.close();
    }

  if (Server.arg("minutoT1Liga")!= NULL){
    MinutoT1Liga = Server.arg("minutoT1Liga");
    File F_MinutoT1Liga = SPIFFS.open("/vMinutoT1Liga.txt", FILE_WRITE);
    F_MinutoT1Liga.print(MinutoT1Liga);
    F_MinutoT1Liga.close();
  }

  if (Server.arg("horaT1Desliga")!= NULL){
    HoraT1Desliga = Server.arg("horaT1Desliga");
    File F_HoraT1Desliga = SPIFFS.open("/vHoraT1Desliga.txt", FILE_WRITE);
    F_HoraT1Desliga.print(HoraT1Desliga);
    F_HoraT1Desliga.close();
  }

  if (Server.arg("minutoT1Desliga")!= NULL){
    MinutoT1Desliga = Server.arg("minutoT1Desliga");
    File F_MinutoT1Desliga = SPIFFS.open("/vMinutoT1Desliga.txt", FILE_WRITE);
    F_MinutoT1Desliga.print(MinutoT1Desliga);
    F_MinutoT1Desliga.close();
  }

  if (Server.arg("horaT2Liga")!= NULL){
    HoraT2Liga = Server.arg("horaT2Liga");
    File F_HoraT2Liga = SPIFFS.open("/vHoraT2Liga.txt", FILE_WRITE);
    F_HoraT2Liga.print(HoraT2Liga);
    F_HoraT2Liga.close();
  }

  if (Server.arg("minutoT2Liga")!= NULL){
    MinutoT2Liga = Server.arg("minutoT2Liga");
    File F_MinutoT2Liga = SPIFFS.open("/vMinutoT2Liga.txt", FILE_WRITE);
    F_MinutoT2Liga.print(MinutoT2Liga);
    F_MinutoT2Liga.close();
  }

  if (Server.arg("horaT2Desliga")!= NULL){
    HoraT2Desliga = Server.arg("horaT2Desliga");
    File F_HoraT2Desliga = SPIFFS.open("/vHoraT2Desliga.txt", FILE_WRITE);
    F_HoraT2Desliga.print(HoraT2Desliga);
    F_HoraT2Desliga.close();
  }

  if (Server.arg("minutoT2Desliga")!= NULL){
    MinutoT2Desliga = Server.arg("minutoT2Desliga");
    File F_MinutoT2Desliga = SPIFFS.open("/vMinutoT2Desliga.txt", FILE_WRITE);
    F_MinutoT2Desliga.print(MinutoT2Desliga);
    F_MinutoT2Desliga.close();
  }

  if (Server.arg("vT1Domingo") == "ON"){
    File F_T1Domingo = SPIFFS.open("/fT1Domingo.txt", FILE_WRITE);
    F_T1Domingo.print("0");
    F_T1Domingo.close();
    }
  else if (Server.arg("vT1Domingo") == "OFF"){
    File F_T1Domingo = SPIFFS.open("/fT1Domingo.txt", FILE_WRITE);
    F_T1Domingo.print("9");
    F_T1Domingo.close();
    }

  if (Server.arg("vT1Segunda") == "ON"){
    File F_T1Segunda = SPIFFS.open("/fT1Segunda.txt", FILE_WRITE);
    F_T1Segunda.print("1");
    F_T1Segunda.close();
    }
  else if (Server.arg("vT1Segunda") == "OFF"){
    File F_T1Segunda = SPIFFS.open("/fT1Segunda.txt", FILE_WRITE);
    F_T1Segunda.print("9");
    F_T1Segunda.close();
    }

  if (Server.arg("vT1Terca") == "ON"){
    File F_T1Terca = SPIFFS.open("/fT1Terca.txt", FILE_WRITE);
    F_T1Terca.print("2");
    F_T1Terca.close();
    }
  else if (Server.arg("vT1Terca") == "OFF"){
    File F_T1Terca = SPIFFS.open("/fT1Terca.txt", FILE_WRITE);
    F_T1Terca.print("9");
    F_T1Terca.close();
    }

  if (Server.arg("vT1Quarta") == "ON"){
    File F_T1Quarta = SPIFFS.open("/fT1Quarta.txt", FILE_WRITE);
    F_T1Quarta.print("3");
    F_T1Quarta.close();
    }
  else if (Server.arg("vT1Quarta") == "OFF"){
    File F_T1Quarta = SPIFFS.open("/fT1Quarta.txt", FILE_WRITE);
    F_T1Quarta.print("9");
    F_T1Quarta.close();
    }

  if (Server.arg("vT1Quinta") == "ON"){
    File F_T1Quinta = SPIFFS.open("/fT1Quinta.txt", FILE_WRITE);
    F_T1Quinta.print("4");
    F_T1Quinta.close();
    }
  else if (Server.arg("vT1Quinta") == "OFF"){
    File F_T1Quinta = SPIFFS.open("/fT1Quinta.txt", FILE_WRITE);
    F_T1Quinta.print("9");
    F_T1Quinta.close();
    }

  if (Server.arg("vT1Sexta") == "ON"){
    File F_T1Sexta = SPIFFS.open("/fT1Sexta.txt", FILE_WRITE);
    F_T1Sexta.print("5");
    F_T1Sexta.close();
    }
  else if (Server.arg("vT1Sexta") == "OFF"){
    File F_T1Sexta = SPIFFS.open("/fT1Sexta.txt", FILE_WRITE);
    F_T1Sexta.print("9");
    F_T1Sexta.close();
    }

  if (Server.arg("vT1Sabado") == "ON"){
    File F_T1Sabado = SPIFFS.open("/fT1Sabado.txt", FILE_WRITE);
    F_T1Sabado.print("6");
    F_T1Sabado.close();
    }
  else if (Server.arg("vT1Sabado") == "OFF"){
    File F_T1Sabado = SPIFFS.open("/fT1Sabado.txt", FILE_WRITE);
    F_T1Sabado.print("9");
    F_T1Sabado.close();
    }

  if (Server.arg("vT2Domingo") == "ON"){
    File F_T2Domingo = SPIFFS.open("/fT2Domingo.txt", FILE_WRITE);
    F_T2Domingo.print("0");
    F_T2Domingo.close();
    }
  else if (Server.arg("vT2Domingo") == "OFF"){
    File F_T2Domingo = SPIFFS.open("/fT2Domingo.txt", FILE_WRITE);
    F_T2Domingo.print("9");
    F_T2Domingo.close();
    }

  if (Server.arg("vT2Segunda") == "ON"){
    File F_T2Segunda = SPIFFS.open("/fT2Segunda.txt", FILE_WRITE);
    F_T2Segunda.print("1");
    F_T2Segunda.close();
    }
  else if (Server.arg("vT2Segunda") == "OFF"){
    File F_T2Segunda = SPIFFS.open("/fT2Segunda.txt", FILE_WRITE);
    F_T2Segunda.print("9");
    F_T2Segunda.close();
    }

  if (Server.arg("vT2Terca") == "ON"){
    File F_T2Terca = SPIFFS.open("/fT2Terca.txt", FILE_WRITE);
    F_T2Terca.print("2");
    F_T2Terca.close();
    }
  else if (Server.arg("vT2Terca") == "OFF"){
    File F_T2Terca = SPIFFS.open("/fT2Terca.txt", FILE_WRITE);
    F_T2Terca.print("9");
    F_T2Terca.close();
    }

  if (Server.arg("vT2Quarta") == "ON"){
    File F_T2Quarta = SPIFFS.open("/fT2Quarta.txt", FILE_WRITE);
    F_T2Quarta.print("3");
    F_T2Quarta.close();
    }
  else if (Server.arg("vT2Quarta") == "OFF"){
    File F_T2Quarta = SPIFFS.open("/fT2Quarta.txt", FILE_WRITE);
    F_T2Quarta.print("9");
    F_T2Quarta.close();
    }

  if (Server.arg("vT2Quinta") == "ON"){
    File F_T2Quinta = SPIFFS.open("/fT2Quinta.txt", FILE_WRITE);
    F_T2Quinta.print("4");
    F_T2Quinta.close();
    }
  else if (Server.arg("vT2Quinta") == "OFF"){
    File F_T2Quinta = SPIFFS.open("/fT2Quinta.txt", FILE_WRITE);
    F_T2Quinta.print("9");
    F_T2Quinta.close();
    }

  if (Server.arg("vT2Sexta") == "ON"){
    File F_T2Sexta = SPIFFS.open("/fT2Sexta.txt", FILE_WRITE);
    F_T2Sexta.print("5");
    F_T2Sexta.close();
    }
  else if (Server.arg("vT2Sexta") == "OFF"){
    File F_T2Sexta = SPIFFS.open("/fT2Sexta.txt", FILE_WRITE);
    F_T2Sexta.print("9");
    F_T2Sexta.close();
    }

  if (Server.arg("vT2Sabado") == "ON"){
    File F_T2Sabado = SPIFFS.open("/fT2Sabado.txt", FILE_WRITE);
    F_T2Sabado.print("6");
    F_T2Sabado.close();
    }
  else if (Server.arg("vT2Sabado") == "OFF"){
    File F_T2Sabado = SPIFFS.open("/fT2Sabado.txt", FILE_WRITE);
    F_T2Sabado.print("9");
    F_T2Sabado.close();
    }

  sendRedirect("/");
}

bool atDetect(IPAddress softapIP) {
  Serial.println("Captive portal started, SoftAP IP:" + softapIP.toString());
  return true;
}

void setup() {

  String output27State;
  String output26State;

  pinMode(output27, OUTPUT);
  pinMode(output26, OUTPUT);

  digitalWrite(output27, HIGH);
  digitalWrite(output26, HIGH);

  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Config.apid = "InteLight";
  Config.psk = "tomada123";
  Config.autoReconnect = true;
    //Config.homeUri = "/index.html";               // Sets home path of the sketch application
  Config.title = "Configuração Wi-Fi";

  Portal.config(Config);
  Portal.begin();

  Server.on("/", handleRoot);
  Server.on("/io", handleGPIO);

  // Starts user web site included the AutoConnect portal.
  Portal.onDetect(atDetect);
  if (Portal.begin()) {
    Serial.println("Started, IP:" + WiFi.localIP().toString());
  }
  else {
    Serial.println("Connection failed.");
    while (true) { yield(); }
  }

  timeClient.begin();
  timeClient.update();
  SPIFFS.begin();

  File F_output27State = SPIFFS.open("/output27State.txt", FILE_READ);
  output27State = F_output27State.readString();
  F_output27State.close();
  output27State == "OFF" ? digitalWrite(output27, HIGH) : digitalWrite(output27, LOW);

  File F_output26State = SPIFFS.open("/output26State.txt", FILE_READ);
  output26State = F_output26State.readString();
  F_output26State.close();
  output26State == "OFF" ? digitalWrite(output26, HIGH) : digitalWrite(output26, LOW);

}

void loop() {

// Variáveis para armazenar horas e datas
String horaFMT;            
String dia;
String horas;
String minutos; 
String segundos;

String HoraT1Liga;
String MinutoT1Liga;
String HoraT1Desliga;
String MinutoT1Desliga;
String HoraT2Liga;
String MinutoT2Liga;
String HoraT2Desliga;
String MinutoT2Desliga;

String T1Domingo;
String T1Segunda;
String T1Terca;
String T1Quarta;
String T1Quinta;
String T1Sexta;
String T1Sabado;

String T2Domingo;
String T2Segunda;
String T2Terca;
String T2Quarta;
String T2Quinta;
String T2Sexta;
String T2Sabado;

  Server.handleClient();
  Portal.handleRequest();   // Need to handle AutoConnect menu.
  if (WiFi.status() == WL_IDLE_STATUS) {
    ESP.restart();
    delay(1000);
  }

  timeClient.update();

  //Armazena na variável hora, o horário atual.
  horaFMT = timeClient.getFormattedTime();
  dia = timeClient.getDay(); //Dia da semana de 0 a 6, sendo 0 o domingo
  horas = timeClient.getHours();
  minutos = timeClient.getMinutes(); 
  segundos = timeClient.getSeconds();

  File F_HoraT1Liga = SPIFFS.open("/vHoraT1Liga.txt", FILE_READ);
  HoraT1Liga = F_HoraT1Liga.readString();
  F_HoraT1Liga.close();
  
  File F_MinutoT1Liga = SPIFFS.open("/vMinutoT1Liga.txt", FILE_READ);
  MinutoT1Liga = F_MinutoT1Liga.readString();
  F_MinutoT1Liga.close();

  File F_HoraT1Desliga = SPIFFS.open("/vHoraT1Desliga.txt", FILE_READ);
  HoraT1Desliga = F_HoraT1Desliga.readString();
  F_HoraT1Desliga.close();

  File F_MinutoT1Desliga = SPIFFS.open("/vMinutoT1Desliga.txt", FILE_READ);
  MinutoT1Desliga = F_MinutoT1Desliga.readString();
  F_MinutoT1Desliga.close();

  File F_HoraT2Liga = SPIFFS.open("/vHoraT2Liga.txt", FILE_READ);
  HoraT2Liga = F_HoraT2Liga.readString();
  F_HoraT2Liga.close();

  File F_MinutoT2Liga = SPIFFS.open("/vMinutoT2Liga.txt", FILE_READ);
  MinutoT2Liga = F_MinutoT2Liga.readString();
  F_MinutoT2Liga.close();

  File F_HoraT2Desliga = SPIFFS.open("/vHoraT2Desliga.txt", FILE_READ);
  HoraT2Desliga = F_HoraT2Desliga.readString();
  F_HoraT2Desliga.close();

  File F_MinutoT2Desliga = SPIFFS.open("/vMinutoT2Desliga.txt", FILE_READ);
  MinutoT2Desliga = F_MinutoT2Desliga.readString();
  F_MinutoT2Desliga.close();

  File F_T1Domingo = SPIFFS.open("/vT1Domingo.txt", FILE_READ);
  T1Domingo = F_T1Domingo.readString();
  F_T1Domingo.close();

  File F_T1Segunda = SPIFFS.open("/vT1Segunda.txt", FILE_READ);
  T1Segunda = F_T1Segunda.readString();
  F_T1Segunda.close();

  File F_T1Terca = SPIFFS.open("/vT1Terca.txt", FILE_READ);
  T1Terca = F_T1Terca.readString();
  F_T1Terca.close();

  File F_T1Quarta = SPIFFS.open("/vT1Quarta.txt", FILE_READ);
  T1Quarta = F_T1Quarta.readString();
  F_T1Quarta.close();

  File F_T1Quinta = SPIFFS.open("/vT1Quinta.txt", FILE_READ);
  T1Quinta = F_T1Quinta.readString();
  F_T1Quinta.close();

  File F_T1Sexta = SPIFFS.open("/vT1Sexta.txt", FILE_READ);
  T1Sexta = F_T1Sexta.readString();
  F_T1Sexta.close();

  File F_T1Sabado = SPIFFS.open("/vT1Sabado.txt", FILE_READ);
  T1Sabado = F_T1Sabado.readString();
  F_T1Sabado.close();

  File F_T2Domingo = SPIFFS.open("/vT2Domingo.txt", FILE_READ);
  T2Domingo = F_T2Domingo.readString();
  F_T2Domingo.close();

  File F_T2Segunda = SPIFFS.open("/vT2Segunda.txt", FILE_READ);
  T2Segunda = F_T2Segunda.readString();
  F_T2Segunda.close();

  File F_T2Terca = SPIFFS.open("/vT2Terca.txt", FILE_READ);
  T2Terca = F_T2Terca.readString();
  F_T2Terca.close();

  File F_T2Quarta = SPIFFS.open("/vT2Quarta.txt", FILE_READ);
  T2Quarta = F_T2Quarta.readString();
  F_T2Quarta.close();

  File F_T2Quinta = SPIFFS.open("/vT2Quinta.txt", FILE_READ);
  T2Quinta = F_T2Quinta.readString();
  F_T2Quinta.close();

  File F_T2Sexta = SPIFFS.open("/vT2Sexta.txt", FILE_READ);
  T2Sexta = F_T2Sexta.readString();
  F_T2Sexta.close();

  File F_T2Sabado = SPIFFS.open("/vT2Sabado.txt", FILE_READ);
  T2Sabado = F_T2Sabado.readString();
  F_T2Sabado.close();

  if (HoraT1Liga == horas && MinutoT1Liga == minutos && segundos == "0" && (T1Domingo || T1Segunda || T1Terca || T1Quarta || T1Quinta || T1Sexta || T1Sabado == dia)){
    digitalWrite(output27, LOW);
    File F_output27State = SPIFFS.open("/output27State.txt", FILE_WRITE);
    F_output27State.print("ON");
    F_output27State.close();
  } 
  if (HoraT1Desliga == horas && MinutoT1Desliga == minutos && segundos == "0" && (T1Domingo || T1Segunda || T1Terca || T1Quarta || T1Quinta || T1Sexta || T1Sabado == dia)){
    digitalWrite(output27, HIGH);
    File F_output27State = SPIFFS.open("/output27State.txt", FILE_WRITE);
    F_output27State.print("OFF");
    F_output27State.close();
  }
  if (HoraT2Liga == horas && MinutoT2Liga == minutos && segundos == "0" && (T2Domingo || T2Segunda || T2Terca || T2Quarta || T2Quinta || T2Sexta || T2Sabado == dia)){
    digitalWrite(output26, LOW);
    File F_output26State = SPIFFS.open("/output26State.txt", FILE_WRITE);
    F_output26State.print("ON");
    F_output26State.close();
  } 
  if (HoraT2Desliga == horas && MinutoT2Desliga == minutos && segundos == "0" && (T2Domingo || T2Segunda || T2Terca || T2Quarta || T2Quinta || T2Sexta || T2Sabado == dia)){
    digitalWrite(output26, HIGH);
    File F_output26State = SPIFFS.open("/output26State.txt", FILE_WRITE);
    F_output26State.print("OFF");
    F_output26State.close();
  }
}
