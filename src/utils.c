#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int checkInput(const char* message, const char* errorMessage) {
    int input;
    printf("%s\n", message);
    while (scanf("%d", &input) != 1) {
        printf("%s", errorMessage);
        while (getchar() != '\n');
    }
    return input;
}

int checkInputInventory(const char* message, const char* errorMessage) {
    int input;
    printf("%s\n", message);
    while (scanf("%d", &input) != 1 || input < 0 || input > 9) {
        printf("%s", errorMessage);
        while (getchar() != '\n');
    }
    return input;
}

int randomInt(int min, int max) {
    return (rand() % (max + 1 - min) + min);
}

void clearScreen(void) {
    system("cls");
}