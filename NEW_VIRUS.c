#include "NEW_VIRUS.h"

int ReadFileVirus(Game *NewGame, Virus *TAB_VIRUS[NB_LINE][NB_POSITION], char NameFile[12], long *Curseur)
{
    /*
    Description:

    Fonction qui lie le fichier level et modifie le tableau au virus en fonction du fichier.

    Parametre:

    Game * NewGame (pointeur sur game)
    Virus *TAB_VIRUS[NB_LINE][NB_POSITION]
    (Tableau contenant tout les pointeurs des virus dans le jeu positionner dans le tableau en fonction de leur positio dans le jeu.)
    char NameFile[12] (Nom du fichier à lire).
    long *Curseur (long donnant l'endroit ou en doit commencer à lire)

    */
    // On définie un curseur (long) qui contiendra l'emplacement du curseur à la fin de la lecture.
    long CurseurEndLine;
    // On initialise le numéro de tour actuel.
    int NumTurn = NewGame->turn;
    Virus *NewVirus;
    // On initialise les attribut du virus.
    int LineVirus;
    char TypeVirus;
    // On définit le pointeur qui va ouvrir le fichier.
    FILE *level = NULL;
    level = fopen(NameFile, "r");
    // On déplace le curseur à l'endroit ou on souhaite lire.
    fseek(level, *Curseur, 0);
    // On ajoute dans la liste chainé et le virus dans le tableau tant que le tour n'a pas changer donc la variable tour.
    while (NumTurn == NewGame->turn)
    {
        // Ce curseur permettra de reprendre la lecture au bon audroit l'or de la réouverture du fichier.
        CurseurEndLine = ftell(level);
        // Tant qu'on arrive pas à la fin du fichier lit
        if (fscanf(level, "%d %d %c", &NumTurn, &LineVirus, &TypeVirus) != EOF)
        {
            // Si on est toujour dans le même tour alors en ajoute.
            if (NumTurn == NewGame->turn)
            {
                NewVirus = DeployVirus(TypeVirus, LineVirus, NB_POSITION, NumTurn);
                InsertVirus(NewVirus, NewGame, TAB_VIRUS);
            }
            // Sinon on redéfinie le curseur pour reprendre au bon endroit à la réouverture.
            else
            {
                *Curseur = CurseurEndLine;
            }
        }
        // Le fichier est fini donc si on passe le tour alors le niveau est fini.
        else
        {
            return 0;
        }
    }
    fclose(level);
    return 1;
}

Virus *DeployVirus(int type, int line, int position, int turn)
{
    // On définit le virus qui va être deployer.
    Virus *newVirus;
    // On alloue la mémoire nécessaire avec malloc.
    newVirus = (Virus *)malloc(sizeof(Virus));
    // On définie les attibuts du virus en fonction du choix du fichier.
    if (newVirus != NULL)
    {
        switch (type)
        {
        // Si type: E (floating point exception :Petit dégat (1) provoquer sur les chips.)
        case 69:
            newVirus->type = 'E';
            newVirus->life = 3;
            newVirus->line = line;
            newVirus->position = NB_POSITION;
            newVirus->speed = 1;
            newVirus->turn = turn;
            newVirus->next_line = NULL;
            newVirus->prev_line = NULL;
            newVirus->next = NULL;
            break;
        // Si type: D (Attaques par déni de service : Un gros vilian très solide mais très long.)
        case 68:
            newVirus->type = 'D';
            newVirus->life = 9;
            newVirus->line = line;
            newVirus->position = NB_POSITION;
            newVirus->speed = 1;
            newVirus->turn = turn;
            newVirus->next_line = NULL;
            newVirus->prev_line = NULL;
            newVirus->next = NULL;
            break;

        // Si type: S (erreurs de segmentation : Un vilian très rapide mais peut robuste.)
        case 83:
            newVirus->type = 'S';
            newVirus->life = 3;
            newVirus->line = line;
            newVirus->position = NB_POSITION;
            newVirus->speed = 2;
            newVirus->turn = turn;
            newVirus->next_line = NULL;
            newVirus->prev_line = NULL;
            newVirus->next = NULL;
            break;
        }
        return newVirus;
    }
    return NULL;
}

void InsertVirus(Virus *NewVirus, Game *NewGame, Virus *TAB_VIRUS[NB_LINE][NB_POSITION])
{
    // Si il n'y pas de virus en arrete.
    if (NewVirus == NULL)
    {
        return;
    }
    // Si la chaine n'est pas initialisée, on l'initialise avec le virus que l'on vient d'ajouter.
    else if (NewGame->virus == NULL)
    {
        NewGame->virus = NewVirus;
        TAB_VIRUS[(NewVirus->line) - 1][(NewVirus->position) - 1] = NewVirus;
    }
    else
    {

        Virus *suivant = NewGame->virus;
        // On parcours la chaine de virus jusqu'a arriver à la fin donc quand il pointe sur NULL.
        while (suivant->next != NULL)
        {
            suivant = suivant->next;
        }
        // On change le pointeur pour qu'il pointe sur le nouveau virus.
        suivant->next = NewVirus;
        // On l'ajoute dans le tableau de virus.
        // On soustrait les index dans le tableau car dans le fichier on commence ils sont entre (1-6) et (1-24).
        TAB_VIRUS[NewVirus->line - 1][NewVirus->position - 1] = NewVirus;
        // Si le virus n'est pas à la fin de la ligne alors il  peut avoir des virus dérriere lui.
        if (NewVirus->position < NB_POSITION - 1)
        {
            // La position du virus sur la ligne.
            int NextLinePosition = NewVirus->position;
            // On réalise une boucle pour trouver le premier virus dérriere lui.
            while (NewVirus->next_line == NULL && NextLinePosition < NB_POSITION)
            {
                NewVirus->next_line = TAB_VIRUS[NewVirus->line - 1][NextLinePosition];
                NextLinePosition++;
            }
            // Si NextLinePosition dépasse le tableau alors pas de virus dérrière lui.
            if (NextLinePosition >= NB_POSITION)
            {
                NewVirus->next_line = NULL;
            }
        }
        // Si il est à la fin alors pas de virus dérrier lui.
        else
        {
            NewVirus->next_line = NULL;
        }
        // Si le virus n'est pas au début de la ligne alors il peut avoir des virus devant lui.
        if (NewVirus->position > 0)
        {
            // La position du virus sur la ligne.
            int PrevLinePosition = NewVirus->position;
            // On réalise une boucle pour trouver le premier virus devant lui.
            while (NewVirus->prev_line == NULL && PrevLinePosition < NB_POSITION)
            {
                NewVirus->prev_line = TAB_VIRUS[NewVirus->line - 1][PrevLinePosition];
                PrevLinePosition++;
            }
            // Si PrevLinePosition dépasse le tableau alors il n'y a pas de virus devant lui.
            if (PrevLinePosition >= NB_POSITION)
            {
                NewVirus->prev_line = NULL;
            }
        }
        // Si il est à la fin alors pas de virus dérrier lui.
        else
        {
            NewVirus->prev_line = NULL;
        }
    }
}

void LevelPreviewVirus(char NameFile[12], Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION], long *Curseur)
{
    // On initialise le numéro de tour actuel.
    int NumTurn;
    Virus *NewVirus;
    // On initialise les attribut du virus.
    int LineVirus;
    char TypeVirus;
    // On définit le pointeur qui va ouvrir le fichier.
    FILE *level = NULL;
    level = fopen(NameFile, "r");
    // On déplace le curseur à l'endroit ou on souhaite lire.
    fseek(level, *Curseur, 0);
    // Tant qu'on arrive pas à la fin du fichier lit
    while (fscanf(level, "%d %d %c", &NumTurn, &LineVirus, &TypeVirus) != EOF)
    {
        NewVirus = DeployVirus(TypeVirus, LineVirus, NB_POSITION, NumTurn);
        TAB_VIRUS_PREVIEW[LineVirus - 1][NumTurn - 1] = NewVirus;
    }
    fclose(level);
}
