#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "libImages.h"
#include "libOutils.h"


typedef char NOM[100]; // nom des chemin+images born� � 100 caract�res

void main(void)
{
	FILE *F = NULL;
	NOM *liste = NULL; // liste des images
	NOM ligne;
	int nb = 0;

	char *nom = NULL;

	// mise en m�moire images pgm/ppm 

	system("dir /S /B *.p*m > listeDesImages.txt");

	F = fopen("listeDesImages.txt", "r");
	while (fscanf(F, "%s", ligne) > 0)
	{
		if (!liste)
		{
			liste = (NOM*)malloc(sizeof(NOM));
			strcpy(liste[nb], ligne);
			nb++;
		}
		else
		{
			liste = (NOM*)realloc(liste, sizeof(NOM)*(++nb));
			strcpy(liste[nb - 1], ligne);
		}
	}
	fclose(F);

	printf("Derniere entree : %s\n", liste[nb - 1]);

	system("pause");
}