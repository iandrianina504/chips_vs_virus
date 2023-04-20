#include <stdio.h>
#include <stdlib.h>
#include "STRUCT.h"
#ifndef MAJ_VIRUS
#define MAJ_VIRUS
#define NB_LINE 7
#define NB_POSITION 23

void LossLifeVirus(Game *NewGame, Chips *NewChips, Virus *TAB_VIRUS[NB_LINE][NB_POSITION]);
void UpdateVirus(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION]);
void DeleteVirus(Game *NewGame, Virus *TAB_VIRUS[NB_LINE][NB_POSITION], Virus *NewVirus, int LineVirus, int PositionVirus);
void AdvancementVirus(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION]);
// ####################################################################################################################### //
void DeleteChips(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Chips *NewChips, int LineChips, int PositionChips);
void LossLifeChips(Game *NewGame, Chips *NewChips, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], int LineChips, int PositionChips);

#endif