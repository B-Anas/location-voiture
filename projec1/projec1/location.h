#pragma once
#include <stdio.h>
#include "structures.h"

extern listL* mesLocation;
location l;
extern FILE* fileL;

void loadfileLocation(FILE*, listL**, location*);
void savefileLocation(FILE*, listL*);
void (*tabFuncLocation[5])(listL**, location*);
void (*menuL(int*))(listL**, location*);
