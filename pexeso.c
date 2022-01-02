#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define CLEAR "clear"

typedef struct
{
	int index;
	bool uhodnuto;
} karta;

int pocet;
char *jmena[] = {"Karina", "Karin", "Karína", "Radmila", "Diana", "Dalimil", "Dalemil", "Melichar", "Baltazar", "Kašpar", "Wilhelmina", "Vilma", "Čestmír", "Vladan",
"Břetislav", "Bohdana", "Pravoslav", "Edita", "Radovan", "Alice", "Česlav", "Ctirad", "Drahoslav", "Vladislav", "Doubravka", "Ilona", "Běla", "Slavomír", "Zdenko",
"Hynek", "Nela", "Blažej", "Jarmila", "Dobromila", "Vanda", "Veronika", "Milada", "Apolena", "Mojmír", "Božena", "Slavěna", "Slávka", "Věnceslav", "Věnceslava",
"Valentýn", "Valentýna", "Jiřina", "Ljuba", "Miloslava", "Gizela", "Patrik", "Oldřich", "Eleonora", "Lenka", "Petr", "Svatopluk", "Matyáš", "Matěj", "Liliana", "Dorota",
"Alexandr", "Horymír", "Bedřich", "Bedřiška", "Anežka", "Kamil", "Stela", "Kazimír", "Míra", "Miroslav", "Tomík", "Tomáš"};

void vykreslikarty(karta karty[pocet])
{
	system(CLEAR);
	printf("     1  2  3  4  5  6  7  8  9  10 11 12\n");
	int index = 0;
	for (int i = 0; i < pocet; i++)
	{
		if (index%12 == 0)
		{
			printf("%d:", index+1);
			
			(index+1 < 10 ? printf("   "):
				index+1 < 100 ? printf("  "):
				printf(" "));
		}
		if (karty[i].uhodnuto) printf("   ");
		else printf("#  ");
		index++;
		if (index%12 == 0)
			printf(" :%d\n", index);
	}
}

void zadejpocet(int min, int max, char* hlaska, int *kam)
{
	do
	{
		printf("%s", hlaska);
		scanf("%d", kam);
	} while (!(*kam >= min && *kam <= max && *kam % 2 == 0));
}

void vygenerujkarty(karta karty[pocet])
{
	int index = 0;
	for (int i = 0; i < pocet; i += 2)
	{
		karty[i].index = index;
		karty[i].uhodnuto = false;
		karty[i+1].index = index;
		karty[i+1].uhodnuto = false;
		index++;
	}
}

void posunkarty(karta karty[pocet], int start, int skok)
{
	int posledni = (pocet - 1) - ((pocet - 1 - start) % skok);
	int posledni_hodnota = karty[posledni].index;

	for (int i = posledni; i > start; i -= skok)
	{
		karty[i].index = karty[i - skok].index;
	}
	karty[start].index = posledni_hodnota;
}

void zamichat(karta karty[pocet])
{
	int n = rand () % 4;
	for (int i = 0; i < n; i++)
		posunkarty(karty, 0, 3);

	n = rand () % 4;
	for (int i = 0; i < n; i++)
		posunkarty(karty, 1, 2);
}

bool hotovo(karta karty[pocet])
{
	for (int i = 0; i < pocet; i++)
	{
		if (!karty[i].uhodnuto) return false;
	}
	return true;
}

int zadej(char *hlaska)
{
	int a;
	do
	{
		printf("%s", hlaska);
		scanf("%d", &a);
	} while(!(a >= 1 && a <= pocet));
	return a;
}

void vyberkarty(karta karty[pocet])
{
	int a, b;
	printf("\n\n");
	a = zadej("Zadej 1. kartu, kterou si přeješ vybrat: ");a--;
	printf("%s\n", jmena[karty[a].index]);
	b = zadej("Zadej 2. kartu, kterou si přeješ vybrat: ");b--;
	printf("%s\n", jmena[karty[b].index]);

	if (karty[a].index == karty[b].index &&
		a != b)
	{
		karty[a].uhodnuto = true;
		karty[b].uhodnuto = true;
	}
}

int main()
{
	srand (time(NULL));
	zadejpocet(20, 144, "Zadej prosím počet karet [20 - 144]: ", &pocet);
	karta karty[pocet];
	vygenerujkarty(karty);
	for (int i = 0; i < 100; i++) zamichat(karty);


	int pokusy;
	for (pokusy = 0; !hotovo(karty); pokusy++)
	{
		vykreslikarty(karty);
		vyberkarty(karty);
		getchar();
		getchar();
	}
	system(CLEAR);
	printf("Výborně, vyhrál jsi, stálo tě to %d pokusů.\n", pokusy);
}