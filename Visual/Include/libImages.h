/* outils li�s aux images - format pgm/ppm */

#pragma once

#ifndef LIB_IMAGES_H
#define LIB_IMAGES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libOutils.h"

	/* structure IMAGE en ndg, acc�s � un pixel par .data[i] ou .pixel[i][j] */
	typedef struct image {
		int   Nblig;
		int   Nbcol;
		unsigned char*  data;
		unsigned char** pixel;
	} IMAGE;

	/* structure RGB pour image 3 plans */
	typedef struct rgb {
		unsigned char R;
		unsigned char G;
		unsigned char B;
	} RGB;

	/* structure IMAGE en ndg, acc�s � la composante R d'un pixel par .data[i].R ou .pixel[i][j].R */
	typedef struct imageRGB {
		int   Nblig;
		int   Nbcol;
		RGB*  data;
		RGB** pixel;
	} IMAGERGB;

	/* signatures bas�es histogramme */
	typedef struct signatures {
		int 	min;
		int 	max;
		double moyenne;
		double ecartType;
		int 	mediane;
	} SIGNATURES;


	IMAGE allocationImage(int Nblig, int Nbcol); /* r�servation en m�moire d'une image ndg */
	void initialisationAleatoireImage(IMAGE img, int ngMin, int ngMax); /* remplissage al�atoire des ndg d'une image ndg pr�alablement allou�e */

	void sauvegardeImage(IMAGE img, const char *type, const char *out); /* sauvegarde d'une image ndg type "P2" ou "P5" */
	void liberationImage(IMAGE *im); /* lib�ration m�moire image ndg */

	IMAGE lectureImage(const char *nom); /* mise en m�moire d'une image au format pgm */

	IMAGERGB allocationImageRGB(int Nblig, int Nbcol); /* r�servation en m�moire d'une image RGB  */
	IMAGERGB lectureImageRGB(const char *nom); /* mise en m�moire d'une image au format ppm */

	void sauvegardeImageRGB(IMAGERGB img, const char *type, const char *out); /* sauvegarde d'une image RGB type "P3" ou "P6" */	 
	void liberationImageRGB(IMAGERGB *im); /* lib�ration m�moire image RGB */

	IMAGE planImage(IMAGERGB img, int plan);
	IMAGE luminanceImage(IMAGERGB img, float r, float g, float b);
	IMAGE inverseImage(IMAGE img);
	IMAGE seuillageImage(IMAGE img, int sInf, int sSup);

	TABLEAU_INT histogrammeImage(IMAGE img, int choix);
	IMAGE expansionImage(IMAGE img, int outMin, int outMax);
	IMAGE egalisationImage(IMAGE img);
	SIGNATURES signaturesImage(IMAGE img);
	IMAGERGB colorisationImage(IMAGE img, char *table);

	IMAGE seuillageOtsu(IMAGE img);

	IMAGERGB bruitAleatoireImage(IMAGERGB img, int amplitude);
	double distanceHistogrammeImage(TABLEAU_INT h1, TABLEAU_INT h2);

	typedef char NOM[100]; // nom des chemin+images borne a 100 caracteres
	void listeImages(void);

	// ***************************************** //
	// Fonctions cod�es pour le projet C IPSI1 : //
	// ***************************************** //

	// Fonctions de morpho OK -----------------------------------------------------------------------------
	IMAGE imDilateV4(IMAGE img); // Dilatation morphologique V4 d'une image
	IMAGE imgReplicate(IMAGE img); // Renvoie l'image avec les pixels de bord dupliqu�s
	IMAGE imgTroncature(IMAGE img); // Renvoie l'image avec les pixels de bord enlev�s
	IMAGE strelV4(void); //renvoie un �l�ment structurant V4 (ndg = 0 quand pas dans voisinage et ndg = 255 quand dans voisinage)
	IMAGE imDilate(IMAGE img, IMAGE strel); // Dilatation morphologique d'une image (fonctionne pour tout �l�ment structurant)
	IMAGE imErode(IMAGE img, IMAGE strel); // Erosion morphologique d'une image (fonctionne pour tout �l�ment structurant)
	IMAGE imClose(IMAGE img, IMAGE strel); // Fermeture (Dilatation puis Erosion morphologique) d'une image
	IMAGE imBiggerWith0(IMAGE img); // Agrandi l'image de +1 pixel sur les bords avec des 0
	IMAGE imCloseMATLAB(IMAGE img, IMAGE strel); // Renvoie la m�me fermeture que matlab c�d r�alise la dilatation sur image + grande 
	IMAGE allocationImage0(int Nblig, int Nbcol); // Initialisation d'une image avec des 0
	IMAGE imSkelApprox(IMAGE img); // Copie de la pr�c�dente quand �tape 1 fonctionne pour ajout �tape 2
	int nbTransitions01forSkel(int nbVoisins1[]); // Renvoie le nombre de transition de 0 vers 1 dans le voisinage V8 par parcours horaire
	IMAGE imSpur1(IMAGE img); // Enl�ve un pixel � chaque extr�mit� (opti possible)
	IMAGE imSpurInf(IMAGE img); // Enleve toutes les extr�mit�s (opti possible car appel en boucle de imSpur1 donc allocations multiples)
	IMAGE imCopy(IMAGE img); // Copie l'image

	// Fonctions de morpho banquales --------------------------------------------------------------------------
	IMAGE imErodeWith0(IMAGE img, IMAGE strel); // On veux le m�me comportement que MATLAB FONCTION A CHECKER
	IMAGE imFill(IMAGE img); // Remplis l'int�rieur des objets ferm�s sur l'image (A SURVEILLER NE MARCHE QUE POUR 1 TROUS SUR L'IMAGE)
	
	// Fonctions de d�tection cercle --------------------------------------------------------------------------
		// Fonction DEBUG
	void detectionCercleFIX(IMAGE img, char *nomImage); // Sauvegarde chaque image boucle obtenue avec chaque �l�ment structurant (FONCTION DE DEBUG)
	void detectionCercleV2(IMAGE img, char *nomImage); // Sauvegarde uniquement la meilleure image boucle d�tect�e (FONCTION DE DEBUG)
	void detectionCercleForAll(); // D�roule detectionCercleV2saveSkel pour tous les caract�res (pour v�rifier sont bon fonctionnement) // DEROULE POUR LE MOMENT QUE LES NEUFS PREMIERS)
	void numDiskToString(int num, char *chaineTaille11); // Renvoie le nom de l'image � ouvrir associ�e au num�ro du disque (ex : num=1 renvoie "disk1.pgm")
	void detectionCercleV2saveSkel(IMAGE img, char* nomImage); // Sauvegarde la meilleure image boucle et le skelette et spur(FONCTION DE DEBUG)
		// Fonction finale utilisable
	void detectionCercle(IMAGE img, IMAGE *OUT, IMAGE *SKEL, IMAGE *SPUR); // Fonction utilisable pour le projet modifie directement les images OUT, SKEL, SPUR entr�es

	// Fonctions de signature ------------------------------------------------------------------------------------------
		// Fonctions OK
	int nbPix255haut(IMAGE img); // Renvoie le nombre de pixels � 255 en haut de l'image
	int nbPix255bas(IMAGE img); // Renvoie le nombre de pixels � 255 en bas de l'image
	double imCompacity(IMAGE OUT, IMAGE SPUR); // Renvoie la compacit� � partir de l'image OUT (boucle) et l'image SPUR par calcul simple (perimetre = nbPixSpur)
	void imCentreGrav(IMAGE img, double *centreXgrav, double *centreYgrav); // Modifie les valeur des centre grav en fonction de l'image d'entree 
	double distSTDcentreGrav(IMAGE img);				// Renvoie l'�cart type des distances entre chaque pixel blanc de l'image et le centre de gravit�
	int nbPixQuartBasGauche255(IMAGE img);	// Renvoie le nombre de pixels � 255 dans la r�gion quart bas gauche de l'image
	int nbPixDiagSup255(IMAGE img);		// Renvoie le nombre de pixels blancs au dessus de la diagonale de l'image (ne compte pas ceux de la diagonale)
	int nbPixDiagInf255(IMAGE img);		// Renvoie le nombre de pixels blancs au dessous de la diagonale de l'image (ne compte pas ceux de la diagonale)

		// Fonctions OK mais seulement des interm�diaires
	TABLEAU_DOUBLE imDistPixCentreGrav(IMAGE img);		// Renvoie le tableau des distances entre chaque pixel blanc de l'image et le centre de gravit�
	double moyenneTableauDouble(TABLEAU_DOUBLE tab);	// Renvoie la moyenne d'un tableau de double
	double ecartTypeTableauDouble(TABLEAU_DOUBLE tab);	// Renvoie l'�cart type d'un tableau de double

		// Fonctions NON OK
	TABLEAU_INT imChainCode(IMAGE img); // Renvoie la chain code de l'objet (faite pour re�evoir des image skelette)
	double imPerimeter(IMAGE img); // Renvoie le perimetre � partir de la chain Code (fait pour recevoir des images skelettes) 
								   // le perimetre n'est pas bon, provient surrement de l'image skel, on calculera la compacit� avec nbPix image SPUR pour le moment

	// Fonction calcul des signatures et enregistrement csv ------------------------------------------------------------------------------------------
	void signatureToCSV(char *repertoire); // EN DEV

	// D�finitions de structures
	typedef struct signaturesOCR {
		int nbPixBoucleHaut;
		int nbPixBoucleBas;
		double compacity;
		double distSTDskel;
		int nbPixSkelQuartBasGauche;
		double skelXcentreGrav;
		double skelYcentreGrav;
		double boucleXcentreGrav;
		double boucleYcentreGrav;
		double diffSkelBoucleXcentreGrav;
		double diffSkelBoucleYcentreGrav;
		int nbPixDiagInfSkel;
		int nbPixDiagSupSkel;
	} SIGNATURES_OCR;

	// FONCTIONS EN DEVELOPPEMENT
	IMAGE imConvexHull(IMAGE img);		// Renvoie l'enveloppe convexe de l'image
	
#endif LIB_IMAGES_H

