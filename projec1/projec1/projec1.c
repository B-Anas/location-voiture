#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "voiture.h"
#include "client.h"
#include "location.h"

int choix = 0;

void gestionLocation()
{
	void (*func)(listL**, location*);
	int ch = 0;

	func = menuL(&ch);
	while (ch != 6)
	{
		(*func)(&mesLocation, &l);
		func = menuL(&ch);
	}

	savefileLocation(fileL, mesLocation);
	savefile(file, maVoiture);
	savefileC(fileC, mesClient);
}
void gestionVoiture()
{
	void (*func)(listV**, voiture*);
	int ch = 0;

	func = menuV(&ch);
	while (ch != 5)
	{
		(*func)(&maVoiture, &v);
		func = menuV(&ch);	
	}
	
	savefile(file, maVoiture);
}
void gestionClient()
{
	void (*func)(listC**, client*);
	int ch = 0;
	func = menuC(&ch);
	while (ch != 5)
	{
		(*func)(&mesClient, &c);
		func = menuC(&ch);
	}

	savefileC(fileC, mesClient);
}
void (*tabMenu[3])() = { gestionLocation,gestionVoiture,gestionClient };
void (*mainMenu(void))()
{
	do {
		printf("Menu principale\n");
		printf("Gestion des location................1\n");
		printf("Gestion des voitures................2\n");
		printf("Gestion des clients.................3\n");
		printf("Quitter.............................4\n");
		printf("votre choix\n");
		scanf("%d", &choix);
	} while (choix < 1 || choix > 4);
	system("CLS");
	if (choix == 4)
		exit(0);
	return tabMenu[choix - 1];
}
int main()
{
	loadfile(file, &maVoiture, &v);
	loadfileC(fileC, &mesClient, &c);
	loadfileLocation(fileL, &mesLocation, &l);
	do {
		void (*funcMenu)();
		funcMenu = mainMenu();
		(*funcMenu)();
	} while (choix != 4);
	
	return 0;
}

