#include <stdio.h>
#include <string.h>
#define INVENTORY_SIZE 10
#define STRING_DEFAULT 33
#define PLAYER_DEFAULT 1
#define DAY_DEFAULT 1
#define HOUR_DEFAULT 8
#define DAY_LENGTH_HOURS 24
#define ERR_DEFAULT "error! Please use a valid int! (press enter and retry)"
#define ERR_DEFAULT_INV "error! Please use a valid int from 0 to 9! (press enter and retry)"

int checkInputInventory(char* message, char* errorMessage); // та же функция что checkInput, но с другими условиями проверки
int checkInput(char* message, char* errorMessage); // проверяет ввод на валидность
void timeCheck(int day, int hour); // смотрим время
void checkInventory(char inventoryDesc[][STRING_DEFAULT], int inventory[]); // смотрим инвентарь
void work(int* day, int* hour); // работаем 
void putItem(char inventoryDesc[][STRING_DEFAULT], int inventory[]); // кладём предметы
void removeItem(char inventoryDesc[][STRING_DEFAULT], int inventory[]); // убираем предметы
void comparer(char inventoryDesc[][STRING_DEFAULT], int inventory[]);
void searchItem(char inventoryDesc[][STRING_DEFAULT], int inventory[]);

int main()
{
	int current_day = DAY_DEFAULT; // день
	int current_hour = HOUR_DEFAULT; // час
	int inventory[INVENTORY_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // инвентарь
	char inventoryDescription[INVENTORY_SIZE][STRING_DEFAULT] = {"empty", "seeds", "wood", "stone", "coal", "watering can", "axe", "hoe", "rake", "scythe"};
	int tempInput, tempInput2; // ну типа эта кароче эээ ну темпорари вариаблс
	int playerInput = PLAYER_DEFAULT;
	char playerName[STRING_DEFAULT];
	FILE* fileItems = fopen("items.txt", "r");

	if (fileItems == NULL)
	{
		printf("error! No input.txt found, using default input\n");
	}
	else
	{
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (fgets(inventoryDescription[i], STRING_DEFAULT, fileItems) == NULL)
				break;  // файл короче 10 строк

			inventoryDescription[i][strcspn(inventoryDescription[i], "\r\n")] = '\0';
		}
		fclose(fileItems);
	}
	FILE* fileDiary = fopen("diary.txt", "a"); // Вот это всё надо будет прибрать в функцию записи или чёт такое

	if (fileDiary == NULL)
	{
		printf("error! No diary.txt found\n");
	}
	else
	{
		fclose(fileDiary);
	}


	printf("Welcome to Happy Farmer(tm, all rights reserved, rated M for Mature)\n\n");
	printf("What is your name, Farmer? ");
	fgets(playerName, STRING_DEFAULT, stdin);

	while (playerInput != 0) // Главный цикл 
	{
		printf("\nGreetings, %s! Please navigate the menu below...\n\n", playerName);
		printf("0 - exit Happy  Farmer(tm)\n");
		printf("1 - check the time\n");
		printf("2 - work for X hours\n");
		printf("3 - check your inventory\n");
		printf("4 - put item in your inventory\n");
		printf("5 - remove item from inventory\n");
		printf("6 - find items heavier than X in your inventory\n\n");

		playerInput = checkInput("Option: ", ERR_DEFAULT);

		switch (playerInput) // логика менюшки 
		{
		case 0: // выход
			printf("\nExiting...\n");
			break;
		case 1: // время
			timeCheck(current_day, current_hour); // смотрим на время
			break;
		case 2: // поработаем
			work(&current_day, &current_hour);
			break;
		case 3: // смотрим инвентарь
			checkInventory(inventoryDescription, inventory);
			break;
		case 4: // добавление предмета
			putItem(inventoryDescription, inventory);
			break;
		case 5: // удаление предмета
			removeItem(inventoryDescription, inventory);
			break;
		case 6: // поиск тяжестей
			comparer(inventoryDescription, inventory);
			break;
		case 7:
			searchItem(inventoryDescription, inventory);
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

void timeCheck(int day, int hour)
{
	printf("\n time: Day %d, %02d:00\n", day, hour);
}

void work(int* day, int* hour)
{
	int tempInput = checkInput("\nWork for how long (in hours)?: ", ERR_DEFAULT); // скока работаем
	// пользоваться поинтерами было больно
	*hour += tempInput;
	if (*hour > DAY_LENGTH_HOURS) // не ломаем время
	{
		printf("+day\n");
		*day += 1;
		*hour = *hour - DAY_LENGTH_HOURS;
	}
	printf("\nWorked for %d hours...\n", tempInput);

}

void checkInventory(char inventoryDesc[][STRING_DEFAULT], int inventory[])
{
	printf("\nYour inventory:\n");
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		printf("%s\n", inventoryDesc[inventory[i]]); // наш инвентарь тута
	}

	printf("\n");
}

void putItem(char inventoryDesc[][STRING_DEFAULT], int inventory[])
{
	int tempInput = checkInputInventory("\nWhat to put in? (0 - 9)", ERR_DEFAULT_INV);
	int tempInput2 = checkInputInventory("Where to put it in? (0 - 9)", ERR_DEFAULT_INV);

	inventory[tempInput2] = tempInput;
	printf("%s now in slot %d!\n", inventoryDesc[tempInput], tempInput2);
}

void removeItem(char inventoryDesc[][STRING_DEFAULT], int inventory[])
{
	int tempInput = checkInputInventory("\nWhat slot to void? (0 - 9)", ERR_DEFAULT_INV);
	printf("%s removed from slot %d!\n", inventoryDesc[tempInput], tempInput);
	inventory[tempInput] = 0;

}

void comparer(char inventoryDesc[][STRING_DEFAULT], int inventory[])
{
	int tempInput = checkInputInventory("\nWhat item to compare with? (0 - 9)", ERR_DEFAULT_INV);
	printf("\nItems in your inventory larger than %s:\n", inventoryDesc[tempInput]);

	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (inventory[i] > tempInput) printf("%s\n", inventoryDesc[inventory[i]]);
	}


}

void searchItem(char inventoryDesc[][STRING_DEFAULT], int inventory[])
{
	char input[STRING_DEFAULT];
	int ctr = 0;
	printf("looking for...");
	scanf("%s", &input);
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if ((strcmp(input, inventoryDesc[inventory[i]])) == 0)
		{
			ctr++;
			printf("%s found in slot %d\n",input, i);
		}
	}
	if (ctr == 0) printf("no %s found in inventory!\n", input);
}