#include <stdio.h>
#include <stdlib.h>
#include "STRUCT.h"
#ifndef SETTING_GAME
#define SETTING_GAME
#define NB_LINE 7
#define NB_POSITION 23

void InitializationPlatter(Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION]);
void ReadFileMoney(Game *NewGame, char NameFile[12], long *Curseur);
int CheckEndGame(Game *NewGame, int Levelestate);
void PrintGame(Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION]);
void PrintPreviewGame(Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION]);
void MessageEndGame(int GameProgress);
void ChoiceMode(char *Mode, char NameFile[12]);
#endif