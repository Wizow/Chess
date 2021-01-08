#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <time.h>  // Pour le timer
#include <string.h> // Pour utiliser strcmp()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "mvmt.h"
#include "savetest.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1415
#define HauteurFenetre 800


// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'une evenement survient
void gestionEvenement(EvenementGfx evenement);

int Move(void)
{
	char *casedep = (char*)malloc(4*sizeof(char));
	char *casearr = (char*)malloc(4*sizeof(char));
	printf("Donner le case de départ:");
    scanf("%s",casedep);
    printf("Où voulez-vous déplacer votre pièces?");
    scanf("%s",casearr);
	mvt(casedep, casearr);
	free(casearr);
	free(casedep);
	return 0;
}

int Fin(void)
{
	int Roi = 0;
	int x = 0; int y =0;

		for (x = 0; x < 8; x++)
		{
			for(y = 0; y < 8; y++)
			{		
				if(strcmp(plateau[x][y].piece,"rn") == 0 )

				{
					Roi++;
					goto Roiblanc;
				}
				
			}
		}
		Roiblanc:
		for (x = 0; x < 8; x++)
		{
			for(y = 0; y < 8; y++)
			{		
				if(strcmp(plateau[x][y].piece,"rb") == 0 )
				{
					Roi++;
				}
				
			}
		}

	return Roi;
}	

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);
	// Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
	// qui elle-meme utilise fonctionAffichage ci-dessous
	
	lanceBoucleEvenements();
	return 0;
}

// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'une evenement survient
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static DonneesImageRGB *imagepb = NULL;  // L'image a afficher au centre de l'ecran
	static DonneesImageRGB *imagepn = NULL;
	static DonneesImageRGB *imagetb = NULL;
	static DonneesImageRGB *imagetn = NULL;
	static DonneesImageRGB *imagecb = NULL;
	static DonneesImageRGB *imagecn = NULL;
	static DonneesImageRGB *imagefb = NULL;
	static DonneesImageRGB *imagefn = NULL;
	static DonneesImageRGB *imagedb = NULL;
	static DonneesImageRGB *imagedn = NULL;
	static DonneesImageRGB *imagerb = NULL;
	static DonneesImageRGB *imagern = NULL;
	static int ctr=0;
	
	
	
	switch (evenement)
	{
		case Initialisation:
			imagepb = lisBMPRGB("Pion blanc.bmp");
			imagepn = lisBMPRGB("Pion noir.bmp");
			imagetb = lisBMPRGB("Tour blanche.bmp");
			imagetn = lisBMPRGB("Tour noire.bmp");
			imagecb = lisBMPRGB("Cavalier blanc.bmp");
			imagecn = lisBMPRGB("Cavalier noir.bmp");
			imagefb = lisBMPRGB("Fou blanc.bmp");
			imagefn = lisBMPRGB("Fou noir.bmp");
			imagedb = lisBMPRGB("Reine blanche.bmp");
			imagedn = lisBMPRGB("Reine noire.bmp");
			imagerb = lisBMPRGB("Roi blanc.bmp");
			imagern = lisBMPRGB("Roi noir.bmp");
			reset_plateau();
			demandeTemporisation(200);
			break;
		
		case Temporisation:
			ctr++;
			if(ctr%2==0)
			{
				printf("Au tour des noirs\n");
			}
			else
			{
				printf("Au tour des blancs\n");
			}
			Move();
			rafraichisFenetre();
			sauvegarde();
			if(Fin()!=2)
			{
				termineBoucleEvenements();
				printf("Fin de la partie!\n");
			}
			break;
			
		case Affichage:
			effaceFenetre (255, 255, 255);
			for(float i=0;i<8;i+=2)
			{
				for(float j=0;j<7;j+=2)
				{
					couleurCourante(109,7,26);
					rectangle(200+(hauteurFenetre()/8)*j, (hauteurFenetre()/8)*i, 200+(hauteurFenetre()/8)*(j+1), (hauteurFenetre()/8)*(i+1));
				}
			}
			
			for(float i=1;i<9;i+=2)
			{
				for(float j=1;j<9;j+=2)
				{
					couleurCourante(109,7,26);
					rectangle(200+(hauteurFenetre()/8)*j, (hauteurFenetre()/8)*i, 200+(hauteurFenetre()/8)*(j+1), (hauteurFenetre()/8)*(i+1));
				}
			}	
			
			// Affichage indices cases
			couleurCourante(255,255,255);
			afficheChaine("a", 10, 200+(hauteurFenetre()/8)-5, 5);
			afficheChaine("c", 10, 200+3*(hauteurFenetre()/8)-10, 5);
			afficheChaine("e", 10, 200+5*(hauteurFenetre()/8)-10, 5);
			afficheChaine("g", 10, 200+7*(hauteurFenetre()/8)-10, 5);
			couleurCourante(109,7,26);			
			afficheChaine("b", 10, 200+2*(hauteurFenetre()/8)-10, 5);
			afficheChaine("d", 10, 200+4*(hauteurFenetre()/8)-10, 5);
			afficheChaine("f", 10, 200+6*(hauteurFenetre()/8)-10, 5);
			afficheChaine("h", 10, 200+8*(hauteurFenetre()/8)-10, 5);
			
			couleurCourante(0,0,0);
			afficheChaine("1", 10, 205, (hauteurFenetre()/8)-10);
			afficheChaine("3", 10, 205, 3*(hauteurFenetre()/8)-10);
			afficheChaine("5", 10, 205, 5*(hauteurFenetre()/8)-10);
			afficheChaine("7", 10, 205, 7*(hauteurFenetre()/8)-10);
			couleurCourante(0,0,0);			
			afficheChaine("2", 10, 205, 2*(hauteurFenetre()/8)-10);
			afficheChaine("4", 10, 205, 4*(hauteurFenetre()/8)-10);
			afficheChaine("6", 10, 205, 6*(hauteurFenetre()/8)-10);
			afficheChaine("8", 10, 205, 8*(hauteurFenetre()/8)-10);
			// Affichage Menus latéraux
			couleurCourante(150,150,150);
			rectangle(200+hauteurFenetre(), 0, largeurFenetre(), hauteurFenetre());
			rectangle(0,0,200,hauteurFenetre());
			
			// Affichage Zone de texte pour les Timer
			couleurCourante(200,200,200);
			rectangle(45,20,155,60);
			rectangle(45,hauteurFenetre()-75, 155,hauteurFenetre()-35);
			couleurCourante(0,0,0);
			rectangle(50,25,150,55);
			rectangle(50,hauteurFenetre()-70,150,hauteurFenetre()-40);
			
			// Affichage des deux "Timer" en noir
			couleurCourante(0,0,0);
			epaisseurDeTrait(3);
			afficheChaine("Timer 1",20,60,65);
			couleurCourante(0,0,0);
			epaisseurDeTrait(3);
			afficheChaine("Timer 2",20,55,hauteurFenetre()-30);
			
			// Affichage Bouton Save
			couleurCourante(125,125,125);
			rectangle(195+hauteurFenetre() + ((largeurFenetre()-hauteurFenetre())/4), hauteurFenetre()*(0.75)-5, 5+largeurFenetre() - ((largeurFenetre()-hauteurFenetre())/4), (hauteurFenetre()*0.75)+35);
			couleurCourante(175,175,175);
			rectangle(200+hauteurFenetre() + ((largeurFenetre()-hauteurFenetre())/4), hauteurFenetre()*0.75, largeurFenetre() - ((largeurFenetre()-hauteurFenetre())/4), (hauteurFenetre()*0.75)+30);
			couleurCourante(0,0,0);
			epaisseurDeTrait(3);
			afficheChaine("Save", 20, largeurFenetre()/2 + 100 + hauteurFenetre()/2 -0.5*tailleChaine("Save", 20),(hauteurFenetre()*0.75)+5);

			// Affichage d'une image
			
			for(int i=0; i<8; i++)
			{
				for(int j=0; j<8; j++)
				{
					switch(plateau[i][j].piece[0])
					{
						case('p'):
							if(plateau[i][j].piece[1]=='n')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagepn->largeurImage, imagepn->largeurImage, imagepn->donneesRGB);
								rafraichisFenetre();
								break;
							}
							
							if(plateau[i][j].piece[1]=='b')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagepb->largeurImage, imagepb->largeurImage, imagepb->donneesRGB);
								rafraichisFenetre();
								break;
							}
							
						case('t'):
							if(plateau[i][j].piece[1]=='n')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagetn->largeurImage, imagetn->largeurImage, imagetn->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
							if(plateau[i][j].piece[1]=='b')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagetb->largeurImage, imagetb->largeurImage, imagetb->donneesRGB);
								rafraichisFenetre();
								break;
							}
							
						case('f'):
							if(plateau[i][j].piece[1]=='n')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagefn->largeurImage, imagefn->largeurImage, imagefn->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
							if(plateau[i][j].piece[1]=='b')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagefb->largeurImage, imagefb->largeurImage, imagefb->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
						case('c'):
							if(plateau[i][j].piece[1]=='n')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagecn->largeurImage, imagecn->largeurImage, imagecn->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
							if(plateau[i][j].piece[1]=='b')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagecb->largeurImage, imagecb->largeurImage, imagecb->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
						case('d'):
							if(plateau[i][j].piece[1]=='n')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagedn->largeurImage, imagedn->largeurImage, imagedn->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
							if(plateau[i][j].piece[1]=='b')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagedb->largeurImage, imagedb->largeurImage, imagedb->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
						case('r'):
							if(plateau[i][j].piece[1]=='n')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagern->largeurImage, imagern->largeurImage, imagern->donneesRGB);
								rafraichisFenetre();
								break;
							}
								
							if(plateau[i][j].piece[1]=='b')
							{
								ecrisImagem(200+j*hauteurFenetre()/8, (7-i)*hauteurFenetre()/8, imagerb->largeurImage, imagerb->largeurImage, imagerb->donneesRGB);
								rafraichisFenetre();
								break;
							}
					}	
				}
			}
			rafraichisFenetre();		
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': // Pour sortir quelque peu proprement du programme
				case 'q':
					libereDonneesImageRGB(&imagepb); // On libere la structure image,
					libereDonneesImageRGB(&imagepn);
					libereDonneesImageRGB(&imagetb);
					libereDonneesImageRGB(&imagetn);
					libereDonneesImageRGB(&imagecb);
					libereDonneesImageRGB(&imagecn);
					libereDonneesImageRGB(&imagefb);
					libereDonneesImageRGB(&imagefn);
					libereDonneesImageRGB(&imagedb);
					libereDonneesImageRGB(&imagedn);
					libereDonneesImageRGB(&imagerb);
					libereDonneesImageRGB(&imagern);
						// c'est plus propre, meme si on va sortir du programme juste apres
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f': 
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;
				case 'P':
				case 'p':
					demandeTemporisation(200);
					break;
				case 'S':
				case 's':
					sauvegarde();
					break;
					
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				/*if((pleinEcran = false)&&()
				if(((200+hauteurFenetre() + ((largeurFenetre()-hauteurFenetre())/4))<=abscisseSouris) && (abscisseSouris<=(largeurFenetre() - ((largeurFenetre()-hauteurFenetre())/4))) &&((hauteurFenetre()*0.75)<=ordonneeSouris) && (ordonneeSouris<=((hauteurFenetre()*0.75)+3)));
				{
					sauvegarde();
					printf("Partie sauvegardée");
				}*/
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			break;
	}
	
}

