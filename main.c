#include <stdio.h>

int main()
{

	int current_day = 1; // день
	int current_hour = 8; // час
	int inventory[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	char playerInput = 1;

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
		case 0:
			break;
		case 1:
			printf("Current time: Day %i, %02i:00\n", current_day, current_hour); // смотрим на время
			break;
		case 2:
			printf("TESTICULAR OPTION\n");
			break;
		case 3:
			printf("TESTICULAR TORSION\n");
			break;
		case 4:
			printf("TESTICULAR TORSION\n");
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