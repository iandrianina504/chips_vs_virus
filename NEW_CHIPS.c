#include "NEW_CHIPS.h"
#include "SETTING_GAME.h"

void ChoiceChips(Game *NewGame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS[NB_LINE][NB_POSITION], Virus *TAB_VIRUS_PREVIEW[NB_LINE][NB_POSITION])
{
    // On définit l'emplacement ou le chips va être placer.
    int line;
    int position;
    // On définit le type de chips qui sera déployer.
    char Deploy;
    // On définit le Chips qui sera déployer
    Chips *NewChips;
    // Tant que le joueur a de l'argent il peut continuer à déployer.
    while (NewGame->money > 0)
    {
        // On affiche son argent.
        printf("Money : %d\n", NewGame->money);
        // On lui propose les choix.
        printf("What chips do you want to deploy ? If you wat to see the level press L.\n \
            F : firewall (125)\n \
            P : PMMU (150)\n \
            A : ALU (100)\n \
            R : RAM(300)\n \
            X : Patch (50)\n \
            q : no more\n \
            L : Preview Level\n \
            Your choice ?\n");
        scanf(" %c", &Deploy);
        // Si il choissi 'q' alors il a fini de déployer.
        if (Deploy == 'q')
        {
            return;
        }
        else if (Deploy == 'L')
        {
            PrintPreviewGame(TAB_VIRUS_PREVIEW);
        }
        if (Deploy != 'L')
        {
            // On créer un controle de saisie pour que le joueur ne choissie pas un emplacement impossible.
            do
            {
                printf("veuillez saisir la ligne où jouer (entre 1 et 7) et la position (entre 1 et 23): ");
                scanf("%d %d", &line, &position);
            } while (0 >= line || line > NB_LINE || 0 >= position || position > NB_POSITION || TAB_CHIPS[line - 1][position - 1] != NULL);
            // On créer le chips grâce à la fonction Deploychips.
            NewChips = DeployChips(Deploy, line - 1, position - 1, NewGame);
            // On insert Chips dans la liste chainé et le tableau de chips.
            InsertChips(NewChips, NewGame, TAB_CHIPS);
            // Puis on affiche le jeu sur le terminal.
            PrintGame(TAB_CHIPS, TAB_VIRUS);
        }
    }
}

void InsertChips(Chips *NewChips, Game *Newgame, Chips *TAB_CHIPS[NB_LINE][NB_POSITION])
{
    // Si il n'y pas de chips en arrete.
    if (NewChips == NULL)
    {
        return;
    }
    // Si la chaine n'est pas initialisée, on l'initialise avec le chips que l'on vient d'ajouter.
    else if (Newgame->chips == NULL)
    {
        Newgame->chips = NewChips;
        TAB_CHIPS[NewChips->line][NewChips->position] = NewChips;
    }
    else
    {
        Chips *suivant = Newgame->chips;
        // On parcours la chaine de chips jusqu'a arriver à la fin donc quand il pointe sur NULL.
        while (suivant->next != NULL)
        {
            suivant = suivant->next;
        }
        // On change le pointeur pour qu'il pointe sur le nouveau chips.
        suivant->next = NewChips;
        // On l'ajoute dans le tableau de chips.
        TAB_CHIPS[NewChips->line][NewChips->position] = NewChips;
    }
}

Chips *DeployChips(int type, int line, int position, Game *NewGame)
{
    // On definit le chips qui va être déployer.
    Chips *newChips;
    // On alloue la mémoire nécessaire avec malloc.
    newChips = (Chips *)malloc(sizeof(Chips));
    // On définie les attibuts du chips en fonction du choix du joueur.
    switch (type)
    {
    // Si type: A (ALLU :Petit dégat (1) provoquer sur toute la ligne .)
    case 65:
        newChips->type = 'A';
        newChips->life = 2;
        newChips->line = line;
        newChips->position = position;
        newChips->price = 100;
        newChips->next = NULL;
        NewGame->money -= 100;
        break;
    // Si type: P (PMMU :Diminue la vitesse de tout les virus de la ligne à 1.)
    case 80:
        newChips->type = 'P';
        newChips->life = 2;
        newChips->line = line;
        newChips->position = position;
        newChips->price = 150;
        newChips->next = NULL;
        NewGame->money -= 150;
        break;
    // Si type: X (Patch : explose sur le virus.)
    case 88:
        newChips->type = 'X';
        newChips->life = 1;
        newChips->line = line;
        newChips->position = position;
        newChips->price = 50;
        newChips->next = NULL;
        NewGame->money -= 50;
        break;
    // Si type: F (Firewall: mur ne faisant pas de dégat.)
    case 70:
        newChips->type = 'F';
        newChips->life = 9;
        newChips->line = line;
        newChips->position = position;
        newChips->price = 125;
        newChips->next = NULL;
        NewGame->money -= 125;
        break;
    // Si type: R (RAM: fait des dégats sur 1 ligne et les 2 lignes à coter.)
    case 82:
        newChips->type = 'R';
        newChips->life = 2;
        newChips->line = line;
        newChips->position = position;
        newChips->price = 300;
        newChips->next = NULL;
        NewGame->money -= 300;
        break;
    }
    // On retourne le chips.
    return newChips;
}