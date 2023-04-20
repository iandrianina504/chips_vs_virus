#include "MAJ_GAME.h"

void LossLifeVirus(Game *NewGame, Chips *NewChips, Virus *TAB_VIRUS[NB_LINE][NB_POSITION])
{
    // On définit le type du Chips qui va agir.
    int ChipsType = NewChips->type;
    // On définit l'emplacement du Chips qui va agir.
    int ChipsLine = NewChips->line;
    // On definit deux variable pour parcourir le tableau Virus.
    int Line;
    int Position;
    // On définit les limites des dégats pour les degats de zones.
    int StartLine;
    int EndLine;
    // On définit le virus qui peut subir des degats.
    Virus *NewVirus;
    // On fonction du type du chips les dégat provoquer sont différent de même pour la porter.
    switch (ChipsType)
    {
    // Si type: A (ALLU :Petit dégat (1) provoquer sur toute la ligne .)
    case 65:
        // On parcours le tableau de virus notament la ligne sur lequelle le chips se situe.
        for (Position = 0; Position < NB_POSITION; Position++)
        {
            NewVirus = TAB_VIRUS[ChipsLine][Position];
            // Si c'est un virus alors on lui enlève 1 à ça vie.
            if (NewVirus != NULL)
            {
                NewVirus->life -= 1;
                // Si le virus n'a plus de vie on le supprime.
                if (NewVirus->life <= 0)
                {
                    DeleteVirus(NewGame, TAB_VIRUS, NewVirus, ChipsLine, Position);
                }
            }
        }
        break;
    // Si type: P (PMMU :Diminue la vitesse de tout les virus de la ligne à 1.)
    case 80:
        // On parcours le tableau de virus notament la ligne sur lequelle est le chips se situe
        for (Position = 0; Position < NB_POSITION; Position++)
        {
            NewVirus = TAB_VIRUS[ChipsLine][Position];
            // Si c'est un virus alors on met ça vitesse à 1 et on met 1 de dégat.
            if (NewVirus != NULL)
            {
                NewVirus->speed = 1;
                NewVirus->life -= 1;
                // Si le virus n'a plus de vie on le supprime.
                if (NewVirus->life <= 0)
                {
                    DeleteVirus(NewGame, TAB_VIRUS, NewVirus, ChipsLine, Position);
                }
            }
        }
        break;
    // Si type: X (Patch : Le virus sera supprimer avec le chips dans une autre fonction.)
    case 88:
        break;

    // Si type: R (RAM :Fait des degat de zones sur 3 lignes et 3 colonne.)
    case 82:
        if (ChipsLine == 0)
        {
            StartLine = ChipsLine;
            EndLine = ChipsLine + 1;
        }
        else if (ChipsLine == NB_LINE - 1)
        {
            StartLine = ChipsLine - 1;
            EndLine = ChipsLine;
        }
        else
        {
            StartLine = ChipsLine - 1;
            EndLine = ChipsLine + 1;
        }
        // On parcourt les 2 lignes voisines si il y a et on fait les degats sur les virus.
        for (Line = StartLine; Line <= EndLine; Line++)
        {
            for (Position = 0; Position < NB_POSITION; Position++)
            {
                NewVirus = TAB_VIRUS[Line][Position];
                // Si c'est un virus alors on lui met des degats.
                if (NewVirus != NULL)
                {
                    NewVirus->life -= 3;
                    // Si le virus n'a plus de vie on le supprime.
                    if (NewVirus->life <= 0)
                    {
                        DeleteVirus(NewGame, TAB_VIRUS, NewVirus, Line, Position);
                    }
                }
            }
        }
        break;
    }
}

void UpdateVirus(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION])
{
    // On definie le chips qui peut mettre des dégats au virus.
    Chips *NewChips = NewGame->chips;
    // On parcours la liste chainée pour faire agir les Chips.
    while (NewChips != NULL)
    {
        LossLifeVirus(NewGame, NewChips, TAB_VIRUS);
        NewChips = NewChips->next;
    }
}

void DeleteVirus(Game *NewGame, Virus *TAB_VIRUS[NB_LINE][NB_POSITION], Virus *NewVirus, int LineVirus, int PositionVirus)
{
    Virus *TheVirus = NULL;
    // Si il n'y pas de virus dans la liste chainé on fait rien.
    if (NewGame->virus == NULL)
    {
        return;
    }
    // Si le virus à supprimer et au premier rang et qui il n'est pas seul dans la liste chainé.
    else if (NewGame->virus == NewVirus && NewGame->virus->next != NULL)
    {
        // Le virus qui sera derière le virus à supprimer sur la ligne.
        Virus *NextLineVirus = NULL;
        // On stocke dans une variable temporaires le debut de la liste.
        TheVirus = NewGame->virus;
        // On modifie le debut de la liste par le Deuxième élément de la liste.
        NewGame->virus = TheVirus->next;
        // PositionNext correspond à l'index ou l'on se trouve dans le tableau de la ligne.
        int PositionNext = PositionVirus;
        // On parcours le tableau jusqu'a trouver un virus ou non.
        while (NextLineVirus == NULL && PositionNext < NB_POSITION)
        {
            NextLineVirus = TAB_VIRUS[LineVirus][PositionNext];
            PositionNext++;
        }
        // Si on est sortie du tableau alors on n'a pas trouver de virus.
        if (PositionNext >= NB_POSITION)
        {
            NextLineVirus = NULL;
        }
        // On oublie pas de modifier le pointeur prev_line et next_line car un élement va être suprimer donc pointer sur NULL.
        NewGame->virus->prev_line = NULL;
        NewGame->virus->next_line = NextLineVirus;
        // On supprime le virus dans le tableau de virus.
        TAB_VIRUS[LineVirus][PositionVirus] = NULL;
        // On libère l'ésapce mémoire.
        free(TheVirus);
    }
    // Si le virus à supprimer et au premier rang et qui il est seul dans la liste chainé.
    else if (NewGame->virus == NewVirus && NewGame->virus->next == NULL)
    {
        NewGame->virus = NULL;
        TAB_VIRUS[LineVirus][PositionVirus] = NULL;
        free(NewVirus);
    }
    // Sinon on parcourt la liste chainé jusqu'à tomber sur l'élement.
    else
    {
        // Le virus qui sera derière le virus à supprimer sur la ligne.
        Virus *NextLineVirus = NULL;
        // Le virus qui sera devant le virus à supprimer sur la ligne.
        Virus *PrevlineVirus = NULL;
        // Le virus avant le virus à supprimer pour le champs Next dans le chainage.
        Virus *BeforeVirus = NewGame->virus;
        // On parcours la liste de chaine jusqu'a trouver le virus à supprimer.
        while (BeforeVirus != NULL && BeforeVirus->next != NewVirus)
        {
            BeforeVirus = BeforeVirus->next;
        }
        // Si on à pas parcourut toute la table alors on a trouver le virus.
        if (BeforeVirus != NULL)
        {
            // On définie le virus a supprimer.
            TheVirus = BeforeVirus->next;
            // Si le virus n'est pas en fin de ligne alors il y peut y avoir un virus derrière lui.
            if (PositionVirus < NB_POSITION - 1)
            {
                // PositionNext correspond à l'index ou l'on se trouve dans le tableau de la ligne.
                int PositionNext = PositionVirus;
                // On parcours le tableau jusqu'a trouver un virus ou non.
                while (NextLineVirus == NULL && PositionNext < NB_POSITION)
                {
                    NextLineVirus = TAB_VIRUS[LineVirus][PositionNext];
                    PositionNext++;
                }
                // Si on est sortie du tableau alors on n'a pas trouver de virus.
                if (PositionNext >= NB_POSITION)
                {
                    NextLineVirus = NULL;
                }
            }
            // Si le virus est en fin de ligne alors pas e virus derrière lui.
            else
            {
                NextLineVirus = NULL;
            }
            // Si le virus n'est pas en début de ligne alors il peut y avoir un virus devant lui.
            if (PositionVirus < NB_POSITION - 1)
            {
                // PositionPrev correspond à l'index ou l'on se trouve dans le tableau de la ligne.
                int PositionPrev = PositionVirus;
                // On parcours le tableau jusqu'a trouver un virus ou non.
                while (PrevlineVirus == NULL && PositionPrev > 0)
                {
                    PrevlineVirus = TAB_VIRUS[LineVirus][PositionPrev];
                    PositionPrev++;
                }
                // Si on est sortie du tableau alors on n'a pas trouver de virus.
                if (PositionPrev <= 0)
                {
                    PrevlineVirus = NULL;
                }
            }
            // Si le virus est en début de ligne alors il n'y a pas de virus devant lui.
            else
            {
                PrevlineVirus = NULL;
            }
            // On change le chainage pour sauter le virus supprimer dans le chainage Next.
            BeforeVirus->next = TheVirus->next;
            BeforeVirus->next_line = NextLineVirus;
            BeforeVirus->prev_line = PrevlineVirus;
            // On supprime le virus dans la mémoire.
            free(TheVirus);
            // On supprime le virus dans le tableau de virus.
            TAB_VIRUS[LineVirus][PositionVirus] = NULL;
        }
    }
}

void AdvancementVirus(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION])
{
    // On définit le virus qui va avancer.
    Virus *NewVirus;
    // On définit le chips qui peut se situer sur son passage.
    Chips *NewChips;
    // On définit 2 int pour parcourir les tableaus (virus et chips).
    int i, j;
    // On définit le type de chips qui peut être rencontrer.
    int ChipsType;
    // On parcours le tableau de virus pour faire avancer 1 par 1 les virus.

    for (i = 0; i < NB_LINE; i++)
    {
        for (j = 0; j < NB_POSITION; j++)
        {
            // On initialise le virus.
            NewVirus = TAB_VIRUS[i][j];
            // Si c'est un virus alors en le fait avancer sur la ligne.
            if (NewVirus != NULL)
            {
                // On récupère la vitesse du virus pour pouvoir supprimer le chips par la suite si il y a une mine.
                int SpeedVirus = NewVirus->speed;
                // Si c'est le gros vilain, on le fait avancer 1 tour sur 2.
                if ((NewVirus->type == 68 && NewGame->turn % 2 == 0) || NewVirus->type != 68)
                {
                    // On initialise le chips qui peut se situer devant lui sur la ligne.
                    NewChips = TAB_CHIPS[i][j - 1];
                    // Si il y a bien un chips alors le virus ne peut pas continuer à avancer mais va faire des dégat au chips.
                    if (NewChips != NULL)
                    {
                        // On initialise le type de chips.
                        ChipsType = NewChips->type;
                        // On fonction du chips, le virus peut se faire éliminer ou non.
                        switch (ChipsType)
                        {
                        // Si type: X ( patchs :explose au contact en tuant ainsi seulement le premier gros vilain.)
                        case 88:
                            // On supprime le virus.
                            DeleteVirus(NewGame, TAB_VIRUS, NewVirus, i, j);
                            // On supprime le chips aprés explosion.
                            DeleteChips(NewGame, TAB_CHIPS, NewChips, i, j - SpeedVirus);
                            break;
                        // Sinon on fait des dégat au chips.
                        default:
                            LossLifeChips(NewGame, NewChips, TAB_CHIPS, i, j - SpeedVirus);
                            break;
                        }
                    }
                    // Si il y a un virus devant lui ou de chips alors il n'avance pas.
                    if (TAB_VIRUS[i][j - 1] == NULL && NewChips == NULL)
                    {
                        NewVirus->position = j - NewVirus->speed;
                        TAB_VIRUS[i][j - NewVirus->speed] = NewVirus;
                        TAB_VIRUS[i][j] = NULL;
                    }
                }
            }
        }
    }
}

// ################################################################################################################## //

void DeleteChips(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Chips *NewChips, int LineChips, int PositionChips)
{
    Chips *TheChips;
    // Si il n'y pas de chips dans la liste chainé on fait rien.
    if (NewGame->chips == NULL)
    {
        return;
    }
    // Si le chips à supprimer et au premier rang.
    else if (NewGame->chips == NewChips)
    {
        // On stocke dans une variable temporaires le debut de la liste.
        TheChips = NewGame->chips;
        // On modifie le debut de la liste par le Deuxième élément de la liste.
        NewGame->chips = NewChips->next;
        // On libère l'ésapce mémoire.
        free(TheChips);
        TAB_CHIPS[LineChips][PositionChips] = NULL;
    }
    // Sinon on parcourt la liste chainé jusqu'à tomber sur l'élement.
    else
    {
        Chips *BeforeChips = NewGame->chips;
        // On parcours la liste de chaine jusqu'a trouver le chips à supprimer.
        while (BeforeChips != NULL && BeforeChips->next != NewChips)
        {
            BeforeChips = BeforeChips->next;
        }
        // Si on à pas parcourut toute la table alors on a trouver le virus.
        if (BeforeChips != NULL)
        {
            // On définie le Chips a supprimer.
            TheChips = BeforeChips->next;
            // On change le chainage pour sauter le chips supprimer dans le chainage Next.
            BeforeChips->next = TheChips->next;
            // On supprime le virus dans la mémoire.
            free(TheChips);
            // On supprime le virus dans le tableau de virus.
            TAB_CHIPS[LineChips][PositionChips] = NULL;
        }
    }
}

void LossLifeChips(Game *NewGame, Chips *NewChips, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], int LineChips, int PositionChips)
{
    // On fait diminuer la vie du chips.
    NewChips->life -= 1;
    // Si le chips n'a plus de vie on le supprime.
    if (NewChips->life <= 0)
    {
        DeleteChips(NewGame, TAB_CHIPS, NewChips, LineChips, PositionChips);
    }
}
