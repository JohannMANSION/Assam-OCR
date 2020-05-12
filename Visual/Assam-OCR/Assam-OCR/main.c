#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "libImages.h"
#include "libOutils.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void main(void)
{
	//IMAGE test = lectureImage("..\\..\\Images\\test\\388.pgm");

	//listeImages();

	IMAGE img = { 0,0,NULL,NULL };
	IMAGE imgSeuillee = { 0,0,NULL,NULL };
	IMAGE imgSeuilleeInversee = { 0,0,NULL,NULL };
	IMAGE imgSeuilInvDil0 = { 0,0,NULL,NULL };

	char nomImage[8] = "001.pgm";
	img = lectureImage(nomImage);
	//sauvegardeImage(img, "P5", "..\\..\\Res\\img.pgm");

	imgSeuillee = seuillageOtsu(img);
	//sauvegardeImage(imgSeuillee, "P5", "..\\..\\Res\\imgSeuillee.pgm");

	imgSeuilleeInversee = inverseImage(imgSeuillee);
	sauvegardeImage(imgSeuilleeInversee, "P5", "..\\..\\Res\\imgSeuilleeInversee.pgm");

	/*
	TABLEAU_DOUBLE tab = imDistPixCentreGrav(imgSeuilleeInversee);
	double moyenne = moyenneTableauDouble(tab);
	double ecartType = ecartTypeTableauDouble(tab);
	
	for (int i = 0; i < tab.size; i++)
		printf("%lf\t", tab.data[i]);
	printf("MOY : %lf, STD : %lf \n", moyenne, ecartType);
	liberationTableauDouble(&tab);
	*/

	/*
	IMAGE testCONVEX = imConvexHull(imgSeuilleeInversee);
	sauvegardeImage(testCONVEX, "P5", "..\\..\\Res\\testCONVEX.pgm");
	liberationImage(&testCONVEX);
	*/
	//printf("TEST : %lf %lf %lf %lf \n", imPHI1(imgSeuilleeInversee), imPHI2(imgSeuilleeInversee), imPHI3(imgSeuilleeInversee), imPHI4(imgSeuilleeInversee));

	liberationImage(&img);
	liberationImage(&imgSeuillee);
	liberationImage(&imgSeuilleeInversee);
	liberationImage(&imgSeuilInvDil0);

	//signatureToCSV("train");
	CHOIX_UTILISATEUR choix = { "train", 1, "002.pgm" };
	TABLEAU_SIGNATURES TAB = calculSignatures(choix);


	_CrtDumpMemoryLeaks();

	system("pause");
}