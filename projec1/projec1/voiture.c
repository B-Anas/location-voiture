#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "structures.h"

listV* maVoiture = NULL;
FILE* file = NULL;

void supprimerV(listV** _list, int _data)
{
    listV* elem = *_list;
    listV* precedent = *_list;

    if (elem->valeur.idVoiture == _data)
    {
        *_list = elem->suivant;
        free(elem);
    }
    else
    {
        while (elem->valeur.idVoiture != _data)
        {
            precedent = elem;
            elem = elem->suivant;
        }
        precedent->suivant = elem->suivant;
        free(elem);
    } 
}
void modifierV(listV** _list, int _data, voiture _ndata)
{
    listV* elem = *_list;

    while (elem->valeur.idVoiture != _data)
    {
        elem = elem->suivant;
    }
    elem->valeur = _ndata;
}
void ajouterV(listV** _list, voiture _data)
{
	listV* nList = (listV*)malloc(sizeof(listV));
	listV* fin = *_list;

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
void loadfile(FILE* _file, listV** maVoiture, voiture* v)
{
	_file = fopen("voiture.txt", "r");
	while (!feof(_file))
	{
		fscanf(_file, "%d %s %s %s %d %d %s\n", &v->idVoiture, &v->marque,
			&v->nomVoiture, &v->couleur, &v->nbPlace, &v->prxJour, &v->enLocation);
		if(v->nbPlace != 0)
			ajouterV(maVoiture, *v);
	}
	fclose(_file);
}
void savefile(FILE* _file, listV* maVoiture)
{
	_file = fopen("voiture.txt", "w");
	while (maVoiture != NULL)
	{
		fprintf(_file, "%d %s %s %s %d %d %s\n", maVoiture->valeur.idVoiture, maVoiture->valeur.marque,
			maVoiture->valeur.nomVoiture, maVoiture->valeur.couleur, maVoiture->valeur.nbPlace,
			maVoiture->valeur.prxJour, maVoiture->valeur.enLocation);
		maVoiture = maVoiture->suivant;
	}
	fclose(_file);
}

void ajouterVoiture(listV** maVoiture, voiture* v)
{
	printf("le id de la voiture: ");
	scanf("%d", &v->idVoiture);
	printf("\nla marque de la voiture: ");
	scanf("%s", &v->marque);
	printf("\nle nom de la voiture: ");
	scanf("%s", &v->nomVoiture);
	printf("\nla couleur de la voiture: ");
	scanf("%s", &v->couleur);
	printf("\nle nombre de place de la voiture: ");
	scanf("%d", &v->nbPlace);
	printf("\nle prix par jour de la voiture: ");
	scanf("%d", &v->prxJour);
	printf("\nEst-ce-que la voiture en location? ");
	scanf("%s", &v->enLocation);

	ajouterV(maVoiture, *v);
	system("pause");
	system("CLS");
}

void supprimerVoiture(listV** maVoiture, voiture* v)
{
	printf("le id de la voiture a supprimer : ");
	scanf("%d", &v->idVoiture);

	supprimerV(maVoiture, v->idVoiture);
	system("pause");
	system("CLS");
}

void modifierVoiture(listV** maVoiture, voiture* v)
{
	printf("le id de la voiture a modifier: ");
	scanf("%d", &v->idVoiture);
	printf("\nla marque de la voiture: ");
	scanf("%s", &v->marque);
	printf("\nle nom de la voiture: ");
	scanf("%s", &v->nomVoiture);
	printf("\nla couleur de la voiture: ");
	scanf("%s", &v->couleur);
	printf("\nle nombre de place de la voiture: ");
	scanf("%d", &v->nbPlace);
	printf("\nle prix par jour de la voiture: ");
	scanf("%d", &v->prxJour);
	printf("\nEst-ce-que la voiture en location? ");
	scanf("%s", &v->enLocation);

	modifierV(maVoiture, v->idVoiture, *v);
	system("pause");
	system("CLS");
}

void afficherVoiture(listV** maVoiture, voiture* v)
{
	listV* lcopy = *maVoiture;
	if (lcopy == NULL)
		printf("aucune voiture...\n");
	while (lcopy != NULL)
	{
		printf("%d %s %s %s %d %d %s\n", lcopy->valeur.idVoiture, lcopy->valeur.marque,
			lcopy->valeur.nomVoiture, lcopy->valeur.couleur, lcopy->valeur.nbPlace,
			lcopy->valeur.prxJour, lcopy->valeur.enLocation);
		lcopy = lcopy->suivant;
	}
	system("pause");
	system("CLS");
}
int chercherVoiture(listV* maVoiture, int id)
{
	if (maVoiture == NULL)
		return 0;

	if (maVoiture->valeur.idVoiture == id)
		return 1;

	return chercherVoiture(maVoiture->suivant, id);
}
int chercherVoitureLocation(listV* maVoiture, int id)
{
	if (maVoiture == NULL)
		return 0;

	if (maVoiture->valeur.idVoiture == id)
	{
		if(strcmp(maVoiture->valeur.enLocation, "non"))
			return 1;
		else
			return 0;
	}
		

	return chercherVoitureLocation(maVoiture->suivant, id);
}
voiture* chercherVoitureII(listV* maVoiture, int id)
{
	if (maVoiture->valeur.idVoiture == id)
		return &(maVoiture->valeur);

	return chercherVoitureII(maVoiture->suivant, id);
}
void enlocationV(listV** maVoiture, int id, int noui)
{
	voiture* v1 = chercherVoitureII(*maVoiture, id);
	if (noui)
	{
		strcpy(v1->enLocation, "oui");
	}
	else
	{
		strcpy(v1->enLocation, "non");
	}
	modifierV(maVoiture, v1->idVoiture, *v1);
}

void (*tabFuncVoi[4])(listV**, voiture*) = { afficherVoiture,ajouterVoiture,modifierVoiture,supprimerVoiture };
void (*menuV(int* choix))(listV**, voiture*)
{
	
	do
	{
		printf("Gestion de voiture\n");
		printf("1 pour afficher\n");
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
	return tabFuncVoi[*choix - 1];
}
