// Contrôle commande de moteur brushless de modélisme
// Sortie des impulsions vers le contrôleur par D13.


int vitesse = 0;					 // Valeur de la mesure de la tension du potentionmère sur A0
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


void setup()//Initialise l'utilisation des PINs de l'arduino
{
	pinMode(sortie_servo,OUTPUT);	// PIN D11 en sortie
	digitalWrite(sortie_servo,LOW);	// PIN D11 à l'état bas
	
	pinMode(distance, INPUT);
	
	Serial.begin(9600);
	
	analogReference(DEFAULT);		// référence du convertisseur
	
	pinMode(btn_plus, INPUT);		
	pinMode(btn_minus, INPUT);
}


void loop()
{
	// valeur pwm enregistrée jusqu'à ce que le reste du programme soit effectué
	// pendant calcul de la moyenne et de l'affichage

	// un programme qui s'effectue en fond pendant que tu en fais un autre

	// 1. vérifier mon adressage
	// 2. intégrer les digits sur son programme

	while(1)
	{
		etat_bouton = digitalRead(btn_plus);
	
		if((etat_bouton != memoire_plus) && (etat_bouton == LOW))
		{
			DIST++; //on incrémente la variable de la consigne
		}
	
		memoire_plus = etat_bouton; //on enregistre l'état du bouton pour le tour suivant
	
		//et maintenant pareil pour le bouton qui décrémente
		etat_bouton = digitalRead(btn_minus); //lecture de son état
		
		//Si le bouton a un état différent que celui enregistré ET que cet état est "appuyé"
		if((etat_bouton != memoire_minus) && (etat_bouton == LOW))
		{
			DIST--; //on décrémente la valeur de la consigne
		}
		memoire_minus = etat_bouton; //on enregistre l'état du bouton pour le tour suivant
		
		//on applique des limites au nombre pour ne pas dépasser 5 ou 0
		if(DIST > 5)
		{
			analogWrite (11, 85);
			DIST = 5;
		}
		if(DIST < 0)
		{
			analogWrite (11, 0);
			DIST = 0;
		}
		
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
			
		analogReference(DEFAULT); 
		debut_periode = micros();	// enregistre le début de la boucle en microsecondes
		mesures(); // prendre la tension du potentiomètre accélérateur
		faire_pulse(vitesse);// appeler la fonction qui génrère l'impulsion

		while( (micros()-debut_periode) < 19999); 
		// attendre les 20 millisecondes pour faire la période suivante 
	}	
}

void mesures(void) // fonction appelée pour mesurer l'entrée analogique
{
	vitesse = 0;
	//la valeur nommée vitesse est moyennée pour diminuer l'effet du bruit de cette valeur analogique
	for(int ii=0; ii<16; ii++)
	{
	vitesse += analogRead(distance);
	}
	vitesse = (vitesse >>4);
}

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