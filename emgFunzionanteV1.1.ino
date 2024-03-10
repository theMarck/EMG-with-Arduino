#include <Servo.h>

// dimmensione dell' array usato collezionare i dati in input, piu' DIM e' grande piu' la precisione del movimento dell' servomotore sara' mogliore
#define DIM 50

// la MACRO SOGLIA rappresenta il valore per la quale arduino riconosce se un muscolo e' contratto o meno, cambia in base all' adesione degli elettrodi e in base all' hardware
#define SOGLIA 100

// dichiarazione variabile di tipo servo
Servo SERVO_1;


// valoreIniziale rappresenta il primo valore in assoluto che arduino raccoglie
int valoreIniziale=0;

/* Per avere un movimento del servo motore il piu' fluido possibile ho deciso di creare un array che colleziona DIM dati in input e successivamente fare la media.
   Cosi' faccendo nel serial plotter otterremo delle curve (con valori simili tra loro) che ci permettono di gestire il servo motore in maniera piu' lieare.
   Se non si fa cio' si otterrano dei valori diversi tra loro che che faranno muovere il srvo motore a scatti.*/

int valori[DIM];
int media=0;

/*spostaValori e' una funzione che inserisce i nuovi valori e li sposta nella coda della lista*/
void spostaValori(int valori, int dim);

/*calcolaMedia e' una funzione che calcola la media di tutti i valori dell' array*/
int calcolaMedia();

void setup() {

  Serial.begin(9600);
  SERVO_1.attach(9);

}


void loop() {

  // stampa delle media dei valori in input 
  Serial.println(media);

  // lettura dei valori in input
  valoreIniziale = analogRead(A0);
  valori[0]= valoreIniziale;
  media = calcolaMedia(valori, DIM);
  spostaValori(valori, DIM);
  
  // se la media dei valori e' maggiore della soglia
  // imposta il servo motore a 170 gradi
  if ( media > SOGLIA){  // prova a sostituire 100 con media +100
    
    SERVO_1.write(170);

  }else{         //altrimenti imposta il servo motore a 10 gradi
    
    SERVO_1.write(10);

  }
  
  

}

void spostaValori(int valori[], int dim){

  int i=0;

  for(i=dim-1; i>0; i--){

    valori[i]= valori[i-1];

  }

}

int calcolaMedia(int valori[], int dim){

  int i, somma=0, media=0;
  
  
  for(i=0; i<dim-1; i++){

    somma = somma + valori[i];

  }

  media=somma/dim;

  return media;

}

