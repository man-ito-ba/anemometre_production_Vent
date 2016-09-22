/* anemometre production */
// 2 boutons, qui incrémentent en 4, de 0 à 20.
// un afficheur donne le résultat
// le moteur envoie plus ou moins de vent

/*
3 parties :
1. Instructions données au moteur PWM à partir de 2 boutons + et -
2. Affichage des consignes sur deux afficheurs à 7 segments
3. Accélération ou décélération du moteur PWM en fonction des consignes
*/

/*	Un point sur les branchements

	A0		distance
	A1
	A2		btn_plus
	A3		btn_minus
	A4		digit des dizaines "e"
	A5		digit des dizaines "d"

	D0		digit des dizaines "f"
	D1		digit des unités "a"
	D2		digit des dizaines "c"
	D3		digit des dizaines "b"
	D4		digit des dizaines "a"
	D5		digit des dizaines "g"
	D6		digit des unités "e"
	D7		digit des unités "c"
	D8		digit des unités "d"
	D9		sortie_servo
	D10		digit des unités "b"
	D11		sortie_tension
	D12		digit des unités "g"
	D13		digit des unités "f"
*/

/*Code Capteur & Deux Afficheurs*/

/* Instructions */
int BoutonPlus = A2;
int BoutonMoins = A3;
bool Etat_Bouton;
int Instructions, Plus, Moins;

// partie PWM
const int SortiePWM = 9;
// Les deux déclarations suivantes sont là au cas où mais je ne les utilise pas
// int sortie_tension  = 11; 	// sortie tension modulé par B.P. vers A0 (il s'agit d'une ligne de code que j'ai pris de chez ton code destiné au UNO)
// int DistancePWM     = A0;	// PIN de conversion analogique digitale du module arduino, utilisé pour lire la tension du B.P. qui sert d'accélérateur sortie en PIN 11 (pareil, ça vient de ton programme, je ne comprends pas son rôle)

int InstructionsPWM;		// variable qui sera utilisée plus tard pour le contrôle de la vitesse du moteur

/* Affichage */	
int Afficheurs[10] = {		// Tableau d'affichage des chiffres
	B00111111 , // 0
	B00000110 , // 1
	B01011011 , // 2
	B01001111 , // 3
	B01100110 , // 4
	B01101101 , // 5
	B01111101 , // 6
	B00000111 , // 7
	B01111111 , // 8
	B01101111 };

/* Infos données par F. pour l'adressage :
	Dizaines
		a = D4
		f = D12
		e = D6
		d = A6
		c = D7
		g = D11
		b = A7

	Unités
		a = D1
		f = D0
		e = A5
		d = A4
		c = D2
		g = D5
		b = D3

	*/

// Adressage
int Dizaines[7] = {
	 4 ,	// a
	A7 ,	// b
	 7 ,	// c
	A6 , 	// d
	 6 ,	// e
	12 ,	// f
	11	};	// g

int Unites[7] = {
	 1 ,	// a
	 3 , 	// b
	 2 , 	// c
	 A4 , 	// d
	 A5 ,	// e
	 0 ,	// f
	 5 };	// g


// ****************************************************************************
// *                                   setup                                  *
// ****************************************************************************

void setup() {
	for (int i = 0; i <= 13; ++i){
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}

	// Boutons
	pinMode(BoutonPlus, INPUT);
	pinMode(BoutonMoins, INPUT);
	Etat_Bouton, Plus, Moins, Instructions, InstructionsPWM = 0;

	pinMode(A4, OUTPUT);
	digitalWrite(A4, LOW);
	pinMode(A5, OUTPUT);
	digitalWrite(A5, LOW);

}


// ****************************************************************************
// *                             boucle principale                            *
// ****************************************************************************

void loop() {
	InstructionsOperateur();						// Instructions par les boutons + et –

	PWM();											// Mise en marche du moteur PWM

	Affichage(1, Afficheurs[Instructions / 10]);	// Affichage dizaines
	Affichage(2, Afficheurs[(Instructions) % 10]);	// Affichage unités
	
	delay(1); 										// à toi de le virer de toute manière si tu le souhaites
}


// ****************************************************************************
// *                       Instructions par les boutons                       *
// ****************************************************************************

void InstructionsOperateur(){
	Etat_Bouton = digitalRead(BoutonPlus);
	if( Etat_Bouton != Plus && Etat_Bouton == 1 ){
		Instructions = Instructions + 4;
	}
	Plus = Etat_Bouton;
	
	if(Instructions > 20){
	    Instructions = 20;
	}

	if(Instructions < 0){
	    Instructions = 0;
	}

	Etat_Bouton = digitalRead(BoutonMoins);
	if( Etat_Bouton != Moins && Etat_Bouton == 1 ){
	    Instructions = Instructions - 4;
	}
	Moins = Etat_Bouton;
}


// ****************************************************************************
// *                                Moteur PWM                                *
// ****************************************************************************

void PWM(){
	InstructionsPWM = map(Instructions, 0, 20, 0, 255);	// À toi de changer la valeur max en la passant peut-être à 254 si le moteur est fragile.
	analogWrite(SortiePWM, InstructionsPWM);			// C'est ici que les Instructions sont utilisées concrètement pour contrôler le moteur
}


// ****************************************************************************
// *                          Affichage double digit                          *
// ****************************************************************************

void Affichage(int Segment, int Digit) {
	if(Digit==0){
	    return;
	}
	int* Segment_Actuel = ((Segment == 1) ? Dizaines : Unites); // choix du Segment (à l'aide d'un pointeur, identifié ici par "*")
	for (int i = 0; i < 7; ++i) {
		digitalWrite(Segment_Actuel[i], Digit & 1); // on écrit le bit le moins signifiant
		Digit >>= 1;
	}
}