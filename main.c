#include <stdio.h>
#define INVENTORY_SIZE 10
#define INVENTORY_STRING_SIZE 15
#define PLAYER_DEFAULT 1
#define DAY_DEFAULT 1
#define HOUR_DEFAULT 8
#define DAY_LENGTH_HOURS 24

int checkInputInventory(char* message, char* errorMessage); // та же функция что checkInput, но с другими условиями проверки
int checkInput(char* message, char* errorMessage); // проверяет ввод на валидность 

int main()
{

	int current_day = DAY_DEFAULT; // день
	int current_hour = HOUR_DEFAULT; // час
	int inventory[INVENTORY_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // инвентарь
	char inventoryDescription[INVENTORY_SIZE][INVENTORY_STRING_SIZE] = {"empty", "seeds", "wood", "stone", "coal", "watering can", "axe", "hoe", "rake", "scythe"};
	int tempInput, tempInput2; // ну типа эта кароче эээ ну темпорари вариаблс
	int playerInput = PLAYER_DEFAULT;

	printf("Welcome to Happy Farmer(tm, all rights reserved, rated M for Mature)\n");

	while (playerInput != 0) // Главный цикл 
	{
		printf("\n0 - exit Happy  Farmer(tm)\n");
		printf("1 - check the time\n");
		printf("2 - work for X hours\n");
		printf("3 - check your inventory\n");
		printf("4 - put item in your inventory\n");
		printf("5 - remove item from inventory\n");
		printf("6 - find items heavier than X in your inventory\n\n");

		playerInput = checkInput("Option: ", "error! Please use a valid int! (press enter and retry)");

		switch (playerInput) // логика менюшки 
		{
		case 0: // выход
			printf("\nExiting...\n");
			break;
		case 1: // время
			printf("\n time: Day %d, %02d:00\n", current_day, current_hour); // смотрим на время

			break;
		case 2: // поработаем
			tempInput = checkInput("\nWork for how long (in hours)?: ", "error! Please use a valid int! (press enter and retry)"); // скока работаем

			current_hour += tempInput;

			if (current_hour > DAY_LENGTH_HOURS) // не ломаем время
			{
				current_day++;
				current_hour -= DAY_LENGTH_HOURS;
			}

			printf("\nWorked for %d hours...\n", tempInput);

			break;
		case 3: // смотрим инвентарь
			printf("\nYour inventory:\n");

			for (int i = 0; i < INVENTORY_SIZE; i++)
			{
				printf("Slot[%d]: %d (%s)\n", i, inventory[i], inventoryDescription[inventory[i]]); // наш инвентарь тута
			}

			break;
		case 4: // добавление предмета
			tempInput = checkInputInventory("\nWhat to put in? (0 - 9)", "error! Please use a valid int from 0 to 9! (press enter and retry)");
			tempInput2 = checkInputInventory("Where to put it in? (0 - 9)", "error! Please use a valid int from 0 to 9! (press enter and retry)");

			inventory[tempInput2] = tempInput;

			printf("\nput %s in inventory slot[%d]\n", inventoryDescription[tempInput], tempInput2);

			break;
		case 5: // удаление предмета
			tempInput = checkInputInventory("\nWhat slot to void? (0 - 9)", "error! Please use a valid int from 0 to 9! (press enter and retry)");
			
			printf("\nRemoved %s from inventory slot[%d]\n", inventoryDescription[tempInput], tempInput);
			
			inventory[tempInput] = 0;
			
			break;
		case 6: // поиск тяжестей
			tempInput = checkInputInventory("\nWhat item to compare with? (0 - 9)", "error! Please use a valid int from 0 to 9! (press enter and retry)");

			printf("\nItems in your inventory larger than %s:\n", inventoryDescription[tempInput]);

			for (int i = 0; i < INVENTORY_SIZE; i++)
			{
				if(inventory[i] > tempInput) printf("Slot[%d]: %d (%s)\n", i, inventory[i], inventoryDescription[inventory[i]]);
			}


			break;
		}
	}
	
	return 0;
}

int checkInputInventory(char* message, char* errorMessage)
{
	int input;
	printf("%s\n", message);
	while (scanf("%d", &input) != 1 || input > 9 || input < 0)
	{
		printf("%s", errorMessage);
		while (getchar() != '\n');
	}
	return input;
}

int checkInput(char* message, char* errorMessage)
{
	int input;
	printf("%s\n", message);
	while (scanf("%d", &input) != 1)
	{
		printf("%s", errorMessage);
		while (getchar() != '\n');
	}
	return input;
}