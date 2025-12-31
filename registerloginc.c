#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_USERS 100 struct User {
	char name[21]; // max 20 chars + '\0'
	char id[7]; // exactly 6 digits + '\0'
}

;

struct User users[MAX_USERS];
int totalUsers=0;

/*  VALIDATION  */

int isValidName(char name[]) {
	int len=strlen(name);
	if (len==0 || len > 20) return 0;

	for (int i=0; i < len; i++) {
		if ( !isalpha(name[i]) && name[i] !=' ') return 0;
	}

	return 1;
}

int isValidID(char id[]) {
	if (strlen(id) !=6) return 0;

	for (int i=0; i < 6; i++) {
		if ( !isdigit(id[i])) return 0;
	}

	return 1;
}

/*  REGISTER  */

void registerUser() {
	struct User newUser;

	do {
		printf("Input your name (max 20 alphabets): ");
		scanf(" %[^\n]", newUser.name);

		if ( !isValidName(newUser.name)) {
			printf("Invalid name! Please try again.\n");
		}
	}

	while ( !isValidName(newUser.name));

	do {
		printf("Your ID (must exactly 6 numbers): ");
		scanf("%s", newUser.id);

		if ( !isValidID(newUser.id)) {
			printf("Invalid ID! Please try again.\n");
		}
	}

	while ( !isValidID(newUser.id));

	users[totalUsers]=newUser;
	totalUsers++;

	printf("\nCONGRATS U ALREADY COMPLETE MEMBERSHIP OF XX LIBRARY\n");
	printf("Please login to our system next\n\n");
}

/*  LOGIN  */

int loginUser(char loggedName[]) {
	char name[21],
	id[7];

	printf("Input your name: ");
	scanf(" %[^\n]", name);
	printf("Input your ID: ");
	scanf("%s", id);

	for (int i=0; i < totalUsers; i++) {
		if (strcmp(users[i].name, name)==0 && strcmp(users[i].id, id)==0) {

			strcpy(loggedName, name);
			printf("\nLOGIN SUCCESSFUL\n");
			return 1;
		}
	}

	printf("\nInvalid name or ID! Please try again.\n");
	return 0;
}

/*  USER MENU  */

void userMainMenu() {
	printf("\n=== WELCOME TO XX LIBRARY ===\n");
	printf("1. Register\n");
	printf("2. Login\n");
	printf("3. Back to CHOOSE YOUR SIDE\n");
	printf("Input your choice: ");
}

/*  MAIN  */

int main() {
	int choice;
	char loggedUser[21];
	int isLogin=0;

	do {
		userMainMenu();
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				registerUser();
			break;

			case 2: do {
				isLogin=loginUser(loggedUser);
			}

			while ( !isLogin);

			printf("\nWELCOME TO XX (%s)\n", loggedUser);
			printf(">> lanjut ke menu borrow / return / show books\n");
			break;

			case 3: printf("Back to CHOOSE YOUR SIDE...\n");
			break;

			default: printf("Invalid choice!\n");
		}

	}

	while (choice !=3);

	return 0;
}