#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
// Test
// Macros
#define INPUT_SIZE 80

// Global Variables

// Events
bool eGameStarted, eWindowOpen, eWoodDoorOpen, eSteelDoorOpen, eHoleOpen, eGnomeDied, eFridgeOpen, eTVOn, eDoorOpenerGot;

// Game
bool gaming = true;
unsigned short int whyNotGaming = 0;
enum gmExitReason{
exitPlayerQuit,
exitPlayerDied,
exitGameWon
};

// Input
char input[INPUT_SIZE];

// Inventory
enum gmItem{
itemDoorOpener = 1,
itemInvisObject = 2,
itemMilk = 3,
itemNothing = 4
};
const char *gmItemName[] = {
"Nothing",
"Mystical Door Opening Device",
"Invisible Object",
"Milk",
"Literally Nothing"
};

unsigned short int inventory[10];

// Location
enum gmArea{
areaBedroom = 1,
areaBackyard = 2,
areaHall = 3,
areaFrontDoor = 4,
areaLawn = 5,
areaDiningRoom = 6,
areaHole = 7,
areaWHAT = 8,
areaHell = 9
};

unsigned short int area = areaWHAT;




// Function Prototypes
void gmLoopBedroom();
void gmLoopBackyard();
void gmLoopHall();
void gmLoopFrontDoor();
void gmLoopLawn();
void gmLoopDiningRoom();
void gmLoopHole();
void gmLoopHell();

// Functions
bool psaid(const char* str)
{
	return strcmp(input, str) == 0;
}

int getInventorySize()
{
	int i = 0;
	while (inventory[i] != 0)
	{
		i ++;
		if (i == 10)
			break;
	}
	return i;
}

void addInventoryItem(const unsigned short int item)
{
	int size = getInventorySize();
	if (size < 10)
	{
		inventory[getInventorySize()] = item;
	}
	else
	{
		printf("The item was not added to your inventory because your inventory is full (greater than 10).\nHow the heck did that happen!?!?\n");
	}
}

int showInventory()
{
	// Printing the first inventory item
	if (inventory[0] != 0)
	{
		printf("%s", gmItemName[inventory[0]]);
	}
	else
	{
		printf("You have no items!?!?!?!?\n");
		return 0;
	}
	
	// Printing the rest
	int size = getInventorySize();
	for (int i = 1; i < size; i ++)
	{
		if (inventory[i] != 0)
			printf(", %s", gmItemName[inventory[i]]);
		else
			break;
	}
	printf("\n");
	return 0;
}

void searchArea(unsigned short int area)
{
	switch (area)
	{
		case areaBedroom:
		{
			printf("The room is incredibly small, has a shitty carpet flooring, and blue painted walls. There is a lamp, window, closet, and two doors. One door is made of wood, the other seems to be made of steel. On the bottom of the steel door, you spot an etched word that reads: \"pee pee\"\n");
			break;
		}
		case areaHole:
		{
			printf("The place is quite damp and dark, but dimly lit light-blue by some unknown force. There is a mound of dirt, dirt walls, and a steel door. Smells good in here!\n");
			break;
		}
		default:
		{
			printf("Where... are you?\n");
			break;
		}
	}
}
char* getAreaName(unsigned short int area)
{
	char* str = malloc(20);
	switch (area)
	{
		case areaBedroom: strcpy(str, "BEDROOM"); break;
		default:
		{
			strcpy(str, "TITLESCREEN");
			break;
		}
	}
	return str;
}

int tryGlobalCommand(char *command)
{
	if (strcmp(command, "help") == 0)
	{
		printf("Some generic commands for you bros:\n");
		printf("search - list all of the interactable elements in the area\n");
		printf("search <object> - examine an object further\n");
		printf("open <object> - open a thing, duh\n");
		printf("close <object> - close a thing, duh\n");
		printf("get <object> - take a thing, duh\n");
		printf("use <object> - use a thing, duh\n");
		printf("use <object> on <object> - use a thing on a thing!\n");
		printf("inventory - show what items you have\n");
		printf("time - show the current time\n");
		printf("clear - clear the screen\n");
		printf("exit - exit the game........ d u h\n");
		printf("\n");
		printf("These are not all of the commands you can use. If you think you can do something, just try it.\n");
		return 1;
	}
	else if (strcmp(command, "exit") == 0)
	{
		gaming = false;
		whyNotGaming = exitPlayerQuit;
		return 1;
	}
	else if (strcmp(command, "search") == 0)
	{
		searchArea(area);
		return 1;
	}
	else if (strcmp(command, "inventory") == 0)
	{
		showInventory();
		return 1;
	}
	else if (strcmp(command, "clear") == 0)
	{
		system("clear");
		return 1;
	}
	else if (strcmp(command, "") == 0)
	{
		printf("What was that? Speak up, son.\n");
		return 1;
	}
	
	return 0;
}

// Printing
void printUnknownCommand(const char* str){ printf("What exactly is a %s?\n", str); }
void printOpen(const char* str){ printf("The %s is already open.\n", str); }
void printOpening(const char* str){ printf("You open the %s.\n", str); }
void printClosed(const char* str){ printf("The %s is already closed.\n", str); }
void printClosing(const char* str){ printf("You close the %s.\n", str); }

// Player Input
void pinput()
{
	char* location = getAreaName(area);
	printf("DUDE AT %s > ", location);
	free(location);

	fgets(input, INPUT_SIZE, stdin);
	input[strlen(input)-1] = '\0';
}

// Loops
void gmLoopBedroom()
{
	if (!eGameStarted)
	{
		printf("You wake up at the crack of dawn. Zombies are roaming the streets. You hear loud sirens blaring off in the distance, and also your thumb kind of hurts. People in the neighborhood are screaming, and you can hear the startling shatter of wood, presumably by your front door. Seems like a good time to get some milk.\nWhat do? Type help for some help.\n");
		eGameStarted = true;
	}
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("search lamp"))
		{
			printf("It looks quite edible if I do say so myself.\n");
		}
		else if (psaid("eat lamp"))
		{
			printf("Eat the lamp? What? You're crazy!\n");
		}
		else if (psaid("search window"))
		{
			printf("Outside the window is your backyard. Looking outside, you can tell that your room is placed high above the ground.\n");
		}
		else if (psaid("open window"))
		{
			if (eWindowOpen)
				printOpen("window");
			else
			{
				printf("You open the window. The smell of air hits you HARD.\n");
				eWindowOpen = true;
			}
		}
		else if (psaid("close window"))
		{
			if (eWindowOpen)
			{
				printf("You close the window. The smell of air must've really gotten to you.\n");
				eWindowOpen = false;
			}
			else
				printClosed("window");
		}
		else if (psaid("jump out window"))
		{
			if (eWindowOpen)
			{
				area = areaBackyard;
				printf("You jump out of your bedroom window and land in your wet and grassy backyard, breaking your legs in the process. It's raining if you couldn't tell\n");
			}
			else
			{
				printf("You run up to the window and jump... and hit your head on the glass since it's closed. You immediately die on impact with the glass because that makes sense.\n");
				gaming = false;
				whyNotGaming = exitPlayerDied;
			}
			break;
		}
		else if (psaid("search wooden door"))
		{
			printf("It looks quite malleable and smelly. Since you've lived in this house your whole life, you know it leads to a hallway.\n");
		}
		else if (psaid("open wooden door"))
		{
			if (eWoodDoorOpen)
				printOpen("door");
			else
			{
				printOpening("door");
				eWoodDoorOpen = true;
			}
		}
		else if (psaid("close wooden door"))
		{
			if (eWoodDoorOpen)
			{
				printClosing("door");
				eWoodDoorOpen = false;
			}
			else
				printClosed("door");
		}
		else if (psaid("go through wooden door"))
		{
			if (eWoodDoorOpen)
			{
				printf("You walk through the door and enter the hallway outside your room.\n");
				area = areaHall;
				break;
			}
			else
			{
				printf("You run towards the door at full speed white it's closed, reslting in a massive head-on collision with the door's deadly wooden surface. It was an injury from which you would never recover. The next day, the city council reported that you had died bruh.\n");
				gaming = false;
				whyNotGaming = exitPlayerDied;
				break;
			}
		}
		else if (psaid("search under closet"))
		{
			if (!eDoorOpenerGot)
			{
				printf("You uncover a mystical door opening device. You grab it.\n");
				eDoorOpenerGot = true;
				addInventoryItem(itemDoorOpener);
			}
			else
			{
				printf("There was once a mystical door opening device under here.\nSome weirdo must have taken it.\n");
			}
			break;
		}
		else if (psaid("search closet"))
		{
			printf("Long ago ur mom locked this closet with the key and then using black magic put the key inside of it rendering the entire object useless.\n");
		}
		else if (psaid("search steel door"))
		{
			printf("It door.\n");
		}
		else if (psaid("use mystical door opening device on steel door"))
		{
			if (eDoorOpenerGot)
			{
				if (!eSteelDoorOpen)
				{
					printf("DOOR OPENED.\n");
					eSteelDoorOpen = true;
				}
				else
				{
					printf("DOOR ALREADY OPENED.\n");
				}
			}
			else
			{
				printUnknownCommand(input);
			}
		}
		else if (psaid("open steel door"))
		{
			if (!eSteelDoorOpen)
			{
				printf("It won't budge.\n");
			}
			else
			{
				printOpen("steel door you just opened with your mystical door opening device that opens doors");
			}
		}
		else if (psaid("close steel door"))
		{
			if (eSteelDoorOpen)
			{
				printClosing("door");
				eSteelDoorOpen = false;
			}
			else
			{
				printClosed("door");
			}
		}
		else if (psaid("go through steel door"))
		{
			if (eSteelDoorOpen)
			{
				area = areaHole;
				printf("You enter a dark dirt corridor with a mound of dirt at the end.\n");
				break;
			}
			else
			{
				printf("You walk into the closed steel door. Ow.\n");
			}
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopBackyard()
{
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopHall()
{
	
}
void gmLoopFrontDoor()
{
	
}
void gmLoopLawn()
{
	
}
void gmLoopDiningRoom()
{
	
}
void gmLoopHole()
{
	printf("You feel like you're doing something wrong.\n");
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("search mount of dirt") && !eHoleOpen)
		{
			printf("Written in pink, soapy crayon on the dirt:\nHELLO BRO. PLEASE SAY AN FUNNY WORDT TO GET THROUGH! :^))\n");
		}
		else if (psaid("search walls of dirt"))
		{
			printf("That's dirt all right.\n");
		}
		else if (psaid("soap") || psaid("spoon") || psaid("sick") || psaid("slick") || psaid("soup") || psaid("soam"))
		{
			if (!eHoleOpen)
			{
				printf("The mound of dirt comes to life and says:\nTHAMK YOU MAN. I WILL MOVE OUT OF THWAY NOW.\n\n\nA dark hole was left in the mound of dirt's place.\n");
				eHoleOpen = true;
			}
			else
			{
				printf("That's nice man.\n");
			}
		}
		else if (psaid("go through hole"))
		{
			area = areaHell;
			printf("You've entered a secret portal to hell.\n");
			break;
		}
		else if (psaid("search steel door"))
		{
			printf("It DOOR, enough said.\n");
		}
		else if (psaid("open steel door"))
		{
			printOpen("door");
		}
		else if (psaid("close steel door"))
		{
			printf("You don't feel comfortable locking yourself in this place.\n");
		}
		else if (psaid("use mystical door opening device on steel door"))
		{
			printf("Nothing happened because it's open already.\n");
		}
		else if (psaid("go through steel door"))
		{
			printf("You leave the dirty hall and enter the bedroom.\n");	
			area = areaBedroom;
			break;
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopHell()
{
	
}

// Game Start
void gmLoop()
{
	// Get start input from player
	while (1)
	{
		pinput();
		if (strcmp(input, "start") == 0)
		{
			break;
		}
		else if (strcmp(input, "die") == 0)
		{
			printf("Y o u   D i e d .\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else
		{
			printf("Dude... type S T A R T, START.\n");
		}
	}
	
	area = areaBedroom;
	
	// Loop through areas of the world
	while (gaming)
	{
		switch (area)
		{
			case areaBedroom: gmLoopBedroom(); break;
			case areaBackyard: gmLoopBackyard(); break;
			case areaHall: gmLoopHall(); break;
			case areaFrontDoor: gmLoopFrontDoor(); break;
			case areaLawn: gmLoopLawn(); break;
			case areaDiningRoom: gmLoopDiningRoom(); break;
			case areaHole: gmLoopHole(); break;
			case areaHell: gmLoopHell(); break;
			default:
			{
				printf("...dude where the HECK are you? I'm gonna end the game ok.\n");
				gaming = false;
				whyNotGaming = 2022;
				break;
			}
		}
	}
}

// Main
int main(void)
{
	// Title
	system("clear");
	printf("      MILK.C\n  a game where u\ntry to drink milk\n       fast\n\ntype start to start\nand die to die\n");
	
	// Starting to Game
	gmLoop();
	
	// Exiting Game
	switch (whyNotGaming)
	{
		case exitPlayerQuit:
		{
			printf("You think you can quit this easily? HUH!?!?!?\nWell guess what, you can. Bye bye.\n");
			break;
		}
		case exitPlayerDied:
		{
			printf("You died? Lmao, get soaped my guy!\nTHE END\n");
			break;
		}
		case exitGameWon:
		{
			printf("YOOOOOOOOO you win thanks for playing!\n");
			break;
		}
		default:
		{
			printf("Not sure why you stopped gaming... but thanks for playing.\n");
			break;
		}
	}
	return 0;
}
