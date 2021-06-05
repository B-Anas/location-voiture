#pragma once
#include <stdio.h>
#include "structures.h"

extern listV* maVoiture;
voiture v;
extern FILE* file;

int chercherVoitureLocation(listV* , int);
void enlocationV(listV** , int, int);
void ajouterVoiture(listV** ,voiture*);
int chercherVoiture(listV*, int);
void loadfile(FILE*, listV**, voiture*);
void savefile(FILE*, listV*);
void (*tabFuncVoi[4])(listV**, voiture*);
void (*menuV(int*))(listV**, voiture*);

