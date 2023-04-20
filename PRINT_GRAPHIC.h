#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "STRUCT.h"
#ifndef PRINT_GRAPHIC

#define PRINT_GRAPHIC
#define WIDTH_WINDOW 1300
#define HEIGHT_WINDOW 800
#define SIZE_INTERLINE 30
#define NB_LINE 7
#define NB_POSITION 23

void PrintGraphiqueGame(MLV_Image *ImageChips[5], MLV_Image *computer, MLV_Image *background, Game *NewGame);
int ClickInterface(int x, int y, int *type, int TypeChips[5]);
int CordoneOnClick(int x, int y, int *type, Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION]);
int ClickEvent(int x, int y, int *type, int TypeChips[5], int *choice, Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION]);
void CordoneToIndex(int *Line, int *Postion);
void PrintChips(MLV_Image *ImageChips[5], Chips *TAB_CHIPS[NB_LINE][NB_POSITION]);
void PrintVirus(MLV_Image *ImageVirus[3], Virus *TAB_VIRUS[NB_LINE][NB_POSITION]);

#endif