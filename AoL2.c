#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX_USERS 100 
#define totalBooks 7

struct User {
	char name[21], email[31], password[21]; // max 20 chars + '\0'
	int borrowedBooks[totalBooks];
};

struct BorrowReturnRecord {
    char email[31], bookName[250], dateTime[20], borrowDate[11], returnDate[11];
    int quantity, isReturned;
    char type[10]; //"borrow" or "return"
};

struct User users[MAX_USERS];
int totalUsers=0;
struct BorrowReturnRecord borrowRecords[1000];
int totalBorrowRecords = 0;

char books[totalBooks][250] = {"Algorithm Programming", "Basic Statistic", "Character Building", "Discrete Math", "Indonesian", "Linear Algebra", "Program Design Method"};
int stockBooks[totalBooks] = {40, 40, 40, 40, 40, 40, 40};
int maxStock[totalBooks] = {40, 40, 40, 40, 40, 40, 40};

int loginUser(char loggedName[], char loggedEmail[]), isValidName(char name[]), isValidEmail(char email[]), isValidPassword(char password[]), isValidDate(char date[]);
void userMainMenu(), userMenu(char name[]), adminMenu(), registerUser();
void header(), pause();
void libraryMenu(char name[], char email[]), showAllBooks(), searchBooks(), borrowBooks(char email[]), returnBooks(char email[]), showAbout();
void saveUsersToFile(), loadUsersFromFile(), saveBooksToFile(), loadBooksFromFile();
void saveRecordsToFile(), loadRecordsFromFile(), saveAllData(), loadAllData();

void header() {
    printf("=====================================\n");
    printf("   WELCOME TO OUR MINI LIBRARY\n");
    printf("=====================================\n");
}

void pause(){
    getchar();
    printf("Press enter to continue.\n");
    getchar();
}

int isValidName(char name[]) {
	int len=strlen(name);
	if (len==0 || len > 20) return 0;
	for (int i=0; i < len; i++) {
		if (!isalpha(name[i]) && name[i] !=' ') return 0;
	} return 1;
}

int isValidEmail(char email[]) {
	int len = strlen(email);
	if (len == 0 || len > 30) return 0;
	int hasAt = 0;
    for (int i = 0; i < len; i++) {
    	if (email[i] == '@') {
        hasAt = 1;
        break; }
	} if (!hasAt) return 0;
    return hasAt;
}

int isValidPassword(char password[]){
	int len = strlen(password);
	if (len < 8 || len > 20) return 0;
	int hasAlpha = 0, hasDigit = 0, hasSymbol = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(password[i])) hasAlpha = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else if (!isspace(password[i])) hasSymbol = 1;
    } return (hasAlpha && hasDigit && hasSymbol);
}

int isValidDate(char date[]) {
    int day, month, year;
    if (strlen(date) != 10) return 0; // Format harus DD/MM/YYYY (10 karakter)
    if (date[2] != '/' || date[5] != '/') return 0;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) return 0;
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) return 0;
    return 1;
}

void userMainMenu() { /*  USER MENU  */
	system ("cls");
	printf("\n=== WELCOME TO XX LIBRARY ===\n");
	printf("1. Register\n");
	printf("2. Login\n");
	printf("3. About this library\n");
	printf("4. Exit\n");
	printf("Input your choice: ");
}

void registerUser() { /*  REGISTER  */
	system ("cls");
	printf("\n===== REGISTER USER =====\n");
	struct User newUser;
	for(int i = 0; i < totalBooks; i++) newUser.borrowedBooks[i] = 0;
	do {
		printf("Input your name (max 20 alphabets): ");
		scanf(" %[^\n]", newUser.name);
		if (!isValidName(newUser.name)) printf("Invalid name! Must be alphabets only and not more than 20 characters. Please try again.\n");
	} while ( !isValidName(newUser.name));
	do {
        printf("Input your BINUS email (must contain @): ");
        scanf(" %[^\n]", newUser.email);
        if (!isValidEmail(newUser.email)) printf("Invalid email! Please try again.\n");
    } while (!isValidEmail(newUser.email)); //perlu dibikin kayak "email udh terdaftar sebelumnya, pls coba dengan email lain" ga ??//
	do {
        printf("Input your password (8-20 chars, must contain letter, number, symbol): ");
        scanf(" %[^\n]", newUser.password);
        if (!isValidPassword(newUser.password)) printf("Invalid password! Must be 8-20 characters and contain at least one letter, one number, and one symbol.\n");
        else printf("\n");
    } while (!isValidPassword(newUser.password));
    
	users[totalUsers]=newUser;
	totalUsers++;
	saveUsersToFile();
	printf("\n========================================\n");
	printf("\nCONGRATS YOU HAVE ALREADY COMPLETE MEMBERSHIP OF XX LIBRARY\n");
	printf("Please login to our system next\n");
	printf("\n========================================\n");
	pause();
}

int loginUser(char loggedName[], char loggedEmail[]) { /*  LOGIN  */
	system ("cls");
	char email[31], password[21];
	printf("\n===== LOGIN USER =====\n");
	printf("Input your email: ");
	scanf(" %[^\n]", email);
	printf("Input your password: ");
	scanf(" %[^\n]", password);
    
	for (int i=0; i < totalUsers; i++) {
	if (strcmp(users[i].email, email)==0 && strcmp(users[i].password, password)==0) {
		strcpy(loggedName, users[i].name);
		strcpy(loggedEmail, users[i].email);
		printf("\n CONGRATULATIONS.... LOGIN SUCCESSFUL!!\n");
		return 1; } }
	printf("\nInvalid email or password! Please try again.\n");
	pause();
	return 0;
}

void userMenu(char name[]){
	system("cls");
    printf("\n ===== WELCOME, %s ! =====\n\n", name);
    printf("Please choose what you're gonna do next.\n");
    printf("1. Show all list of books\n");
    printf("2. Search books\n");
    printf("3. Borrow books\n");
    printf("4. Return books\n");
    printf("5. Logout\n");
    printf("Input your choice: ");
}

void showAllBooks(){
	int sortChoice, showAgain;   
	do {
	system("cls");
    printf("===== LIST OF ALL BOOKS =====:\n");
    printf("1. Show in default order\n");
    printf("2. Show sorted by stock (Highest to Lowest)\n");
    printf("3. Back to library menu\n");
    printf("Input your choice: ");
    scanf("%d", &sortChoice);
    
    if (sortChoice == 3) {
        printf("\nReturning to library menu...\n");
        pause();
        return; } 
    if (sortChoice < 1 || sortChoice > 2) {
        printf("Invalid choice! Please select 1-3.\n");
        pause();
        continue; } 
    system("cls");
    if (sortChoice == 1) printf("===== LIST OF ALL BOOKS (Default Order) =====\n");
    else if (sortChoice == 2) printf("===== LIST OF ALL BOOKS (Sorted by Stock - Highest to Lowest) =====\n");
    
    printf("--------------------------------------------------------\n");
    printf("| No. |                   Book Title                   |\n");
    printf("--------------------------------------------------------\n");
    if (sortChoice == 1) {
        for(int i = 0; i < totalBooks; i++) printf("%-4d. %-45s %-6d\n", i + 1, books[i], stockBooks[i]); }
    else if (sortChoice == 2) {
        int sortedIndices[totalBooks];
        for(int i = 0; i < totalBooks; i++) sortedIndices[i] = i;
        for(int i = 0; i < totalBooks - 1; i++) {
            int maxIndex = i;
            for(int j = i + 1; j < totalBooks; j++) {
                if (stockBooks[sortedIndices[j]] > stockBooks[sortedIndices[maxIndex]]) maxIndex = j; }
        int temp = sortedIndices[i];
        sortedIndices[i] = sortedIndices[maxIndex];
        sortedIndices[maxIndex] = temp;
    }
        
        for(int i = 0; i < totalBooks; i++) {
            int idx = sortedIndices[i];
            printf("%-4d. %-45s %-6d\n", i + 1, books[idx], stockBooks[idx]); }
        printf("\n? Books are sorted by stock (highest to lowest)\n");
    }
    printf("\nDo you want to:\n");
    printf("1. View books with different sorting\n");
    printf("2. Back to library menu\n");
    printf("Your choice: ");
    scanf("%d", &showAgain);
    } while (showAgain == 1);
}

void searchBooks() {
    system("cls");
    printf("\n===== SEARCH BOOKS =====\n");
    printf("Feature not yet available.\n");
}

void borrowBooks(char email[]){
    int choice, qty, userIndex = -1;
    char borrowDate[11];
    
    for (int i = 0; i < totalUsers; i++) {
    if (strcmp(users[i].email, email) == 0) {
        userIndex = i;
        break; }} 
	if (userIndex == -1) return;
    
    do {
    system("cls");
    printf("\n===== BORROW BOOKS =====\n");
    printf("===== LIST OF ALL BOOKS =====\n");
        printf("--------------------------------------------------------\n");
        printf("| No. |                   Book Title                   | Stock |\n");
        printf("--------------------------------------------------------\n");
        for(int i = 0; i < totalBooks; i++) printf("%-4d. %-45s %-6d\n", i + 1, books[i], stockBooks[i]);
        printf("\n");
    printf("Choose book number to borrow: (type 0 to finish). ");
    scanf("%d", &choice);
    
    if(choice == 0) break;
    if(choice < 1 || choice > totalBooks){
        printf("Invalid book number!\n");
        pause();
        continue; }

    printf("How many copies to borrow?\n");
    scanf("%d", &qty);
    if(qty <= 0) {
	printf("Invalid quantity!\n");
	pause();
	continue;}
	
    else if (stockBooks[choice - 1] < qty) {
	printf("Sorry this book is out of stock. Only %d copy(s) left.\n", stockBooks[choice - 1]);
    pause();
    continue; }
    
    else {
        stockBooks[choice - 1] -= qty;
        printf("You have borrowed %d book(s) of %s\n", qty, books[choice - 1]); }
        
    do {
        printf("Input borrow date (DD/MM/YYYY): ");
        scanf(" %[^\n]", borrowDate);
        if (!isValidDate(borrowDate)) printf("Invalid date! Format must be DD/MM/YYYY\n");
    } while (!isValidDate(borrowDate));
            
    users[userIndex].borrowedBooks[choice - 1] += qty;   
	     
        struct BorrowReturnRecord record;
        strcpy(record.email, email);
        strcpy(record.bookName, books[choice - 1]);
        record.quantity = qty;
        strcpy(record.type, "BORROW");
        strcpy(record.borrowDate, borrowDate);
        strcpy(record.returnDate, "");
        record.isReturned = 0;
        
        borrowRecords[totalBorrowRecords] = record;
        totalBorrowRecords++;
        printf("\n========================================\n");
        printf("\n? Successfully borrowed %d book(s) of \"%s\"\n", qty, books[choice - 1]);
        printf("Borrow date: %s\n", borrowDate);
        printf("========================================\n");
    	pause();
    saveBooksToFile();
    saveRecordsToFile();
    } while (choice != 0); }

void returnBooks(char email[]){
    int choice, qty, userIndex = -1;
    char returnDate[11];
    for (int i = 0; i < totalUsers; i++) {
    if (strcmp(users[i].email, email) == 0) {
        userIndex = i;
        break; } 
		} if (userIndex == -1) return;
		
    do{
	system ("cls");
	printf("\n===== RETURN BOOKS =====\n");
	printf("\nYour borrowed books:\n");
	printf("-------------------------------------------------------\n");
	int hasBorrowed = 0;
    for (int i = 0; i < totalBooks; i++) {
    if (users[userIndex].borrowedBooks[i] > 0) {
        printf("%d. %s (Borrowed: %d)\n", i + 1, books[i], users[userIndex].borrowedBooks[i]);
        hasBorrowed = 1; } }
            
    if (!hasBorrowed) {
    printf("\nYou don't have any borrowed books.\n");
    pause();
    break;}

    printf("Choose book number to return: (type 0 to finish). ");
    scanf("%d", &choice);
    if(choice == 0)break;
    if(choice < 1 || choice > totalBooks){
        printf("Invalid book number!\n");
        pause();
        continue; }
    
    printf("How many copies to return?\n");
    scanf("%d", &qty);
    if(qty <= 0) {
		printf("Invalid quantity!\n");
		pause();
		continue;}
    if(qty > users[userIndex].borrowedBooks[choice - 1]) printf("Return quantity exceeds borrowed amount.\n");
    else {
        stockBooks[choice - 1] += qty;
        printf("You have returned %d book(s) of %s\n", qty, books[choice - 1]);
		users[userIndex].borrowedBooks[choice - 1] -= qty; }
        
	do {
        printf("Input return date (DD/MM/YYYY): ");
        scanf(" %[^\n]", returnDate);
        if (!isValidDate(returnDate)) printf("Invalid date! Format must be DD/MM/YYYY\n");
    } while (!isValidDate(returnDate));
        
struct BorrowReturnRecord record;
    strcpy(record.email, email);
    strcpy(record.bookName, books[choice - 1]);
    record.quantity = qty;
    strcpy(record.type, "RETURN");
    strcpy(record.borrowDate, "");
    strcpy(record.returnDate, returnDate);
    record.isReturned = 1;
    
    borrowRecords[totalBorrowRecords] = record;
    totalBorrowRecords++;
    printf("\n========================================\n");
    printf("\n? Successfully returned %d book(s) of \"%s\"\n", qty, books[choice - 1]);
    printf("Return date: %s\n", returnDate);
    printf("========================================\n");
    pause();
    saveBooksToFile();
    saveRecordsToFile();
} while(choice != 0);
}

void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error saving user data!\n");
        return;} 
	fprintf(file, "%d\n", totalUsers);
    for (int i = 0; i < totalUsers; i++) {
	fprintf(file, "%s|%s|%s", users[i].name, users[i].email, users[i].password);
    for (int j = 0; j < totalBooks; j++) {
	fprintf(file, "|%d", users[i].borrowedBooks[j]);}
	fprintf(file, "\n");}
    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("No user data found. Starting fresh.\n");
        return; }
    fscanf(file, "%d\n", &totalUsers);
    for (int i = 0; i < totalUsers; i++) {
	fscanf(file, "%[^|]|%[^|]|%[^|]", users[i].name, users[i].email, users[i].password);
    for (int j = 0; j < totalBooks; j++) {
	fscanf(file, "|%d", &users[i].borrowedBooks[j]); }
    fscanf(file, "\n"); }
    fclose(file);
}

void saveBooksToFile() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error saving book data!\n");
        return; }
    for (int i = 0; i < totalBooks; i++) fprintf(file, "%s|%d|%d\n", books[i], stockBooks[i], maxStock[i]);
    fclose(file);
}

void loadBooksFromFile() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("No book data found. Using default.\n");
        return; }
    for (int i = 0; i < totalBooks; i++) {
        if (fscanf(file, "%[^|]|%d|%d\n", books[i], &stockBooks[i], &maxStock[i]) != 3) break; // Jika gagal membaca, berhenti
    } fclose(file);
}

void saveRecordsToFile() {
    FILE *file = fopen("transactions.txt", "w");
    if (file == NULL) {
        printf("Error saving transaction data!\n");
        return;}
    fprintf(file, "%d\n", totalBorrowRecords);
    for (int i = 0; i < totalBorrowRecords; i++) fprintf(file, "%s|%s|%d|%s|%s|%s|%d\n",borrowRecords[i].email, borrowRecords[i].bookName, borrowRecords[i].quantity, borrowRecords[i].type, borrowRecords[i].borrowDate, borrowRecords[i].returnDate, borrowRecords[i].isReturned);
    fclose(file);
}

void loadRecordsFromFile() {
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("No transaction data found.\n");
        return; }
    fscanf(file, "%d\n", &totalBorrowRecords);
    for (int i = 0; i < totalBorrowRecords; i++) fscanf(file, "%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d\n",borrowRecords[i].email, borrowRecords[i].bookName, &borrowRecords[i].quantity, borrowRecords[i].type, borrowRecords[i].borrowDate, borrowRecords[i].returnDate, &borrowRecords[i].isReturned);
    fclose(file);
}

void saveAllData() {saveUsersToFile(); saveBooksToFile(); saveRecordsToFile();
}
void loadAllData() {loadUsersFromFile(); loadBooksFromFile(); loadRecordsFromFile();
}

void showAbout() {
    system("cls");
    printf("===== ABOUT XX LIBRARY =====\n");
    printf("XX Library Management System\n");
    printf("Developed by: BINUS University Students\n\n");
    
    printf("Features:\n");
    printf("� User Registration & Authentication\n");
    printf("� Book Borrowing & Returning System\n");
    printf("� Real-time Stock Management\n");
    printf("� Transaction History Tracking\n");
    printf("� Advanced Search Functionality\n");
    printf("� Admin Panel for Management\n"); //GATAU
    printf("� Data Saving and Updating\n\n");
    
    printf("Contact Information:\n");
    printf("Email: library@xx.edu\n");
    printf("Phone: 081234567890\n");
    pause();
}

void libraryMenu(char name[], char email[]){
    int x;
    do {	
    userMenu(name);
    if (scanf("%d", &x) != 1) {
        printf("Invalid input! Please enter a number.\n");
        pause();
		continue; }
    switch (x){
        case 1: showAllBooks(); pause(); break;
        case 2: searchBooks(); pause(); break;
        case 3: borrowBooks(email); break;
        case 4: returnBooks(email); break;
		case 5:
			printf("\nLogging out...\n");
	        printf("Thank you for visiting our library, %s!\n", name);
	        pause();
	        break;  
        default:
	        printf("Invalid choice! Please select 1-5.\n");
	        pause();
	        break;
        	}
    } while(x != 5);
}

/*  MAIN  */
int main() {
	loadAllData();
	int choice;
	char loggedUser[21], loggedEmail[31];
	int isLogin=0;
	do {
		userMainMenu();
		if (scanf("%d", &choice) != 1) {
		printf("Invalid input! Please enter a number.\n");
		pause();
        continue; }

	switch (choice) {
	case 1: registerUser(); break;	
	case 2:      
		do {
			isLogin=loginUser(loggedUser, loggedEmail);
	    } while (!isLogin);
		printf("--------------------------------------------------\n");
		printf("\nWELCOME TO XX, %s !!\n", loggedUser);
		printf(">> Please continue to borrow/return/show books menu\n");
		printf("--------------------------------------------------\n");
		pause();
		libraryMenu(loggedUser, loggedEmail);
		isLogin = 0;
		break;
	case 3: showAbout(); break;
	case 4: 
		system("cls"); 
		saveAllData();
	    printf("\n------------------------------------------------------------\n\n");
	    printf("  Thank you for using XX Library! See you next time!\n\n");
	    printf("------------------------------------------------------------\n");
	    printf("\n"); 
		break;   
	default: 
		printf("Invalid choice! Please select 1-4.\n"); 
		pause(); 
		break; }	
	} while (choice !=4);
	return 0; }
