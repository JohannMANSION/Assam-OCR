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

	// Initialisation des variables, première utilisation du programme par l'utilisateur immédiatement après éxécution
	CHOIX_UTILISATEUR choix = interractionUtilisateur();
	TABLEAU_SIGNATURES TAB = calculSignatures(choix);
	TABLEAU_SIGNATURES TABverdict = classification(TAB); //TABverdict pointe vers les mêmes adresses que TAB

	// Affichage des résultats
	if (TABverdict.nbSignatures > 1)
	{
		matriceConfusion(TABverdict);
	}
	else
		printf("...\n\nVous avez teste le caractere : %d qui est un %d et le verdict est : %d\n", TABverdict.tabSignatures[0].numero, (((TABverdict.tabSignatures[0].numero)%100)%10), TABverdict.tabSignatures[0].numeroDetecte);
	
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
				printf("...\n\nVous avez teste le caractere : %d qui est un %d et le verdict est : %d\n", TABverdict.tabSignatures[0].numero, (((TABverdict.tabSignatures[0].numero) % 100) % 10), TABverdict.tabSignatures[0].numeroDetecte);

			liberationTableauSignatures(&TAB);
		}
	}

	// permet de retracer les fuites mémoires (il en reste dailleurs quelques fuites mineures mais rien d'ennuyant pour ce programme en particulier)
	_CrtDumpMemoryLeaks();

	// Message fermeture du programme
	printf("\n***************************\n");
	printf("A bientot sur Assam-OCR !\n");
	printf("***************************\n\n");

	system("pause");
}