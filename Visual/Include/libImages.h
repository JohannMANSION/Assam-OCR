/* outils li�s aux images - format pgm/ppm */

#pragma once

#ifndef LIB_IMAGES_H
#define LIB_IMAGES_H

#include <stdlib.h>
#include <stdio.h>

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
#endif LIB_IMAGES_H

