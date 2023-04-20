#include "SETTING_GAME.h"

void InitializationPlatter(Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION])
{
    int i, j;
    // On parcours le tableau pour ajouter les NULL un par un.
    for (i = 0; i < NB_LINE; i++)
    {
        for (j = 0; j < NB_POSITION; j++)
        {
            TAB_CHIPS[i][j] = NULL;
            TAB_VIRUS[i][j] = NULL;
            TAB_VIRUS_PREVIEW[i][j] = NULL;
        }
    }
}

void ReadFileMoney(Game *NewGame, char NameFile[12], long *Curseur)
{
    // On ouvre le fichier.
    FILE *level = NULL;
    level = fopen(NameFile, "r");
    // On récupère la première variable du fichier qui est 'money'.
    fscanf(level, "%d", &NewGame->money);
    // On renvoie ensuite le curseur de la ou en est dans le fichier pour pouvoir continuer la lecture apré la fermeture du fichier.
    *Curseur = ftell(level);
    // On ferme le fichier.
    fclose(level);
}

int CheckEndGame(Game *NewGame, int Levelestate)
{
    Virus *NewVirus;
    if (NewGame->virus == NULL && Levelestate == 0)
    {
        return 1;
    }
    else
    {
        // On definie le virus qui peut attaquer l'ordinateur.
        NewVirus = NewGame->virus;
        // On parcours la liste chainée pour vérifier si un virus n'atteint pas l'ordinateur.
        while (NewVirus != NULL)
        {
            if (NewVirus->position <= 0)
            {
                return -1;
            }
            NewVirus = NewVirus->next;
        }
        return 0;
    }
}

void PrintGame(Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION])
{
    // Ces 2 variables permettrons de parcourirs les tableau chips et Virus.
    int TheLine, ThePosition;
    // On créer une variable qui correspond au chips que l'on va afficher;
    Chips *PointerChips;
    // On créer une variable qui correspond au chips que l'on va afficher;
    Virus *PointerVirus;
    // On définit les attributs du chips.
    int LifeChips, TypeChips;
    // On définit les attributs du chips.
    int LifeVirus, TypeVirus;
    // On utilise ce formatage pour nettoyer la console.
    printf("\e[1;1H\e[2J");
    /* On parcours ensuite les deux tableaux pour afficher soit un virus ou soit chips ou rien.
     Le programme est structurer de tel manière a ce
     qu'il n'y a pas 1 virus et 1 chips avec le même index dans leur tableau réspectifs.
     Donc pas de superposition.*/
    for (TheLine = 1; TheLine <= NB_LINE; TheLine++)
    {
        printf("|%d", TheLine);
        for (ThePosition = 1; ThePosition <= NB_POSITION; ThePosition++)
        {
            // On initialise les poiteur.
            PointerChips = TAB_CHIPS[TheLine - 1][ThePosition - 1];
            PointerVirus = TAB_VIRUS[TheLine - 1][ThePosition - 1];
            // Si il n'y a pas de chips et de virus alors on affiche rien.
            if (PointerChips == NULL && PointerVirus == NULL)
            {
                printf("    ");
            }
            // Si il y a un chips alors en affiche.
            else if (PointerChips != NULL && PointerVirus == NULL)
            {
                LifeChips = PointerChips->life;
                TypeChips = PointerChips->type;
                printf("  %c%d", TypeChips, LifeChips);
            }
            // Si il y a un virus alors on l'affiche.
            else if (PointerChips == NULL && PointerVirus != NULL)
            {
                LifeVirus = PointerVirus->life;
                TypeVirus = PointerVirus->type;
                printf("  %d%c", LifeVirus, TypeVirus);
            }
        }
        printf("\n");
    }
}

void PrintPreviewGame(Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION])
{
    // Ces 2 variables permettrons de parcourirs le tableau de Virus.
    int TheLine, ThePosition;
    // On créer une variable qui correspond au chips que l'on va afficher;
    Virus *PointerVirus;
    // On définit les attributs du virus.
    int LifeVirus, TypeVirus;
    // On utilise ce formatage pour nettoyer la console.
    printf("\e[1;1H\e[2J");
    printf("Here is the wave of problems approaching...\n");
    // On parcours le tableau.
    for (TheLine = 1; TheLine <= NB_LINE; TheLine++)
    {
        printf("|%d", TheLine);
        for (ThePosition = 1; ThePosition <= NB_POSITION; ThePosition++)
        {
            // On initialise les poiteur.
            PointerVirus = TAB_VIRUS_PREVIEW[TheLine - 1][ThePosition - 1];
            // Si il n'y a pas de chips et de virus alors on affiche rien.
            if (PointerVirus == NULL)
            {
                printf("    ");
            }
            // Si il y a un virus alors on l'affiche.
            else if (PointerVirus != NULL)
            {
                LifeVirus = PointerVirus->life;
                TypeVirus = PointerVirus->type;
                printf("  %d%c", LifeVirus, TypeVirus);
            }
        }
        printf("\n");
    }
}

void MessageEndGame(int GameProgress)
{
    if (GameProgress == -1)
        printf("Vous avez perdu !\n");
    else if (GameProgress == 1)
        printf("Vous avez gagner\n");
}

void ChoiceMode(char *Mode, char NameFile[12])
{
    char Level = '1';
    do
    {
        printf("Dans quelle mode souhaitez-vous jouer ?(G : Graphique ou C : Console)\n");
        scanf("%c", Mode);
    } while (*Mode != 'G' && *Mode != 'C');
    do
    {
        printf("Quel niveau souhaitez-vous ? (1,2,3)\n");
        scanf(" %c", &Level);
    } while (Level != '1' && Level != '2' && Level != '3');
    NameFile[5] = Level;
}