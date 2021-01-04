#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "Pion.h"
// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1400
#define HauteurFenetre 800


// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'une evenement survient
void gestionEvenement(EvenementGfx evenement);



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
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			rafraichisFenetre();
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

			
			// Affichage d'une image

			if (imagepb != NULL)
			{
				for(int i=0;i<8;i++)
				{
					ecrisImagem(200+i*hauteurFenetre()/8, hauteurFenetre()/8, imagepb->largeurImage, imagepb->largeurImage, imagepb->donneesRGB);
				}
			}
			
			if (imagepn != NULL)
			{
				for(int i=0;i<8;i++)
				{
					ecrisImagem(200+i*hauteurFenetre()/8, 6*hauteurFenetre()/8, imagepn->largeurImage, imagepn->largeurImage, imagepn->donneesRGB);
				}
			}		
				
			if (imagetn != NULL)
			{					
				ecrisImagem(200, 7*hauteurFenetre()/8, imagetn->largeurImage, imagetn->largeurImage, imagetn->donneesRGB);
				ecrisImagem(200+7*hauteurFenetre()/8, 7*hauteurFenetre()/8, imagetn->largeurImage, imagetn->largeurImage, imagetn->donneesRGB);
			}
			
			if (imagetb != NULL)
			{
				ecrisImagem(200, 0, imagetb->largeurImage, imagetb->largeurImage, imagetb->donneesRGB);
				ecrisImagem(200+7*hauteurFenetre()/8, 0, imagetb->largeurImage, imagetb->largeurImage, imagetb->donneesRGB);
			}
			
			if (imagecn != NULL)
			{					
				ecrisImagem(200+hauteurFenetre()/8, 7*hauteurFenetre()/8, imagecn->largeurImage, imagecn->largeurImage, imagecn->donneesRGB);
				ecrisImagem(200+6*hauteurFenetre()/8, 7*hauteurFenetre()/8, imagecn->largeurImage, imagecn->largeurImage, imagecn->donneesRGB);
			}
			
			if (imagecb != NULL)
			{
				ecrisImagem(200+hauteurFenetre()/8, 0, imagecb->largeurImage, imagecb->largeurImage, imagecb->donneesRGB);
				ecrisImagem(200+6*hauteurFenetre()/8, 0, imagecb->largeurImage, imagecb->largeurImage, imagecb->donneesRGB);
			}
			
			if (imagefn != NULL)
			{					
				ecrisImagem(200+2*hauteurFenetre()/8, 7*hauteurFenetre()/8, imagefn->largeurImage, imagefn->largeurImage, imagefn->donneesRGB);
				ecrisImagem(200+5*hauteurFenetre()/8, 7*hauteurFenetre()/8, imagefn->largeurImage, imagefn->largeurImage, imagefn->donneesRGB);
			}
			
			if (imagefb != NULL)
			{
				ecrisImagem(200+2*hauteurFenetre()/8, 0, imagefb->largeurImage, imagefb->largeurImage, imagefb->donneesRGB);
				ecrisImagem(200+5*hauteurFenetre()/8, 0, imagefb->largeurImage, imagefb->largeurImage, imagefb->donneesRGB);
			}	
			
			if (imagedn != NULL)
			{					
				ecrisImagem(200+4*hauteurFenetre()/8, 7*hauteurFenetre()/8, imagedn->largeurImage, imagedn->largeurImage, imagedn->donneesRGB);
			}
			
			if (imagedb != NULL)
			{
				ecrisImagem(200+3*hauteurFenetre()/8, 0, imagedb->largeurImage, imagedb->largeurImage, imagedb->donneesRGB);
			}	
			
			if (imagedn != NULL)
			{					
				ecrisImagem(200+3*hauteurFenetre()/8, 7*hauteurFenetre()/8, imagern->largeurImage, imagern->largeurImage, imagern->donneesRGB);
			}
			
			if (imagedb != NULL)
			{
				ecrisImagem(200+4*hauteurFenetre()/8, 0, imagerb->largeurImage, imagerb->largeurImage, imagerb->donneesRGB);
			}
						
			/*
			// Affichage Zone de texte
			couleurCourante(200,200,200);
			rectangle(195+hauteurFenetre() + ((largeurFenetre()-hauteurFenetre())/4), hauteurFenetre()*(0.75)-5, 5+largeurFenetre() - ((largeurFenetre()-hauteurFenetre())/4), (hauteurFenetre()*0.75)+35);
			couleurCourante(0,0,0);
			rectangle(200+hauteurFenetre() + ((largeurFenetre()-hauteurFenetre())/4), hauteurFenetre()*0.75, largeurFenetre() - ((largeurFenetre()-hauteurFenetre())/4), (hauteurFenetre()*0.75)+30);
			
			*/
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
					libereDonneesImageRGB(&imagecb); // On libere la structure image,
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
				
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
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

