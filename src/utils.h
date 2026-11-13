#ifndef UTILS_H
#define UTILS_H

#define STRING_DEFAULT 33
#define INVENTORY_SIZE 10
#define DAY_LENGTH_HOURS 24
#define DAY_DEFAULT 1
#define HOUR_DEFAULT 8
#define ERR_DEFAULT "error! Please use a valid int! (press enter and retry)"
#define ERR_DEFAULT_INV "error! Please use a valid int from 0 to 9! (press enter and retry)"

int checkInput(const char* message, const char* errorMessage);
int checkInputInventory(const char* message, const char* errorMessage);
int randomInt(int min, int max);
void clearScreen(void);

#endif