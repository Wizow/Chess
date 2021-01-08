#ifndef MVMT_H
#define MVMT_H

typedef struct {
        char* piece;
        char* nom_case;
}Echiquier;
Echiquier plateau[8][8];

int reset_plateau(void);

int* recup(char *caseAVerif);	

int reine(int x, int y, int *deplacement); // stocke tous les mouvements de la reine placée sur une certaines case

int fou(int x, int y, int *deplacement); // stocke tous les mouvements du fou placé sur une certaines case

int tour(int x,int y,int *deplacement); // stocke tous les mouvements de la tour placée sur une certaines case

int pion( int y, int x, int *deplacement); // stocke tous les mouvements du pion placé sur une certaines case

int cavalier( int y, int x, int *deplacement); // stocke tous les mouvements du cavalier placé sur une certaines case

int roi( int x, int y, int *deplacement); // stocke tous les mouvements du roi placé sur une certaines case

void promotion ( bool testpromo, char *casearr );

int echec(void);

int mvt(char *casedep, char *casearr); //Fonction codant le déplacement de toutes les pièces

#endif
