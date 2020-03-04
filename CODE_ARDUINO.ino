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

//                                    Haut et bas --> concerne ce qui se passe au niveau des pinces
//                                    Ciel et terre --> concerne ce qui se passe au niveau des extrémités du robot (tout en haut / tout en bas)


Servo moteur_principal;    //moteur à rotation continue
Servo pince_bas;
Servo pince_haut;

const int LIMITE_INFRA = 100;  //on dira que quand le capteur mesure une valeur inférieure à ce seuil, c'est qu'il est en train de détecter

const int LIMITE_ROTATION_PINCE = 100;   //c'est un seuil qui ne sera pas dépassé pour la rotation des pinces (--> permet d'éviter des dégradations à cause d'une rotation trop grande,
//                                                                                                             par exemple si la pince est bien sur l'échelon mais le contact n'est pas détecté)

const int t =60;  //sera utilisé dans les delay(...) , un temps t sera attendu avant chaque itération dans les boucles (utilisé pour les rotations des petits servos) --> contrôle sur la vitesse de rotation



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

  //Booléens liés aux capteurs pour voir s'ils détectent ou pas :                  si c'est true, le capteur est en train de détecter
  boolean detecte_infra_haut;
  boolean detecte_infra_bas;
  boolean detecte_infra_ciel = analogRead(INFRA_CIEL) < LIMITE_INFRA;
  boolean detecte_contact_haut = (digitalRead(CONTACT_HAUT) == 1);
  boolean detecte_contact_bas = (digitalRead(CONTACT_BAS) == 1);
  boolean detecte_contact_ciel = (digitalRead(CONTACT_CIEL) == 1);
  boolean detecte_contact_terre = (digitalRead(CONTACT_TERRE) == 1);

  // CODE PRINCIPAL si le robot commence en bas --> montée simple

  if(detecte_contact_bas){      // MOUVEMENT DE LA PARTIE "HAUT"
    int rotation_ph = 90;
    for(rotation_ph = 90; rotation_ph > 0; rotation_ph--)  //valeurs peut-être fausses, à déterminer quand on fera des tests
    {
      pince_haut.write(rotation_ph);          //ici .write(angle) permet que le servo aille à un angle précis (ce ne sera pas pareil pour le moteur principal, qui est à rotation continue)
      delay(t);
    }                           //ce for permet de décrocher la pince
    
    detecte_infra_haut = false;
    moteur_principal.write(0);
    //delay(1000);
    
    while(!(detecte_infra_haut or detecte_infra_ciel or detecte_contact_ciel)){     //le moteur tourne tant que l'échelon n'est pas détecté et tant qu'il n'y a pas de problème
      detecte_infra_haut = analogRead(INFRA_HAUT) < LIMITE_INFRA; 
      detecte_contact_ciel = (digitalRead(CONTACT_CIEL) == 1);
      detecte_infra_ciel = analogRead(INFRA_CIEL) < LIMITE_INFRA;
    }                           //la fonction .write(...) permet que ça tourne en continu dans un sens, l'argument permet de contrôler la vitesse (0 pour un sens, 180 pour l'autre, 94 pour l'arrêt) (pas pareil que pour les petits servos!)
                                 
    moteur_principal.writeMicrosecond(1510);  // on stoppe d'office le moteur
    
    //                              pour plus de précision on peut utiliser .writeMicrosecond()
    
    if(!(detecte_contact_ciel or detecte_infra_ciel)){  //ne sera pas lu si un problème est survenu (--> si c'est le cas, retour en début de loop)
      
      //pince_haut.write(100);                !!!!!!!!!!!!! à vérifier !!!!!!!!!!!
      detecte_contact_haut = (digitalRead(CONTACT_HAUT) == 1);   
      while( ! detecte_contact_haut or rotation_ph <= LIMITE_ROTATION_PINCE ){  //ce while permet que la pince tourne tant que le contact avec l'échelon n'est pas détecté
        pince_haut.write(rotation_ph);
        rotation_ph+=1;
        detecte_contact_haut = (digitalRead(CONTACT_HAUT) == 1);
        delay(t);                                //petit t --> grande vitesse de rotation
      }
      if(detecte_contact_haut){       //MOUVEMENT DE LA PARTIE "BAS", la logique est exactement la même que pour la partie du haut
        int rotation_pb = 90;
        for(rotation_pb = 90; rotation_pb > 0; rotation_pb--)  //valeurs peut-être fausses, à déterminer quand on fera des tests
        {
          pince_bas.write(rotation_pb);
          delay(t);
        }
        detecte_infra_bas = false;
        moteur_principal.write(180);           // Le moteur principal tourne dans l'autre sens
        //delay(1000);
        while(!detecte_infra_bas){             //!!!!!!!!!! A ajouter : detecte_contact_terre !!!!!!!!!!!!! 
          detecte_infra_bas = analogRead(INFRA_BAS) < LIMITE_INFRA;
        }
        moteur_principal.writeMicrosecond(1510);
        detecte_contact_bas = (digitalRead(CONTACT_BAS) == 1);
        while( ! detecte_contact_bas or rotation_pb <= LIMITE_ROTATION_PINCE ){  
          pince_bas.write(rotation_pb);
          rotation_pb+=1;
          detecte_contact_bas = (digitalRead(CONTACT_BAS) == 1);
          delay(t);
        }  
      }
    }
  }   
}     //                           A AJOUTER : faire en sorte que tout s'arrête si rotation_ph dépasse la limite   
