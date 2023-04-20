#include <stdio.h>
#include <stdlib.h>
#include "STRUCT.h"
#ifndef NEW_VIRUS
#define NEW_VIRUS
#define NB_LINE 7
#define NB_POSITION 23

int ReadFileVirus(Game *NewGame, Virus *TAB_VIRUS[NB_LINE][NB_POSITION], char NameFile[12], long *Curseur);
void InsertVirus(Virus *NewVirus, Game *NewGame, Virus *TAB_VIRUS[NB_LINE][NB_POSITION]);
Virus *DeployVirus(int type, int line, int position, int turn);
void LevelPreviewVirus(char NameFile[12], Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION], long *Curseur);

#endif
