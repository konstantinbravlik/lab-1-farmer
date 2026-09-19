#include <stdio.h>

int main()
{

	int current_day = 1; // день
	int current_hour = 8; // час
	int inventory[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int tempInput, tempInput2; 
	int playerInput = 1;

	/*
	* TODO: дополнить инвентарь
	инвентарь:
	0 - пусто
	1 - дерево
	2 - камень
	3 - семена
	4 
	5 
	6
	7
	8
	9
	*/

	while (playerInput != 0) // Главный цикл 
	{
		
		// TODO: менюшку сюды
		printf("Option: ");
		scanf("%i", &playerInput); 
		
		switch (playerInput) // логика менюшки тута
		{
		case 0: // выход
			printf("Exiting...\n");
			break;
		case 1: // время
			printf("Current time: Day %i, %02i:00\n", current_day, current_hour); // смотрим на время
			
			break;
		case 2: // поработаем
			printf("Work for how long (in hours)?: "); 
			scanf("%i", &tempInput); // скока работаем
			
			current_hour += tempInput;
			
			if (current_hour > 24) // не ломаем время
			{
				current_day++;
				current_hour -= 24;
			}
			
			printf("Worked for %i hours...\n", tempInput);

			break;
		case 3: // смотрим инвентарь
			printf("Your inventory:\n");

			for (int i = 0; i < 10; i++)
			{
				printf("Slot[%i]: %i\n", i, inventory[i]); // наш инвентарь тута
			}
			
			break;
		case 4: // добавление предмета
			tempInput = 0;

			do
			{
				if (tempInput < 0 || tempInput > 9) printf("Unsuported item! Please, try again.\n");
				printf("What to put in inventory? (0-9): ");
				scanf("%i", &tempInput);
			} while (tempInput < 0 || tempInput > 9); // держим в заложниках если неправильный ввод
			
			tempInput2 = 0;

			do
			{
				if (tempInput2 < 0 || tempInput2 > 9) printf("Outside of inventory range! Please, try again.\n");
				printf("Where to put it? (0-9): ");
				scanf("%i", &tempInput2);
			} while (tempInput2 < 0 || tempInput2 > 9); // тоже самое

			inventory[tempInput2] = tempInput; // записываем проверенные данные

			printf("Put '%i' in inventory slot %i\n", tempInput, tempInput2);

			break;
		case 5:
			printf("TESTICULAR TORSION\n");
			break;
		case 6:
			printf("TESTICULAR TORSION\n");
			break;
		default:
			printf("STOOPID HOOMAN :P\n");
			break;
		}
	}








	return 0;
}