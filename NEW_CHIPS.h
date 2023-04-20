#include <stdio.h>
#include <stdlib.h>
#include "STRUCT.h"
#ifndef NEW_CHIPS
#define NEW_CHIPS
#define NB_LINE 7
#define NB_POSITION 23

void ChoiceChips(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION]);
void InsertChips(Chips *NewChips, Game *Newgame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION]);
Chips *DeployChips(int type, int line, int position, Game *NewGame);

#endif
