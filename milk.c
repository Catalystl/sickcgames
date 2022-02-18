#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Macros
#define INPUT_SIZE 80

// Global Variables

// Time
time_t timeGameBegan, timeLawnEntered, timeMilkFell;

// Events
bool eGameStarted, eWindowOpen, eWoodDoorOpen, eSteelDoorOpen, eHoleOpen, eGnomeDied, eFridgeOpen, eTVOn, eDoorOpenerGot, eThisGuyDead, eGateOpen, eFenceBroken, eGapStairsSide, eStaredAtPainting, eSpeedrunning, eMeteorCrashed, eLawnZombDead, eTreeItemGot, eGnome2Died, eFortEntered, eGnome2Happy, eGnome2Met;

// Complicated Events

/* milkFallState - determines the state of falling milk
 * 0 = milk hasn't fallen yet
 * 1 = milk is falling
 * 2 = milk has finished falling
 * 3 = player failed to catch the milk
 */
unsigned short int milkFallState = 0;

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
itemPlotholer = 4,
itemSMedal = 5,
itemMoney = 6,
itemBagels = 7,
itemShovel = 8,
itemGlass = 9,
itemMilkGlass = 10
};
const char *gmItemName[] = {
"Nothing",				//1
"Mystical Door Opening Device",
"Invisible Object",
"Milk",
"The Plotholer",
"Spongebob Medal",			//5
"One Million Dollars",
"Bagel Collection",
"Shovel",
"Glass",
"GLASS OF MILK"				//10
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
areaHell = 9,
areaFort = 10
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
void gmLoopFort();

// Functions

// String uppercasing/lowercasing
void strupr(char* str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i ++)
	{
		str[i] = toupper(str[i]);
	}
}
void strlwr(char* str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i ++)
	{
		str[i] = tolower(str[i]);
	}
}

// Read Player Input
bool psaid(char* str)
{
	strlwr(input);
	return strcmp(input, str) == 0;
}

// Inventory
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

bool hasInventoryItem(const unsigned short int item)
{
	int size = getInventorySize();
	for (int i = 0; i < size; i ++)
	{
		if (inventory[i] == item)
			return true;
	}
	return false;
}

// Searching
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
		case areaHell:
		{
			printf("This place looks like the nether from Minecraft. It's also pretty hot, also look at that there's fire and... aw shit it's consumed you.\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		case areaBackyard:
		{
			printf("There's a lotta rain, maybe munsters too, just kidding though there is no truth to that last remark. It's a little dark outside and everything looks gloomy. There is long grass, a tiny lake, a fence, and a gate. The fence separates your backyard from other peoples' backyards.\n"); 
			break;
		}
		case areaHall:
		{
			printf("The hall is very run down, only illuminated by a lightbulb tangling from the cieling from a tiny string. The floor is made of dark wood and the walls are covered with a dark green carpet-like pattern. There is a crack in the floor, a painting, stairs that lead to the front door, and a locked door.\n");
			break;
		}
		case areaFrontDoor:
		{	
			printf("You are standing at a small section of the house close to the stairs, front door, and hallway to the dining room. There's a zombie on the ground also.\n");
			break;
		}
		case areaLawn:
		{
			printf("You're standing in your lawn. There's a ravine where the street once was and a zombie that will reach you in about 60 seconds. There's also the front door to your house and a tree.");
			if (eMeteorCrashed)
				printf(" And also a meteor.");
			printf("\n");
			break;
		}
		case areaDiningRoom:
		{
			printf("This is the only somewhat-nice looking room in your house, but still looks like a liminal space. There is a fridge, table, black hole, and TV.\nYou're pretty sure this is where the milk is.\n");
			break;
		}
		case areaFort:
		{
			printf("There is a huge stack of cardboard boxes that I guess you could call a fort. In the midst of the pile, you spot an opening where ");
			if (eGnome2Died)
				printf("that gnome you killed is on the verge of slipping from.");
			else
				printf("a lone gnome stands.");
			printf("\n");
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
		case areaBackyard: strcpy(str, "BACKYARD"); break;
		case areaHall: strcpy(str, "HALL"); break;
		case areaHole: strcpy(str, "???"); break;
		case areaHell: strcpy(str, "HELL"); break;
		case areaFrontDoor: strcpy(str, "FRONT DOOR"); break;
		case areaDiningRoom: strcpy(str, "DINING ROOM"); break;
		case areaLawn: strcpy(str, "LAWN"); break;
		case areaFort: strcpy(str, "BOX FORT"); break;
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
	else if (strcmp(command, "time") == 0)
	{
		printf("You have been searching for milk for %ld seconds.\n", time(NULL) - timeGameBegan);
		return 1;
	}
	else if (strcmp(command, "use the plotholer") == 0) // Item Uses
	{
		if (hasInventoryItem(itemPlotholer))
		{
			printf("Milk bruhs out of thin air into your hands. You drink it.\n[PLOTHOLEC] PLOT SUCCESSFULLY HOLED, exit code 0\n[PLOTHOLEC] WARNING: holes in reality may be unintentionally opened\n");
			gaming = false;
			whyNotGaming = exitGameWon;
			return 1;
		}
		else
			return 0;
	}
	else if (strcmp(command, "drink milk") == 0)
	{
		if (hasInventoryItem(itemMilk))
			printf("Woah woah woah are you some kind of uncivilized freak? We pour milk into glasses here before we drink them, thank you very much.\n");
		else
			printf("No.\n");
		
		return 1;
	}
	else if (strcmp(command, "drink glass of milk") == 0)
	{
		if (hasInventoryItem(itemMilkGlass))
		{
			printf("You drink milk.\n");
			gaming = false;
			whyNotGaming = exitGameWon;
		}
		else
			printf("NO.\n");

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

	if (eSpeedrunning)
		printf("%s %ld > ", location, time(NULL) - timeGameBegan);
	else
		printf("DUDE AT %s > ", location);
	
	free(location);

	fgets(input, INPUT_SIZE, stdin);
	input[strlen(input)-1] = '\0';
}
// Player Input (talking)
void pinputt()
{
	printf("YOUR RESPONSE > ");
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
				printf("You jump out of your bedroom window and land in your wet and grassy backyard, breaking your legs in the process. It's raining if you couldn't tell.\n");
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
				eGapStairsSide = false;
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
		else if (psaid("break steel door"))
		{
			printf("You punch it.\nOw.\nNothing happened.\n");
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
		else if (psaid("dig") && hasInventoryItem(itemShovel))
		{
			printf("That command is too straight-forward.\n");
		}
		else if (psaid("use shovel on dirt") && hasInventoryItem(itemShovel))
		{
			if (hasInventoryItem(itemBagels))
			{
				printf("You already did that.\n");
			}
			else
			{
				printf("You find the box fort gnome's bagels.\n");
				addInventoryItem(itemBagels);
			}
		}
		else if (psaid("search grass"))
		{
			printf("You find a note that reads:\nI've been constructing many devices my son must not be aware of. One of them is my genius door opening device, which I hid under his closet. He'll never find it, unless this note exposing all of my secrets for absolutely no reason somehow ends up in his hands.\nThe rest of the note is torn or soaked with water.\n");
		}
		else if (psaid("search lake"))
		{
			printf("The lake is incredibly shallow but spans much of the backyard. Like the 3 year old you mentally are, you think it looks fun to splash in.\n");
		}
		else if (psaid("splash in lake"))
		{
			printf("When you reach the lake, you slip and fall face forwards into it. Due to the frailness of your body form eating nothing but egg seeds all day for the past 25 years, you lack the strength the get up, and lie there until you drown.\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else if (psaid("search fence"))
		{
			if (eFenceBroken)
			{
				printf("It toppled, dude.\n");
			}
			else
			{
				printf("It's made of flimsy wood. It looks like it could easily be knocked down, though you might not want to wreck it since you'll probably alert zombies to your location.\n");
			}
		}
		else if (psaid("knock over fence"))
		{
			if (eFenceBroken)
			{
				printf("You tap the knocked over fence. All of a sudden, a huge FLASH OF LIGHT-Just kidding nothing happens.\n");
			}
			else
			{	
				printf("You tap the fence and it topples over like dominoes. On the other side is a million dollars.\n");
				eFenceBroken = true;
			}
		}
		else if (psaid("get million dollars"))
		{
			if (eFenceBroken && !hasInventoryItem(itemMoney))
			{
				printf("You pick up the money.\n");
				addInventoryItem(itemMoney);
			}
			else
				printUnknownCommand(input);
		}
		else if (psaid("search gate"))
		{
			printf("It leads to your front lawn.\n");
		}
		else if (psaid("go through gate"))
		{
			if (eGateOpen)
			{
				printf("You enter your front lawn.\n");
				area = areaLawn;
				break;
			}
			else
			{
				printf("You walk into the gate, shattering your entire face and body and everything, also breaking open the gate in the process. Due to the amount of radioactive soaps, salts, and bagels in the surrounding area, the shatter caused a rift in time, two dimensions have been created from one, one where your clanking against the gate startles a bird, and one where that bird is not startled. In the dimension where the bird was startled, it flew to a tree that knocked over a leaf that blew into a can of beans. The high crystal content of the beans caused both dimensions to merge. The high council spotted this and worked quickly to stich the universe back together, rewinding time to the point where you hadn't broken the gate and your face. A team of spoon inspector-investigators detected the high spoon content of the nearby soil and eliminated the issue. They also opened the gate and mysticaly stopped it from ever being closed again.\n");
				eGateOpen = true;
			}
		}
		else if (psaid("open gate"))
		{
			if (eGateOpen)
			{
				printOpen("gate");
			}
			else
			{
				eGateOpen = true;
				printOpening("gate");
			}
		}
		else if (psaid("close gate"))
		{
			if (eGateOpen)
			{
				printf("you may not.\n");
			}
			else
			{
				printClosed("gate");
			}
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopHall()
{
	while (1)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("search crack"))
		{
			printf("This leads to a hole that probably never ends.\nI would not advise exploring it.\nAlso I just realized I probably should've named this a chasm or something because crack just implies it's a dent on the floor...\n");
		}
		else if (psaid("explore crack"))
		{
			printf("Dude, that's not a command bruh you use search for that crap.\n");
		}
		else if (psaid("go through crack"))
		{
			printf("You fall through the crack and are died.\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else if (psaid("jump over crack"))
		{
			printf("You jump over the crack in the floor.\n");
			if (eGapStairsSide)
			{
				eGapStairsSide = false;
				printf("You are now on the side of the hall close to the door to your bedroom.\n");
			}
			else
			{
				eGapStairsSide = true;
				printf("You are now on the side of the hall close to the stairs to the front door.\n");
			}
		}
		else if (psaid("smoke crack"))
		{
			printf("I'm gonna kill you for how unfunny you are.\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else if (psaid("i speak to the bruhs"))
		{
			gaming = false;
			whyNotGaming = 40;
			break;
		}
		else if (psaid("close wooden door"))
		{
			if (eWoodDoorOpen)
			{
				eWoodDoorOpen = false;
				printClosing("door");
			}
			else
				printClosed("door");
		}
		else if (psaid("open wooden door"))
		{
			if (eWoodDoorOpen)
				printOpen("door");
			else
			{
				eWoodDoorOpen = true;
				printOpening("door");
			}
		}
		else if (psaid("go through wooden door"))
		{
			if (eGapStairsSide)
			{
				printf("While walking to the door, you fall through the crack in the floor.\n");
				gaming = false;
				whyNotGaming = exitPlayerDied;
				break;
			}
			else
			{
				if (eWoodDoorOpen)
				{
					printf("You enter your bedroom.\n");
					area = areaBedroom;
					break;
				}
				else
				{
					printf("The door is closed my dude.\n");
				}
			}
		}
		else if (psaid("search painting"))
		{
			if (eStaredAtPainting)
			{
				printf("You stare at the soapy man further. The ground starts to shake. The soap in his eyes become soaked with suds.\nThe man jumps out of the painting and froze time.\n");
				gaming = false;
				whyNotGaming = 8;
				break;
			}
			else
			{
				printf("It's a painting of a guy with soap for eyes.\nYou feel like staring at this for longer will curse you somehow.\n");
				eStaredAtPainting = true;
			}
		}
		else if (psaid("search gnome"))
		{
			if (eGnomeDied)
			{
				printf("He ded.\n");
			}
			else
			{
				printf("It's a little tiny gnome bruh.\nYou walk up to get to get a closer look, and as you take another step he runs under your boot and.............. OH NO\n");
				eGnomeDied = true;
			}
			printf(":(\n");
		}
		else if (psaid("search locked door"))
		{
			printf("You find a post-it note stuck to the door, it reads:\nFiller.\n");
		}
		else if (psaid("search stairs"))
		{
			printf("It's a black spiral staircase made of wood that leads to your front door.\n");
		}
		else if (psaid("go down stairs"))
		{
			if (eGapStairsSide)
			{
				printf("You fall down the stairs, permanently damaging your internal organs.\n");
				area = areaFrontDoor;
				break;
			}
			else
			{
				printf("Since you were on the opposite side of the hallway to the stairs. You run into the crack in the floor and were never heard from again.\n");
				gaming = false;
				whyNotGaming = exitPlayerDied;
				break;
			}
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopFrontDoor()
{
	while (1)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("search front door"))
		{
			printf("It's broken.\n");
		}
		else if (psaid("search zombie"))
		{
			printf("It's dead, and has tons of splinters.\n");
		}
		else if (psaid("go up stairs"))
		{
			printf("You walk up the stairs.\n");
			area = areaHall;
			eGapStairsSide = true;
			break;
		}
		else if (psaid("search stairs"))
		{
			printf("Who gives a shit about stairs?\n");
		}
		else if (psaid("go through hall"))
		{
			printf("You walk down the hall.\n");
			area = areaFort;
			break;
		}
		else if (psaid("go through front door"))
		{
			printf("You step through the broken door and exit the house.\n");
			area = areaLawn;
			break;
		}
		else if (psaid("open front door") || psaid("close front door"))
		{
			printf("You touch the door knob, covered with splinters.\ngg mate.\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else if (psaid("search hall"))
		{
			printf("It stretches pretty long and you can't see the end of it, but you're pretty sure the dining room is down it somewhere\n");
			break;
		}
		else
		{
			printUnknownCommand(input);
		}
	}	
}
void gmLoopLawn()
{
	timeLawnEntered = time(NULL);

	while (gaming)
	{
		pinput();
		if (time(NULL) - timeLawnEntered >= 60 && !eLawnZombDead)
		{
			printf("You go ahead and-\nWait, nevermind, it's been 60 seconds so the zombie's killed you.\n");
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else if (tryGlobalCommand(input)){}
		else if (psaid("kill zombie"))
		{
			if (eLawnZombDead)
				printf("It's dead already.\n");
			else
			{
				printf("You kill the zombie. Nice job man.\n");
				eLawnZombDead = true;
			}
		}
		else if (psaid("search zombie"))
		{
			printf("It looks like it's about %ld seconds from reaching you.\n", 60 - (time(NULL) - timeLawnEntered));
		}
		else if (psaid("search front door") || psaid("open front door") || psaid("close front door"))
		{
			printf("It's broken.\n");
		}
		else if (psaid("go through front door"))
		{
			printf("You go through the door, also, I probably should've replaced every go through command with enter now that I think about it.\n");
			area = areaFrontDoor;
			break;
		}
		else if (psaid("open gate"))
		{
			if (eGateOpen)
				printOpen("gate");
			else
			{
				printOpening("gate");
				eGateOpen = true;
			}
		}
		else if (psaid("close gate"))
		{
			if (eGateOpen)
			{
				printClosing("gate");
				eGateOpen = false;
			}
			else
				printClosed("gate");
		}
		else if (psaid("go through gate"))
		{
			if (eGateOpen)
			{
				printf("You go through the gate. The zombie does not follow you through it.\n");
				area = areaBackyard;
				break;
			}
			else
			{
				printf("You walk into the closed gate, letting the zombie catch up to you by approximately 15 seconds, which might not make sense but shhhhhhhh\n");
				timeLawnEntered -= 15;
			}
		}
		else if (psaid("talk to zombie"))
		{
			printf("It responds:\n\"I'm gonna kill you. Sup.\"");
		}
		else if (psaid("search tree"))
		{
			printf("It's pretty tall but still looks climbable.\n");
		}
		else if (psaid("climb tree"))
		{
			if (eTreeItemGot)
			{
				printf("You climb the tree. From here you can see a couple of the houses around you. Most of them have been ahnillated by meteors.\n");
			}
			else
			{
				printf("You find a mysterious invisible and useless object in the tree. You grab it.\n");
				addInventoryItem(itemInvisObject);
				eTreeItemGot = true;
			}
		}
		else
		{
			printUnknownCommand(input);
		}
	}	
}
void gmLoopFort()
{
	if (!eFortEntered)
	{
		printf("You thought you'd eventually reach the dining room... but you seem to have run into a box fort.\n");
		eFortEntered = true;
	}
	
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("go through hall"))
		{
			printf("You make your way back to your front door.\n");
			area = areaFrontDoor;
			break;
		}
		else if (psaid("go through fort"))
		{
			if (eGnome2Died)
			{
				printf("You pass through the fort and enter the dining room with no problem.\n");
				area = areaDiningRoom;
				break;
			}
			else
			{
				if (eGnome2Happy)
				{
					printf("The gnome lets you through, you enter the dining room.\n");
					area = areaDiningRoom;
					break;
				}
				else
				{
					printf("The gnome spots you and speaks:\nI NEVER SAID YOU COULD DO THAT!!!!!!!!!!\n*He tackles you*\n");
					gaming = false;
					whyNotGaming = exitPlayerDied;		
				}
			}
			break;
		}
		else if (psaid("search gnome"))
		{
			if (eGnome2Died)
			{
				printf("He looks pretty dead.\n");
			}
			else
			{
				printf("He looks pretty pissed, but not that attentive. Maybe you could sneak past him.\n");
			}
		}
		else if (psaid("sneak past gnome"))
		{
			if (eGnome2Died)
			{
				printf("He's dead.\n");
			}
			else
			{
				printf("You begin to crawl on the ground, trying your hardest to not make the floorboards creak, but before you know it, the gnome rappels down from the cardboard and stabs you, ending your mission to secure some good ass milk.\nHA! That's what you get for trying to have fun pursuing an interesting path in this game!\n");
				gaming = false;
				whyNotGaming = exitPlayerDied;
				break;
			}
		}
		else if (psaid("kill gnome"))
		{
			if (eGnome2Died)
			{
				printf("He's already dead.\n");
			}
			else
			{
				printf("He suddenly falls down dead. Quite epic if I do say so myself!\n");
				eGnome2Died = true;
			}
		}
		else if (psaid("talk to gnome"))
		{
			if (eGnome2Died)
			{
				printf("He's dead.\n");
				continue;
			}

			if (eGnome2Met)
			{
				if (eGnome2Happy)
				{
					printf("The fucker speaks:\nI no longer have any use for you.\n");
				}
				else
				{
					if (hasInventoryItem(itemBagels))
					{
						printf("The gnome speaks:\nMIIIIINE!!!!!!\n*He grabs the sack of bagels out of your backpack or whatever the fuck you store your items in*\nYou may enter and exit the fort as you please now.\n");
						eGnome2Happy = true;
					}
					else
					{
						printf("The gnome speaks:\nYou've come back to me empty handed, huh?\nI have no use for idiots like you.\n*His eyes start to glow red and they start shooting lasers at you*\n");
						gaming = false;
						whyNotGaming = exitPlayerDied;
						break;
					}
				}
			}
			else
			{
				eGnome2Met = true;
				printf("In a deep, startling voice the gnome speaks:\nSTOP! Who are you?!\n");
				pinputt();
				char *pname;
				strcpy(pname, input);
				strupr(pname);
				printf("%s!? That's a dumb fucking name dude. So, you gonna work for me?\n", pname);
				pinputt();
				
				// Removing ? from the end of player's response	
				{
					int last = strlen(input) - 1;
					if (input[last] == '?')
					{
						input[last] = '\0';
					}
				}

				if (psaid("what") || psaid("what are you talking about") || psaid("what the fuck are you talking about"))
				{
					printf("Not so intelligent, are you? well... um, fuck you bitch.\n*The gnome chucks a miniature cardboard knife at you*\n");
					gaming = false;
					whyNotGaming = exitPlayerDied;
					break;
				}
				else if (psaid("yes") || psaid("i will") || psaid("of course"))
				{
					printf("Good.\nNow take this shovel and dig up my bagel collection in the backyard, slave!\n");	
				}
				else if (psaid("no") || psaid("fuck you"))
				{
					printf("Defiance will get you nowhere son.\n*Gnome shoves a cardboard box full of 10-ton soap weights onto you*\n");
					gaming = false;
					whyNotGaming = exitPlayerDied;
					break;
				}
				else
				{
					printf("...What? Get the fuck out of my face bitch, you have no use.\n*Gnome chucks soap at your eyes*\n");
					gaming = false;
					whyNotGaming = exitPlayerDied;
					break;
				}
				addInventoryItem(itemShovel);
			}
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopDiningRoom()
{
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("go through fort"))
		{
			printf("You leave the dining room.\n");
			area = areaFort;
			break;
		}
		else if (psaid("search black hole"))
		{
			printf("J4N65DL9185D8N8XC\n");
		}
		else if (psaid("go through black hole"))
		{
			printf("You d i i i e e e i i e e e i AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA.\n");
			area = areaWHAT;
			break;
		}
		else if (psaid("search tv"))
		{
			int num = rand() % 3;
			switch (num)
			{
				case 0:
				{
					printf("OMG SPONGEBOB IS ON THE TV!?!?!\n");
					if (!hasInventoryItem(itemSMedal))
						addInventoryItem(itemSMedal);
					break;
				}
				case 1:
				{
					printf("It's turned off???\n");
					break;
				}
				case 2:
				{
					printf("There's a show playing where a bunch of gnomes arrange themselves into the words:\nL O O K   U N D E R   Y O U R   C L O S E T\nF O R\nThe tv just shut off again.\n");
					break;
				}
			}
		}
		else if (psaid("turn on tv"))
		{
			printf("You go to turn on the tv and-WAIT... it's just turned on by itself again.\n");
		}
		else if (psaid("search fridge"))
		{
			if (eFridgeOpen)
			{
				if (hasInventoryItem(itemMilk))
				{
					printf("It's empty.\n");
				}
				else
				{
					printf("THERE'S MILK IN THERE OMG\n");
				}
			}
			else
				printf("It's closed, so you just stare at the fridge door.\n");
		}
		else if (psaid("search table"))
		{
			if (hasInventoryItem(itemGlass))
			{
				printf("There's nothing on it.\n");
			}
			else
			{
				printf("There's an empty glass on it.\n");
			}
		}
		else if (psaid("get glass"))
		{
			if (hasInventoryItem(itemGlass))
			{
				printf("No.\n");
			}
			else
			{
				printf("You grab the glass.\n");
				addInventoryItem(itemGlass);
			}
		}
		else if (psaid("open fridge"))
		{
			if (eFridgeOpen)
				printOpen("fridge");
			else
			{
				printOpening("fridge");
				eFridgeOpen = true;
			}
		}
		else if (psaid("close fridge"))
		{
			if (eFridgeOpen)
			{
				printClosing("fridge");
				eFridgeOpen = false;
			}
			else
				printClosed("fridge");
		}
		else if (psaid("get milk"))
		{
			if (eFridgeOpen)
			{
				if (hasInventoryItem(itemMilk))
				{
					printf("You already have milk.\n");
				}
				else
				{
					printf("You grab the milk. That's fucking epic.\n");
					addInventoryItem(itemMilk);
				}
			}
			else
				printf("You don't see any milk around here.\n");
		}
		else if (psaid("use milk on glass") || psaid("use glass on milk") || psaid("pour milk in glass"))
		{
			if (!hasInventoryItem(itemMilk))
			{
				printf("You don't have milk!?!?!?!\n");
				continue;
			}

			if (!hasInventoryItem(itemGlass))
			{
				printf("YOU DON'T HAVE A GLASS!?!?!?!?!?!?\n");
				continue;
			}

			switch (milkFallState)
			{
				case 0:
				{
					printf("Eager to drink some milk... YOU POUR THE MILK TOO QUICKLY AND DROP THE MILK!?!?!?!?\nType \"oh god save the milk\" to catch the milk before it hits the ground in approximately 6 seconds.\n");
					milkFallState = 1;
					timeMilkFell = time(NULL);
					break;
				}
				case 1:
				{
					printf("THE MILK IS IN THE MIDDLE OF FALLING WTF WHY ARE YOU TRYING TO POUR IT STILL!?!?!?\n");
					break;
				}
				case 2:
				{
					printf("You poured the milk into the glass slowly and carefully this time, and you were succesful. Now you have a glass of milk.\n");
					addInventoryItem(itemMilkGlass);
					break;
				}
				case 3:
				{
					printf("The milk has fallen, and it is no longer possible to construct a milk glass device out of it. This game, and your life, are over.\nBAD ENDING\n");
					gaming = false;
					whyNotGaming = exitPlayerDied;
					break;
				}
			}
		}
		else if (psaid("oh god save the milk"))
		{
			switch (milkFallState)
			{
				case 0:
				{
					printf("That hasn't happened yet wtf?\n");
					break;
				}
				case 1:
				{
					if (time(NULL) - timeMilkFell < 6)
					{
						printf("Y o u  s u c c e s s f u l l y   c a t c h   t h e   m i l k .\n");
						milkFallState = 2;
					}
					else
					{
						printf("It's too late. The milk has fully fallen.\n");
						milkFallState = 3;
					}
					break;
				}
				case 2:
				{
					printf("You just did that.\n");
					break;
				}
			}
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopHole()
{
	printf("You feel like you're doing something wrong.\n");
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("search mound of dirt") && !eHoleOpen)
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
				printf("The mound of dirt comes to life and says:\nTHAMK YOU MAN. I WILL MOVE OUT OF THWAY NOW.\n\nA dark hole was left in the mound of dirt's place.\n");
				eHoleOpen = true;
			}
			else
			{
				printf("That's nice man.\n");
			}
		}
		else if (psaid("go through hole"))
		{
			if (eHoleOpen)
			{
				area = areaHell;
				printf("You've entered a secret portal to hell.\n");
				break;
			}
			else
				printf("No.\n");
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
		else if (psaid("search hole"))
		{
			if (eHoleOpen)
			{
				printf("My advice?\nLisa the Painful OST - Don't Go in There\n");
			}
			else
				printf("What? That does not exist yet bro.\n");
		}
		else
		{
			printUnknownCommand(input);
		}
	}
}
void gmLoopHell()
{
	while (gaming)
	{
		pinput();
		if (tryGlobalCommand(input)){}
		else if (psaid("do a cool"))
		{
			area = areaWHAT;
			gaming = false;
			whyNotGaming = exitPlayerDied;
			break;
		}
		else if (psaid("kill this guy"))
		{
			if (!eThisGuyDead)
			{
				printf("Amidst the flames you make out some dark figure. You slap a couple times into the flames and he dissapears, guess he died or something. You pick up a legendary item: The Plotholer, that he dropped.\n");
				addInventoryItem(itemPlotholer);
				eThisGuyDead = true;
			}
			else
				printUnknownCommand(input);
		}
		else if (psaid("go through hole"))
		{
			printf("You find the hole by walking backwards into it.\nBack to that weird dirt hallway!\n");
			area = areaHole;
			break;
		}
		else
		{
			printUnknownCommand(input);
		}

	}
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
		else if (strcmp(input, "start speedrun") == 0)
		{
			eSpeedrunning = true;
			break;
		}
		else
		{
			printf("Dude... type S T A R T, START.\n");
		}
	}
	
	timeGameBegan = time(NULL);
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
			case areaFort: gmLoopFort(); break;
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
			printf("YOOOOOOOOO you win thanks for playing!\nTIME: %ld seconds\n", time(NULL) - timeGameBegan);
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
