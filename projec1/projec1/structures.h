#pragma once
//structure voiture
typedef struct {
	int idVoiture;
	char marque[15];
	char nomVoiture[15];
	char couleur[7];
	int nbPlace;
	int prxJour;
	char enLocation[3];
}voiture;
//structure client
typedef struct Client
{
	int idClient;
	char nom[20];
	char prenom[20];
	char cin[20];
	char adresse[15];
	char telephone[15];
}client;
//structure date
typedef struct date {
	int jours;
	int mois;
	int annee;
}date;
//structure Location
typedef struct Location
{
	int numContrat;
	int idVoiture;
	int idClient;
	date debut;
	date fin;
	int cout;
}location;
//list des voitures
struct listV {
	voiture valeur;
	struct listV* suivant;
};
typedef struct listV listV;
//list des clients
struct listC {
	client valeur;
	struct listC* suivant;
};
typedef struct listC listC;
//list des location
struct listL {
	location valeur;
	struct listL* suivant;
};
typedef struct listL listL;