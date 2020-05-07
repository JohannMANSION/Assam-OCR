/* outils liés aux images */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "libImages.h"

IMAGE allocationImage(int Nblig, int Nbcol)
{
	IMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (unsigned char*)malloc(Nblig*Nbcol*sizeof(unsigned char));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (unsigned char**)malloc(Nblig*sizeof(unsigned char*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i<Nblig; i++)
		mat.pixel[i] = &mat.data[i*Nbcol];

	return(mat);
}

void initialisationAleatoireImage(IMAGE img, int ngMin, int ngMax)
{
	int i, j;
	printf("Dans initialisation : img -> %p img.data -> %p img.pixel -> %p\n", &img, img.data, img.pixel);

	for (i = 0; i<img.Nblig; i++)
		for (j = 0; j<img.Nbcol; j++)
			img.pixel[i][j] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));

	/* solution avec un seul indice
	for (i=0;i<img.Nblig*img.Nbcol;i++)
		img.data[i] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
	*/
}

void liberationImage(IMAGE *img)
{
	if (img->data != NULL) {
		free(img->data);
		img->data = NULL;
	}
	if (img->pixel != NULL) {
		free(img->pixel);
		img->pixel = NULL;
	}
}

IMAGE lectureImage(const char *in)
{
	FILE *F = NULL;
	IMAGE img = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				img.Nbcol = img.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				img.Nblig = img.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

			/* taille connue, allocation dynamique possible */
			img = allocationImage(img.Nblig, img.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i<img.Nblig; i++)
					for (j = 0; j<img.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						img.pixel[i][j] = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					img.Nbcol = img.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					img.Nblig = img.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

				/* taille connue, allocation dynamique possible */
				img = allocationImage(img.Nblig, img.Nbcol);

				/* lecture d'un bloc */
				fread(img.data, sizeof(unsigned char), img.Nbcol*img.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return img;
}

void sauvegardeImage(IMAGE img, const char *type, const char *out)
{
	FILE *F = NULL;

	if (img.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i<img.Nblig; i++)
					for (j = 0; j<img.Nbcol; j++)
						fprintf(F, "%d ", img.pixel[i][j]);
			}
			fclose(F);
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P5\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
				fputs(tmp, F);
				/* sauvegarde par bloc */
				fwrite(img.data, sizeof(unsigned char), img.Nbcol*img.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

IMAGERGB allocationImageRGB(int Nblig, int Nbcol)
{
	IMAGERGB mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (RGB*)malloc(Nblig*Nbcol*sizeof(RGB));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (RGB**)malloc(Nblig*sizeof(RGB*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i<Nblig; i++)
		mat.pixel[i] = &(mat.data[i*Nbcol]);

	return(mat);
}

void liberationImageRGB(IMAGERGB *m)
{
	if (m->data != NULL) {
		free(m->data);
		m->data = NULL;
	}
	if (m->pixel != NULL) {
		free(m->pixel);
		m->pixel = NULL;
	}
}

IMAGERGB lectureImageRGB(const char *in)
{
	FILE *F = NULL;
	IMAGERGB img = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P3") == 0)  /* cas ASCII couleur */
		{
			char tmp[255] = "";
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				img.Nbcol = img.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				img.Nblig = img.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			printf("Lecture image RGB type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

			/* taille connue, allocation dynamique possible */
			img = allocationImageRGB(img.Nblig, img.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i<img.Nblig; i++)
					for (j = 0; j<img.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						img.pixel[i][j].R = (unsigned char)tmp;
						fscanf(F, "%d", &tmp);
						img.pixel[i][j].G = (unsigned char)tmp;
						fscanf(F, "%d", &tmp);
						img.pixel[i][j].B = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P6") == 0)  /* cas brut couleur */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					img.Nbcol = img.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					img.Nblig = img.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				printf("Lecture image RGB type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

				/* taille connue, allocation dynamique possible */
				img = allocationImageRGB(img.Nblig, img.Nbcol);

				/* lecture d'un bloc */
				fread(img.data, sizeof(RGB), img.Nbcol*img.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return img;
}

void sauvegardeImageRGB(IMAGERGB img, const char *type, const char *out)
{
	FILE *F = NULL;

	if (img.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P3") == 0)  /* cas ASCII couleur */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i<img.Nblig; i++)
					for (j = 0; j<img.Nbcol; j++) {
						fprintf(F, "%d ", img.pixel[i][j].R);
						fprintf(F, "%d ", img.pixel[i][j].G);
						fprintf(F, "%d ", img.pixel[i][j].B);
					}
				fclose(F);
			}
		}
		else
			if (strcmp(type, "P6") == 0)  /* cas brut couleur */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P6\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
				fputs(tmp, F);

				/* sauvegarde par bloc */
				fwrite(img.data, sizeof(RGB), img.Nbcol*img.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

IMAGE inverseImage(IMAGE img)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;

	lut = (int*)calloc(256, sizeof(int)); /* LUT pour optimiser */
	for (i = 0; i<256; i++)
		lut[i] = 255 - i;

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i<img.Nbcol*img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);

	return out;
}

IMAGE seuillageImage(IMAGE img, int sInf, int sSup)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;

	lut = (int*)calloc(256, sizeof(int));
	for (i = sInf; i <= sSup; i++)
		lut[i] = 255; /* 1 -> bleu */

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i<img.Nbcol*img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);

	return out;
}


IMAGE planImage(IMAGERGB img, int plan)
{
	IMAGE out = { 0,0,NULL,NULL };
	int i;

	out = allocationImage(img.Nblig, img.Nbcol);
	switch (plan)
	{
	case 0: /* plan rouge */
		for (i = 0; i<out.Nbcol*out.Nblig; i++)
			out.data[i] = img.data[i].R;
		break;
	case 1: /* plan vert */
		for (i = 0; i<out.Nbcol*out.Nblig; i++)
			out.data[i] = img.data[i].G;
		break;
	case 2: /* plan bleu */
		for (i = 0; i<out.Nbcol*out.Nblig; i++)
			out.data[i] = img.data[i].B;
		break;
	}
	return(out);
}

IMAGE luminanceImage(IMAGERGB img, float r, float g, float b)
{
	IMAGE out = { 0,0,NULL,NULL };
	int i;

	out = allocationImage(img.Nblig, img.Nbcol);

	for (i = 0; i<out.Nbcol*out.Nblig; i++)
		out.data[i] = (unsigned char)((float)img.data[i].R*r + (float)img.data[i].G*g + (float)img.data[i].B*b);
	return(out);
}

TABLEAU_INT histogrammeImage(IMAGE img, int choix)
{
	TABLEAU_INT h = { 0,NULL };

	if (img.data)
	{
		int i;

		h = allocationTableau(256);

		for (i = 0; i < img.Nbcol*img.Nblig; i++)
			h.data[(int)img.data[i]] += 1;

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE *F;

			F = fopen("..\\Res\\histo.csv", "w");
			int i;
			for (i = 0; i < h.size; i++)
				fprintf(F, "%d\n", h.data[i]);
			fclose(F);
		}
	}

	return h;
}

IMAGE expansionImage(IMAGE img, int outMin, int outMax)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;
	float a, b;
	int mini = 255, maxi = 0;

	for (i = 0; i<img.Nblig*img.Nbcol; i++)
	{
		mini = (img.data[i] < mini) ? img.data[i] : mini;
		maxi = (img.data[i] > maxi) ? img.data[i] : maxi;
	}

	a = (float)(outMax - outMin) / ((float)(maxi - mini));
	b = (float)outMin - a * mini;

	lut = (int*)calloc(256, sizeof(int));
	for (i = mini; i <= maxi; i++)
		lut[i] = (int)(a*i + b);

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i<img.Nbcol*img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);

	return out;
}

IMAGE egalisationImage(IMAGE img)
{
	IMAGE out = { 0,0,NULL,NULL };
	TABLEAU_INT h = histogrammeImage(img, 0);
	TABLEAU_INT hC = { 0,NULL };
	int* lut = NULL;
	int i;

	hC = allocationTableau(256);

	hC.data[0] = h.data[0];
	for (i = 1; i<256; i++)
		hC.data[i] = hC.data[i - 1] + h.data[i];
	liberationTableau(&h);

	lut = (int*)calloc(256, sizeof(int));
	for (i = 0; i<256; i++)
		lut[i] = (int)((255 / (float)(img.Nbcol*img.Nblig)) * hC.data[i]);
	liberationTableau(&hC);

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i<img.Nbcol*img.Nblig; i++)
		out.data[i] = lut[img.data[i]];
	free(lut);

	return(out);
}

SIGNATURES signaturesImage(IMAGE img)
{
	SIGNATURES sig;
	int i;
	double som = 0, som2 = 0;
	int somme, moitPop = (img.Nbcol*img.Nblig) / 2;
	TABLEAU_INT h = histogrammeImage(img, 0);

	for (i = 0; i<img.Nbcol*img.Nblig; i++) {
		som += (double)img.data[i];
		som2 += (double)img.data[i] * (double)img.data[i];
	}

	som /= (double)(img.Nblig*img.Nbcol);
	som2 = sqrt(som2 / (double)(img.Nblig*img.Nbcol) - som*som);

	sig.moyenne = som;
	sig.ecartType = som2;

	i = 0;
	while (h.data[i] == 0)
		i += 1;
	sig.min = i;

	i = 255;
	while (h.data[i] == 0)
		i -= 1;
	sig.max = i;

	i = 0;
	somme = h.data[i];
	while (somme < moitPop) {
		i += 1;
		if (i < 256)
			somme += h.data[i];
	}
	sig.mediane = i;

	liberationTableau(&h);

	return sig;
}

IMAGERGB colorisationImage(IMAGE img, char *table)
{
	FILE *lut;
	IMAGERGB out = { 0,0,NULL,NULL };
	char ligne[255];

	int i;
	RGB *LUT = NULL;

	lut = fopen(table, "r");

	LUT = (RGB*)calloc(256, sizeof(RGB));

	while (fgets(ligne, 255, lut) != NULL)
	{
		int a, b, c, d;

		sscanf(ligne, "%d %d %d %d", &a, &b, &c, &d);
		LUT[a].R = b;
		LUT[a].G = c;
		LUT[a].B = d;
	}

	fclose(lut);

	out = allocationImageRGB(img.Nblig, img.Nbcol);

	for (i = 0; i < img.Nblig*img.Nbcol; i++)
	{
		out.data[i].R = LUT[img.data[i]].R;
		out.data[i].G = LUT[img.data[i]].G;
		out.data[i].B = LUT[img.data[i]].B;
	}
	free(LUT);

	return out;
}

IMAGE seuillageOtsu(IMAGE img)
{
	IMAGE out = { 0, 0, NULL, NULL };
	TABLEAU_INT h = histogrammeImage(img, 0);
	TABLEAU_INT hC = { 0,NULL };

	double *tab = NULL;
	int i, seuil;
	double M1, M2;
	double w1;
	int* lut = NULL;
	int min, max;

	/* recherche min et max */
	i = 0;
	while (h.data[i] == 0)
		i++;
	min = i;
	i = 255;
	while (h.data[i] == 0)
		i--;
	max = i;

	hC = allocationTableau(256);

	hC.data[0] = h.data[0];
	for (i = 1; i < 256; i++)
		hC.data[i] = hC.data[i - 1] + h.data[i];

	tab = (double*)calloc(256, sizeof(double));

	/* parcours entre min et max pour éviter divisions par 0 */
	/* initialisation */
	M1 = min;
	seuil = min;
	w1 = (double)hC.data[min] / (double)(img.Nbcol*img.Nblig);
	M2 = 0;
	for (int i = min + 1; i <= max; i++)
		M2 += (double)h.data[i] * i;
	M2 /= (double)(hC.data[max] - h.data[min]);
	tab[min] = w1*(1 - w1)*(M1 - M2)*(M1 - M2);

	// parcours
	for (int i = min + 1; i < max; i++) {
		M1 = ((double)hC.data[i - 1] * M1 + (double)h.data[i] * i) / hC.data[i];
		M2 = ((double)(hC.data[255] - hC.data[i - 1])*M2 - (double)(h.data[i] * i)) / (double)(hC.data[255] - hC.data[i]);
		w1 = (double)hC.data[i] / (double)(img.Nbcol*img.Nblig);
		tab[i] = w1*(1 - w1)*(M1 - M2)*(M1 - M2);
		if (tab[i] > tab[seuil])
			seuil = i;
	}

	liberationTableau(&h);
	liberationTableau(&hC);
	free(tab);

	lut = (int*)calloc(256, sizeof(int));
	for (i = seuil; i <= max; i++)
		lut[i] = 255; /* 1 -> bleu */

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i<img.Nbcol*img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);
	return out;
}

double distanceHistogrammeImage(TABLEAU_INT h1, TABLEAU_INT h2)
{
	double dist = 0;
	int i;

	/* histos supposés de même taille */
	for (i = 0; i < h1.size; i++) {
		double ecart = (double)h1.data[i] - (double)h2.data[i];
		dist += ecart*ecart;
	}
	/* normalisation */
	dist = sqrt(dist/(double)h1.size);

	return(dist);
}

IMAGERGB bruitAleatoireImage(IMAGERGB img, int amplitude)
{
	IMAGERGB out = { 0,0,NULL,NULL };

	out = allocationImageRGB(img.Nblig, img.Nbcol);

	for (int i = 0; i < img.Nblig*img.Nbcol; i++)
	{
		int bruit = (-amplitude + rand() % (amplitude + 1 + amplitude));

		if (bruit > 0)
		{
			out.data[i].R = (unsigned char)min((int)(img.data[i].R+bruit),255);
			out.data[i].G = (unsigned char)min((int)(img.data[i].G+bruit),255);
			out.data[i].B = (unsigned char)min((int)(img.data[i].B+bruit),255);
		}
		else
		{
			out.data[i].R = (unsigned char)max(0,(int)(img.data[i].R+bruit));
			out.data[i].G = (unsigned char)max(0,(int)(img.data[i].G+bruit));
			out.data[i].B = (unsigned char)max(0,(int)(img.data[i].B+bruit));
		}
	}

	return out;
}

void listeImages(void)
{
	FILE *F = NULL;
	NOM *liste = NULL; // liste des images
	NOM ligne;
	int nb = 0;

	char *nom = NULL;

	// mise en memoire images pgm/ppm 

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



/////////////////////////////////////////
//	FONCTIONS CODEES POUR PROJET IPSI1 //
/////////////////////////////////////////

IMAGE imDilateV4(IMAGE img)
{
	// Définition de l'élément structurant V4
	IMAGE strel = allocationImage(3, 3);
	strel.pixel[0][0] = 0;
	strel.pixel[0][1] = 255;
	strel.pixel[0][2] = 0;
	strel.pixel[1][0] = 255;
	strel.pixel[1][1] = 255;
	strel.pixel[1][2] = 255;
	strel.pixel[2][0] = 0;
	strel.pixel[2][1] = 255;
	strel.pixel[2][2] = 0;
	int nbligStrelX = 3, nbligStrelY = 3;

	
	unsigned char valApropager = NULL;
	int coordRelativeImageX = 0, coordRelativeImageY = 0;
	int centreStrelX = (nbligStrelX/2), centreStrelY = (nbligStrelY/2);
	int tailleTableau255strel = 0;

	// Parcours de l'élément structurant pour récupérer le nombre de pixels appartenant au voisinage
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				tailleTableau255strel += 2;
				
			}
		}
	}

	TABLEAU_INT coordRelXY = allocationTableau(tailleTableau255strel);
	int compteur = 0;

	// Deuxième parcours de l'élément structurant pour enregistrer les coordonées relatives des pixels du voisinage à 
	// appliquer directement à l'image pour rechercher la valeur à propager
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				coordRelativeImageX = n - centreStrelX;
				coordRelativeImageY = m - centreStrelY;
				coordRelXY.data[compteur] = coordRelativeImageX;
				coordRelXY.data[compteur + 1] = coordRelativeImageY;
				compteur += 2;
			}
		}
	}

	
	IMAGE imgReplicated = imgReplicate(img);
	IMAGE dilated = allocationImage(img.Nblig, img.Nbcol);

	// Retient la plus grande valeur présente dans le voisinage et l'applique à l'image de sortie
	for (int i = 1; i < imgReplicated.Nblig - 1; i++)
	{
		for (int j = 1; j < imgReplicated.Nbcol - 1; j++)
		{
			valApropager = 0;
			for (int k = 0; k < coordRelXY.size; k+= 2)
			{
				if (imgReplicated.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]] > valApropager)
				{
					valApropager = imgReplicated.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]];
				}
			}
			dilated.pixel[i - 1][j - 1] = valApropager;
		}
	}

	liberationImage(&imgReplicated);
	liberationImage(&strel);
	liberationTableau(&coordRelXY);
	
	return dilated;

}

IMAGE imgReplicate(IMAGE img)
{
	IMAGE imgReplicated = allocationImage(img.Nblig + 2, img.Nbcol + 2); // Création de l'image avec bords dupliqués

	// Duplication des pixels des quatres coins
	imgReplicated.pixel[0][0] = img.pixel[0][0];
	imgReplicated.pixel[0][imgReplicated.Nbcol - 1] = img.pixel[0][img.Nbcol - 1];
	imgReplicated.pixel[imgReplicated.Nblig - 1][0] = img.pixel[img.Nblig - 1][0];
	imgReplicated.pixel[imgReplicated.Nblig - 1][imgReplicated.Nbcol - 1] = img.pixel[img.Nblig - 1][img.Nbcol - 1];

	// Duplication des pixels des bords
	for (int i = 0; i < img.Nblig; i++)
	{
		imgReplicated.pixel[i + 1][0] = img.pixel[i][0];
		imgReplicated.pixel[i + 1][imgReplicated.Nbcol - 1] = img.pixel[i][img.Nbcol - 1];
		imgReplicated.pixel[0][i + 1] = img.pixel[0][i];
		imgReplicated.pixel[imgReplicated.Nblig - 1][i + 1] = img.pixel[img.Nblig - 1][i];
	}

	// Insertion de l'image originale dans l'image agrandie
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			imgReplicated.pixel[i + 1][j + 1] = img.pixel[i][j];
		}
	}


	return imgReplicated;
}

IMAGE imgTroncature(IMAGE img)
{
	IMAGE imgTronquee = allocationImage(img.Nblig - 2, img.Nbcol - 2);
	for (int i = 0; i < imgTronquee.Nblig; i++)
	{
		for (int j = 0; j < imgTronquee.Nbcol; j++)
		{
			imgTronquee.pixel[i][j] = img.pixel[i + 1][j + 1];
		}
	}

	return imgTronquee;
}

IMAGE strelV4(void)
{
	IMAGE strel = allocationImage(3, 3);
	strel.pixel[0][0] = 0;
	strel.pixel[0][1] = 255;
	strel.pixel[0][2] = 0;
	strel.pixel[1][0] = 255;
	strel.pixel[1][1] = 255;
	strel.pixel[1][2] = 255;
	strel.pixel[2][0] = 0;
	strel.pixel[2][1] = 255;
	strel.pixel[2][2] = 0;

	strel.Nblig = 3;
	strel.Nbcol = 3;

	return strel;
}

IMAGE imDilate(IMAGE img, IMAGE strel)
{
	
	int nbligStrelX = strel.Nblig;
	int nbligStrelY = strel.Nbcol;


	unsigned char valApropager = NULL;
	int coordRelativeImageX = 0, coordRelativeImageY = 0;
	int centreStrelX = (nbligStrelX / 2), centreStrelY = (nbligStrelY / 2);
	int tailleTableau255strel = 0;

	// Parcours de l'élément structurant pour récupérer le nombre de pixels appartenant au voisinage
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				tailleTableau255strel += 2;

			}
		}
	}

	TABLEAU_INT coordRelXY = allocationTableau(tailleTableau255strel);
	int compteur = 0;

	// Deuxième parcours de l'élément structurant pour enregistrer les coordonées relatives des pixels du voisinage à 
	// appliquer directement à l'image pour rechercher la valeur à propager
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				coordRelativeImageX = n - centreStrelX;
				coordRelativeImageY = m - centreStrelY;
				coordRelXY.data[compteur] = coordRelativeImageX;
				coordRelXY.data[compteur + 1] = coordRelativeImageY;
				compteur += 2;
			}
		}
	}

	// Agrandissement de l'image autant de fois que necessaire (dépend de la taille de l'élement structurant)
	IMAGE imgReplicated = imgReplicate(img);
	IMAGE imgReplicatedTempo = { 0, 0, NULL, NULL };
	int nbAgrandissementSupp = NULL;
	if ((strel.Nblig / 2) > 1)
	{
		nbAgrandissementSupp = (strel.Nblig / 2) - 1;

		imgReplicatedTempo = imCopy(imgReplicated);
		liberationImage(&imgReplicated);
		imgReplicated = imgReplicate(imgReplicatedTempo);

		for (int i = 1; i < nbAgrandissementSupp; i++)
		{
			liberationImage(&imgReplicatedTempo);
			imgReplicatedTempo = imCopy(imgReplicated);
			liberationImage(&imgReplicated);
			imgReplicated = imgReplicate(imgReplicatedTempo);
		}
		liberationImage(&imgReplicatedTempo);
	}
	int nbAgrandissement = nbAgrandissementSupp + 1;

	IMAGE dilated = allocationImage(img.Nblig, img.Nbcol);

	// Retient la plus grande valeur présente dans le voisinage et l'applique à l'image de sortie
	for (int i = nbAgrandissement; i < imgReplicated.Nblig - nbAgrandissement; i++)
	{
		for (int j = nbAgrandissement; j < imgReplicated.Nbcol - nbAgrandissement; j++)
		{
			valApropager = 0;
			for (int k = 0; k < coordRelXY.size; k += 2)
			{
				if (imgReplicated.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]] > valApropager)
				{
					valApropager = imgReplicated.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]];
				}
			}
			dilated.pixel[i - nbAgrandissement][j - nbAgrandissement] = valApropager;
		}
	}

	liberationImage(&imgReplicated);
	liberationTableau(&coordRelXY);

	return dilated;
}

IMAGE imErode(IMAGE img, IMAGE strel)
{
	int nbligStrelX = strel.Nblig;
	int nbligStrelY = strel.Nbcol;


	unsigned char valApropager = NULL;
	int coordRelativeImageX = 0, coordRelativeImageY = 0;
	int centreStrelX = (nbligStrelX / 2), centreStrelY = (nbligStrelY / 2);
	int tailleTableau255strel = 0;

	// Parcours de l'élément structurant pour récupérer le nombre de pixels appartenant au voisinage
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				tailleTableau255strel += 2;

			}
		}
	}

	TABLEAU_INT coordRelXY = allocationTableau(tailleTableau255strel);
	int compteur = 0;

	// Deuxième parcours de l'élément structurant pour enregistrer les coordonées relatives des pixels du voisinage à 
	// appliquer directement à l'image pour rechercher la valeur à propager
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				coordRelativeImageX = n - centreStrelX;
				coordRelativeImageY = m - centreStrelY;
				coordRelXY.data[compteur] = coordRelativeImageX;
				coordRelXY.data[compteur + 1] = coordRelativeImageY;
				compteur += 2;
			}
		}
	}

	// Agrandissement de l'image autant de fois que necessaire (dépend de la taille de l'élement structurant)
	IMAGE imgReplicated = imgReplicate(img);
	IMAGE imgReplicatedTempo = { 0, 0, NULL, NULL };
	int nbAgrandissementSupp = NULL;
	if ((strel.Nblig / 2) > 1)
	{
		nbAgrandissementSupp = (strel.Nblig / 2) - 1;

		imgReplicatedTempo = imCopy(imgReplicated);
		liberationImage(&imgReplicated);
		imgReplicated = imgReplicate(imgReplicatedTempo);

		for (int i = 1; i < nbAgrandissementSupp; i++)
		{
			liberationImage(&imgReplicatedTempo);
			imgReplicatedTempo = imCopy(imgReplicated);
			liberationImage(&imgReplicated);
			imgReplicated = imgReplicate(imgReplicatedTempo);
		}
		liberationImage(&imgReplicatedTempo);
	}
	int nbAgrandissement = nbAgrandissementSupp + 1;

	IMAGE dilated = allocationImage(img.Nblig, img.Nbcol);

	// Retient la plus petite valeur présente dans le voisinage et l'applique à l'image de sortie
	for (int i = nbAgrandissement; i < imgReplicated.Nblig - nbAgrandissement; i++)
	{
		for (int j = nbAgrandissement; j < imgReplicated.Nbcol - nbAgrandissement; j++)
		{
			valApropager = 255;
			for (int k = 0; k < coordRelXY.size; k += 2)
			{
				if (imgReplicated.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]] < valApropager)
				{
					valApropager = imgReplicated.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]];
				}
			}
			dilated.pixel[i - nbAgrandissement][j - nbAgrandissement] = valApropager;
		}
	}

	liberationImage(&imgReplicated);
	liberationTableau(&coordRelXY);

	return dilated;
}

IMAGE imClose(IMAGE img, IMAGE strel)
{
	IMAGE dilated = imDilate(img, strel);
	IMAGE closed = imErode(dilated, strel);
	liberationImage(&dilated);
	return closed;
}

IMAGE imErodeWith0(IMAGE img, IMAGE strel)
{
	int nbligStrelX = strel.Nblig;
	int nbligStrelY = strel.Nbcol;


	unsigned char valApropager = NULL;
	int coordRelativeImageX = 0, coordRelativeImageY = 0;
	int centreStrelX = (nbligStrelX / 2), centreStrelY = (nbligStrelY / 2);
	int tailleTableau255strel = 0;

	// Parcours de l'élément structurant pour récupérer le nombre de pixels appartenant au voisinage
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				tailleTableau255strel += 2;

			}
		}
	}

	TABLEAU_INT coordRelXY = allocationTableau(tailleTableau255strel);
	int compteur = 0;

	// Deuxième parcours de l'élément structurant pour enregistrer les coordonées relatives des pixels du voisinage à 
	// appliquer directement à l'image pour rechercher la valeur à propager
	for (int n = 0; n < strel.Nblig; n++)
	{
		for (int m = 0; m < strel.Nbcol; m++)
		{
			if (strel.pixel[n][m] == 255)
			{
				coordRelativeImageX = n - centreStrelX;
				coordRelativeImageY = m - centreStrelY;
				coordRelXY.data[compteur] = coordRelativeImageX;
				coordRelXY.data[compteur + 1] = coordRelativeImageY;
				compteur += 2;
			}
		}
	}

	// Agrandissement de l'image autant de fois que necessaire (dépend de la taille de l'élement structurant)
	IMAGE imBigger0 = imBiggerWith0(img);

	int nbAgrandissementSupp = NULL;
	if ((strel.Nblig / 2) > 1)
	{
		nbAgrandissementSupp = (strel.Nblig / 2) - 1;
		for (int i = 0; i < nbAgrandissementSupp; i++)
		{
			imBigger0 = imgReplicate(imBigger0);
		}
	}
	int nbAgrandissement = nbAgrandissementSupp + 1;

	IMAGE dilated = allocationImage(img.Nblig, img.Nbcol);

	// Retient la plus petite valeur présente dans le voisinage et l'applique à l'image de sortie
	for (int i = nbAgrandissement; i < imBigger0.Nblig - nbAgrandissement; i++)
	{
		for (int j = nbAgrandissement; j < imBigger0.Nbcol - nbAgrandissement; j++)
		{
			valApropager = 255;
			for (int k = 0; k < coordRelXY.size; k += 2)
			{
				if (imBigger0.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]] < valApropager)
				{
					valApropager = imBigger0.pixel[i + coordRelXY.data[k]][j + coordRelXY.data[k + 1]];
				}
			}
			dilated.pixel[i - nbAgrandissement][j - nbAgrandissement] = valApropager;
		}
	}

	liberationImage(&imBigger0);
	liberationTableau(&coordRelXY);

	return dilated;
}

IMAGE imBiggerWith0(IMAGE img)
{
	IMAGE bigger = allocationImage(img.Nblig + 2, img.Nbcol + 2);
	for (int i = 0; i < bigger.Nbcol; i++)
	{
		bigger.pixel[0][i] = 0;
		bigger.pixel[bigger.Nblig - 1][i] = 0;
	}
	for (int i = 0; i < bigger.Nblig; i++)
	{
		bigger.pixel[i][0] = 0;
		bigger.pixel[i][bigger.Nbcol - 1] = 0;
	}
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			bigger.pixel[i + 1][j + 1] = img.pixel[i][j];
		}
	}
	return bigger;
}

IMAGE imCloseMATLAB(IMAGE img, IMAGE strel)
{
	int nbAggrandissement = strel.Nblig / 2;
	IMAGE image = { 0, 0, NULL, NULL };
	IMAGE image2 = { 0, 0, NULL, NULL };
	image = imBiggerWith0(img);
	if (nbAggrandissement > 1)
	{
		for (int i = 1; i < nbAggrandissement; i++)
		{
			if (image.Nbcol != 0)
				liberationImage(&image2);
			image2 = imCopy(image);
			liberationImage(&image);
			image = imBiggerWith0(image2);
		}
		liberationImage(&image2);
	}

	IMAGE dilated = imDilate(image, strel);
	IMAGE closed = imErode(dilated, strel);
	
	IMAGE OUT = allocationImage(image.Nblig - 2*nbAggrandissement, image.Nbcol - 2*nbAggrandissement);
	//printf("OUT nblig : %d, nbcol : %d \n", OUT.Nblig, OUT.Nbcol);
	//printf("closed nblig : %d, nbcol : %d \n", closed.Nblig, closed.Nbcol);
	for (int i = 0; i < OUT.Nblig; i++)
	{
		for (int j = 0; j < OUT.Nbcol; j++)
		{
			OUT.pixel[i][j] = closed.pixel[i + nbAggrandissement][j + nbAggrandissement];
		}
	}

	liberationImage(&dilated);
	liberationImage(&closed);
	liberationImage(&image);
	return OUT;
}

IMAGE allocationImage0(int Nblig, int Nbcol)
{
	IMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (unsigned char*)calloc(Nblig*Nbcol, sizeof(unsigned char));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (unsigned char**)calloc(Nblig, sizeof(unsigned char*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i<Nblig; i++)
		mat.pixel[i] = &mat.data[i*Nbcol];

	return(mat);
}


int nbTransitions01forSkel(int voisinage01[])
{
	int nbTransitions = 0;
	for (int i = 0; i < 7; i++)
	{
		if ((voisinage01[i] == 0) & (voisinage01[i + 1] == 1))
			nbTransitions++;
	}
	if ((voisinage01[7] == 0) & (voisinage01[0] == 1))
		nbTransitions++;

	return nbTransitions;
}

IMAGE imSkelApprox(IMAGE img) // Opti possible en testant d'abord si le pixel est un pixel de bord avant de faire des opérations...
{
	// Utilisations d'images aggrandies pour pallier aux effets de bords
	IMAGE imgAggrandie = imBiggerWith0(img);
	IMAGE imgAggrandie2 = allocationImage0(img.Nblig + 2, img.Nbcol + 2);

	// Initialisation des variables utilisées par la suite
	int voisinage01[8] = { NULL };
	int nbVoisins1 = 0;
	int test;
	int nbPixInitial = 0;
	TABLEAU_INT histo = histogrammeImage(imgAggrandie, 0);
	int nbPixFinal = histo.data[255];
	liberationTableau(&histo);

	// On enleve des pixels de bords tant que l'image de sortie est différente de l'image entrée
	while (nbPixInitial != nbPixFinal)
	{
		nbPixInitial = nbPixFinal;
		for (int i = 1; i < img.Nblig + 1; i++)
		{
			for (int j = 1; j < img.Nbcol + 1; j++)
			{
				// Construction du vecteur voisinage (LUT pour opti utile ?)
				if (imgAggrandie.pixel[i - 1][j] == 0)
					voisinage01[0] = 0;
				else
					voisinage01[0] = 1;

				if (imgAggrandie.pixel[i - 1][j + 1] == 0)
					voisinage01[1] = 0;
				else
					voisinage01[1] = 1;

				if (imgAggrandie.pixel[i][j + 1] == 0)
					voisinage01[2] = 0;
				else
					voisinage01[2] = 1;

				if (imgAggrandie.pixel[i + 1][j + 1] == 0)
					voisinage01[3] = 0;
				else
					voisinage01[3] = 1;

				if (imgAggrandie.pixel[i + 1][j] == 0)
					voisinage01[4] = 0;
				else
					voisinage01[4] = 1;

				if (imgAggrandie.pixel[i + 1][j - 1] == 0)
					voisinage01[5] = 0;
				else
					voisinage01[5] = 1;

				if (imgAggrandie.pixel[i][j - 1] == 0)
					voisinage01[6] = 0;
				else
					voisinage01[6] = 1;

				if (imgAggrandie.pixel[i - 1][j - 1] == 0)
					voisinage01[7] = 0;
				else
					voisinage01[7] = 1;

				// Calcul du nombre de voisins V8 = 1
				nbVoisins1 = 0;
				for (int n = 0; n < 8; n++)
					nbVoisins1 += voisinage01[n];

				// Vérification des conditions de suppression et création de l'image de sortie en conséquence
				if ((nbVoisins1 >= 2) & (nbVoisins1 <= 6))
				{
					if ((nbTransitions01forSkel(voisinage01) == 1) & (voisinage01[0] * voisinage01[2] * voisinage01[4] == 0) & (voisinage01[2] * voisinage01[4] * voisinage01[6] == 0))
						imgAggrandie2.pixel[i][j] = 0;
					else
						imgAggrandie2.pixel[i][j] = imgAggrandie.pixel[i][j];
				}
				else
					imgAggrandie2.pixel[i][j] = imgAggrandie.pixel[i][j];
			}
		}

		for (int i = 1; i < img.Nblig + 1; i++)
		{
			for (int j = 1; j < img.Nbcol + 1; j++)
			{
				// Construction du vecteur voisinage (LUT pour opti utile ?)
				if (imgAggrandie2.pixel[i - 1][j] == 0)
					voisinage01[0] = 0;
				else
					voisinage01[0] = 1;

				if (imgAggrandie2.pixel[i - 1][j + 1] == 0)
					voisinage01[1] = 0;
				else
					voisinage01[1] = 1;

				if (imgAggrandie2.pixel[i][j + 1] == 0)
					voisinage01[2] = 0;
				else
					voisinage01[2] = 1;

				if (imgAggrandie2.pixel[i + 1][j + 1] == 0)
					voisinage01[3] = 0;
				else
					voisinage01[3] = 1;

				if (imgAggrandie2.pixel[i + 1][j] == 0)
					voisinage01[4] = 0;
				else
					voisinage01[4] = 1;

				if (imgAggrandie2.pixel[i + 1][j - 1] == 0)
					voisinage01[5] = 0;
				else
					voisinage01[5] = 1;

				if (imgAggrandie2.pixel[i][j - 1] == 0)
					voisinage01[6] = 0;
				else
					voisinage01[6] = 1;

				if (imgAggrandie2.pixel[i - 1][j - 1] == 0)
					voisinage01[7] = 0;
				else
					voisinage01[7] = 1;

				// Calcul du nombre de voisins V8 = 1
				nbVoisins1 = 0;
				for (int n = 0; n < 8; n++)
					nbVoisins1 += voisinage01[n];

				// Vérification des conditions de suppression et création de l'image de sortie en conséquence
				if ((nbVoisins1 >= 2) & (nbVoisins1 <= 6))
				{
					if ((nbTransitions01forSkel(voisinage01) == 1) & (voisinage01[0] * voisinage01[2] * voisinage01[6] == 0) & (voisinage01[0] * voisinage01[4] * voisinage01[6] == 0))
						imgAggrandie.pixel[i][j] = 0;
					else
						imgAggrandie.pixel[i][j] = imgAggrandie2.pixel[i][j];
				}
				else
					imgAggrandie.pixel[i][j] = imgAggrandie2.pixel[i][j];

			}
		}
		histo = histogrammeImage(imgAggrandie, 0);
		nbPixFinal = histo.data[255];
		liberationTableau(&histo);
	}

	liberationImage(&imgAggrandie2);
	IMAGE troncature = imgTroncature(imgAggrandie);
	liberationImage(&imgAggrandie);
	return troncature;
}

IMAGE imSpur1(IMAGE img)
{
	IMAGE spurAg = imBiggerWith0(img);
	IMAGE spur = allocationImage(img.Nblig, img.Nbcol);
	int passage = 0;
	int nbPixInitial = 0;
	
	for (int i = 1; i < img.Nblig + 1; i++)
	{
		for (int j = 1; j < img.Nbcol + 1; j++)
		{
			passage = 0;
			// Si le pixel objet est sur un bord, il faut le mettre à 0
			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i][j - 1] == 255) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i - 1][j + 1] == 0) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j + 1] == 0) & (spurAg.pixel[i + 1][j] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j] == 255) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j + 1] == 0) & (spurAg.pixel[i + 1][j] == 0) & (spurAg.pixel[i + 1][j - 1] == 0) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j - 1] == 0) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i][j + 1] == 255) & (spurAg.pixel[i + 1][j] == 0) & (spurAg.pixel[i + 1][j - 1] == 0) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j - 1] == 0) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i - 1][j + 1] == 0) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j] == 255) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j - 1] == 255) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i - 1][j + 1] == 0) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j + 1] == 0) & (spurAg.pixel[i + 1][j] == 0) & (spurAg.pixel[i + 1][j - 1] == 0) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j - 1] == 0) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i - 1][j + 1] == 255) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j + 1] == 0) & (spurAg.pixel[i + 1][j] == 0) & (spurAg.pixel[i + 1][j - 1] == 0) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j - 1] == 0) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i - 1][j + 1] == 0) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j + 1] == 255) & (spurAg.pixel[i + 1][j] == 0) & (spurAg.pixel[i + 1][j - 1] == 0) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			if ((spurAg.pixel[i][j] == 255) & (spurAg.pixel[i - 1][j - 1] == 0) & (spurAg.pixel[i - 1][j] == 0) & (spurAg.pixel[i - 1][j + 1] == 0) & (spurAg.pixel[i][j + 1] == 0) & (spurAg.pixel[i + 1][j + 1] == 0) & (spurAg.pixel[i + 1][j] == 0) & (spurAg.pixel[i + 1][j - 1] == 255) & (spurAg.pixel[i][j - 1] == 0))
			{
				spur.pixel[i - 1][j - 1] = 0;
				passage = 1;
			}

			// Si aucune des conditions précédentes sont vérifiée, le pixel est inchangé
			if (passage == 0)
				spur.pixel[i - 1][j - 1] = spurAg.pixel[i][j];
		}
	}

	liberationImage(&spurAg);
	return spur;
}

IMAGE imSpurInf(IMAGE img)
{
	IMAGE spur = imSpur1(img);
	IMAGE spur2 = { 0, 0, NULL, NULL };
	TABLEAU_INT histo = histogrammeImage(spur, 0);
	int nbPixinitial = 0;
	int nbPixFinal = histo.data[255];

	// On enleve les pixels des extrémités un par un tant que ça change l'image
	while (nbPixinitial != nbPixFinal)
	{
		nbPixinitial = nbPixFinal;

		spur2 = imSpur1(spur);
		liberationImage(&spur);
		spur = imCopy(spur2);
		liberationImage(&spur2);

		liberationTableau(&histo);
		histo = histogrammeImage(spur, 0);
		nbPixFinal = histo.data[255];
	}
	liberationTableau(&histo);
	return spur;
}

IMAGE imFill(IMAGE img)
{
	IMAGE fill = allocationImage0(img.Nblig, img.Nbcol);
	int bord_gauche = 0;
	int bord_droite = img.Nbcol - 1;
	int detection = 0;
	int j = 0;

	int test;

	for (int i = 0; i < img.Nblig; i++)
	{
		// Détection du rang de la première occurence d'une valeur à 255 en partant de la gauche
		detection = 0;
		bord_gauche = -1;
		j = 0;
		while ((j < img.Nbcol) & (detection == 0))
		{
			if (img.pixel[i][j] == 255)
			{
				bord_gauche = j;
				detection = 1;
			}
			j++;
		}

		// Détection du rang de la première occurence d'une valeur à 255 en partant de la droite
		detection = 0;
		bord_droite = -1;
		j = img.Nbcol-1;
		while ((j >= 0) & (detection == 0))
		{
			if (img.pixel[i][j] == 255)
			{
				bord_droite = j;
				detection = 1;
			}
			j--;
		}

		// Mise à 255 des pixels entre les deux bords --> provoque des bug si plusieurs trous à combler sur la même ligne
		for (int j = 0; j < img.Nbcol; j++)
		{
			if (bord_gauche == -1)
				fill.pixel[i][j] = 0;
			else if ((j >= bord_gauche) & (j <= bord_droite))
				fill.pixel[i][j] = 255;
			else if ((j <= bord_gauche) | (j >= bord_droite))
				fill.pixel[i][j] = 0;
		}
	}
	return fill;
}


void numDiskToString(int num, char *chaineTaille11) //On pourrai remplacer beacuoup d'insctructions en utilisant la fonction sprintf comme fait dans detectionCercle
{
	// Création du numéro
	int a = num / 10;
	int b = num % 10;
	char carac1[3];
	carac1[0] = '0' + a;
	carac1[1] = '0' + b;
	carac1[2] = '\0';

	if (carac1[0] == '0')
	{
		carac1[0] = carac1[1];
		carac1[1] = carac1[2];
	}

	// Concaténation avec la chaine "disk"
	char disk[11] = "disk";
	strncat(disk, carac1, 2);

	// Concaténation avec la chaibe ".pgm"
	char pgm[5] = ".pgm";
	strncat(disk, pgm, 4);

	// Copie de la chaine construite dans le chaine envoyée comme argument dans la fonction
	char caracCopie = disk[0];
	int i = 0;
	while (caracCopie != '\0')
	{
		chaineTaille11[i] = caracCopie;
		i++;
		caracCopie = disk[i];
	}
	chaineTaille11[i] = '\0';
}

void detectionCercleFIX(IMAGE img, char* nomImage) // IMAGE *SKEL, IMAGE *FILL    // EN COURS DE DEV
{
	// Seuillage et inversion de l'image de base
	IMAGE seuillee = seuillageOtsu(img);
	IMAGE BW = inverseImage(seuillee);
	IMAGE SE = { 0,0,NULL, NULL };
	IMAGE SKEL = { 0,0,NULL, NULL };
	IMAGE FILL = { 0,0,NULL, NULL };

	// Vecteur de stockage des surfaces des boucles détectée
	TABLEAU_INT surfaces = allocationTableau(13);
	int *max;
	int *indice;

	// Définition des différentes composantes du nom de sauvegarde
	char chaineSauvegarde[21] = "..\\\\..\\\\Res\\\\"; // Quand on met '\\', seul '\' est pris en compte donc on en met deux fois plus
	char chaineOUT[4] = "OUT";
	char troisPremiersChiffres[4];
	troisPremiersChiffres[0] = nomImage[0];
	troisPremiersChiffres[1] = nomImage[1];
	troisPremiersChiffres[2] = nomImage[2];
	troisPremiersChiffres[3] = '\0';
	char ChaineNumero[4] = "";
	char chaineDynamique[27];

	// Construction de la partie statique du chemin de sauvegarde. Càd "OUT" & 3premiersNumImage & '-'
	strncat(chaineSauvegarde, chaineOUT, 3);
	strncat(chaineSauvegarde, troisPremiersChiffres, 3);
	strncat(chaineSauvegarde, "-", 1);
	chaineSauvegarde[20] = '\0';

	for (int i = 0; i < 13; i++)
	{
		// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
		char imAouvrir[11];
		numDiskToString(i, imAouvrir);

		// Ouverture de l'élément structurant et réalisation des opérations sur l'image
		SE = lectureImage(imAouvrir);
		//printf("-----SE ouvert par fonction detection cercle : %s \n", imAouvrir);
		SKEL = imCloseMATLAB(BW, SE);
		SKEL = imSkelApprox(SKEL);
		FILL = imSpurInf(SKEL);
		FILL = imFill(FILL);

		// Construction de la partie dynamique du chemin de sauvegarde : Càd chaineStatique & chaineNumero & ".pgm"
		for (int compteur = 0; compteur < 20; compteur++)
		{
			chaineDynamique[compteur] = chaineSauvegarde[compteur];
		}
		chaineDynamique[20] = '\0';

		sprintf(ChaineNumero, "%d", i); // Met dans ChaineNumero le numero i sous forme de chaine de caractère
		strncat(chaineDynamique, ChaineNumero, 3);
		strncat(chaineDynamique, ".pgm", 4);

		// Sauvegarde de l'image issue de TOUTES les opérations (image FILL)
		//printf("*****Chemin de sauvegarde fonction detection cercle : %s \n", chaineDynamique);
		sauvegardeImage(FILL, "P5", chaineDynamique);

		// Calcul de surface des boucles détectées
		surfaces.data[i] = histogrammeImage(FILL,0).data[255];
	}

	maxETindTabInt(surfaces, &max, &indice);


	// Liberation de la mémoire allouée
	liberationImage(&seuillee);
	liberationImage(&BW);
	liberationImage(&SE);
	liberationImage(&SKEL);
	liberationImage(&FILL);
	liberationTableau(&surfaces);
}

void detectionCercleV2(IMAGE img, char* nomImage) // IMAGE *SKEL, IMAGE *FILL    // EN COURS DE DEV
{
	// Seuillage et inversion de l'image de base
	IMAGE seuillee = seuillageOtsu(img);
	IMAGE BW = inverseImage(seuillee);
	IMAGE SE = { 0,0,NULL, NULL };
	IMAGE SKEL = { 0,0,NULL, NULL };
	IMAGE FILL = { 0,0,NULL, NULL };

	// Vecteur de stockage des surfaces des boucles détectée
	TABLEAU_INT surfaces = allocationTableau(13);
	int *max;
	int *indice;

	// Définition des différentes composantes du nom de sauvegarde
	char chaineSauvegarde[21] = "..\\\\..\\\\Res\\\\"; // Quand on met '\\', seul '\' est pris en compte donc on en met deux fois plus
	char chaineOUT[4] = "OUT";
	char troisPremiersChiffres[4];
	troisPremiersChiffres[0] = nomImage[0];
	troisPremiersChiffres[1] = nomImage[1];
	troisPremiersChiffres[2] = nomImage[2];
	troisPremiersChiffres[3] = '\0';
	char ChaineNumero[4] = "";
	char chaineDynamique[27];

	// Construction de la partie statique du chemin de sauvegarde. Càd "OUT" & 3premiersNumImage & '-'
	strncat(chaineSauvegarde, chaineOUT, 3);
	strncat(chaineSauvegarde, troisPremiersChiffres, 3);
	strncat(chaineSauvegarde, "-", 1);
	chaineSauvegarde[20] = '\0';

	for (int i = 0; i < 13; i++)
	{
		// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
		char imAouvrir[11];
		numDiskToString(i, imAouvrir);

		// Ouverture de l'élément structurant et réalisation des opérations sur l'image
		SE = lectureImage(imAouvrir);
		//printf("-----SE ouvert par fonction detection cercle : %s \n", imAouvrir);
		SKEL = imCloseMATLAB(BW, SE);
		SKEL = imSkelApprox(SKEL);
		FILL = imSpurInf(SKEL);
		FILL = imFill(FILL);

		

		// Calcul de surface des boucles détectées
		surfaces.data[i] = histogrammeImage(FILL, 0).data[255];
	}

	maxETindTabInt(surfaces, &max, &indice);

	// Construction de la partie dynamique du chemin de sauvegarde : Càd chaineStatique & chaineNumero & ".pgm"
	for (int compteur = 0; compteur < 20; compteur++)
	{
		chaineDynamique[compteur] = chaineSauvegarde[compteur];
	}
	chaineDynamique[20] = '\0';

	sprintf(ChaineNumero, "%d", indice); // Met dans ChaineNumero le numero i sous forme de chaine de caractère
	strncat(chaineDynamique, ChaineNumero, 3);
	strncat(chaineDynamique, ".pgm", 4);

	// On refait toutes les opérations morphologiques sur l'image qui nous renvoie la meilleure détection de boucle (i.e la plus grande aire)
	// ----
	// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
	char imAouvrir[11];
	numDiskToString(indice, imAouvrir);
	// Ouverture de l'élément structurant et réalisation des opérations sur l'image
	SE = lectureImage(imAouvrir);
	SKEL = imCloseMATLAB(BW, SE);
	SKEL = imSkelApprox(SKEL);
	FILL = imSpurInf(SKEL);
	FILL = imFill(FILL);
	// ----

	// Sauvegarde de l'image issue de TOUTES les opérations (image FILL)
	printf("Valeur de indice : %d \n", indice);
	printf("*****Chemin de sauvegarde fonction detection cercle : %s \n", chaineDynamique);
	sauvegardeImage(FILL, "P5", chaineDynamique);


	// Liberation de la mémoire allouée
	liberationImage(&seuillee);
	liberationImage(&BW);
	liberationImage(&SE);
	liberationImage(&SKEL);
	liberationImage(&FILL);
	liberationTableau(&surfaces);
}

void detectionCercleForAll()
{
	char nomImage[8];
	char intToStr[4];
	IMAGE img = { 0,0,NULL,NULL };
	/*
	for (int i = 1; i < 10; i++)
	{
		// Création du nom de l'image à ouvrir
		nomImage[0] = '0';
		nomImage[1] = '0';
		nomImage[2] = '\0';
		sprintf(intToStr, "%d", i);
		strncat(nomImage, intToStr, 1);
		strncat(nomImage, ".pgm", 4);
		nomImage[7] = '\0';
		printf("Chaine : %s \n", nomImage);

		// Ouverture de l'image
		img = lectureImage(nomImage);

		// Appel de la fonction de détection
		detectionCercleV2saveSkel(img, nomImage);
		liberationImage(&img);
	}
	
	
	for (int i = 10; i < 100; i++)
	{
		// Création du nom de l'image à ouvrir
		nomImage[0] = '0';
		nomImage[1] = '\0';
		sprintf(intToStr, "%d", i);
		strncat(nomImage, intToStr, 2);
		strncat(nomImage, ".pgm", 4);
		nomImage[7] = '\0';
		printf("Chaine : %s \n", nomImage);

		// Ouverture de l'image
		img = lectureImage(nomImage);

		// Appel de la fonction de détection
		detectionCercleV2saveSkel(img, nomImage);
		liberationImage(&img);
	}
	*/
	for (int i = 340; i < 388; i++)
	{
		// Création du nom de l'image à ouvrir
		nomImage[0] = '\0';
		sprintf(intToStr, "%d", i);
		strncat(nomImage, intToStr, 3);
		strncat(nomImage, ".pgm", 4);
		nomImage[7] = '\0';
		printf("Chaine : %s \n", nomImage);

		// Ouverture de l'image
		img = lectureImage(nomImage);

		// Appel de la fonction de détection
		detectionCercleV2saveSkel(img, nomImage);
		liberationImage(&img);
	}
}

int nbPix255haut(IMAGE img)
{
	int h[256];
	h[0] = 0;
	h[255] = 0;

	// Histogramme de l'image uniquemet sur la partie haute de celle-ci
	for (int i = 0; i < (img.Nblig/2); i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			h[(int)img.pixel[i][j]] += 1;
		}
	}
	return h[255];
}

int nbPix255bas(IMAGE img)
{
	int h[256];
	h[0] = 0;
	h[255] = 0;

	// Histogramme de l'image uniquemet sur la partie basse de celle-ci
	for (int i = (img.Nblig / 2); i < 100; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			h[(int)img.pixel[i][j]] += 1;
		}
	}
	return h[255];
}

void detectionCercleV2saveSkel(IMAGE img, char* nomImage) // IMAGE *SKEL, IMAGE *FILL
{
	// Seuillage et inversion de l'image de base
	IMAGE seuillee = seuillageOtsu(img);
	IMAGE BW = inverseImage(seuillee);
	IMAGE SE = { 0,0,NULL, NULL };
	IMAGE SKEL = { 0,0,NULL, NULL };
	IMAGE SPUR = { 0,0,NULL, NULL };
	IMAGE FILL = { 0,0,NULL, NULL };

	// Vecteur de stockage des surfaces des boucles détectée
	TABLEAU_INT surfaces = allocationTableau(13);
	int *max;
	int *indice;

	// Définition des différentes composantes du nom de sauvegarde
	char chaineSauvegarde[21] = "..\\\\..\\\\Res\\\\"; // Quand on met '\\', seul '\' est pris en compte donc on en met deux fois plus
	char chaineOUT[4] = "OUT";
	char troisPremiersChiffres[4];
	troisPremiersChiffres[0] = nomImage[0];
	troisPremiersChiffres[1] = nomImage[1];
	troisPremiersChiffres[2] = nomImage[2];
	troisPremiersChiffres[3] = '\0';
	char ChaineNumero[4] = "";
	char chaineDynamique[27];

	// Construction de la partie statique du chemin de sauvegarde. Càd "OUT" & 3premiersNumImage & '-'
	strncat(chaineSauvegarde, chaineOUT, 3);
	strncat(chaineSauvegarde, troisPremiersChiffres, 3);
	strncat(chaineSauvegarde, "-", 1);
	chaineSauvegarde[20] = '\0';

	for (int i = 0; i < 13; i++)
	{
		// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
		char imAouvrir[11];
		numDiskToString(i, imAouvrir);

		// Ouverture de l'élément structurant et réalisation des opérations sur l'image
		SE = lectureImage(imAouvrir);
		//printf("-----SE ouvert par fonction detection cercle : %s \n", imAouvrir);
		SKEL = imCloseMATLAB(BW, SE);
		SKEL = imSkelApprox(SKEL);
		SPUR = imSpurInf(SKEL);
		FILL = imFill(SPUR);



		// Calcul de surface des boucles détectées
		surfaces.data[i] = histogrammeImage(FILL, 0).data[255];
	}

	maxETindTabInt(surfaces, &max, &indice);

	// Construction de la partie dynamique du chemin de sauvegarde : Càd chaineStatique & chaineNumero & ".pgm"
	for (int compteur = 0; compteur < 20; compteur++)
	{
		chaineDynamique[compteur] = chaineSauvegarde[compteur];
	}
	chaineDynamique[20] = '\0';

	sprintf(ChaineNumero, "%d", indice); // Met dans ChaineNumero le numero i sous forme de chaine de caractère
	strncat(chaineDynamique, ChaineNumero, 3);
	strncat(chaineDynamique, ".pgm", 4);

	// On refait toutes les opérations morphologiques sur l'image qui nous renvoie la meilleure détection de boucle (i.e la plus grande aire)
	// ----
	// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
	char imAouvrir[11];
	numDiskToString(indice, imAouvrir);
	// Ouverture de l'élément structurant et réalisation des opérations sur l'image
	SE = lectureImage(imAouvrir);
	SKEL = imCloseMATLAB(BW, SE);
	SKEL = imSkelApprox(SKEL);
	SPUR = imSpurInf(SKEL);
	FILL = imFill(SPUR);
	// ----

	// Sauvegarde de l'image issue de TOUTES les opérations (image FILL)
	printf("Valeur de indice : %d \n", indice);
	printf("*****Chemin de sauvegarde fonction detection cercle : %s \n", chaineDynamique);
	sauvegardeImage(FILL, "P5", chaineDynamique);

	
	// Sauvegarde de l'image SKEL
	char chaineSauvSkel[29];
	for (int compteur = 0; compteur < 21; compteur++)
		chaineSauvSkel[compteur] = chaineDynamique[compteur];
	chaineSauvSkel[21] = '\0';
	strncat(chaineSauvSkel, "skl", 3);
	strncat(chaineSauvSkel, ".pgm", 4);
	printf("Chaine Sauv Skel : %s \n", chaineSauvSkel);
	sauvegardeImage(SKEL, "P5", chaineSauvSkel);

	// Sauvegarde de l'image SPUR
	char chaineSauvSpur[29];
	for (int compteur = 0; compteur < 21; compteur++)
		chaineSauvSpur[compteur] = chaineDynamique[compteur];
	chaineSauvSpur[21] = '\0';
	strncat(chaineSauvSpur, "spr", 3);
	strncat(chaineSauvSpur, ".pgm", 4);
	printf("Chaine Sauv Spur : %s \n", chaineSauvSpur);
	sauvegardeImage(SPUR, "P5", chaineSauvSpur);


	// Liberation de la mémoire allouée
	liberationImage(&seuillee);
	liberationImage(&BW);
	liberationImage(&SE);
	liberationImage(&SKEL);
	liberationImage(&FILL);
	liberationTableau(&surfaces);
	liberationImage(&SPUR);
}

IMAGE imCopy(IMAGE img)
{
	IMAGE imgCopie = { 0,0,NULL,NULL };
	imgCopie = allocationImage(img.Nblig, img.Nbcol);
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			imgCopie.pixel[i][j] = img.pixel[i][j];
		}
	}
	return imgCopie;
}

TABLEAU_INT imChainCode(IMAGE img)
{
	IMAGE imAgg = { 0,0,NULL,NULL };
	imAgg = imBiggerWith0(img);

	// Parcours de l'image jusqu'à trouver un pixel blanc (notre point de départ de parcours du contour)
	int i = 1;
	int j = 1;
	int pixelBlanc = 0;
	int indX = 0;
	int indY = 0;
	while ((i < img.Nblig + 1) & (pixelBlanc == 0))
	{
		while ((j < img.Nbcol + 1) & (pixelBlanc == 0))
		{
			if (imAgg.pixel[i][j] == 255)
			{
				pixelBlanc = 1;
				indX = i;
				indY = j;
			}
			j++;
		}
		i++;
		j = 0;
	}

	int nbPixBlanc = histogrammeImage(img, 0).data[255];
	TABLEAU_INT chainCode = allocationTableau(nbPixBlanc); //On bloque la taille de la chain code au nombre de pixels blancs sur l'image

	i = 0;
	int condition = 0;
	if ((imAgg.pixel[indX - 1][indY - 1] == 0) & (imAgg.pixel[indX - 1][indY] == 0) & (imAgg.pixel[indX - 1][indY + 1] == 0) & (imAgg.pixel[indX][indY + 1] == 0) & (imAgg.pixel[indX + 1][indY + 1] == 0) & (imAgg.pixel[indX + 1][indY] == 0) & (imAgg.pixel[indX + 1][indY - 1] == 0) & (imAgg.pixel[indX][indY - 1] == 0))
		condition = 1; // i.e tous les pixels en V8 sont nul --> fin du parcour
	// Parcours du contour de l'objet et enregistrement de la chain code
	while ((i < nbPixBlanc) & (condition == 0))
	{
		if (imAgg.pixel[indX][indY + 1] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indY++;
			chainCode.data[i] = 0;
		}
		else if (imAgg.pixel[indX + 1][indY + 1] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indX++;
			indY++;
			chainCode.data[i] = 7;
		}
		else if (imAgg.pixel[indX + 1][indY] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indX++;
			chainCode.data[i] = 6;
		}
		else if (imAgg.pixel[indX + 1][indY - 1] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indX++;
			indY--;
			chainCode.data[i] = 5;
		}
		else if (imAgg.pixel[indX][indY - 1] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indY--;
			chainCode.data[i] = 4;
		}
		else if (imAgg.pixel[indX - 1][indY - 1] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indX--;
			indY--;
			chainCode.data[i] = 3;
		}
		else if (imAgg.pixel[indX - 1][indY] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indX--;
			chainCode.data[i] = 2;
		}
		else if (imAgg.pixel[indX - 1][indY + 1] == 255)
		{
			imAgg.pixel[indX][indY] = 0;
			indX--;
			indY++;
			chainCode.data[i] = 1;
		}
		else
			condition = 1;
		
		i++;
	}

	liberationImage(&imAgg);
	return chainCode;
}

double imPerimeter(IMAGE img)
{
	TABLEAU_INT chainCode = imChainCode(img);

	// Parcours de la chain code à l'envers pour détecter le dernier élément non nul (est normalement le dernier à être pertinent
	// car le point de départ est le premier pixel à 255 en haut à gauche donc ne doit pas finir par des 0)
	int indiceStopCompris = 0;
	int i = chainCode.size - 1;
	while ((i >= 0) & (indiceStopCompris == 0))
	{
		if (chainCode.data[i] != 0)
			indiceStopCompris = i;
		i--;
	}

	// Calcul du perimetre en fonction de la parité des valeurs de la chain code
	double perimeter = 0;
	for (int j = 0; j <= indiceStopCompris; j++)
	{
		if (chainCode.data[j] % 2 == 0)
			perimeter += 1;
		else
			perimeter += 1.4142; // approx de racine de 2
	}

	return perimeter;
}

void signatureToCSV(char *repertoire)
{
	// Variables pour construction du chemin à ouvrir
	char nomImg[8];
	char intToStr[4];
	// Variables images
	IMAGE img = { 0, 0, NULL, NULL };
	IMAGE OUT = { 0, 0, NULL, NULL };
	IMAGE SKEL = { 0, 0, NULL, NULL };
	IMAGE SPUR = { 0, 0, NULL, NULL };
	SIGNATURES_OCR signatures;
	// Ouverture du flux pour écriture dans fichier CSV
	FILE *F = NULL;
	F = fopen("..\\..\\Res\\signatures.csv", "w");
	// écriture titre colonnes signatures
	fprintf(F, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", "NomImage", "Numero", "nbPixBoucleHaut", "nbPixBoucleBas", "Compacity", "distSTDskel", "nbPixSkelQuartBasGauche", "skelXcentreGrav", "skelYcentreGrav", "boucleXcentreGrav", "boucleYcentreGrav", "diffSkelBoucleXcentreGrav", "diffSkelBoucleYcentreGrav", "nbPixDiagInfSkel", "nbPixDiagSupSkel");


	// Construction du chemin fixe à partir du repertoire envoyé par l'utitisateur
	char prefixe[30] = "..\\..\\Images\\";
	strncat(prefixe, repertoire, 5);
	strncat(prefixe, "\\", 3);

	if (repertoire == "train")
	{
		for (int i = 1; i < 10; i++)
		{
			// Recopie du chemin fixe pour concaténation variable avec le nom de l'image
			char chemin[35];
			for (int i = 0; i < 30; i++)
				chemin[i] = prefixe[i];

			// Création du nom de l'image à ouvrir
			nomImg[0] = '0';
			nomImg[1] = '0';
			nomImg[2] = '\0';
			sprintf(intToStr, "%d", i);
			strncat(nomImg, intToStr, 1);
			strncat(nomImg, ".pgm", 4);
			nomImg[7] = '\0';

			strncat(chemin, nomImg, 8);

			img = lectureImage(chemin);
			OUT = allocationImage0(img.Nblig, img.Nbcol);
			SKEL = allocationImage0(img.Nblig, img.Nbcol);
			SPUR = allocationImage0(img.Nblig, img.Nbcol);
			detectionCercle(img, &OUT, &SKEL, &SPUR);

			// Calcul des signatures
			signatures.nbPixBoucleHaut = nbPix255haut(OUT);
			signatures.nbPixBoucleBas = nbPix255bas(OUT);
			signatures.compacity = imCompacity(OUT, SPUR);
			signatures.distSTDskel = distSTDcentreGrav(SKEL);
			signatures.nbPixSkelQuartBasGauche = nbPixQuartBasGauche255(SKEL);
			imCentreGrav(SKEL, &(signatures.skelXcentreGrav), &(signatures.skelYcentreGrav));
			imCentreGrav(OUT, &(signatures.boucleXcentreGrav), &(signatures.boucleYcentreGrav));
			signatures.diffSkelBoucleXcentreGrav = signatures.skelXcentreGrav - signatures.boucleXcentreGrav;
			signatures.diffSkelBoucleYcentreGrav = signatures.skelYcentreGrav - signatures.boucleYcentreGrav;
			signatures.nbPixDiagSupSkel = nbPixDiagSup255(SKEL);
			signatures.nbPixDiagInfSkel = nbPixDiagInf255(SKEL);

			fprintf(F, "%s;%d;%d;%d;%lf;%lf;%d;%lf;%lf;%lf;%lf;%lf;%lf;%d;%d\n", nomImg, i % 10, signatures.nbPixBoucleHaut, signatures.nbPixBoucleBas, signatures.compacity, signatures.distSTDskel, signatures.nbPixSkelQuartBasGauche, signatures.skelXcentreGrav, signatures.skelYcentreGrav, signatures.boucleXcentreGrav, signatures.boucleYcentreGrav, signatures.diffSkelBoucleXcentreGrav, signatures.diffSkelBoucleYcentreGrav, signatures.nbPixDiagSupSkel, signatures.nbPixDiagInfSkel);
			liberationImage(&img);
			liberationImage(&OUT);
			liberationImage(&SKEL);
			liberationImage(&SPUR);
		}
		
		for (int i = 10; i < 100; i++)
		{
			// Recopie du chemin fixe pour concaténation variable avec le nom de l'image
			char chemin[35];
			for (int i = 0; i < 30; i++)
				chemin[i] = prefixe[i];

			// Création du nom de l'image à ouvrir
			nomImg[0] = '0';
			nomImg[1] = '\0';
			sprintf(intToStr, "%d", i);
			strncat(nomImg, intToStr, 2);
			strncat(nomImg, ".pgm", 4);
			nomImg[7] = '\0';

			strncat(chemin, nomImg, 8);

			img = lectureImage(chemin);
			OUT = allocationImage0(img.Nblig, img.Nbcol);
			SKEL = allocationImage0(img.Nblig, img.Nbcol);
			SPUR = allocationImage0(img.Nblig, img.Nbcol);
			detectionCercle(img, &OUT, &SKEL, &SPUR);

			// Calcul des signatures
			signatures.nbPixBoucleHaut = nbPix255haut(OUT);
			signatures.nbPixBoucleBas = nbPix255bas(OUT);
			signatures.compacity = imCompacity(OUT, SPUR);
			signatures.distSTDskel = distSTDcentreGrav(SKEL);
			signatures.nbPixSkelQuartBasGauche = nbPixQuartBasGauche255(SKEL);
			imCentreGrav(SKEL, &(signatures.skelXcentreGrav), &(signatures.skelYcentreGrav));
			imCentreGrav(OUT, &(signatures.boucleXcentreGrav), &(signatures.boucleYcentreGrav));
			signatures.diffSkelBoucleXcentreGrav = signatures.skelXcentreGrav - signatures.boucleXcentreGrav;
			signatures.diffSkelBoucleYcentreGrav = signatures.skelYcentreGrav - signatures.boucleYcentreGrav;
			signatures.nbPixDiagSupSkel = nbPixDiagSup255(SKEL);
			signatures.nbPixDiagInfSkel = nbPixDiagInf255(SKEL);

			fprintf(F, "%s;%d;%d;%d;%lf;%lf;%d;%lf;%lf;%lf;%lf;%lf;%lf;%d;%d\n", nomImg, i % 10, signatures.nbPixBoucleHaut, signatures.nbPixBoucleBas, signatures.compacity, signatures.distSTDskel, signatures.nbPixSkelQuartBasGauche, signatures.skelXcentreGrav, signatures.skelYcentreGrav, signatures.boucleXcentreGrav, signatures.boucleYcentreGrav, signatures.diffSkelBoucleXcentreGrav, signatures.diffSkelBoucleYcentreGrav, signatures.nbPixDiagSupSkel, signatures.nbPixDiagInfSkel);
			liberationImage(&img);
			liberationImage(&OUT);
			liberationImage(&SKEL);
			liberationImage(&SPUR);
		}
	
		for (int i = 100; i < 388; i++)
		{
			// Recopie du chemin fixe pour concaténation variable avec le nom de l'image
			char chemin[35];
			for (int i = 0; i < 30; i++)
				chemin[i] = prefixe[i];

			// Création du nom de l'image à ouvrir
			nomImg[0] = '\0';
			sprintf(intToStr, "%d", i);
			strncat(nomImg, intToStr, 3);
			strncat(nomImg, ".pgm", 4);
			nomImg[7] = '\0';

			strncat(chemin, nomImg, 8);

			img = lectureImage(chemin);
			OUT = allocationImage0(img.Nblig, img.Nbcol);
			SKEL = allocationImage0(img.Nblig, img.Nbcol);
			SPUR = allocationImage0(img.Nblig, img.Nbcol);
			detectionCercle(img, &OUT, &SKEL, &SPUR);

			// Calcul des signatures
			signatures.nbPixBoucleHaut = nbPix255haut(OUT);
			signatures.nbPixBoucleBas = nbPix255bas(OUT);
			signatures.compacity = imCompacity(OUT, SPUR);
			signatures.distSTDskel = distSTDcentreGrav(SKEL);
			signatures.nbPixSkelQuartBasGauche = nbPixQuartBasGauche255(SKEL);
			imCentreGrav(SKEL, &(signatures.skelXcentreGrav), &(signatures.skelYcentreGrav));
			imCentreGrav(OUT, &(signatures.boucleXcentreGrav), &(signatures.boucleYcentreGrav));
			signatures.diffSkelBoucleXcentreGrav = signatures.skelXcentreGrav - signatures.boucleXcentreGrav;
			signatures.diffSkelBoucleYcentreGrav = signatures.skelYcentreGrav - signatures.boucleYcentreGrav;
			signatures.nbPixDiagSupSkel = nbPixDiagSup255(SKEL);
			signatures.nbPixDiagInfSkel = nbPixDiagInf255(SKEL);

			fprintf(F, "%s;%d;%d;%d;%lf;%lf;%d;%lf;%lf;%lf;%lf;%lf;%lf;%d;%d\n", nomImg, i % 10, signatures.nbPixBoucleHaut, signatures.nbPixBoucleBas, signatures.compacity, signatures.distSTDskel, signatures.nbPixSkelQuartBasGauche, signatures.skelXcentreGrav, signatures.skelYcentreGrav, signatures.boucleXcentreGrav, signatures.boucleYcentreGrav, signatures.diffSkelBoucleXcentreGrav, signatures.diffSkelBoucleYcentreGrav, signatures.nbPixDiagSupSkel, signatures.nbPixDiagInfSkel);
			liberationImage(&img);
			liberationImage(&OUT);
			liberationImage(&SKEL);
			liberationImage(&SPUR);
		}
	}
	else if (repertoire == "test")
	{
		for (int i = 388; i < 517; i++) // i < 517 pour toute les mettre
		{
			// Recopie du chemin fixe pour concaténation variable avec le nom de l'image
			char chemin[35];
			for (int i = 0; i < 30; i++)
				chemin[i] = prefixe[i];

			// Création du nom de l'image à ouvrir
			nomImg[0] = '\0';
			sprintf(intToStr, "%d", i);
			strncat(nomImg, intToStr, 3);
			strncat(nomImg, ".pgm", 4);
			nomImg[7] = '\0';

			strncat(chemin, nomImg, 8);

			img = lectureImage(chemin);
			OUT = allocationImage0(img.Nblig, img.Nbcol);
			SKEL = allocationImage0(img.Nblig, img.Nbcol);
			SPUR = allocationImage0(img.Nblig, img.Nbcol);
			detectionCercle(img, &OUT, &SKEL, &SPUR);

			// Calcul des signatures
			signatures.nbPixBoucleHaut = nbPix255haut(OUT);
			signatures.nbPixBoucleBas = nbPix255bas(OUT);
			signatures.compacity = imCompacity(OUT, SPUR);
			signatures.distSTDskel = distSTDcentreGrav(SKEL);
			signatures.nbPixSkelQuartBasGauche = nbPixQuartBasGauche255(SKEL);
			imCentreGrav(SKEL, &(signatures.skelXcentreGrav), &(signatures.skelYcentreGrav));
			imCentreGrav(OUT, &(signatures.boucleXcentreGrav), &(signatures.boucleYcentreGrav));
			signatures.diffSkelBoucleXcentreGrav = signatures.skelXcentreGrav - signatures.boucleXcentreGrav;
			signatures.diffSkelBoucleYcentreGrav = signatures.skelYcentreGrav - signatures.boucleYcentreGrav;
			signatures.nbPixDiagSupSkel = nbPixDiagSup255(SKEL);
			signatures.nbPixDiagInfSkel = nbPixDiagInf255(SKEL);

			fprintf(F, "%s;%d;%d;%d;%lf;%lf;%d;%lf;%lf;%lf;%lf;%lf;%lf;%d;%d\n", nomImg, i % 10, signatures.nbPixBoucleHaut, signatures.nbPixBoucleBas, signatures.compacity, signatures.distSTDskel, signatures.nbPixSkelQuartBasGauche, signatures.skelXcentreGrav, signatures.skelYcentreGrav, signatures.boucleXcentreGrav, signatures.boucleYcentreGrav, signatures.diffSkelBoucleXcentreGrav, signatures.diffSkelBoucleYcentreGrav, signatures.nbPixDiagSupSkel, signatures.nbPixDiagInfSkel);
			liberationImage(&img);
			liberationImage(&OUT);
			liberationImage(&SKEL);
			liberationImage(&SPUR);
		}
	}

	// Fermeture flux et images
	fclose(F);
	
}

void detectionCercle(IMAGE img, IMAGE *OUT, IMAGE *SKEL, IMAGE *SPUR)
{
	// Seuillage et inversion de l'image de base
	IMAGE seuillee = seuillageOtsu(img);
	IMAGE BW = inverseImage(seuillee);
	IMAGE SE = { 0,0,NULL, NULL };
	IMAGE close = { 0, 0, NULL, NULL };
	TABLEAU_INT histo;

	// Vecteur de stockage des surfaces des boucles détectée
	TABLEAU_INT surfaces = allocationTableau(13);
	int *max;
	int *indice;

	char cheminSE[25] = "..\\..\\Images\\STREL\\";
	char cheminSEetSE[35];

	for (int i = 0; i < 13; i++)
	{
		// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
		char imAouvrir[11];
		numDiskToString(i, imAouvrir);
		
		// Ouverture de l'élément structurant et réalisation des opérations sur l'image
		liberationImage(&SE);
		strcpy(cheminSEetSE, cheminSE);
		strncat(cheminSEetSE, imAouvrir, 10);
		SE = lectureImage(cheminSEetSE);
		
		// Liberation avec allocation
		liberationImage(&close);
		liberationImage(SKEL);
		liberationImage(SPUR);
		liberationImage(OUT);

		// Réalisation des opérations morphologiques
		close = imCloseMATLAB(BW, SE);
		SKEL[0] = imSkelApprox(close);
		SPUR[0] = imSpurInf(SKEL[0]);
		OUT[0] = imFill(SPUR[0]);


		// Calcul de surface des boucles détectées
		histo = histogrammeImage(OUT[0], 0);
		surfaces.data[i] = histo.data[255];
		liberationTableau(&histo);
	}

	maxETindTabInt(surfaces, &max, &indice);

	// On refait toutes les opérations morphologiques sur l'image qui nous renvoie la meilleure détection de boucle (i.e la plus grande aire)
	// ----
	// Construction du nom de l'élément structurant à ouvrir (pattern : "disk" suivis du numéro suivis de ".pgm")
	char imAouvrir[11];
	numDiskToString(indice, imAouvrir);
	strcpy(cheminSEetSE, cheminSE);
	strncat(cheminSEetSE, imAouvrir, 10);

	// Libération de mémoire
	liberationImage(&SE);
	liberationImage(&close);
	liberationImage(SKEL);
	liberationImage(SPUR);
	liberationImage(OUT);


	// Ouverture de l'élément structurant et réalisation des opérations sur l'image
	SE = lectureImage(cheminSEetSE);
	close = imCloseMATLAB(BW, SE);
	SKEL[0] = imSkelApprox(close);
	SPUR[0] = imSpurInf(SKEL[0]);
	OUT[0] = imFill(SPUR[0]);
	// ----

	// Liberation de la mémoire allouée
	liberationImage(&seuillee);
	liberationImage(&BW);
	liberationImage(&SE);
	liberationTableau(&surfaces);
	liberationImage(&close);
}

double imCompacity(IMAGE OUT, IMAGE SPUR)
{
	double perimeter = histogrammeImage(SPUR,0).data[255];
	int surface = histogrammeImage(OUT, 0).data[255];
	double compacity = ((perimeter*perimeter) / (4 * 3.1415*surface));
	//printf("%lf %d %lf \n", perimeter, surface, compacity);
	return compacity;
}

void imCentreGrav(IMAGE img, double *centreXgrav, double *centreYgrav)
{
	*centreXgrav = 0;
	*centreYgrav = 0;
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			if (img.pixel[i][j] == 255)
			{
				*centreXgrav += i;
				*centreYgrav += j;
			}
		}
	}
	TABLEAU_INT histo = histogrammeImage(img, 0);
	*centreXgrav = *centreXgrav / histo.data[255];
	*centreYgrav = *centreYgrav / histo.data[255];
	liberationTableau(&histo);
}

TABLEAU_DOUBLE imDistPixCentreGrav(IMAGE img)
{
	TABLEAU_INT histo = histogrammeImage(img, 0);
	TABLEAU_DOUBLE distances = allocationTableauDouble(histo.data[255]);
	double centreXgrav;
	double centreYgrav;
	imCentreGrav(img, &centreXgrav, &centreYgrav);

	int compteur = 0;
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			if (img.pixel[i][j] == 255)
			{
				distances.data[compteur] = sqrt(((i - centreXgrav)*(i - centreXgrav)) + ((j - centreYgrav)*(j - centreYgrav)));
				compteur++;
			}
		}
	}

	liberationTableau(&histo);
	return distances;
}

double moyenneTableauDouble(TABLEAU_DOUBLE tab)
{
	double moy = 0;
	for (int i = 0; i < tab.size; i++)
	{
		moy += tab.data[i];
	}
	moy = moy / tab.size;
	return moy;
}

double ecartTypeTableauDouble(TABLEAU_DOUBLE tab)
{
	double ecart_type = 0;
	double moyenne = moyenneTableauDouble(tab);

	for (int i = 0; i < tab.size; i++)
		ecart_type += (tab.data[i] - moyenne)*(tab.data[i] - moyenne);
	
	ecart_type = ecart_type / tab.size;
	ecart_type = sqrt(ecart_type);
	
	return ecart_type;
}

double distSTDcentreGrav(IMAGE img)
{
	TABLEAU_DOUBLE distances = imDistPixCentreGrav(img);
	double distSTD = ecartTypeTableauDouble(distances);
	liberationTableauDouble(&distances);
	return distSTD;
}

int nbPixQuartBasGauche255(IMAGE img)
{
	int nbPix = 0;
	TABLEAU_INT histoQuartBasGauche = allocationTableau(256);
	histoQuartBasGauche.data[255] = 0;
	histoQuartBasGauche.data[0] = 0;

	for (int i = img.Nblig / 2; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol/2; j++)
		{
			histoQuartBasGauche.data[img.pixel[i][j]] ++;
		}
	}
	
	nbPix = histoQuartBasGauche.data[255];
	liberationTableau(&histoQuartBasGauche);
	return nbPix;
}

int nbPixDiagSup255(IMAGE img)
{
	int nbPix = 0;
	TABLEAU_INT histoDiagSup = allocationTableau(256);
	histoDiagSup.data[255] = 0;
	histoDiagSup.data[0] = 0;

	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			if (j > i)
				histoDiagSup.data[img.pixel[i][j]] ++;
		}
	}

	nbPix = histoDiagSup.data[255];
	liberationTableau(&histoDiagSup);
	return nbPix;
}

int nbPixDiagInf255(IMAGE img)
{
	int nbPix = 0;
	TABLEAU_INT histoDiagSup = allocationTableau(256);
	histoDiagSup.data[255] = 0;
	histoDiagSup.data[0] = 0;

	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			if (j < i)
				histoDiagSup.data[img.pixel[i][j]] ++;
		}
	}

	nbPix = histoDiagSup.data[255];
	liberationTableau(&histoDiagSup);
	return nbPix;
}

IMAGE imConvexHull(IMAGE img)
{
	IMAGE imgAgg = imBiggerWith0(img);
	IMAGE imgAgg2 = allocationImage(img.Nblig + 2, img.Nbcol + 2);
	IMAGE img2 = allocationImage(img.Nblig, img.Nbcol);
	//IMAGE img2bis = allocationImage(img.Nblig, img.Nbcol);
	int nbAggrandissement = 1;
	TABLEAU_INT histo = histogrammeImage(imgAgg, 0);
	int nbPixAvant = histo.data[255];
	int nbPixApres = -1;

	// Premier parcours hit or miss de l'image 
	for (int i = nbAggrandissement; i < img.Nblig + nbAggrandissement; i++)
	{
		for (int j = nbAggrandissement; j < img.Nbcol + nbAggrandissement; j++)
		{
			if ((imgAgg.pixel[i][j] == 0) & (imgAgg.pixel[i - 1][j - 1] == 255) & (imgAgg.pixel[i][j - 1] == 255) & (imgAgg.pixel[i + 1][j - 1] == 255))
				img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = 255;
			else
				img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = imgAgg.pixel[i][j];
		}
		liberationTableau(&histo);
		histo = histogrammeImage(img2, 0);
		nbPixApres = histo.data[255];
	}

	// Hit or miss gauche jusqu'à ne plus avoir de changements sur l'image
	while (nbPixAvant != nbPixApres)
	{
		nbPixAvant = nbPixApres;
		liberationImage(&imgAgg2);
		imgAgg2 = imBiggerWith0(img2);

		for (int i = nbAggrandissement; i < img.Nblig + nbAggrandissement; i++)
		{
			for (int j = nbAggrandissement; j < img.Nbcol + nbAggrandissement; j++)
			{
				if ((imgAgg2.pixel[i][j] == 0) & (imgAgg2.pixel[i - 1][j - 1] == 255) & (imgAgg2.pixel[i][j - 1] == 255) & (imgAgg2.pixel[i + 1][j - 1] == 255))
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = 255;
				else
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = imgAgg2.pixel[i][j];
			}
			liberationTableau(&histo);
			histo = histogrammeImage(img2, 0);
			nbPixApres = histo.data[255];
		}


	}

	nbPixApres = -1;
	while (nbPixAvant != nbPixApres)
	{
		nbPixAvant = nbPixApres;
		liberationImage(&imgAgg2);
		imgAgg2 = imBiggerWith0(img2);

		for (int i = nbAggrandissement; i < img.Nblig + nbAggrandissement; i++)
		{
			for (int j = nbAggrandissement; j < img.Nbcol + nbAggrandissement; j++)
			{
				if ((imgAgg2.pixel[i][j] == 0) & (imgAgg2.pixel[i - 1][j - 1] == 255) & (imgAgg2.pixel[i - 1][j] == 255) & (imgAgg2.pixel[i - 1][j + 1] == 255))
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = 255;
				else
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = imgAgg2.pixel[i][j];
			}
			liberationTableau(&histo);
			histo = histogrammeImage(img2, 0);
			nbPixApres = histo.data[255];
		}


	}

	nbPixApres = -1;
	while (nbPixAvant != nbPixApres)
	{
		nbPixAvant = nbPixApres;
		liberationImage(&imgAgg2);
		imgAgg2 = imBiggerWith0(img2);

		for (int i = nbAggrandissement; i < img.Nblig + nbAggrandissement; i++)
		{
			for (int j = nbAggrandissement; j < img.Nbcol + nbAggrandissement; j++)
			{
				if ((imgAgg2.pixel[i][j] == 0) & (imgAgg2.pixel[i - 1][j + 1] == 255) & (imgAgg2.pixel[i][j + 1] == 255) & (imgAgg2.pixel[i + 1][j + 1] == 255))
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = 255;
				else
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = imgAgg2.pixel[i][j];
			}
			liberationTableau(&histo);
			histo = histogrammeImage(img2, 0);
			nbPixApres = histo.data[255];
		}


	}

	nbPixApres = -1;
	while (nbPixAvant != nbPixApres)
	{
		nbPixAvant = nbPixApres;
		liberationImage(&imgAgg2);
		imgAgg2 = imBiggerWith0(img2);

		for (int i = nbAggrandissement; i < img.Nblig + nbAggrandissement; i++)
		{
			for (int j = nbAggrandissement; j < img.Nbcol + nbAggrandissement; j++)
			{
				if ((imgAgg2.pixel[i][j] == 0) & (imgAgg2.pixel[i + 1][j + 1] == 255) & (imgAgg2.pixel[i + 1][j] == 255) & (imgAgg2.pixel[i + 1][j - 1] == 255))
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = 255;
				else
					img2.pixel[i - nbAggrandissement][j - nbAggrandissement] = imgAgg2.pixel[i][j];
			}
			liberationTableau(&histo);
			histo = histogrammeImage(img2, 0);
			nbPixApres = histo.data[255];
		}


	}

	liberationImage(&imgAgg);
	liberationImage(&imgAgg2);
	liberationTableau(&histo);
	return img2;
}