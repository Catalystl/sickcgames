#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
	char* name;
	int hp;
} warrior;

char* getRandomName()
{
	char fn[10];
	char l1[10];
	char l2[10];

	// Getting First Name
	int num = rand() % 10;
	switch (num)
	{
		case 0:{strncpy(fn,"Slam ",sizeof(fn));break;}
		case 1:{strncpy(fn,"Plop ",sizeof(fn));break;}
		case 2:{strncpy(fn,"Crack ",sizeof(fn));break;}
		case 3:{strncpy(fn,"Sha ",sizeof(fn));break;}
		case 4:{strncpy(fn,"Bro ",sizeof(fn));break;}
		case 5:{strncpy(fn,"Shame ",sizeof(fn));break;}
		case 6:{strncpy(fn,"Croe ",sizeof(fn));break;}
		case 7:{strncpy(fn,"Trough ",sizeof(fn));break;}
		case 8:{strncpy(fn,"Sham ",sizeof(fn));break;}
		case 9:{strncpy(fn,"Farn ",sizeof(fn));break;}
	}

	// Getting Last Name Part 1
	num = rand() % 10;
	switch (num)
	{
		case 0:{strncpy(l1,"Man",sizeof(l1));break;}
		case 1:{strncpy(l1,"Iron",sizeof(l1));break;}
		case 2:{strncpy(l1,"Wod",sizeof(l1));break;}
		case 3:{strncpy(l1,"Harp",sizeof(l1));break;}
		case 4:{strncpy(l1,"Jack",sizeof(l1));break;}
		case 5:{strncpy(l1,"Frick",sizeof(l1));break;}
		case 6:{strncpy(l1,"Bro",sizeof(l1));break;}
		case 7:{strncpy(l1,"Card",sizeof(l1));break;}
		case 8:{strncpy(l1,"Chap",sizeof(l1));break;}
		case 9:{strncpy(l1,"Slap",sizeof(l1));break;}
	}

	// Getting Last Name Part 2
	num = rand() % 10;
	switch (num)
	{
		case 0:{strncpy(l2,"page",sizeof(l2));break;}
		case 1:{strncpy(l2,"snatch",sizeof(l2));break;}
		case 2:{strncpy(l2,"switch",sizeof(l2));break;}
		case 3:{strncpy(l2,"fist",sizeof(l2));break;}
		case 4:{strncpy(l2,"crack",sizeof(l2));break;}
		case 5:{strncpy(l2,"brap",sizeof(l2));break;}
		case 6:{strncpy(l2,"zick",sizeof(l2));break;}
		case 7:{strncpy(l2,"ran",sizeof(l2));break;}
		case 8:{strncpy(l2,"rod",sizeof(l2));break;}
		case 9:{strncpy(l2,"bro",sizeof(l2));break;}
	}
	
	// Concatenating Strings
	char* name = malloc(28 + 1);
	strcat(name, fn);
	strcat(name, l1);
	strcat(name, l2);
	return name;
}

void csleep(int secs)
{
	fflush(stdout);
	struct timespec ts = {0, 0.2 * secs * 1000000000};
	nanosleep(&ts, NULL);
}

int checkGnomeStatus(const warrior gnome, bool* battling)
{
	if (gnome.hp <= 0)
	{
		*battling = false;
		printf("%s was soaped!!!\n", gnome.name);
		csleep(4);
		return 2022;	
	}
	else
		return 0;
}

int getCharSum(char* str)
{
	int i = 0;
	int sum = 0;
	while (str[i] != '\0')
	{
		sum += (int) str[i];
		i ++;
	}
	return sum;
}

int main()
{
	// Opening Chatter
	system("clear");
	printf("Welcome! I have rich.\n");
	csleep(1);
	printf("NO!\n");
	csleep(2);
	printf(":)\n");
	csleep(1);

	// Welcome
	printf("\n\n\nWelcome to");
	csleep(1);
	printf(".");
	csleep(1);
	printf(".");
	csleep(1);
	printf(".");
	csleep(1);
	printf("   A SICK GAME.");
	csleep(2);
	printf("\n\n~ Gnome Warriors ~");
	csleep(1);
	printf("\n\n\n\n");
	csleep(1);

	// Player Sets seed
	printf("Before we begin though, please mash up to 40 characters to set a random seed: ");
	char seed[41];
	scanf("%[^\n]40s", seed);
	srand(getCharSum(seed));

	printf("\n\n");

	// Story
	printf("Gnomes have come to the far rock mountains to battle. Hello Soup.\nToday's warriors approach from a distance. Who could they be? ");
	csleep(1);
	printf(".");
	csleep(1);
	printf(".");
	csleep(1);
	printf(".\n");
	csleep(1);
	
	// Create Gnomes
	warrior gnome1 = {getRandomName(), 40};
	warrior gnome2 = {getRandomName(), 40};
	printf("WOAH IT'S %s!!!!!\n", gnome1.name);
	csleep(2);
	printf("AND %s!?!?!?!? NO WAY!!!!!!\n", gnome2.name);
	csleep(2);

	// Player Picks Bet
	printf("\nWho do you think will win? ");
	char betName[30];
	getchar();
	scanf("%[^\n]29s", betName);

	int bet = 0;
	if (strcmp(betName, gnome1.name) == 0){ bet = 1; }
	if (strcmp(betName, gnome2.name) == 0){ bet = 2; }

	if (bet != 0)
	{
		printf("Ah yes, %s! Quite a knowledgeable fellow. Well, let's see how he performs.\n", betName);
	}
	else
	{
		printf("...you ok dude? That gnome doesn't exist.\n");
		csleep(1);
		printf("...\n");
		csleep(1);
		printf("You know what? This is just gonna go nowhere.\n");
		csleep(1);
		printf("You have been kicked out of this executable file.\n");
		return 0;
	}

	// Battling Starts
	printf("\n*Gnomes prepare their weapons*\n\n");
	csleep(4);
	csleep(4);
	csleep(4);
	csleep(4);

	const char wait = 4;
	bool battling = true;
	while (battling)
	{
		system("clear");
		
		// Printing Gnome Hitpoints
		printf("%s\nHitpoints: %d\n\n%s\nHitoints: %d\n\n------------\n\n", gnome1.name, gnome1.hp, gnome2.name, gnome2.hp);

		// Gnome 1 Attacks
		printf("%s attacks!\n", gnome1.name);
		csleep(wait);
		int damage = 1 + rand() % 10;
		printf("%s took %d points of damage!\n", gnome2.name, damage);
		csleep(wait);
		gnome2.hp -= damage;
		
		if (checkGnomeStatus(gnome2, &battling) == 2022)
			continue;

		// Gnome 2 Attacks
		printf("%s attacks!\n", gnome2.name);
		csleep(wait);
		damage = 1 + rand() % 10;
		printf("%s took %d points of damage!\n", gnome1.name, damage);
		csleep(wait);
		gnome1.hp -= damage;

		if (checkGnomeStatus(gnome1, &battling) == 2022)
			continue;

		csleep(wait);
	}

	int whodead;
	if (gnome1.hp <= 0){ whodead = 1; }
       	if (gnome2.hp <= 0){ whodead = 2; }
	
	bet != whodead ? printf("You've won! Long live %s.\n", betName) : printf("Lmao you lose. Bye Bye.\n");	
	printf("SEED: %s\n", seed);
	return 0;
}
