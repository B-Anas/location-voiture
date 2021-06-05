#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "structures.h"

listC* mesClient = NULL;
FILE* fileC = NULL;

void supprimerC(listC** _list, char _data[])
{
	listC* elem = *_list;
	listC* precedent = *_list;

	if (strcmp(elem->valeur.nom, _data))
	{
		*_list = elem->suivant;
		free(elem);
	}
	else
	{
		while (strcmp(elem->valeur.nom, _data))
		{
			precedent = elem;
			elem = elem->suivant;
		}
		precedent->suivant = elem->suivant;
		free(elem);
	}
}
void modifierC(listC** _list, char _data[], client _ndata)
{
	listC* elem = *_list;

	while (!strcmp(elem->valeur.nom, _data))
	{
		elem = elem->suivant;
	}
	elem->valeur = _ndata;
}
void ajouterC(listC** _list, client _data)
{
	listC* nList = (listC*)malloc(sizeof(listC));
	listC* fin = *_list;

	nList->valeur = _data;
	nList->suivant = NULL;

	if (*_list == NULL)
	{
		*_list = nList;
	}
	else
	{
		while (fin->suivant != NULL)
			fin = fin->suivant;

		fin->suivant = nList;
	}
}
void loadfileC(FILE* _file, listC** mClient, client* c)
{
	_file = fopen("client.txt", "r");
	while (!feof(_file))
	{
		fscanf(_file, "%d %s %s %s %s %s\n", &c->idClient, &c->nom, &c->prenom,
			&c->cin, &c->adresse, &c->telephone);
		if(c->idClient != 0)
			ajouterC(mClient, *c);
	}
	fclose(_file);
}
void savefileC(FILE* _file, listC* mClient)
{
	_file = fopen("client.txt", "w");
	while (mClient != NULL)
	{
		fprintf(_file, "%d %s %s %s %s %s\n", mClient->valeur.idClient,
			mClient->valeur.nom, mClient->valeur.prenom, mClient->valeur.cin,
			mClient->valeur.adresse, mClient->valeur.telephone);
		mClient = mClient->suivant;
	}
	fclose(_file);
}

void ajouterClient(listC** mClient, client* c)
{
	printf("le id du client: ");
	scanf("%d", &c->idClient);
	printf("\nle nom du client: ");
	scanf("%s", &c->nom);
	printf("\nle prenom du client: ");
	scanf("%s", &c->prenom);
	printf("\nle cin du client: ");
	scanf("%s", &c->cin);
	printf("\nL'adresse du client: ");
	scanf("%s", &c->adresse);
	printf("\nle numero de telephone du client: ");
	scanf("%s", &c->telephone);

	ajouterC(mClient, *c);
	system("pause");
	system("CLS");
}

void supprimerClient(listC** mClient, client* c)
{
	printf("le cin du client : ");
	scanf("%s", &c->nom);

	supprimerC(mClient, c->nom);
	system("pause");
	system("CLS");
}

void modifierClient(listC** mClient, client* c)
{
	char nom[20];
	printf("le nom du client a modifier: ");
	scanf("%s", nom);
	printf("le id du client: ");
	scanf("%d", &c->idClient);
	printf("\nle nom du client: ");
	scanf("%s", &c->nom);
	printf("\nle prenom du client: ");
	scanf("%s", &c->prenom);
	printf("\nle cin du client: ");
	scanf("%s", &c->cin);
	printf("\nL'adresse du client: ");
	scanf("%s", &c->adresse);
	printf("\nle numero de telephone du client: ");
	scanf("%s", &c->telephone);

	modifierC(mClient, nom, *c);
	system("pause");
	system("CLS");
}

void afficherClient(listC** mClient, client* c)
{
	listC* lcopy = *mClient;
	if (lcopy == NULL)
		printf("aucun client...\n");
	while (lcopy != NULL)
	{
		printf("%d %s %s %s %s %s\n", lcopy->valeur.idClient,
			lcopy->valeur.nom,lcopy->valeur.prenom,lcopy->valeur.cin,
			lcopy->valeur.adresse,lcopy->valeur.telephone);
		lcopy = lcopy->suivant;
	}
	system("pause");
	system("CLS");
}
int chercherClient(listC* mClient, int id)
{
	if (mClient == NULL)
		return 0;
	 
	if (mClient->valeur.idClient == id)
		return 1;

	return chercherVoiture(mClient->suivant, id);
}
void (*tabFuncClient[4])(listC**, client*) = { afficherClient,ajouterClient,modifierClient,supprimerClient };
void (*menuC(int* choix))(listC**, client*)
{
	do
	{
		printf("Gestion du client\n");
		printf("1 pour lister\n");
		printf("2 pour ajouter\n");
		printf("3 pour modifier\n");
		printf("4 pour supprimer\n");
		printf("5 pour quitter\n");
		scanf("%d", choix);
	} while (*choix < 1 || *choix > 5);
	if (*choix == 5)
	{
		system("CLS");
		return;
	}
	system("CLS");
	return tabFuncClient[*choix - 1];
}
