// Contrôle commande de moteur brushless de modélisme
// Sortie des impulsions vers le contrôleur par D13.


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

int vitesse = 0;			// Valeur de la mesure de la tension du potentionmère sur A0
unsigned int temps_pulse;	// largeur d'impulsion de la sortie

int sortie_servo=9; // numéro de PIN du module arduino NANO utilisé en sortie pour la connexion vers le contrôleur du moteur brushless.
int sortie_tension=11; // sortie tension modulé par B.P. vers A0
unsigned long debut_periode; // pour noter le début de chaque période de 20 millisecondes qui doit séparer les impulsions de commande du contrôleur brushless.

int distance = A0; // numéro de PIN de conversion analogique digitale du module arduino
// utilisé pour lire la tension du B.P. qui sert d'accélérateur sortie en PIN 11

const int btn_minus = A3;
const int btn_plus = A2;
int etat_bouton;
int DIST;
int memoire_plus = HIGH;
int memoire_minus = HIGH;

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
// *                            fonction de mesure                            *
// ****************************************************************************
// Alors en général je place toujours les fonctions en bas, après la fonction loop puisque setup() et loop() sont en général celles qui définissent un programme, mais savoir pourquoi, sur tes deux fonctions, celle-ci fait planter le programme si je ne la laisse pas avant setup :/

void mesures(void) // fonction appelée pour mesurer l'entrée analogique
{
	vitesse = 0;
	//la valeur nommée vitesse est moyennée pour diminuer l'effet du bruit de cette valeur analogique
	for(int ii=0; ii<16; ii++)
	{
		vitesse += analogRead(distance); 	// Notation qui équivaut à écrire : "vitesse = vitesse + analogRead(distance);"
	}
	vitesse = (vitesse >> 4);				// Alors ça c'est un bitshift right si j'ai bien suivi, c.à.d. une autre façon d'effectuer une multiplication (ici, par 4). D'après mes recherches, utiliser le signe de multiplication dans ce type de cas est bien plus clair pour ceux qui relisent le code, et absolument **aussi pratique**.
	// vitesse = vitesse * 4;
}


// ****************************************************************************
// *                                   setup                                  *
// ****************************************************************************

void setup()//Initialise l'utilisation des PINs de l'arduino
{
	pinMode(sortie_servo,OUTPUT);	// PIN D11 en sortie
	digitalWrite(sortie_servo,LOW);	// PIN D11 à l'état bas
	
	pinMode(distance, INPUT);
	
	// Serial.begin(9600);			// Comme on utilise les pins 0 et 1, je désactive l'engagement du Serial qui va sinon géner l'emploi de ces pins (ils assurant la transmission et réception de donnée avec le Serial)
	
	analogReference(DEFAULT);		// référence du convertisseur (je ne comprends pas pourquoi tu utilises cette fonction ; elle est utile quand le pin AREF est utilisé, mais surtout quand le voltage de référence a été modifié à un autre moment tu programme (en appelant par exemple "analogReference(EXTERNAL);" par exemple). Là ce ne semble pas être le cas, si ? Dans loop, tu utilises la même fonction analogReference(DEFAULT). Donc en théorie, puisqu'à aucun moment le programme ne demande de prendre en compte une autre valeur de voltage, il me semble que ton convertisseur continue à convertir ton entrée entre 0 et 5 V.)
	
	pinMode(btn_plus, INPUT);		
	pinMode(btn_minus, INPUT);
}


// ****************************************************************************
// *                             boucle principale                            *
// ****************************************************************************

void loop()
{
	while(1)
	{
		EtatBouton();									// On regarde ce qui se passe sur les boutons
		
		SortieTension();								// On traduit ça en tension sur le pin 11
			
		analogReference(DEFAULT);

		debut_periode = micros();						// enregistre le début de la boucle en microsecondes
		
		mesures(); 										// prendre la tension du potentiomètre accélérateur
		
		faire_pulse(vitesse);							// fonction qui génère l'impulsion

		int Instructions = DIST * 4;

		Affichage(1, Afficheurs[Instructions   / 10]);	// Affichage dizaines
		Affichage(2, Afficheurs[(Instructions) % 10]);	// Affichage unités

		while( (micros()-debut_periode) < 19999); 		// attendre les 20 millisecondes pour faire la période suivante 
	}
}


// ****************************************************************************
// *                       Instructions par les boutons                       *
// ****************************************************************************

void EtatBouton(){
	etat_bouton = digitalRead(btn_plus);
	
	if((etat_bouton != memoire_plus) && (etat_bouton == LOW)){
		DIST++; //on incrémente la variable de la consigne
	}

	memoire_plus = etat_bouton; //on enregistre l'état du bouton pour le tour suivant

	//et maintenant pareil pour le bouton qui décrémente
	etat_bouton = digitalRead(btn_minus); //lecture de son état
	
	//Si le bouton a un état différent que celui enregistré ET que cet état est "appuyé"
	if((etat_bouton != memoire_minus) && (etat_bouton == LOW)){
		DIST--; //on décrémente la valeur de la consigne
	}
	memoire_minus = etat_bouton; //on enregistre l'état du bouton pour le tour suivant
}

void SortieTension(){
	// on applique des limites au nombre pour ne pas dépasser 5
	if(DIST > 5)
	{
		analogWrite (11, 85);
		DIST = 5;
	}

	// on applique des limites au nombre pour ne pas aller en dessous de 0
	if(DIST < 0)
	{
		analogWrite (11, 0);
		DIST = 0;
	}
	
	// ====== Ici, on indique les valeurs à envoyer par sortie_tension dans chaque cas
	if(DIST < 1)
	{
		analogWrite (11, 0);
	}
	
	if(DIST >= 1)
	{
		analogWrite (11, 34);
	}
	
	if(DIST >= 2)
	{
		 analogWrite (11, 55);
	}
	
	if(DIST >=3)
	{
		analogWrite (11, 65);
	}
	
	if(DIST >=4)
	{
		analogWrite (11, 75);
	}
	
	if(DIST >=5)
	{
		analogWrite (11, 85);
	}
}

// ****************************************************************************
// *                      fonction d'impulsion du moteur                      *
// ****************************************************************************

void faire_pulse(int commande)
{
	// On utilise une largeur minimale d'impulsion de 0,99 ms
	// et un maximum de 0,99 + 1,023 = 2,013 ms
	temps_pulse = (990 + constrain(commande,0,1023));
	// constrain utilisé pour que la durée de l'impulsion reste dans les
	// limites précédentes, même en cas d'erreur sur commande.
	digitalWrite(sortie_servo,HIGH); // mise à l'état haut de D9
	delayMicroseconds(temps_pulse);	// maintien à l'état haut
	digitalWrite(sortie_servo,LOW);	// retour à l'état bas
}


// ****************************************************************************
// *                           fonction d'affichage                           *
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
