#pragma once
#include <stdio.h>
#include "structures.h"

extern listC* mesClient;
client c;
extern FILE* fileC;

void ajouterClient(listC**, client*);
int chercherClient(listC*, int);
void loadfileC(FILE*, listC**, client*);
void savefileC(FILE*, listC*);
void (*tabFuncClient[4])(listC**, client*);
void (*menuC(int*))(listC**, client*);
