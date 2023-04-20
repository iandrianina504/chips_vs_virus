#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MAJ_GAME.h"
#include "NEW_CHIPS.h"
#include "NEW_VIRUS.h"
#include "SETTING_GAME.h"
#include "PRINT_GRAPHIC.h"
#define NB_LINE 7
#define NB_POSITION 23

int main(void)
{
    char Mode;
    Game NewGame;
    NewGame.chips = NULL;
    NewGame.virus = NULL;
    NewGame.turn = 1;
    NewGame.money = -1;
    char NameFile[12] = "level1.txt";
    ChoiceMode(&Mode, NameFile);

    Chips *TAB_CHIPS[NB_LINE][NB_POSITION];
    Virus *TAB_VIRUS[NB_LINE][NB_POSITION];
    Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION];
    long Curseur;
    int GameProgress = 0;
    int LevelState = 1;
    InitializationPlatter(TAB_CHIPS, TAB_VIRUS, TAB_VIRUS_PREVIEW);
    ReadFileMoney(&NewGame, NameFile, &Curseur);
    LevelPreviewVirus(NameFile, TAB_VIRUS_PREVIEW, &Curseur);
    if (Mode == 'C')
    {

        ChoiceChips(&NewGame, TAB_CHIPS, TAB_VIRUS, TAB_VIRUS_PREVIEW);
        while (GameProgress == 0)
        {
            AdvancementVirus(&NewGame, TAB_CHIPS, TAB_VIRUS);
            // si le fichier a été lu alors Level state devient 0 sinon il reste un et on continue de lire.
            if (LevelState != 0)
                LevelState = ReadFileVirus(&NewGame, TAB_VIRUS, NameFile, &Curseur);
            UpdateVirus(&NewGame, TAB_CHIPS, TAB_VIRUS);
            // GameProgress devient 1 si le fichier à fini d'être lu et qu'il y a plus de virus.
            GameProgress = CheckEndGame(&NewGame, LevelState);
            // On affiche le jeu sur le terminal.
            PrintGame(TAB_CHIPS, TAB_VIRUS);
            // On attend une seconde.
            sleep(1);
            NewGame.turn++;
        }
        // Affiche le message de fin.
        MessageEndGame(GameProgress);
    }
    else
    {

        MLV_create_window(" Chips vs Virus", " Chips vs Virus", WIDTH_WINDOW, HEIGHT_WINDOW);
        // Pointeur sur les chips.
        MLV_Image *alu = MLV_load_image("alu.png");
        MLV_Image *firewall = MLV_load_image("firewall.png");
        MLV_Image *patch = MLV_load_image("patch.png");
        MLV_Image *pmmu = MLV_load_image("pmmu.png");
        MLV_Image *ram = MLV_load_image("ram.png");
        // Pointeur sur virus.

        MLV_Image *fpe = MLV_load_image("fpe.png");
        MLV_Image *ddos = MLV_load_image("ddos.png");
        MLV_Image *segfault = MLV_load_image("segfault.png");

        // Pointeus sur des images de jeu.
        MLV_Image *background = MLV_load_image("background.jpg");
        MLV_Image *computer = MLV_load_image("computer.png");
        MLV_Image *ImageChips[5] = {alu, firewall, patch, pmmu, ram};
        MLV_Image *ImageVirus[3] = {fpe, ddos, segfault};
        int TypeChips[5] = {65, 70, 88, 80, 82};
        int type = 0;
        int x, y;
        int choice = 0;
        int PreGame = 1;
        int GameProgress = 0;
        // Met à jour l'affichage.*/

        do
        {
            PrintGraphiqueGame(ImageChips, computer, background, &NewGame);
            PrintChips(ImageChips, TAB_CHIPS);
            MLV_actualise_window();
            MLV_wait_mouse(&x, &y);
            switch (ClickEvent(x, y, &type, TypeChips, &choice, &NewGame, TAB_CHIPS))
            {
            case 1:
                choice = 1;
                break;

            case 2:
                // Affichage vague.
                PrintGraphiqueGame(ImageChips, computer, background, &NewGame);
                PrintVirus(ImageVirus, TAB_VIRUS_PREVIEW);
                MLV_actualise_window();
                sleep(15);
                printf("Vague\n");
                break;
            case 3:
                // On lance le jeu.
                printf(" Game !\n");
                PreGame = 0;
                GameProgress = 0;
                break;
            case -1:
                // On arrete le jeu.
                printf("Fin\n");
                PreGame = 0;
                GameProgress = 1;
                break;
            }

        } while (PreGame == 1);
        while (GameProgress == 0)
        {
            AdvancementVirus(&NewGame, TAB_CHIPS, TAB_VIRUS);
            // si le fichier a été lu alors Level state devient 0 sinon il reste un et on continue de lire.
            if (LevelState != 0)
                LevelState = ReadFileVirus(&NewGame, TAB_VIRUS, NameFile, &Curseur);
            UpdateVirus(&NewGame, TAB_CHIPS, TAB_VIRUS);
            // GameProgress devient 1 si le fichier à fini d'être lu et qu'il y a plus de virus.
            GameProgress = CheckEndGame(&NewGame, LevelState);
            // On affiche le jeu sur le terminal.
            PrintGraphiqueGame(ImageChips, computer, background, &NewGame);
            PrintVirus(ImageVirus, TAB_VIRUS);
            PrintChips(ImageChips, TAB_CHIPS);
            MLV_actualise_window();
            // On attend une seconde.
            sleep(1);
            NewGame.turn++;
        }
        MLV_free_window();
        return 0;
    }

    return 0;
}
