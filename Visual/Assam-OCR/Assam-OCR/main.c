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
	// Message de bienvenue et premier test image
	printf("Bienvenue sur le programme Assam-OCR \n");
	CHOIX_UTILISATEUR choix = interractionUtilisateur();
	//CHOIX_UTILISATEUR choix = { "test", 0, "200.pgm" };
	TABLEAU_SIGNATURES TAB = calculSignatures(choix);
	TABLEAU_SIGNATURES TABverdict = classification(TAB); //TABverdict pointe vers les mêmes adresses que TAB

	/*
	int nbOK = 0;
	for (int i = 0; i < TABverdict.nbSignatures; i++)
	{
		//printf("NUM : %d, VERDICT : %d \n", TABverdict.tabSignatures[i].numero, TABverdict.tabSignatures[i].numeroDetecte);
		if (((TABverdict.tabSignatures[i].numero % 100) % 10) == TABverdict.tabSignatures[i].numeroDetecte)
			nbOK++;
		if ((((TABverdict.tabSignatures[i].numero % 100) % 10) == 7) & (TABverdict.tabSignatures[i].numeroDetecte == 4))
			printf("NUM : %d, VERDICT %d, %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %d, %lf, %lf, %lf, %lf \n", TABverdict.tabSignatures[i].numero, TABverdict.tabSignatures[i].numeroDetecte,TABverdict.tabSignatures[i].nbPixSkelQuartBasGauche, TABverdict.tabSignatures[i].boucleXcentreGrav, TABverdict.tabSignatures[i].boucleYcentreGrav, TABverdict.tabSignatures[i].diffSkelBoucleYcentreGrav, TABverdict.tabSignatures[i].orientationSkel, TABverdict.tabSignatures[i].PHI4skel, TABverdict.tabSignatures[i].diffSkelBoucleXcentreGrav, TABverdict.tabSignatures[i].majorAxisSkel, TABverdict.tabSignatures[i].skelXcentreGrav, TABverdict.tabSignatures[i].nbPixDiagSupSkel, TABverdict.tabSignatures[i].minorAxisSkel, TABverdict.tabSignatures[i].PHI2skel, TABverdict.tabSignatures[i].distSTDskel, TABverdict.tabSignatures[i].skelYcentreGrav);
	}
	printf("NB OK : %d \n", nbOK);
	*/

	// Affichage des résultats
	if (TABverdict.nbSignatures > 1)
	{
		matriceConfusion(TABverdict);
	}
	else
		printf("\nVous avez teste le caractere : %d qui est un %d et le verdict est : %d\n", TABverdict.tabSignatures[0].numero, (((TABverdict.tabSignatures[0].numero)%100)%10), TABverdict.tabSignatures[0].numeroDetecte);
	
	liberationTableauSignatures(&TAB);
	
	// On fait tourner le programme jusqu'à que l'utilisateur veuille arrêter
	int CONTINUER = 1;
	while (CONTINUER == 1)
	{
		printf("Voulez-vous tester un autre/d'autres caracteres ? OUI : 1, NON : 0\n");
		scanf("%d", &CONTINUER);

		if (CONTINUER == 1)
		{
			choix = interractionUtilisateur();
			TAB = calculSignatures(choix);
			TABverdict = classification(TAB);

			if (TABverdict.nbSignatures > 1)
				matriceConfusion(TABverdict);
			else
				printf("Vous avez teste le caractere : %d qui est un %d et le verdict est : %d\n", TABverdict.tabSignatures[0].numero, (((TABverdict.tabSignatures[0].numero) % 100) % 10), TABverdict.tabSignatures[0].numeroDetecte);

			liberationTableauSignatures(&TAB);
		}
	}


	_CrtDumpMemoryLeaks();
	printf("A bientot sur Assam-OCR !\n");
	system("pause");
}