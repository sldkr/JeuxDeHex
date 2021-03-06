/*!
   \file test_Plateau.c
   \brief Exemple d'utilisation de la structure plateau avec ces tests
   \author Sylvain DEKER
   \date 1/05/2017
*/

#define _POSIX_C_SOURCE 1
#include "Plateau.h"

#define TAILLE_PLAT 8

void afficher_plateau(Plateau p);
void bilan(Plateau p);
void afficher_menu(int *c);
int main(int argc, char const *argv[]) {
    printf("======================TEST : contructeur_Joueur(){ ==========================\n" );
    Joueur patrick=contructeur_Joueur();
    Joueur robert=contructeur_Joueur();



    printf("======================TEST : contructeur_plateu(){ ==========================\n" );
    Plateau p=constructeur_plateau(TAILLE_PLAT,patrick,robert);


    printf("======================TEST : Poser_un_pion(){ ==========================\n" );

    srand((long int)p);
    while(!Existe_Gangnant(p)){
    // for (size_t i = 0; i < 5; i++) {

        int x=rand()%Dimention_plateau(p);
        int y=rand()%Dimention_plateau(p);
        if(Case_Vide(p,Coord(x,y)))
            poser_un_pion(p,patrick,Coord(x,y));
        x=rand()%Dimention_plateau(p);
        y=rand()%Dimention_plateau(p);
        if(Case_Vide(p,Coord(x,y)))
            poser_un_pion(p,robert,Coord(x,y));
        afficher_plateau(p);
        bilan(p);
    }
    // }
    printf("=====================TEST Emplacement_libre() ===================================\n" );

    Coordonnee cd_libre = Emplacement_libre(p);
    printf("Emplacement_libre à %d,%d\n",cd_libre.x, cd_libre.y);



    freed_all(p);
    return 0;
}





void afficher_plateau(Plateau p){
    assert(p);
    printf("================================================\n" );
    for (int i = 0; i < Dimention_plateau(p); i++) {
        for (size_t h = 0; h < i; h++) {
            printf("  " );
        }
        for (int j = 0; j < Dimention_plateau(p); j++) {
            if(!Case_Vide(p,Coord(i,j))){
                if(Joueur_du_groupe( Groupe_de_la_Case( Case_de_la_Coordonnee(p,Coord(i,j)) ) )==Joueur1(p))
                    printf("\\ o " );
                else
                    printf("\\ 1 " );
            }
            else printf("\\ . " );
        }
        printf("\\\n" );
    }
    printf("================================================\n" );
}


//Fonction de visualisation et de test :

//Tests !
/*
                Mur 1
                Joueur 0
    \ 1 \ 1 \ o \ o \ o \ o \ o \ o \
      \ o \ 1 \ o \ o \ o \ o \ 1 \ 1 \
        \ 1 \ o \ o \ 1 \ 1 \ 1 \ 1 \ o \
          \ 1 \ o \ . \ 1 \ 1 \ o \ o \ o \     Mur2
Mur1        \ 1 \ . \ 1 \ o \ . \ o \ o \ o \   Joueur 1
Joueur 1      \ 1 \ 1 \ 1 \ o \ o \ . \ . \ o \
                \ o \ 1 \ 1 \ . \ o \ 1 \ 1 \ 1 \
                  \ 1 \ o \ o \ 1 \ o \ 1 \ . \ 1 \
                                Mur 2
                                joueur 0
*/


void bilan(Plateau p){
    ListeItr itr_grp,itr_case;


    printf("Joueur 0\n");
    itr_grp=constructeur_liste_iterateur(Liste_Groupe_du_Joueur(Joueur1(p)),FIFO);
    for(start_liste_iterateur(itr_grp);!fin_liste_iterateur(itr_grp);suivant_liste_iterateur(itr_grp)){

            Groupe g=(Groupe)liste_iterateur_courant(itr_grp);
            printf("Groupe: %p  ",g );
            if(Groupe_co_au_mur1(g))printf("Mur1 ");
            if(Groupe_co_au_mur2(g))printf("Mur2 ");
            printf(": ");
        itr_case=constructeur_liste_iterateur(Liste_Case_du_Groupe(g),FIFO);
        for(start_liste_iterateur(itr_case);!fin_liste_iterateur(itr_case);suivant_liste_iterateur(itr_case)){

            Case ca=(Case)liste_iterateur_courant(itr_case);
            Coordonnee co = Coordonne_de_la_Case(ca);
            printf("\t(%d,%d)",co.x,co.y );

        }
        printf("\n");
        freed_liste_iterateur(itr_case);
    }
    freed_liste_iterateur(itr_grp);
    printf("---------------\n" );

    printf("Joueur 1\n");
    itr_grp=constructeur_liste_iterateur(Liste_Groupe_du_Joueur(Joueur2(p)),FIFO);
    for(start_liste_iterateur(itr_grp);!fin_liste_iterateur(itr_grp);suivant_liste_iterateur(itr_grp)){

            Groupe g=(Groupe)liste_iterateur_courant(itr_grp);
            printf("Groupe: %p  ",g );
            if(Groupe_co_au_mur1(g))printf("Mur1 ");
            if(Groupe_co_au_mur2(g))printf("Mur2 ");
            printf(": ");
        itr_case=constructeur_liste_iterateur(Liste_Case_du_Groupe(g),FIFO);
        for(start_liste_iterateur(itr_case);!fin_liste_iterateur(itr_case);suivant_liste_iterateur(itr_case)){

            Case ca=(Case)liste_iterateur_courant(itr_case);
            Coordonnee co = Coordonne_de_la_Case(ca);
            printf("\t(%d,%d)",co.x,co.y );

        }
        printf("\n");
        freed_liste_iterateur(itr_case);
    }
    freed_liste_iterateur(itr_grp);
    printf("---------------\n" );

    if(Existe_Gangnant(p))printf("Joueur gagnant : %p\n",Existe_Gangnant(p) );




    printf("Historique joueur 0\n" );
    ListeItr itr_histo;
    itr_histo=constructeur_liste_iterateur(Historique_Joueur(Joueur1(p)),FIFO);
    for(start_liste_iterateur(itr_histo);!fin_liste_iterateur(itr_histo);suivant_liste_iterateur(itr_histo)){

        Case cas=(Case)liste_iterateur_courant(itr_histo);
        Coordonnee cd = Coordonne_de_la_Case(cas);
        printf("(%d,%d) ",cd.x,cd.y );

    }
    printf("\n");
    freed_liste_iterateur(itr_histo);
    printf("Historique joueur 1\n" );
    itr_histo=constructeur_liste_iterateur(Historique_Joueur(Joueur2(p)),FIFO);
    for(start_liste_iterateur(itr_histo);!fin_liste_iterateur(itr_histo);suivant_liste_iterateur(itr_histo)){

        Case cas=(Case)liste_iterateur_courant(itr_histo);
        Coordonnee cd = Coordonne_de_la_Case(cas);
        printf("(%d,%d) ",cd.x,cd.y );

    }
    printf("\n");
    freed_liste_iterateur(itr_histo);

}
