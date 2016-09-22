// Contrôle commande de moteur brushless de modélisme
// Sortie des impulsions vers le contrôleur par D13.

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
// *                                   setup                                  *
// ****************************************************************************

void setup()//Initialise l'utilisation des PINs de l'arduino
{
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
		EtatBoutons();

		int Instructions = DIST * 4;

		Affichage(1, Afficheurs[Instructions   / 10]);	// Affichage dizaines
		Affichage(2, Afficheurs[(Instructions) % 10]);	// Affichage unités
	}
}


// ****************************************************************************
// *                       Instructions par les boutons                       *
// ****************************************************************************

void EtatBoutons(){
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