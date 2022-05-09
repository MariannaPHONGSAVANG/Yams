/**
 * @file codev3doxygen.c
 * @author Marianna Phongsavang (marianna.phongsavang@etudiant.univ-rennes1.fr)
 * @brief  Programme du yams
 * @version 0.3
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 * Ce programme doit faire jouer deux personnes dans une partie de yams
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

const int BONUS = 62;
const int PTBONUS = 35;
const int FULLHOUSE = 25;
const int PETISUITE = 30;
const int GRANSUITE = 40;
const int YAMS = 50;
const int DE1 = 1;
const int DE2 = 2;
const int DE3 = 3;
const int DE4 = 4;
const int DE5 = 5;
const int DE6 = 6;


void remiseAZero(int[17], int[17]);
void noms(char[9], char[9]);
void affichegrille(char[9], char[9], int[17], int[17]);
char propose();
void lancerdes(int[5]);
void choixdes(int[5]);
void affectionduscore(int[17], int[17], int[5], int);
void triselec(int[5]);
void vainqueur(int[17], int[17], char[9], char[9]);

/*****************************************************
                * PROGRAMME PRINCIPAL *
*****************************************************/
/**
 * @fn int main()
 * @brief programme principale
 * 
 * @return int 0
 */
int main()
{
    char j1[9], j2[9];
    int tab1[17];
    int tab2[17];
    char rep;
    int tour, joueur = 0;
    int lesdes[5];
    remiseAZero(tab1, tab2);
    noms(j1, j2);
    for (tour = 0; tour < 13; tour++)
    {

        for (joueur = 0; joueur < 2; joueur++)
        {
            printf("tour du joueur :%d \n", joueur + 1);
            affichegrille(j1, j2, tab1, tab2);
            do
            {
                rep = propose();
                
            } while (rep != 'O' );
            if (rep == 'O')
            {
                lancerdes(lesdes);
                affichegrille(j1, j2, tab1, tab2);
                choixdes(lesdes);
                affectionduscore(tab1, tab2, lesdes, joueur);
            }
        }
    }
    vainqueur(tab1, tab2, j1, j2);
    return EXIT_SUCCESS;
}




/*****************************************************
 * FONCTIONS UTILITAIRES POUR MANIPULER LES PRODUITS *
*****************************************************/
/**
 * @fn void remiseAZero(int tabscore1[17], int tabscore2[17])
 * @brief procedure qui met a zero les valeurs des tableaux tab1 et tab2 qui sont le score des joueurs
 * @param tabscore1 : la chaine a mettre a zero
 * @param tabscore2 : la chainne a mettre a zero
 */
void remiseAZero(int tabscore1[17], int tabscore2[17])
{
    int i;
    for (i = 0; i < 17; i++)
    {
        tabscore1[i] = 00;
        tabscore2[i] = 00;
    }
}

/**
 * @fn void noms(char nom1[9], char nom2[9])
 * @brief procedure qui demande le noms des joueur  
 * @param nom1 : chaine à tester
 * @param nom2 : chaine à tester
 * 
 * verifie que les noms font bien 9 caractères et les assigne
 */
void noms(char nom1[9], char nom2[9])
{
    int lon = 10;
    int l = 10;
    while (lon > 9)
    {
        printf("ecrire le nom du 1er joueur (pas plus de 9 caractères)\n");
        scanf("%s", nom1);
        lon = strlen(nom1);
    }

    while (l > 9)
    {

        printf("ecrire le nom du deuxieme joueur( pas plus de 9 caractères)\n");
        scanf("%s", nom2);
        l = strlen(nom2);
    }
}

/**
 * @fn affichegrille(char nom1[9], char nom2[9], int tabscore1[17], int tabscore2[17])
 *  @brief affiche la grille des joueurs
 * 
 * 
 * @param nom1 : montre le nom du joueur dans le tableau
 * @param nom2 :monter le nom du joueur dans le tableau
 * @param tabscore1 : score du joueur 1
 * @param tabscore2 : score du joueur 2
 * 
 * affiche la grille des joueurs, leurs noms, et chaque score 
 * dans chaque case
 */
void affichegrille(char nom1[9], char nom2[9], int tabscore1[17], int tabscore2[17])
{

    printf("---------------------------------------\n");
    printf("||||||||||||||||||%9s|%9s|\n", nom1, nom2);
    printf("| Total de 1     |%9d|%9d|\n", tabscore1[0], tabscore2[0]);
    printf("| Total de 2     |%9d|%9d|\n", tabscore1[1], tabscore2[1]);
    printf("| Total de 3     |%9d|%9d|\n", tabscore1[2], tabscore2[2]);
    printf("| Total de 4     |%9d|%9d|\n", tabscore1[3], tabscore2[3]);
    printf("| Total de 5     |%9d|%9d|\n", tabscore1[4], tabscore2[4]);
    printf("| Total de 6     |%9d|%9d|\n", tabscore1[5], tabscore2[5]);
    printf("| Bonus si +de 62|%9d|%9d|\n", tabscore1[6], tabscore2[6]);
    printf("| Total sup      |%9d|%9d|\n", tabscore1[7], tabscore2[7]);
    printf("| Brelan         |%9d|%9d|\n", tabscore1[8], tabscore2[8]);
    printf("| Carre          |%9d|%9d|\n", tabscore1[9], tabscore2[9]);
    printf("| Full house     |%9d|%9d|\n", tabscore1[10], tabscore2[10]);
    printf("| Petite suite   |%9d|%9d|\n", tabscore1[11], tabscore2[11]);
    printf("| Grande suite   |%9d|%9d|\n", tabscore1[12], tabscore2[12]);
    printf("| Yams           |%9d|%9d|\n", tabscore1[13], tabscore2[13]);
    printf("| Chance         |%9d|%9d|\n", tabscore1[14], tabscore2[14]);
    printf("| Total inf      |%9d|%9d|\n", tabscore1[15], tabscore2[15]);
    printf("| Total          |%9d|%9d|\n", tabscore1[16], tabscore2[16]);
    printf("---------------------------------------\n");
}

/**
 * @fn propose()
 * @brief fonction qui propose au joueur de jouer son tour
 * 
 * @return char : caractère a verifie dans le main
 */
char propose()
{
    char p;
    printf("Voulez-vous jouez ? (O ou N) : ");
    scanf(" %c", &p);
    return p;
}

/**
 * @fn lancerdes( des[5]int)
 * @brief procédure qui lance cinq dés aléatoirement
 * 
 * @param des : tableau des 5 dés 
 * 
 * donne un chiffre entre 1 et 6 aléatoirement et l'affecte au tableau de dés
 */
void lancerdes(int des[5])
{
    
    srand(time(NULL));
    for (int m = 1; m < 6; m++)
    {
        des[m] = 1 + rand() % 6;
        printf("de %d : %d\n", m, des[m]);
    }
}

/**
 * @fn choixdes(int des[5])
 * @brief procédure qui demande si le joueur veux garder des dés ou pas
 * 
 * @param des : tableau à changer au besoin
 * 
 * demande si on veut relancer des dés.si oui demande le nombre de dés 
 * à changer puis demande les dés à changer tant que les dés ne sont 
 * pas relancer trois fois
 */
void choixdes(int des[5])
{

    int relance = 1;
    char rep;
    int nblan = 0;
    int d;
    int tmpd[5];
    while (relance <= 3)
    {
        do
        {
            printf("voulez-vous relancer des des (O/N) : ");
            scanf(" %c", &rep);
        } while (rep != 'O' && rep != 'N');
        if (rep == 'O')
        {
            do
            {
                printf("Combien de des souhaitez-vous relancer ? ");
                scanf("%d", &nblan);
            } while (nblan < 1 && nblan > 5);

            printf("%d\n", nblan);
            srand(time(NULL));
            for (int i = 1; i <= nblan; i++)
            {
                do
                {
                    printf("Quel de souhaite vous change ? ");
                    scanf("%d", &d);
                } while (d < 1 && d > 5);
                tmpd[i] = d;
            }

            for (int j = 1; j <= nblan; j++)
            {
                des[tmpd[j]] = 1 + rand() % 6;
            }
        }
        if (rep == 'N')
        {
            relance = 4;
        }

        relance = relance + 1;
        for (int k = 1; k < 6; k++)
        {
            printf("de %d : %d\n", k, des[k]);
        }

        relance = relance + 1;
    }
}

/**
 * @fn affectionduscore(int tabscore1[17], int tabscore2[17], int des[5], int j)
 * @brief procedure qui affecte le score du joueur
 * 
 * @param tabscore1 :score du joueur 1
 * @param tabscore2 : score du joueur 2
 * @param des : les des à calculer pour affecter le score
 * @param j : numéro du joueur qui fait son tour
 * 
 * demande un nombre pour l'affecter a leur score , vérifie si aucun score déja affecter à la 
 * case choisie 
 */
void affectionduscore(int tabscore1[17], int tabscore2[17], int des[5], int j)
{
    int resp = 0;
    int sc1 = 0;
    int c = 20;
    bool reus = false;

    while (reus == false)
    {
        do
        {
            printf("A vous d'affecter vos des!\n");
            printf("Tapez l'un des chiffres suivants pour l'affecter : \n");
            printf("1 - Total de 1\n");
            printf("2 - total de 2\n");
            printf("3 - total de 3\n");
            printf("4 - total de 4\n");
            printf("5 - total de 5\n");
            printf("6 - total de 6\n");
            printf("7 - brelan\n");
            printf("8 - carre\n");
            printf("9 - full house\n");
            printf("10 - petite suite\n");
            printf("11 - grande suite\n");
            printf("12 - yams\n");
            printf("13 - chance\n");
            printf("14 - barrer une case\n");
            printf("? : \n");
            scanf(" %d", &resp);
            printf("%d\n", resp);
        } while ((resp > 14) && (resp <= 0));
        switch (resp)
        {

        case 1:
            if (((j == 0) && (tabscore1[0] == 0)) || (j == 1 && tabscore2[0] == 0))
            {
                for (int j = 1; j < 5; j++)
                {
                    if (des[j] == 1)
                    {
                        sc1 = sc1 + 1;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[0] = DE1 * sc1;
                }
                if (j == 1)
                {
                    tabscore2[0] = DE1 * sc1;
                }
            }

            break;

        case 2:
            if ((j == 0 && tabscore1[1] == 0) || (j == 1 && tabscore2[1] == 0))
            {
                for (int j = 1; j < 6; j++)
                {
                    if (des[j] == 2)
                    {
                        sc1 = sc1 + 1;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[1] = DE2 * sc1;
                }
                if (j == 1)
                {
                    tabscore2[1] = DE2 * sc1;
                }
            }

            break;
        case 3:
            if ((j == 0 && tabscore1[2] == 0) || (j == 1 && tabscore2[2] == 0))
            {
                for (int j = 1; j < 6; j++)
                {
                    if (des[j] == 3)
                    {
                        sc1 = sc1 + 1;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[2] = DE3 * sc1;
                }
                if (j == 1)
                {
                    tabscore2[2] = DE3 * sc1;
                }
            }

            break;
        case 4:
            if ((j == 0 && tabscore1[3] == 0) || (j == 1 && tabscore2[3] == 0))
            {
                for (int j = 1; j < 6; j++)
                {
                    if (des[j] == 4)
                    {
                        sc1 = sc1 + 1;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[3] = DE4 * sc1;
                }
                if (j == 1)
                {
                    tabscore2[3] = DE4 * sc1;
                }
            }

            break;
        case 5:
            if ((j == 0 && tabscore1[4] == 0) || (j == 1 && tabscore2[4] == 0))
            {
                for (int j = 1; j < 6; j++)
                {
                    if (des[j] == 5)
                    {
                        sc1 = sc1 + 1;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[4] = DE5 * sc1;
                }
                if (j == 1)
                {
                    tabscore2[4] = DE5 * sc1;
                }
            }

            break;
        case 6:
            if ((j == 0 && tabscore1[5] == 0) || (j == 1 && tabscore2[5] == 0))
            {
                for (int j = 1; j < 6; j++)
                {
                    if (des[j] == 6)
                    {
                        sc1 = sc1 + 1;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[5] = DE6 * sc1;
                }
                if (j == 1)
                {
                    tabscore2[5] = DE6 * sc1;
                }
            }

            break;
        case 7:
            if ((j == 0 && tabscore1[8] == 0) || (j == 1 && tabscore2[8] == 0))
            {
                triselec(des);
                for (int k = 1; k < 6; k++)
                {
                    if (des[k] == des[k + 1] && des[k] == des[k + 2])
                    {
                        sc1 = des[k] * 3;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[8] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[8] = sc1;
                }
            }

            break;
        case 8:
            if ((j == 0 && tabscore1[9] == 0) || (j == 1 && tabscore2[9] == 0))
            {
                triselec(des);
                for (int k = 1; k < 6; k++)
                {
                    if ((des[k] == des[k + 1]) && (des[k] == des[k + 2]) && (des[k] == des[k + 3]))
                    {
                        sc1 = des[k] * 4;
                        reus = true;
                    }
                }
                if (j == 0)
                {
                    tabscore1[9] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[9] = sc1;
                }
            }

            break;
        case 9:
            if ((j == 0 && tabscore1[10] == 0) || (j == 1 && tabscore2[10] == 0))
            {
                triselec(des);
                if (((des[1] == des[2]) && (des[3] == des[4] && des[3] == des[5])) || ((des[1] == des[2] && des[1] == des[3]) && (des[4] == des[5])))
                {
                    sc1 = FULLHOUSE;
                    reus = true;
                }
                if (j == 0)
                {
                    tabscore1[10] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[10] = sc1;
                }
            }

            break;
        case 10:
            if ((j == 0 && tabscore1[11] == 0) || (j == 1 && tabscore2[11] == 0))
            {
                triselec(des);
                if ((des[1] == 1 && des[2] == 2 && des[3] == 3 && des[4] == 4) || (des[1] == 2 && des[2] == 3 && des[3] == 4 && des[4] == 5) || (des[2] == 1 && des[3] == 2 && des[4] == 3 && des[5] == 4) || (des[2] == 2 && des[3] == 3 && des[4] == 4 && des[5] == 5) || (des[1] == 3 && des[2] == 4 && des[3] == 5 && des[4] == 6) || (des[2] == 3 && des[3] == 4 && des[4] == 5 && des[5] == 6))
                {
                    sc1 = PETISUITE;
                    reus = true;
                }

                if (j == 0)
                {
                    tabscore1[11] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[11] = sc1;
                }
            }

            break;

        case 11:
            if ((j == 0 && tabscore1[12] == 0) || (j == 1 && tabscore2[12] == 0))
            {
                triselec(des);
                if ((des[1] == 1 && des[2] == 2 && des[3] == 3 && des[4] == 4 && des[5] == 5) || (des[1] == 2 && des[2] == 3 && des[3] == 4 && des[4] == 5 && des[5] == 6))
                {
                    sc1 = GRANSUITE;
                    reus = true;
                }
                if (j == 0)
                {
                    tabscore1[12] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[12] = sc1;
                }
            }

            break;

        case 12:
            if ((j == 0 && tabscore1[13] == 0) || (j == 1 && tabscore2[13] == 0))
            {
                if (des[1] == des[2] && des[1] == des[3] && des[1] == des[4] && des[1] == des[5])
                {
                    sc1 = YAMS;
                    reus = true;
                }
                if (j == 0)
                {
                    tabscore1[13] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[13] = sc1;
                }
            }

            break;

        case 13:
            if ((j == 0 && tabscore1 == 0) || (j == 1 && tabscore2 == 0))
            {
                sc1 = des[1] + des[2] + des[3] + des[4] + des[5];
                reus = true;
                if (j == 0)
                {
                    tabscore1[14] = sc1;
                }
                if (j == 1)
                {
                    tabscore2[14] = sc1;
                }
            }

            break;

        case 14:
            printf("%d\n", c);

            printf("quelle case souhaite vous barrer (inscrit -1)? ");
            scanf(" %d", &c);

            sc1 = 1;
            if (c == 1)
            {
                if (j == 0)
                {
                    tabscore1[0] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[0] = -1;
                    ;
                    reus = true;
                }
            }

            if (c == 2)
            {
                if (j == 0)
                {
                    tabscore1[1] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[1] = -1;
                    reus = true;
                }
            }
            if (c == 3)
            {
                if (j == 0)
                {
                    tabscore1[2] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[2] = -1;
                    reus = true;
                }
            }
            if (c == 4)
            {
                if (j == 0)
                {
                    tabscore1[3] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[3] = -1;
                    reus = true;
                }
            }
            if (c == 5)
            {
                if (j == 0)
                {
                    tabscore1[4] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[4] = -1;
                    reus = true;
                }
            }
            if (c == 6)
            {
                if (j == 0)
                {
                    tabscore1[5] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[5] = -1;
                    reus = true;
                }
            }
            if (c == 7)
            {
                if (j == 0)
                {
                    tabscore1[8] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[8] = -1;
                    reus = true;
                }
            }
            if (c == 8)
            {
                if (j == 0)
                {
                    tabscore1[9] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[9] = -1;
                    reus = true;
                }
            }
            if (c == 9)
            {
                if (j == 0)
                {
                    tabscore1[10] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[10] = -1;
                    reus = true;
                }
            }
            if (c == 10)
            {
                if (j == 0)
                {
                    tabscore1[11] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[11] = -1;
                    reus = true;
                }
            }
            if (c == 11)
            {
                if (j == 0)
                {
                    tabscore1[12] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[12] = -1;
                    reus = true;
                }
            }
            if (c == 12)
            {
                if (j == 0)
                {
                    tabscore1[13] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[13] = -1;
                    reus = true;
                }
            }
            if (c == 13)
            {
                if (j == 0)
                {
                    tabscore1[14] = -1;
                    reus = true;
                }
                if (j == 1)
                {
                    tabscore2[14] = -1;
                    reus = true;
                }
            }

            break;
        default:
            if (sc1 == 0)
            {
                printf("affection impossible \n");
                reus = false;
                affectionduscore(tabscore1, tabscore2, des, j);
            }

            break;
        }
    }
    tabscore1[7] = 0;
    tabscore2[7] = 0;
    tabscore1[15] = 0;
    tabscore2[15] = 0;
    tabscore1[16] = 0;
    tabscore2[16] = 0;
    for (int totsup = 0; totsup < 7; totsup++)
    {
        if (tabscore1[totsup] != -1)
        {
            tabscore1[7] = tabscore1[7] + tabscore1[totsup];
        }
        if (tabscore2[totsup] != 1)
        {
            tabscore2[7] = tabscore2[7] + tabscore2[totsup];
        }
    }
    if (tabscore1[7] > BONUS)
    {
        tabscore1[6] = PTBONUS;
    }
    if (tabscore2[7] > BONUS)
    {
        tabscore2[6] = PTBONUS;
    }
    for (int totinf = 8; totinf < 15; totinf++)
    {
        if (tabscore1[totinf] != -1)
        {
            tabscore1[15] = tabscore1[15] + tabscore1[totinf];
        }
        if (tabscore2[totinf] != -1)
        {
            tabscore2[15] = tabscore2[15] + tabscore2[totinf];
        }
    }
    tabscore1[16] = tabscore1[7] + tabscore1[15];
    tabscore2[16] = tabscore2[7] + tabscore2[15];
}

/**
 * @fn triselec(int des[5])
 * @brief procédure qui tri les dés en ordre croissant
 * 
 * @param des : tableau à trier
 * 
 * trie les dés pour faciliter les conditions de demande d'affection dans le score
 */
void triselec(int des[5])
{
    int indmin;
    int j;
    int min = 0;
    int tmpd = 0;
    for (int i = 1; i < 5; i++)
    {
        min = des[i];
        indmin = i;
        for (j = i + 1; j < 6; j++)
        {
            if (des[j] < min)
            {
                min = des[j];
                indmin = j;
            }
        }

        tmpd = des[i];
        des[i] = des[indmin];
        des[indmin] = tmpd;
    }
}

/**
 * @fn vainqueur(int tabscore1[17], int tabscore2[17], char nom1[9], char nom2[9])
 * @brief procedure qui dit qui est le vainqueur selon le score totale
 * 
 * @param tabscore1 : regarde le score totale du joueur 1
 * @param tabscore2 : regarde le score du joueur 2
 * @param nom1 : donne le nom du premier joueur
 * @param nom2 donne le nom du deuxieme joueur
 */
void vainqueur(int tabscore1[17], int tabscore2[17], char nom1[9], char nom2[9])
{
    if (tabscore1[16] < tabscore2[16])
    {
        printf("Le deuxieme joueur: %s est vainqueur \n", nom2);
    }
    else
    {
        printf("le premier joueur: %s est vainqueur \n", nom1);
    }
}
