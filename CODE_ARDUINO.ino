#include <Servo.h>

//On définit ici ce qui suit par souci de clarté (pour éviter d'avoir directement des valeurs 1,2,3,... ou A1, A2,... dans le code, ce qui serait très galère chaque fois qu'on refait le circuit.
//Du coup ça permet de voir directement qu'est ce qui correspond à quoi
#define INFRA_HAUT A0
#define INFRA_BAS A1
#define INFRA_CIEL A2

#define CONTACT_HAUT 3
#define CONTACT_BAS 4
#define CONTACT_CIEL 5
#define CONTACT_TERRE 6

//Haut et bas --> concernent ce qui se passe au niveau des pinces
//Ciel et terre --> concernent ce qui se passe au niveau des extrémités du robot (tout en haut / tout en bas)


Servo moteur_principal;
Servo pince_bas;
Servo pince_haut;

const int LIMITE_INFRA = 100;  //on dira que quand le capteur mesure une valeur inférieure à ce seuil, c'est qu'il est en train de détecter


void setup() {  // exécuté une seule fois au tout début --> en gros on dit à l'Arduino ce qui se trouve à chacun de ses pins

  //Moteurs
  moteur_principal.attach(0);
  pince_bas.attach(1);
  pince_haut.attach(2);

  //Capteurs infrarouges
  pinMode(INFRA_HAUT, INPUT);
  pinMode(INFRA_BAS, INPUT);
  pinMode(INFRA_CIEL, INPUT);

  //Capteurs de contact
  pinMode(CONTACT_HAUT,INPUT);
  pinMode(CONTACT_BAS,INPUT);
  pinMode(CONTACT_CIEL,INPUT); 
  pinMode(CONTACT_TERRE,INPUT);  
  
}



void loop() { //répété en boucle

  //Booléens liés aux capteurs pour voir s'ils détectent ou pas
  boolean detecte_infra_haut = analogRead(INFRA_HAUT) > LIMITE_INFRA;
  boolean detecte_infra_bas = analogRead(INFRA_BAS) > LIMITE_INFRA;
  boolean detecte_infra_ciel = analogRead(INFRA_CIEL) > LIMITE_INFRA;
  boolean detecte_contact_haut = digitalRead(CONTACT_HAUT);
  boolean detecte_contact_bas = digitalRead(CONTACT_BAS);
  boolean detecte_contact_ciel = digitalRead(CONTACT_CIEL);
  boolean detecte_contact_terre = digitalRead(CONTACT_TERRE);

  // CODE PRINCIPAL

  

}
