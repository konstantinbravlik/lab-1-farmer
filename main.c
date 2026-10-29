#include <stdio.h>
#include <string.h>
#include <conio.h> // вот эта библиотека для getch() чтобы получать ввод с клавы для управления в данже
#include <stdlib.h> // тупо ради одной константы для рандома
#include <time.h> // для рандомной рандомности
#define INVENTORY_SIZE 10
#define STRING_DEFAULT 33
#define PLAYER_DEFAULT 1
#define DAY_DEFAULT 1
#define HOUR_DEFAULT 8
#define DAY_LENGTH_HOURS 24
#define MAP_MIN 5
#define MAP_MAX 30
#define MAP_WALL '#'
#define MAP_EMPTY '.'
#define MAP_PLAYER '@'
#define MAP_EXIT 'Q'
#define MAP_ROCK 'R'
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
void diaryWrite(char* fileName, char name[STRING_DEFAULT], int hour, int day, char inventoryDesc[][STRING_DEFAULT], int inventory[]);
void decipher(char* fileName, char* fileOutput, int hour);
int random(int min, int max);
char** generateMap(int row, int col, int* playerX, int* playerY, int* exitX, int* exitY, char* bufferDraw); // Генерирует карту
void drawMap(char** map, int row, int col); // Отрисовывает карту
void adventure();

int main()
{
	srand((unsigned)time(NULL)); // сид для рандома

	int current_day = DAY_DEFAULT; // день
	int current_hour = HOUR_DEFAULT; // час
	int inventory[INVENTORY_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // инвентарь
	char inventoryDescription[INVENTORY_SIZE][STRING_DEFAULT] = {"empty", "seeds", "wood", "stone", "coal", "watering can", "axe", "hoe", "rake", "scythe"};
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

	printf("Welcome to Happy Farmer(tm, all rights reserved, rated M for Mature)\n\n");
	printf("What is your name, Farmer? ");
	fgets(playerName, STRING_DEFAULT, stdin);
	playerName[strcspn(playerName, "\r\n")] = '\0'; // фикс имени

	while (playerInput != 0) // Главный цикл 
	{
		printf("\nGreetings, %s! Please navigate the menu below...\n\n", playerName);
		printf("0 - exit Happy  Farmer(tm)\n");
		printf("1 - check the time\n");
		printf("2 - work for X hours\n");
		printf("3 - check your inventory\n");
		printf("4 - put item in your inventory\n");
		printf("5 - remove item from inventory\n");
		printf("6 - find items heavier than X in your inventory\n");
		printf("7 - search for item name\n");
		printf("8 - write in diary\n");
		printf("9 - get villager info\n");
		printf("10 - go on an adventure\n\n");

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
		case 8:
			diaryWrite("diary.txt", playerName, current_hour, current_day, inventoryDescription, inventory);
			break;
		case 9:
			decipher("input.txt", "output.txt", current_hour);
			break;
		case 10:
			adventure();
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
		printf("[%d] - %s\n", i, inventoryDesc[inventory[i]]); // наш инвентарь тута
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
		if (inventory[i] > tempInput) printf("[%d] - %s\n", i, inventoryDesc[inventory[i]]);
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

void diaryWrite(char* fileName, char name[STRING_DEFAULT], int hour, int day, char inventoryDesc[][STRING_DEFAULT], int inventory[])
{
	FILE* fileDiary = fopen(fileName, "a"); // Вот это всё надо будет прибрать в функцию записи или чёт такое

	if (fileDiary == NULL)
	{
		printf("error! No %s found\n", fileName);
	}
	else
	{
		fprintf(fileDiary, "Diary entry:\nName: %sCurrent day: %d\nCurrent hour: %d\n", name, day, hour);
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			fprintf(fileDiary, "[%d] - %s\n", i, inventoryDesc[inventory[i]]);
		}
		fprintf(fileDiary, "entry finished\n");
		fclose(fileDiary);
		printf("new diary entry in %s\n", fileName);
	}

}

void decipher(char* fileName, char* fileOutput, int hour)
{
	FILE* file = fopen(fileName, "r");
	FILE* outputFile = fopen(fileOutput, "a");
	char info[STRING_DEFAULT];
	if (file == NULL)
	{
		printf("error! No %s found\n", fileName);	
	}
	else
	{
		while (fgets(info, STRING_DEFAULT, file) != NULL)
		{
			info[strcspn(info, "\r\n")] = '\0';   // убираем перевод строки

			char* name = strtok(info, ";");
			char* workStart = strtok(NULL, ";");
			char* workEnd = strtok(NULL, ";");
			char* workPlace = strtok(NULL, ";");

			printf("%s is at %s. ", name, workPlace);
			if (hour >= atoi(workStart) && hour < atoi(workEnd)) printf("[AT WORK]\n");
			else printf("[RESTING HOME]\n");

			fprintf(outputFile, "%s is at %s. ", name, workPlace);
			if (hour >= atoi(workStart) && hour < atoi(workEnd)) fprintf(outputFile, "[AT WORK]\n");
			else fprintf(outputFile, "[RESTING HOME]\n");
		}
		fclose(file);
	}
}

int random(int min, int max)
{
	return (rand() % (max + 1 - min) + min);

}

char** generateMap(int row, int col, int* playerX, int* playerY, int* exitX, int* exitY, char* bufferDraw)
{
	int isPlayer = 0;
	int isExit = 0;
	int ranResult;
	
	char** map;
	// 1. Выделяем память под массив указателей (строк)
	map = (char**)malloc(row * sizeof(char*));
	// 2. В цикле выделяем память под каждую строку (столбцы)
	for (int i = 0; i < row; i++) {
		map[i] = (char*)malloc(col * sizeof(char));
	}

	for (int i = 0; i < row; i++) // генератор карты (потом мб перенести в отдельную функцию)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
			{
				map[i][j] = MAP_WALL; // рисуем стены
			}
			else
			{
				ranResult = random(0, 10); // штука которая делает рандомные препятствия
				switch (ranResult)
				{
				case 0:
					map[i][j] = MAP_ROCK; // рандом препятствие (потом наверно изменю)
					break;
				case 1:

					if (map[i][j] != MAP_WALL && isExit == 0)
					{
						isExit = 1;
						*exitX = i;
						*exitY = j;
						map[i][j] = MAP_EXIT;
					}
					else map[i][j] = MAP_EMPTY;
					break;
				default:
					map[i][j] = MAP_EMPTY;
					break;
				}
			}
			if (map[i][j] == MAP_EMPTY && isPlayer == 0)
			{
				*bufferDraw = map[i][j]; // запоминаем что было на клетке до игрока
				isPlayer = 1;
				*playerX = i;
				*playerY = j;
				map[i][j] = MAP_PLAYER;
			}
		}
	}

	return map;
}

void drawMap(char** map, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void adventure()
{
	/*
	Я немножко дурачок так что Y тут это <-> там влево вправо			
	а X получается	вверх вниз
	дэбил
	*/
	int row, col, playerX, playerY, exitX, exitY;
	int floor = 1;
	char input = ' ';
	char bufferDraw;
	row = random(MAP_MIN, MAP_MAX); // рандомно
	col = random(MAP_MIN, MAP_MAX); // делаем размер
//	printf("height: %d\n width: %d\n", row, col); // debug
	
	char** map = generateMap(row, col, &playerX, &playerY, &exitX, &exitY, &bufferDraw); // делаем нашу карту
	
	while (input != 'q' && 'Q') // потом проверять что стоим на точке где можно выйти (но это потом) вроде не сложно проверить
	{
		system("cls");
		printf("Tower floor %d\n", floor);
		drawMap(map, row, col);
		input = _getch();
		switch (input) // движение
		{
		case 'w':
		case 'W':
			if (map[playerX - 1][playerY] != MAP_WALL && map[playerX - 1][playerY] != MAP_ROCK)
			{
				map[playerX][playerY] = bufferDraw;
				bufferDraw = map[playerX - 1][playerY];
				map[playerX - 1][playerY] = MAP_PLAYER;
				playerX--;
			}
			break;
		case 'a':
		case 'A':
			if (map[playerX][playerY - 1] != MAP_WALL && map[playerX][playerY - 1] != MAP_ROCK)
			{
				map[playerX][playerY] = bufferDraw;
				bufferDraw = map[playerX][playerY - 1];
				map[playerX][playerY - 1] = MAP_PLAYER;
				playerY--;
			}
			break;
		case 's':
		case 'S':
			if (map[playerX + 1][playerY] != MAP_WALL && map[playerX + 1][playerY] != MAP_ROCK)
			{
				map[playerX][playerY] = bufferDraw;
				bufferDraw = map[playerX + 1][playerY];
				map[playerX + 1][playerY] = MAP_PLAYER;
				playerX++;
			}
			break;
		case 'd':
		case 'D':
			if (map[playerX][playerY + 1] != MAP_WALL && map[playerX][playerY + 1] != MAP_ROCK)
			{
				map[playerX][playerY] = bufferDraw;
				bufferDraw = map[playerX][playerY + 1];
				map[playerX][playerY + 1] = MAP_PLAYER;
				playerY++;
			}
			break;
		}
	}

	for (int i = 0; i < row; i++) {
		free(map[i]);
	}
	free(map);
	system("cls");
}