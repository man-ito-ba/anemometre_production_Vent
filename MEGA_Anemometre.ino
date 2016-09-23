// ==== Pins liés à l'affichage
	const int DIGIT_C1e=17;
	const int DIGIT_C1d=18;
	const int DIGIT_C1c=19;
	const int DIGIT_C1g=15;
	const int DIGIT_C1f=16;
	const int DIGIT_C1a=21;
	const int DIGIT_C1b=20;

	const int DIGIT_C2e=26;
	const int DIGIT_C2d=25;
	const int DIGIT_C2c=24;
	const int DIGIT_C2g=28;
	const int DIGIT_C2f=27;
	const int DIGIT_C2a=22;
	const int DIGIT_C2b=23;

	const int DIGIT_V1e=34;
	const int DIGIT_V1d=33;
	const int DIGIT_V1c=32;
	const int DIGIT_V1g=36;
	const int DIGIT_V1f=35;
	const int DIGIT_V1a=30;
	const int DIGIT_V1b=31;

	const int DIGIT_V2e=42;
	const int DIGIT_V2d=41;
	const int DIGIT_V2c=40;
	const int DIGIT_V2dp=45;
	const int DIGIT_V2g=44;
	const int DIGIT_V2f=43;
	const int DIGIT_V2a=38;
	const int DIGIT_V2b=39; //declaration constante de broche

	const int DIGIT_V3e=50;
	const int DIGIT_V3d=49;
	const int DIGIT_V3c=48;
	const int DIGIT_V3g=52;
	const int DIGIT_V3f=51;
	const int DIGIT_V3a=46;
	const int DIGIT_V3b=47; //declaration constante de broche

const int LEDVt = A6;
const int LEDRg = A7;

int CmdeB1=A5;
int CmdeB2=A1;
int CmdeB3=A2;

// Variables destinées au calcul de la moyenne
const int NbLectures = 5;	// à modifier pour augmenter temps de calcul de moyenne ; Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau. J'ai réduit à 5 pour accélérer le programme.
int Tableau[NbLectures];	// Tableau recevant le nombre de signaux analogiques définit juste au dessus par la variable NbLectures
int IndexTableau = 0;		// l'index de position du tableau
int Total;
int Moyenne;


// ****************************************************************************
// *                                   Setup                                  *
// ****************************************************************************

void setup()	 {
	Moyenne, Total = 0;				// Mise à zéro des variables pour éviter les résultats aléatoires (ça arrive parfois quand on le fait pas)

	// ==== Initialisation des pins liés à l'affichage
		pinMode(DIGIT_C1e, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C1d, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C1c, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C1g, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C1f, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C1a, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C1b, OUTPUT); //met la broche en sortie 

		pinMode(DIGIT_C2e, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C2d, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C2c, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C2g, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C2f, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C2a, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_C2b, OUTPUT); //met la broche en sortie 

		pinMode(DIGIT_V1e, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V1d, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V1c, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V1g, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V1f, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V1a, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V1b, OUTPUT); //met la broche en sortie 

		pinMode(DIGIT_V2e, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2d, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2c, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2dp, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2g, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2f, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2a, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V2b, OUTPUT); //met la broche en sortie

		pinMode(DIGIT_V3e, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V3d, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V3c, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V3g, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V3f, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V3a, OUTPUT); //met la broche en sortie 
		pinMode(DIGIT_V3b, OUTPUT); //met la broche en sortie 

		pinMode(LEDVt, OUTPUT); //met la broche en sortie 
		pinMode(LEDRg, OUTPUT); //met la broche en sortie 

		pinMode(CmdeB1, OUTPUT); //met la broche en sortie 
		pinMode(CmdeB2, OUTPUT); //met la broche en sortie 
		pinMode(CmdeB3, OUTPUT); //met la broche en sortie 

	analogWrite(CmdeB1, LOW);		// ???
}


// ****************************************************************************
// *                             Boucle principale                            *
// ****************************************************************************

void loop(){  
	LectureBatteries();
	MoyenneGlissante();
	Affichage();
}

// ****************************************************************************
// *                        Vérification des batteries                        *
// ****************************************************************************

void LectureBatteries(){
	int MV1 = analogRead(A4);
	float MV1b = (MV1 * (5.000 / 1022)*1000); //valeur en MILIVOLT
	
	int MV2 = analogRead(A3);
	float MV2b = (MV2 * (5.000 / 1022)*1000); //valeur en MILIVOLT

	if(MV1b > 4900)
	{
		digitalWrite(CmdeB1,1);
		digitalWrite(CmdeB2,0);
		digitalWrite(CmdeB3,0);
		digitalWrite(LEDVt,1);
		digitalWrite(LEDRg,0);
	} 
	if(MV1b < 5300 && MV2b > 4900)
	{
		digitalWrite(CmdeB2,1);
		digitalWrite(CmdeB3,0);
		digitalWrite(LEDVt,1);
		digitalWrite(LEDRg,1);
	}
	if(MV1b < 5300 && MV2b < 5200)
	{
		digitalWrite(CmdeB2,0);
		digitalWrite(CmdeB3,1);
		digitalWrite(LEDVt,0);
		digitalWrite(LEDRg,1);
	}
}

// ****************************************************************************
// *                           Calcul de la moyenne                           *
// ****************************************************************************

int MoyenneGlissante(){	 /*Tableau glissant (running average)*/
	int ANEMOMETRE = analogRead(A0);
	float Anemometre = (ANEMOMETRE * (5.00 / 1023)*1000); //valeur en MILIVOLT
	
	float Anemometre2 = map(Anemometre, 620, 3000, 00, 2000);
	Anemometre2 = Anemometre2 / 100.00 ;
	/*----------*/									// Début du calcul
	Total = Total - Tableau[IndexTableau];			// soustraire à la position précédente
	Tableau[IndexTableau] = Anemometre2;			// lecture du capteur
	Total = Total + Tableau[IndexTableau];			// ajouter la lecture au tableau
	IndexTableau = IndexTableau + 1;				// avancer à la position suivante dans le tableau (= "glisser")
	if (IndexTableau >= NbLectures) 
	{
		IndexTableau = 0;							// Si on est à la fin du tableau... recommencer au début
	}
	Moyenne = Total / NbLectures;					// Calcul de la moyenne à partir des valeurs accumulées lors du glissement
	delay(100); 									// délai entre les lectures
	return(Moyenne);								// la fonction renvoie la valeur de Moyenne à la fonction Loop
}


// ****************************************************************************
// *                                 Affichage                                *
// ****************************************************************************

void Affichage(){
	// Affichage
		if(Moyenne < 0.5)
		{
		V10(), V20(), V30();
		}
		if(Moyenne >= 0.5 && Moyenne < 1)
		{
		V10(), V20(), V35();
		}
		if(Moyenne >= 1 && Moyenne < 1.5)
		{
		V10(), V21(), V30();
		}
		if(Moyenne >= 1.5 && Moyenne < 2)
		{
		V10(), V21(), V35();
		}
		if(Moyenne >= 2 && Moyenne < 2.5)
		{
		V10(), V22(), V30();
		}
		if(Moyenne >= 2.5 && Moyenne < 3)
		{
		V10(), V22(), V35();
		}
		if(Moyenne >= 3 && Moyenne < 3.5)
		{
		V10(), V23(), V30();
		}
		if(Moyenne >= 3.5 && Moyenne < 4)
		{
		V10(), V23(), V35();
		}
		if(Moyenne >= 4 && Moyenne < 4.5)
		{
		V10(), V24(), V30();
		}
		if(Moyenne >= 4.5 && Moyenne < 5)
		{
		V10(), V24(), V35();
		}
		if(Moyenne >= 5 && Moyenne < 5.5)
		{
		V10(), V25(), V30();
		}
		if(Moyenne >= 5.5 && Moyenne < 6)
		{
		V10(), V25(), V35();
		}
		if(Moyenne >= 6 && Moyenne < 6.5)
		{
		V10(), V26(), V30();
		}
		if(Moyenne >= 6.5 && Moyenne < 7)
		{
		V10(), V26(), V35();
		}
		if(Moyenne >= 7 && Moyenne < 7.5)
		{
		V10(), V27(), V30();
		}
		if(Moyenne >= 7.5 && Moyenne < 8)
		{
		V10(), V27(), V35();
		}
		if(Moyenne >= 8 && Moyenne < 8.5)
		{
		V10(), V28(), V30();
		}
		if(Moyenne >= 8.5 && Moyenne < 9)
		{
		V10(), V28(), V35();
		}
		if(Moyenne >= 9 && Moyenne < 9.5)
		{
		V10(), V29(), V30();
		}
		if(Moyenne >= 9.5 && Moyenne < 10)
		{
		V10(), V29(), V35();
		}
		if(Moyenne >= 10 && Moyenne < 10.5)
		{
		V11(), V20(), V30();
		}
		if(Moyenne >= 10.5 && Moyenne < 11)
		{
		V11(), V20(), V35();
		}
		if(Moyenne >= 11 && Moyenne < 11.5)
		{
		V11(), V21(), V30();
		}
		if(Moyenne >= 11.5 && Moyenne < 12)
		{
		V11(), V21(), V35();
		}
		if(Moyenne >= 12 && Moyenne < 12.5)
		{
		V11(), V22(), V30();
		}
		if(Moyenne >= 12.5 && Moyenne < 13)
		{
		V11(), V22(), V35();
		}
		if(Moyenne >= 13 && Moyenne < 13.5)
		{
		V11(), V23(), V30();
		}
		if(Moyenne >= 13.5 && Moyenne < 14)
		{
		V11(), V23(), V35();
		}
		if(Moyenne >= 14 && Moyenne < 14.5)
		{
		V11(), V24(), V30();
		}
		if(Moyenne >= 14.5 && Moyenne < 15)
		{
		V11(), V24(), V35();
		}
		if(Moyenne >= 15 && Moyenne < 15.5)
		{
		V11(), V25(), V30();
		}
		if(Moyenne >= 15.5 && Moyenne < 16)
		{
		V11(), V25(), V35();
		}
		if(Moyenne >= 16 && Moyenne < 16.5)
		{
		V11(), V26(), V30();
		}
		if(Moyenne >= 16.5 && Moyenne < 17)
		{
		V11(), V26(), V35();
		}
		if(Moyenne >= 17 && Moyenne < 17.5)
		{
		V11(), V27(), V30();
		}
		if(Moyenne >= 17.5 && Moyenne < 18)
		{
		V11(), V27(), V35();
		}
		if(Moyenne >= 18 && Moyenne < 18.5)
		{
		V11(), V28(), V30();
		}
		if(Moyenne >= 18.5 && Moyenne < 19)
		{
		V11(), V28(), V35();
		}
		if(Moyenne >= 19 && Moyenne < 19.5)
		{
		V11(), V29(), V30();
		}
		if(Moyenne >= 19.5 && Moyenne < 20)
		{
		V11(), V29(), V35();
		}
		if(Moyenne >= 20 && Moyenne < 20.5)
		{
		V12(), V20(), V30();
		}
		if(Moyenne >= 20.5)
		{
		V12(), V20(), V35();
		}
}

// Fonctions d'affichage
	void C10(){
		digitalWrite(DIGIT_C1a,1),digitalWrite(DIGIT_C1b,1),digitalWrite(DIGIT_C1c,1),digitalWrite(DIGIT_C1d,1);
		digitalWrite(DIGIT_C1e,1),digitalWrite(DIGIT_C1f,1),digitalWrite(DIGIT_C1g,0); 
	}

	void C11(){
		digitalWrite(DIGIT_C1a,0),digitalWrite(DIGIT_C1b,1),digitalWrite(DIGIT_C1c,1),digitalWrite(DIGIT_C1d,0);
		digitalWrite(DIGIT_C1e,0),digitalWrite(DIGIT_C1f,0),digitalWrite(DIGIT_C1g,0); 
	}

	void C12(){
		digitalWrite(DIGIT_C1a,1),digitalWrite(DIGIT_C1b,1),digitalWrite(DIGIT_C1c,0),digitalWrite(DIGIT_C1d,1);
		digitalWrite(DIGIT_C1e,1),digitalWrite(DIGIT_C1f,0),digitalWrite(DIGIT_C1g,1);
	}

	//----------------------------------------------------------

	void C20(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,1),digitalWrite(DIGIT_C2f,1),digitalWrite(DIGIT_C2g,0); 
	}

	void C21(){
		digitalWrite(DIGIT_C2a,0),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,0);
		digitalWrite(DIGIT_C2e,0),digitalWrite(DIGIT_C2f,0),digitalWrite(DIGIT_C2g,0); 
	}

	void C22(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,0),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,1),digitalWrite(DIGIT_C2f,0),digitalWrite(DIGIT_C2g,1);
	}

	void C23(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,0),digitalWrite(DIGIT_C2f,0),digitalWrite(DIGIT_C2g,1); 
	}

	void C24(){
		digitalWrite(DIGIT_C2a,0),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,0);
		digitalWrite(DIGIT_C2e,0),digitalWrite(DIGIT_C2f,1),digitalWrite(DIGIT_C2g,1); 
	}

	void C25(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,0),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,0),digitalWrite(DIGIT_C2f,1),digitalWrite(DIGIT_C2g,1); 
	}

	void C26(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,0),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,1),digitalWrite(DIGIT_C2f,1),digitalWrite(DIGIT_C2g,1);
	}

	void C27(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,0);
		digitalWrite(DIGIT_C2e,0),digitalWrite(DIGIT_C2f,0),digitalWrite(DIGIT_C2g,0); 
	}

	void C28(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,1),digitalWrite(DIGIT_C2f,1),digitalWrite(DIGIT_C2g,1);
	}

	void C29(){
		digitalWrite(DIGIT_C2a,1),digitalWrite(DIGIT_C2b,1),digitalWrite(DIGIT_C2c,1),digitalWrite(DIGIT_C2d,1);
		digitalWrite(DIGIT_C2e,0),digitalWrite(DIGIT_C2f,1),digitalWrite(DIGIT_C2g,1); 
	}

	//----------------------------------------------------------

	void V10(){
		digitalWrite(DIGIT_V1a,1),digitalWrite(DIGIT_V1b,1),digitalWrite(DIGIT_V1c,1),digitalWrite(DIGIT_V1d,1);
		digitalWrite(DIGIT_V1e,1),digitalWrite(DIGIT_V1f,1),digitalWrite(DIGIT_V1g,0); 
	}

	void V11(){
		digitalWrite(DIGIT_V1a,0),digitalWrite(DIGIT_V1b,1),digitalWrite(DIGIT_V1c,1),digitalWrite(DIGIT_V1d,0);
		digitalWrite(DIGIT_V1e,0),digitalWrite(DIGIT_V1f,0),digitalWrite(DIGIT_V1g,0); 
	}

	void V12(){
		digitalWrite(DIGIT_V1a,1),digitalWrite(DIGIT_V1b,1),digitalWrite(DIGIT_V1c,0),digitalWrite(DIGIT_V1d,1);
		digitalWrite(DIGIT_V1e,1),digitalWrite(DIGIT_V1f,0),digitalWrite(DIGIT_V1g,1);
	}

	// --------------------------------------------------------------

	void V20(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,1),digitalWrite(DIGIT_V2f,1),digitalWrite(DIGIT_V2g,0),digitalWrite(DIGIT_V2dp,1); 
	}

	void V21(){
		digitalWrite(DIGIT_V2a,0),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,0);
		digitalWrite(DIGIT_V2e,0),digitalWrite(DIGIT_V2f,0),digitalWrite(DIGIT_V2g,0),digitalWrite(DIGIT_V2dp,1); 
	}

	void V22(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,0),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,1),digitalWrite(DIGIT_V2f,0),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1);
	}

	void V23(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,0),digitalWrite(DIGIT_V2f,0),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1);
	}
		
	void V24(){
		digitalWrite(DIGIT_V2a,0),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,0);
		digitalWrite(DIGIT_V2e,0),digitalWrite(DIGIT_V2f,1),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1); 
	}

	void V25(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,0),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,0),digitalWrite(DIGIT_V2f,1),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1);
	}
		
	void V26(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,0),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,1),digitalWrite(DIGIT_V2f,1),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1);
	}

	void V27(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,0);
		digitalWrite(DIGIT_V2e,0),digitalWrite(DIGIT_V2f,0),digitalWrite(DIGIT_V2g,0),digitalWrite(DIGIT_V2dp,1);
	}

	void V28(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,1),digitalWrite(DIGIT_V2f,1),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1);
	}

	void V29(){
		digitalWrite(DIGIT_V2a,1),digitalWrite(DIGIT_V2b,1),digitalWrite(DIGIT_V2c,1),digitalWrite(DIGIT_V2d,1);
		digitalWrite(DIGIT_V2e,0),digitalWrite(DIGIT_V2f,1),digitalWrite(DIGIT_V2g,1),digitalWrite(DIGIT_V2dp,1);
	}

	void V30(){
		digitalWrite(DIGIT_V3a,1),digitalWrite(DIGIT_V3b,1),digitalWrite(DIGIT_V3c,1),digitalWrite(DIGIT_V3d,1);
		digitalWrite(DIGIT_V3e,1),digitalWrite(DIGIT_V3f,1),digitalWrite(DIGIT_V3g,0); 
	}

	void V35(){
		digitalWrite(DIGIT_V3a,1),digitalWrite(DIGIT_V3b,0),digitalWrite(DIGIT_V3c,1),digitalWrite(DIGIT_V3d,1);
		digitalWrite(DIGIT_V3e,0),digitalWrite(DIGIT_V3f,1),digitalWrite(DIGIT_V3g,1);
	}