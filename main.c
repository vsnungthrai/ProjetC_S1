#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))	//Déplacement x,y

int nombre_article = 0;
int nombre_article_panier1 = 0;
int nombre_article_panier2 = 0;

char code_produit[12];
char code_for_del[12];

int main();
void affichage();
void affichage_panier();
void affichage_panier2();

//Tableau Fruits
char *fruit[15] = { "🍓", "🍇", "🍏", "🍎", "🍐", "🍊", "🥝", "🍋", "🥑", "🍅", "🍑", "🥭", "🍍", "🍅", "🍌" };
char *fruitcode[15] = { "F00", "F01", "F02", "F03", "F04", "F05", "F06", "F07", "F08", "F09", "F10", "F11", "F12", "F13", "F14" };
float fruitprix[15] = { 3.1, 4.1, 2.9, 2.2, 2.0, 3.1, 1.0, 2.5, 3.8, 2.5, 2.0, 1.6, 1.8, 3.7, 1.5 };

//Tableau Legumes
char *legumes[15] = { "🧅", "🌽", "🥦", "🌶", "🥕", "🍊", "🍠", "🍆", "🫑", "🫒", "🥜", "🍄", "🌿", "🍃", "🥥" };
char *legumescode[15] = { "L00", "L01", "L02", "L03", "L04", "L05", "L06", "L07", "L08", "L09", "L10", "L11", "L12", "L13", "L14" };
float legumesprix[15] = { 2.4, 2.1, 1.9, 2.8, 1.7, 2.1, 2.9, 1.9, 1.9, 3.1, 2.1, 2.5, 2.8, 2.3, 2.7 };

//Tableau Viandes
char *viande[15] = { "🍗", "🍖", "🥚", "🥩", "🍤", "🥓", "🍠", "🐓", "🌰", "🐟", "🧆", "🌭", "🍕", "🦀", "🦐" };
char *viandecode[15] = { "V00", "V01", "V02", "V03", "V04", "V05", "V06", "V07", "V08", "V09", "V10", "V11", "V12", "V13", "V14" };
float viandeprix[15] = { 3.2, 3.9, 4.3, 3.8, 4.9, 5.0, 5.1, 2.3, 3.8, 4.0, 5.4, 3.1, 4.3, 4.8, 5.1 };

//Tableau pour les coordornées du panier 1
int ypanier1[9] = { 45, 49, 53, 45, 49, 53, 45, 49, 53 };
int xpanier1[9] = { 28, 28, 28, 27, 27, 27, 26, 26, 26 };

//Tableau pour les coordornées du panier 2
int ypanier2[9] = { 67, 71, 75, 67, 71, 75, 67, 71, 75 };
int xpanier2[9] = { 28, 28, 28, 27, 27, 27, 26, 26, 26 };

//Tableau pour les elements du panier 1 et 2
char *iconeproduitpanier1[10];
char *codeproduitpanier1[10];
float prixproduitpanier1[20];

char *iconeproduitpanier2[10];
char *codeproduitpanier2[10];
float prixproduitpanier2[20];

//Fonction qui gère l'affichage
void affichage()
{
	system("clear");
	system("cat Affichage.txt");
}

//Affichage panier 1
void affichage_panier()
{
	if (nombre_article_panier1 > 0)
	{
		int i;
		for (i = 1; i <= nombre_article_panier1; i++)
		{
			int x = xpanier1[i - 1];
			int y = ypanier1[i - 1];
			gotoxy(y, x);
			printf("%s", iconeproduitpanier1[i - 1]);
		}
	}
}

//Fonction qui va generer un nombre aleatoir pour quelle panier ajouter l'element
int aleatoire()
{
	srand(time(NULL));
	int nbgen = rand() % 2 + 1;

	if (nbgen == 1)
	{

		if (nombre_article_panier1 <= 8)
		{
			return nbgen;
		}
		else

		{
			return 2;
		}
	}

	if (nbgen == 2)
	{
		if (nombre_article_panier2 <= 8)
		{
			return nbgen;
		}
		else

		{
			return 1;
		}
	}
}

// Fonction qui gere la caisse
void caisse()
{
	affichage_panier();
	affichage_panier2();
	float reste;
	float total;
	float monnaie;
	gotoxy(100, 34);
	int i;
	for (i = 0; i <= 10; i++)
	{
		total += prixproduitpanier1[i];
		total += prixproduitpanier2[i];
	}
	
	printf("%.2f", total);
	gotoxy(107, 35);
	scanf("%f", &monnaie);
	if (monnaie >= total)
	{
		reste = monnaie - total;
		gotoxy(93, 36);
		printf("%.2f", reste);
		gotoxy(0, 50);
		exit(EXIT_SUCCESS);
	}
	else
	{
		affichage();
		gotoxy(50, 39);
		reste = total - monnaie;
		printf("Il vous manque %.2f €", reste);
		affichage_panier();
		affichage_panier2();
		caisse();
	}
}

//Fonction Panier 1
void panier1(char *icone, char *code, float prix)
{
	iconeproduitpanier1[nombre_article_panier1] = icone;
	codeproduitpanier1[nombre_article_panier1] = code;
	prixproduitpanier1[nombre_article_panier1] = prix;
	nombre_article_panier1++;
}

//Fonction Panier 2
void panier2(char *icone, char *code, float prix)
{
	iconeproduitpanier2[nombre_article_panier2] = icone;
	codeproduitpanier2[nombre_article_panier2] = code;
	prixproduitpanier2[nombre_article_panier2] = prix;
	nombre_article_panier2++;
}

//Fonction de comptage pour 3 elements max
int count_3_time(char *code)
{
	int i;
	int count = 0;
	for (i = 0; i <= nombre_article; i++)
	{
		if (codeproduitpanier1[i] == code)
		{
			count++;
		}
		if (codeproduitpanier2[i] == code)
		{
			count++;
		}
	}
	if (count >= 3)
	{
		gotoxy(48, 39);
		printf("Element deja present 3X ! ");
		main();
	}
}

//Affichage panier 2 (permanent)
void affichage_panier2()
{
	if (nombre_article_panier2 > 0)
	{
		int i;
		for (i = 1; i <= nombre_article_panier2; i++)
		{

			int x = xpanier2[i - 1];
			int y = ypanier2[i - 1];
			gotoxy(y, x);
			printf("%s", iconeproduitpanier2[i - 1]);
		}
	}
}

//Fonction pour supprimer element
void delete()
{
	int num_of_panier_for_del;
	int i, k;
	int indice;
	gotoxy(24, 36);
	printf(" ");
	scanf("%d", &num_of_panier_for_del);
	gotoxy(26, 36);
	printf(" ");
	scanf("%s", code_for_del);
	if (num_of_panier_for_del == 1)
	{
		indice = -1;
		for (i = 0;
			(i < 15) && (indice == -1); i++)
		{
			if (strcmp(codeproduitpanier1[i], code_for_del) == 0)
			{
				indice = i;
				for (k = indice; k < nombre_article_panier1; k++)
				{
					if (k < nombre_article_panier1)
					{
						iconeproduitpanier1[k] = iconeproduitpanier1[k + 1];
						codeproduitpanier1[k] = codeproduitpanier1[k + 1];
						prixproduitpanier1[k] = prixproduitpanier1[k + 1];
					}
				}
			}
		}
		nombre_article_panier1--;
	}
	if (num_of_panier_for_del == 2)
	{
		indice = -1;
		for (i = 0;
			(i < 15) && (indice == -1); i++)
		{
			if (strcmp(codeproduitpanier2[i], code_for_del) == 0)
			{
				indice = i;
				for (k = indice; k < nombre_article_panier2; k++)
				{
					if (k < nombre_article_panier2)
					{
						iconeproduitpanier2[k] = iconeproduitpanier2[k + 1];
						codeproduitpanier2[k] = codeproduitpanier2[k + 1];
						prixproduitpanier2[k] = prixproduitpanier2[k + 1];
					}
				}
			}
		}

		nombre_article_panier2--;
	}
	nombre_article--;
	main();
}

//Fonction pour l'ajout des articles dans les tabeaux
void addtab(int location)
{
	char *icone;
	char *code;
	float prix;
	int i;
	int alea = aleatoire();

	for (i = 0; i < 15; i++)
	{
		if (strcmp(fruitcode[i], code_produit) == 0)
		{

			icone = fruit[location];
			code = fruitcode[location];
			prix = fruitprix[location];
			count_3_time(code);
			if (alea == 1)
			{
				panier1(icone, code, prix);
			}
			else
			{
				panier2(icone, code, prix);
			}

			nombre_article++;
			main();
		}

		if (strcmp(legumescode[i], code_produit) == 0)
		{

			icone = legumes[location];
			code = legumescode[location];
			prix = legumesprix[location];
			count_3_time(code);
			
			if (alea == 1)
			{
				panier1(icone, code, prix);
			}
			else
			{
				panier2(icone, code, prix);
			}

			nombre_article++;
			main();
		}

		if (strcmp(viandecode[i], code_produit) == 0)
		{

			icone = viande[location];
			code = viandecode[location];
			prix = viandeprix[location];
			count_3_time(code);

			if (alea == 1)
			{
				panier1(icone, code, prix);
			}
			else
			{
				panier2(icone, code, prix);
			}

			nombre_article++;
			main();
		}
	}
}

int main()
{
	while (nombre_article < 18)
	{
		system("PAUSE");
		affichage();
		affichage_panier();
		affichage_panier2();
		gotoxy(21, 36);
		int i;
		scanf("%s", code_produit);
		if (strcmp("SUP", code_produit) == 0)
		{
			delete();
		}

		if (strcmp("FIN", code_produit) == 0)
		{
			caisse();
		}
		
		for (i = 0; i < 15; i++)
		{
			if (strcmp(fruitcode[i], code_produit) == 0 || strcmp(legumescode[i], code_produit) == 0 || strcmp(viandecode[i], code_produit) == 0)
			{
				addtab(i);
			}
		}
		
		for (i = 0; i < 15; i++)
		{
			if (strcmp(fruitcode[i], code_produit) != 0 || strcmp(legumescode[i], code_produit) != 0 || strcmp(viandecode[i], code_produit) != 0)
			{
				gotoxy(48, 39);
				printf("Element introuvable");
				main();
			}
		}
	}
	caisse();

}
