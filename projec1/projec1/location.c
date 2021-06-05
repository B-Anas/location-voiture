#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "structures.h"
#include "voiture.h"
#include "client.h"

listL* mesLocation = NULL;
FILE* fileL = NULL;

void supprimerL(listL** _list, int _data)
{
	listL* elem = *_list;
	listL* precedent = *_list;

	if (elem->valeur.numContrat == _data)
	{
		*_list = elem->suivant;
		free(elem);
	}
	else
	{
		while (elem->valeur.numContrat != _data)
		{
			precedent = elem;
			elem = elem->suivant;
		}
		precedent->suivant = elem->suivant;
		free(elem);
	}
}
void modifierL(listL** _list, int _data, location _ndata)
{
	listL* elem = *_list;

	while (elem->valeur.idVoiture != _data)
	{
		elem = elem->suivant;
	}
	elem->valeur = _ndata;
}
void ajouterL(listL** _list, location _data)
{
	listL* nList = (listL*)malloc(sizeof(listL));
	listL* fin = *_list;

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
void loadfileLocation(FILE* _file, listL** mlocation, location* l)
{
	_file = fopen("location.txt", "r");
	while (!feof(_file))
	{
		fscanf(_file, "%d %d %d %d &d %d %d %d %d &d\n", &l->numContrat, &l->idVoiture, &l->idClient, &l->debut.jours, &l->debut.mois, &l->debut.annee, &l->fin.jours, &l->fin.mois, &l->fin.annee, &l->cout);
		if(l->idClient !=0)
			ajouterL(mlocation, *l);
	}
	fclose(_file);
}
void savefileLocation(FILE* _file, listL* mlocation)
{
	_file = fopen("location.txt", "w");
	while (mlocation != NULL)
	{
		
		fprintf(_file, "%d %d %d %d %d %d %d %d %d %d\n", mlocation->valeur.numContrat, mlocation->valeur.idVoiture, mlocation->valeur.idClient,
			mlocation->valeur.debut.jours, mlocation->valeur.debut.mois, mlocation->valeur.debut.annee,
			mlocation->valeur.fin.jours, mlocation->valeur.fin.mois, mlocation->valeur.fin.annee,
			mlocation->valeur.cout);
		mlocation = mlocation->suivant;
	}
	fclose(_file);
}

void ajouterLocation(listL** mlocation, location* l)
{
	int ch;
	
	printf("le id de voiture:\n");
	scanf("%d", &l->idVoiture);
	if (!chercherVoiture(maVoiture, l->idVoiture))
	{
		printf("la voiture n'existe pas, pour l'ajouter(1 si oui/0 sinon)");
		scanf("%d", &ch);
		if (ch)
		{
			system("CLS");
			ajouterVoiture(&maVoiture, &v);
		}
		else
		{
			return;
		}
	}
	if (chercherVoitureLocation(maVoiture, l->idVoiture))
	{
		printf("la voiture est deja en location\n");
		system("pause");
		system("CLS");
		return;
	}
	printf("le id du client:\n");
	scanf("%d", &l->idClient);
	if (!chercherClient(mesClient, l->idClient))
	{
		printf("le client n'existe pas, pour l'ajouter(1 si oui/0 sinon)\n");
		scanf("%d", &ch);
		if (ch)
		{
			system("CLS");
			ajouterClient(&mesClient, &c);
		}
		else
		{
			return;
		}
	}
	printf("le id du nouveau contrat: ");
	scanf("%d", &l->numContrat);
	printf("\nla date du debut de location(jj mm aaaa): ");
	scanf("%d %d %d", &l->debut.jours, &l->debut.mois, &l->debut.annee);
	printf("\nla date de la fin de location(jj mm aaaa): ");
	scanf("%d %d %d", &l->fin.jours, &l->fin.mois, &l->fin.annee);
	printf("\nle prix a paye? ");
	scanf("%d", &l->cout);
	enlocationV(&maVoiture, l->idVoiture, 1);
	ajouterL(mlocation, *l);
	system("pause");
	system("CLS");
}

void supprimerLocation(listL** mlocation, location* l)
{
	printf("le id du contrat a supprimer : ");
	scanf("%d", &l->numContrat);

	supprimerL(mlocation, l->numContrat);
	system("pause");
	system("CLS");
}

void modifierLocation(listL** mlocation, location* l)
{
	printf("le id du contrat a modifier: ");
	scanf("%d", &l->numContrat);
	system("CLS");
	printf("\nle id de la voiture: ");
	scanf("%d", &l->idVoiture);
	printf("\nle id du client: ");
	scanf("%d", &l->idClient);
	printf("\nla date du debut de location(jj mm aaaa): ");
	scanf("%d %d %d", &l->debut.jours, &l->debut.mois, &l->debut.annee);
	printf("\nla date de la fin de location(jj mm aaaa): ");
	scanf("%d %d %d", &l->fin.jours, &l->fin.mois, &l->fin.annee);
	printf("\nle prix a paye? ");
	scanf("%d", &l->cout);

	modifierL(mlocation, l->numContrat, *l);
	system("pause");
	system("CLS");
}

void afficherLocation(listL** mlocation, location* l)
{
	listL* lcopy = *mlocation;
	if (lcopy == NULL)
		printf("aucun contrat...\n");
	else
		printf("le # du contrat|id voiture|id client|date debut|date fin|cout\n");
	while (lcopy != NULL)
	{
		printf("%d          %d         %d        %d-%d-%d    %d-%d-%d    %d\n",
			lcopy->valeur.numContrat, lcopy->valeur.idVoiture, lcopy->valeur.idClient,
			lcopy->valeur.debut.jours, lcopy->valeur.debut.mois, lcopy->valeur.debut.annee,
			lcopy->valeur.fin.jours, lcopy->valeur.fin.mois, lcopy->valeur.fin.annee,
			lcopy->valeur.cout);
		lcopy = lcopy->suivant;
	}
	system("pause");
	system("CLS");
}
location* chercherLocation(listL* mlocation, int id)
{
	if (mlocation == NULL)
	{
		printf("Ce contrat n'existe pas\n");
		return NULL;
	}
	if (mlocation->valeur.numContrat == id)
		return &(mlocation->valeur);

	return chercherVoitureII(mlocation->suivant, id);
}
void retournerLocation(listL** mlocation, location* l)
{
	printf("le id du contrat:\n");
	scanf("%d", l->numContrat);
	l = chercherLocation(mlocation, l->numContrat);
	enlocationV(&maVoiture, l->idVoiture, 0);
	if(l != NULL)
		supprimerL(mlocation, l->numContrat);
	system("pause");
	system("CLS");
}
void (*tabFuncLocation[5])(listL**, location*) = { afficherLocation,ajouterLocation,retournerLocation,modifierLocation,supprimerLocation };
void (*menuL(int* choix))(listL**, location*)
{

	do
	{
		printf("Gestion de location\n");
		printf("1 pour afficher\n");
		printf("2 pour ajouter\n");
		printf("3 pour retourner\n");
		printf("4 pour modifier\n");
		printf("5 pour supprimer\n");
		printf("6 pour quitter\n");
		scanf("%d", choix);
	} while (*choix < 1 || *choix > 6);
	if (*choix == 6)
	{
		system("CLS");
		return;
	}
	system("CLS");
	return tabFuncLocation[*choix - 1];
}
