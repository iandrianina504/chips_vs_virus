#include "PRINT_GRAPHIC.h"
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "STRUCT.h"
#include "NEW_CHIPS.h"

void PrintGraphiqueGame(MLV_Image *ImageChips[5], MLV_Image *computer, MLV_Image *background, Game *NewGame)
{
    // Valeur pour boucle for dans l'affichage.
    int i, j;
    int x = 10, y = 20;
    int x_cercle, y_cercle;
    int x_depart, y_depart, x_arrivee, y_arrivee, x_arrivee2;
    // Redimissionner l'image de l'ordinateur.
    MLV_resize_image_with_proportions(computer, 100, 100);

    /*********/
    // Affiche le background.
    MLV_draw_image(background, 0, 0);
    MLV_set_alpha_on_image(MLV_ALPHA_OPAQUE, background);

    /******LIGNES + TOUR*/

    x_depart = 50, y_depart = (HEIGHT_WINDOW / 2) - 40;
    x_arrivee = 1500, y_arrivee = 150, x_arrivee2 = 190;
    for (i = 0; i < 7; i++)
    {
        MLV_draw_line(x_depart, y_depart, x_arrivee2, y_arrivee, MLV_COLOR_WHITE);
        MLV_draw_line(x_arrivee2, y_arrivee, x_arrivee, y_arrivee, MLV_COLOR_RED1);
        y_arrivee += 70;
    }

    x_cercle = 190, y_cercle = 150;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 24; j++)
        {
            MLV_draw_filled_circle(x_cercle, y_cercle, 5, MLV_COLOR_GREEN);
            x_cercle += 50;
        }
        y_cercle += 70;
        x_cercle = 190;
    }

    for (i = 0; i < 5; i++)
    {
        x += 60;
        MLV_draw_image(ImageChips[i], x, y);
        MLV_draw_adapted_text_box_on_image(x, y, "prix", SIZE_INTERLINE, MLV_COLOR_RED, MLV_COLOR_RED, MLV_COLOR_RED, MLV_TEXT_CENTER, ImageChips[i]);
    }

    // Affichage de l'ordinateur.
    MLV_draw_image(computer, 10, (HEIGHT_WINDOW / 2) - 100);

    MLV_draw_adapted_text_box(
        800, 20,
        "Voir la vague !",
        SIZE_INTERLINE,
        MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_GREY,
        MLV_TEXT_CENTER);

    MLV_draw_adapted_text_box(
        1000, 20,
        "Commencer !",
        SIZE_INTERLINE,
        MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_GREY,
        MLV_TEXT_CENTER);

    MLV_draw_adapted_text_box(
        1200, 20,
        "Quitter",
        SIZE_INTERLINE,
        MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_GREY,
        MLV_TEXT_CENTER);

    MLV_draw_adapted_text_box(
        400, 20,
        "Money : %d",
        SIZE_INTERLINE,
        MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_GREY,
        MLV_TEXT_LEFT, NewGame->money);
}

int ClickInterface(int x, int y, int *type, int TypeChips[5])
{
    int choice;
    // Taille d'une chips en longueur.
    int SizeChips = 60;
    // On vérifie si il click dans la liste de chips.
    if (70 < x && x < 360 && 20 < y && y < 70)
    {
        // On convertit le click.
        choice = (x / SizeChips) - 1;
        *type = TypeChips[choice];
        return 1;
    }
    // On click sur voir la vague.
    else if (800 < x && x < 955 && 20 < y && y < 95)
    {
        return 2;
    }
    // On click sur lancer le jeu.
    else if (1000 < x && x < 1150 && 20 < y && y < 95)
    {
        // Fonction qui lance le jeu.
        return 3;
    }
    // On click sur quitter.
    else if (1200 < x && x < 1310 && 20 < y && y < 95)
    {
        // On quitte.
        return -1;
    }
    return 0;
}

int CordoneOnClick(int x, int y, int *type, Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION])
{
    int Line, Position;
    int LineStart = 130;
    int LineEnd = 170;
    int PositionStart;
    int PositionEnd;
    Chips *NewChips = NULL;
    for (Line = 0; Line < NB_LINE; Line++)
    {
        PositionStart = 170;
        PositionEnd = 210;
        for (Position = 0; Position < NB_POSITION; Position++)
        {
            if (PositionStart < x && PositionEnd > x && LineStart < y && LineEnd > y)
            {
                NewChips = DeployChips(*type, Line, Position, NewGame);
                // On insert Chips dans la liste chainé et le tableau de chips.
                InsertChips(NewChips, NewGame, TAB_CHIPS);
                *type = 0;

                return 1;
            }
            PositionStart += 50;
            PositionEnd += 50;
        }
        LineStart += 70;
        LineEnd += 70;
    }
    return 0;
}

int ClickEvent(int x, int y, int *type, int TypeChips[5], int *choice, Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION])
{
    // Permet de savoir si on click dans l'inteface ou dans le jeu.
    if (y < 100)
    {
        // Retourne 1 si on choisi un chips, 2 si on veut voir la vague, 3 si on lance le jeu et -1 si on quitte.
        return (ClickInterface(x, y, type, TypeChips));
    }
    else if (NewGame->money <= 0)
    {
        printf("Plus d'argent Lancement du jeu\n.");
        return 3;
    }
    else
    {
        if (*choice == 1 && CordoneOnClick(x, y, type, NewGame, TAB_CHIPS) == 1)
        {
            // Insert du chips.
            *choice = 0;
            return 4;
        }
    }
    return 0;
}

void CordoneToIndex(int *Line, int *Postion)
{
    int TheLine;
    int ThePosition;
    int xStart = 190;
    int yStart = 150;

    // On se deplace sur la plateau graphique en partant du premier point.
    for (TheLine = 0; TheLine < *Line; TheLine++)
    {
        yStart += 70;
    }

    for (ThePosition = 0; ThePosition < *Postion; ThePosition++)
    {
        xStart += 50;
    }
    *Line = yStart;
    *Postion = xStart;
}

void PrintChips(MLV_Image *ImageChips[5], Chips *TAB_CHIPS[NB_LINE][NB_POSITION])
{
    int Line;
    int Position;
    int TheLine;
    int ThePosition;
    int TypeChips = 0;
    Chips *NewChips = NULL;
    for (Line = 0; Line < NB_LINE; Line++)
    {
        for (Position = 0; Position < NB_POSITION; Position++)
        {
            NewChips = TAB_CHIPS[Line][Position];
            if (NewChips != NULL)
            {
                TheLine = Line;
                ThePosition = Position;
                TypeChips = NewChips->type;
                CordoneToIndex(&TheLine, &ThePosition);
                switch (TypeChips)
                {
                case 65:
                    MLV_draw_image(ImageChips[0], ThePosition - 20, TheLine - 20);
                    break;
                case 70:
                    MLV_draw_image(ImageChips[1], ThePosition - 20, TheLine - 20);
                    break;
                case 88:
                    MLV_draw_image(ImageChips[2], ThePosition - 20, TheLine - 20);
                    break;
                case 80:
                    MLV_draw_image(ImageChips[3], ThePosition - 20, TheLine - 20);
                    break;
                case 82:
                    MLV_draw_image(ImageChips[4], ThePosition - 20, TheLine - 20);
                    break;
                }
            }
        }
    }
}

void PrintVirus(MLV_Image *ImageVirus[3], Virus *TAB_VIRUS[NB_LINE][NB_POSITION])
{
    int cmp, life;
    int width_rect=40, height_rect=10;
    int Line;
    int Position;
    int TheLine;
    int ThePosition;
    int TypeVirus = 0;
    Virus *NewVirus = NULL;
    for (Line = 0; Line < NB_LINE; Line++)
    {
        for (Position = 0; Position < NB_POSITION; Position++)
        {
            NewVirus = TAB_VIRUS[Line][Position];
            if (NewVirus != NULL)
            {
                TheLine = Line;
                ThePosition = Position;
                TypeVirus = NewVirus->type;
                CordoneToIndex(&TheLine, &ThePosition);
                switch (TypeVirus)
                {
                // Si type: E (floating point exception :Petit dégat (1) provoquer sur les chips.)
                            case 69:
                    life = 3;
                    MLV_draw_image(ImageVirus[0], ThePosition - 20, TheLine - 20);
                    break;
                // Si type: D (Attaques par déni de service : Un gros vilian très solide mais très long.)
                case 68:
                    life = 9;
                    MLV_draw_image(ImageVirus[1], ThePosition - 20, TheLine - 20);
                    break;
                // Si type: S (erreurs de segmentation : Un vilian très rapide mais peut robuste.)
                case 83:
                    life = 3;
                    MLV_draw_image(ImageVirus[2], ThePosition - 20, TheLine - 20);
                    break;
                }
                    
                cmp = width_rect/life;
                
                MLV_draw_filled_rectangle(ThePosition-15, TheLine+35, width_rect, height_rect, MLV_COLOR_RED);
                MLV_draw_filled_rectangle(ThePosition-15, TheLine+35, cmp*NewVirus->life, height_rect, MLV_COLOR_GREEN);
                
            }
        }
    }
}