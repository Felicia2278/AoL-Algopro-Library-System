#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX_USERS 100 
#define totalBooks 7

struct User {
	char name[21], email[31], password[21]; 
	int borrowedBooks[totalBooks]; //array buku yg dipinjam per user
};

struct BorrowReturnRecord {
    char email[31], bookName[250];
	char borrowDate[11], returnDate[11];
    int quantity;
    char type[10]; //"borrow" or "return"
};

struct User users[MAX_USERS];
int totalUsers=0;
struct BorrowReturnRecord borrowRecords[1000];
int totalBorrowRecords = 0;

char books[totalBooks][250] = {"Algorithm Programming", "Basic Statistic", "Character Building", "Discrete Math", "Indonesian", "Linear Algebra", "Program Design Method"};
int stockBooks[totalBooks] = {40, 40, 40, 40, 40, 40, 40};
int maxStock[totalBooks] = {40, 40, 40, 40, 40, 40, 40};


int loginUser(char loggedName[], char loggedEmail[]);
int isValidName(char name[]);
int isValidEmail(char email[]);
int isValidPassword(char password[]);
int isValidDate(char date[]);

void userMainMenu();
void adminmenu();
void registerUser();
void showAbout();

void header(), pause();

void libraryMenu(char name[], char email[]);
void showAllBooks();
void searchBooks();
void borrowBooks(char email[]);
void returnBooks(char email[]);

void saveUsersToFile();
void loadUsersFromFile();
void saveBooksToFile();
void loadBooksFromFile();

void saveRecordsToFile();
void loadRecordsFromFile(); 
void saveAllData();
void loadAllData();

void header() {
    printf("=====================================\n");
    printf("=   WELCOME TO OUR MINI LIBRARY !!  =\n");
    printf("=====================================\n");
}

void pause(){
	getchar();
    printf("Press enter to continue.\n");
	getchar();
}

int isValidName(char name[]) {
    for (int i = 0; name[i]; i++)
        if (!isalpha(name[i]) && name[i] != ' ') return 0;
    return (strlen(name) > 0 && strlen(name) <= 20); 
}

int isValidEmail(char email[]) { //harus ada '@' dan domain binus
    return strlen(email) > 0 && strlen(email) <= 30 && strchr(email, '@') && strstr(email, "@binus.");
}

int isValidPassword(char password[]) {
    int hasAlpha = 0, hasDigit = 0, hasSymbol = 0;
    for (int i = 0; password[i]; i++) {
        hasAlpha += isalpha(password[i]);
        hasDigit += isdigit(password[i]);
        hasSymbol += !isalnum(password[i]); //karakter bukan alphanumeric
    } return (hasAlpha && hasDigit && hasSymbol && strlen(password) >= 8 && strlen(password) <= 20); }

int isValidDate(char date[]) { //format DD/MM/YYYY
    int day, month, year;
    return (strlen(date) == 10 && date[2] == '/' && date[5] == '/' && sscanf(date, "%d/%d/%d", &day, &month, &year) == 3 && day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100);
}

// USER AUTHENTICATION
void userMainMenu() { 
	system ("cls"); 
	header();	
	printf("1. Register\n");
	printf("2. Login\n");
	printf("3. About this library\n");
	printf("4. Exit\n");
	printf("Input your choice: ");
}

void registerUser() { /*  REGISTER  */
	system ("cls");
	printf("\n===== REGISTER USER =====\n");
	struct User newUser = {0};
	
	do {
		printf("Input your name (max 20 alphabets): ");
		scanf(" %[^\n]", newUser.name);
	} while (!isValidName(newUser.name) && printf("Invalid name! Must be alphabets only and not more than 20 characters. Please try again.\n"));
	
	do {
        printf("Input your BINUS email (must contain @): ");
        scanf(" %[^\n]", newUser.email);
    } while (!isValidEmail(newUser.email) && printf("Invalid email! Must be BINUS email (@binus.ac.id/.edu). Please try again.\n"));
    
	do {
        printf("Input your password (8-20 chars, must contain letter, number, symbol): ");
        scanf(" %[^\n]", newUser.password);
    } while (!isValidPassword(newUser.password) && printf("Invalid password! Must be 8-20 characters and contain at least one letter, one number, and one symbol.\n"));
    
	users[totalUsers++]=newUser;
	saveUsersToFile();
	
	printf("\n========================================\n");
	printf("\nCONGRATS YOU HAVE ALREADY COMPLETE MEMBERSHIP OF LIBRARY\nPlease login to our system next\n");
	printf("\n========================================\n");
	pause();
}

int loginUser(char loggedName[], char loggedEmail[]) { /*  LOGIN  */
	system ("cls");
	char inputemail[31], password[21];
	
	printf("\n===== LOGIN USER =====\n");
	printf("Input your email: ");
	scanf(" %[^\n]", inputemail);
	printf("Input your password: ");
	scanf(" %[^\n]", password);
    
	for (int i=0; i < totalUsers; i++) {
	if (strcmp(users[i].email, inputemail)==0 && strcmp(users[i].password, password)==0) {
		strcpy(loggedName, users[i].name);
		strcpy(loggedEmail, users[i].email);
		
		printf("--------------------------------------------------\n");
		printf("CONGRATULATIONS.... LOGIN SUCCESSFUL!!\n");
		printf("\nWELCOME TO XX, %s !!\n", loggedName);
		printf(">> Please continue to library menu\n");
		printf("--------------------------------------------------\n");
		pause();
		return 1; } }
		
	printf("\nInvalid email or password! Please try again.\n");
	pause();
	return 0;
}

// LIBRARY FUNCTIONS
void showAllBooks(){
	int choice;   
	do {
	system("cls");
    printf("===== LIST OF ALL BOOKS =====:\n");
    printf("1. Show in default order\n");
    printf("2. Show sorted by stock (Highest to Lowest)\n");
    printf("3. Back to library menu\n");
    printf("Input your choice: ");
    scanf("%d", &choice);
    
    if (choice == 3) return; 
    if (choice < 1 || choice > 3) {
        printf("Invalid choice! Please select 1-3.\n");
        pause();
        continue; } 
        
    system("cls");
    if (choice == 1) printf("===== LIST OF ALL BOOKS (Default Order) =====\n");
    else if (choice == 2) printf("===== LIST OF ALL BOOKS (Sorted by Stock from Highest to Lowest) =====\n");
    
    printf("-----------------------------------------------------------\n");
	printf("| %-3s | %-40s | %-6s |\n", "No.", "Book Title", "Stock");
    printf("-----------------------------------------------------------\n");
    
    if (choice == 1) { //tampilan buku dalam default
        for(int i = 0; i < totalBooks; i++) printf("| %-3d | %-40s | %-6d |\n", i + 1, books[i], stockBooks[i]);}
    //Sorting by stock
	else if (choice == 2) {
        int idx[totalBooks];
        for(int i = 0; i < totalBooks; i++) idx[i] = i;
        for(int i = 0; i < totalBooks - 1; i++) {
            int max = i;
            for(int j = i + 1; j < totalBooks; j++) {
                if (stockBooks[idx[j]] > stockBooks[idx[max]]) max = j; }
        int temp = idx[i];
        idx[i] = idx[max];
        idx[max] = temp;
        //buku yg sudah diurutkan
    } for(int i = 0; i < totalBooks; i++) printf("| %-3d | %-40s | %-6d |\n", i + 1, books[idx[i]], stockBooks[idx[i]]); }
    
    printf("\nDo you want to:\n");
    printf("1. View books with different sorting\n");
    printf("2. Back to library menu\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    } while (choice == 1);
}

void searchBooks() {
    system("cls");
    printf("\n===== SEARCH BOOKS =====\n");
    char keyword[100];
    printf("Search (enter keyword): ");
    scanf(" %[^\n]", keyword);
    
    printf("\nSearch result for '%s':\n", keyword);
    printf("-----------------------------------------------------------\n");
	printf("| %-3s | %-40s | %-6s |\n", "No.", "Book Title", "Stock");
    printf("-----------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < totalBooks; i++) {
    	//case insensitive
    	char bookLower[250], keyLower[100];
    	strcpy(bookLower, books[i]);
        for (int j = 0; bookLower[j]; j++) bookLower[j] = tolower(bookLower[j]);
        strcpy(keyLower, keyword);
        for (int j = 0; keyLower[j]; j++) keyLower[j] = tolower(keyLower[j]);
        // Cek jika keyword ada dlm judul
        if (strstr(bookLower, keyLower) != NULL) printf("| %-3d | %-40s | %-6d |\n", ++found, books[i], stockBooks[i]);
    }
    if (found == 0) printf("\n No books found containing '%s'\n", keyword);
    else printf("\n Found %d book(s)\n", found);
}

void borrowBooks(char email[]){
    int choice, qty, userIndex = -1;
    char borrowDate[11];
    
    //cari index user berdasarkan email
    for (int i = 0; i < totalUsers; i++) {
    if (strcmp(users[i].email, email) == 0) {
        userIndex = i;
        break; }} 
	if (userIndex == -1) return;
    
    do {
    system("cls");
    printf("\n===== BORROW BOOKS =====\n");
    printf("-----------------------------------------------------------\n");
	printf("| %-3s | %-40s | %-6s |\n", "No.", "Book Title", "Stock");
    printf("-----------------------------------------------------------\n");
    for(int i = 0; i < totalBooks; i++) printf("| %-3d | %-40s | %-6d |\n", i + 1, books[i], stockBooks[i]);
    printf("-----------------------------------------------------------\n");
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
	
    else if (stockBooks[choice - 1] < qty) { //cek ketersediaan stock
	printf("Sorry this book is out of stock. Only %d copy(s) left.\n", stockBooks[choice - 1]);
    pause();
    continue; }
        
    do { //input tanggal pinjam
        printf("Input borrow date (DD/MM/YYYY): ");
        scanf(" %[^\n]", borrowDate);
    } while (!isValidDate(borrowDate) && printf("Invalid date! Format must be DD/MM/YYYY\n"));
    
	// Update data   
	stockBooks[choice-1] -= qty;        
    users[userIndex].borrowedBooks[choice - 1] += qty;   
	    
		//buat record transaksi borrow 
        struct BorrowReturnRecord record;
        strcpy(record.email, email);
        strcpy(record.bookName, books[choice - 1]);
        record.quantity = qty;
        strcpy(record.type, "BORROW");
        strcpy(record.borrowDate, borrowDate);
        strcpy(record.returnDate, "");
        
        borrowRecords[totalBorrowRecords++] = record;
        printf("\n========================================\n");
        printf("Successfully borrowed %d book(s) of \"%s\"\n", qty, books[choice - 1]);
        printf("Borrow date: %s\n", borrowDate);
        printf("========================================\n");
    	pause();
    	
    saveBooksToFile();
    saveRecordsToFile();
    } while (1); }


void returnBooks(char email[]){
    int choice, qty, userIndex = -1;
    char returnDate[11];
    
    for (int i = 0; i < totalUsers; i++) {
    if (strcmp(users[i].email, email) == 0) {
        userIndex = i;
        break; } 
		} if (userIndex == -1) return;
		
    do{
    	system("cls");
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
		
		//tidak bisa mengembalikan lebih dari yang dipinjam
    if(qty > users[userIndex].borrowedBooks[choice - 1]){
    	printf("Return quantity exceeds borrowed amount.\n");
    	pause();
        continue; }

	do {
        printf("Input return date (DD/MM/YYYY): "); //tanggal pemgembalian
        scanf(" %[^\n]", returnDate);
        if (!isValidDate(returnDate)) printf("Invalid date! Format must be DD/MM/YYYY\n");
    } while (!isValidDate(returnDate));
    
    // Update stock dan data user
    stockBooks[choice - 1] += qty;
    users[userIndex].borrowedBooks[choice - 1] -= qty;
        
	struct BorrowReturnRecord record; //buat record pengembalian
    strcpy(record.email, email);
    strcpy(record.bookName, books[choice - 1]);
    record.quantity = qty;
    strcpy(record.type, "RETURN");
    strcpy(record.borrowDate, "");
    strcpy(record.returnDate, returnDate);
    
    borrowRecords[totalBorrowRecords++] = record;
    printf("\n========================================\n");
    printf("\n? Successfully returned %d book(s) of \"%s\"\n", qty, books[choice - 1]);
    printf("Return date: %s\n", returnDate);
    printf("========================================\n");
    pause();
    saveBooksToFile();
    saveRecordsToFile();
} while(choice != 0);
}

// FILE OPERATIONS
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
        printf("No user data found.\n");
        return; }
    fscanf(file, "%d\n", &totalUsers);
    for (int i = 0; i < totalUsers; i++) {
	fscanf(file, "%[^|]|%[^|]|%[^|]", users[i].name, users[i].email, users[i].password);
    for (int j = 0; j < totalBooks; j++) {
	fscanf(file, "|%d", &users[i].borrowedBooks[j]); }
    fscanf(file, "\n"); }
    fclose(file);
}

//format: bookName|currentStock|maxStock
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
        if (fscanf(file, "%[^|]|%d|%d\n", books[i], &stockBooks[i], &maxStock[i]) != 3) break;
    } fclose(file);
}

//format: email|bookName|quantity|type|borrowDate|returnDate|
void saveRecordsToFile() {
    FILE *file = fopen("transactions.txt", "w");
    if (file == NULL) {
        printf("Error saving transaction data!\n");
        return;}
    fprintf(file, "%d\n", totalBorrowRecords);
    for (int i = 0; i < totalBorrowRecords; i++) fprintf(file, "%s|%s|%d|%s|%s|%s\n",borrowRecords[i].email, borrowRecords[i].bookName, borrowRecords[i].quantity, borrowRecords[i].type, borrowRecords[i].borrowDate, borrowRecords[i].returnDate);
    fclose(file);
}

void loadRecordsFromFile() {
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("No transaction data found.\n");
        return; }
    fscanf(file, "%d\n", &totalBorrowRecords);
    for (int i = 0; i < totalBorrowRecords; i++) fscanf(file, "%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^\n]\n",borrowRecords[i].email, borrowRecords[i].bookName, &borrowRecords[i].quantity, borrowRecords[i].type, borrowRecords[i].borrowDate, borrowRecords[i].returnDate);
    fclose(file);
}

void saveAllData() {saveUsersToFile(); saveBooksToFile(); saveRecordsToFile();}
void loadAllData() {loadUsersFromFile(); loadBooksFromFile(); loadRecordsFromFile();}

void showAbout() {
    system("cls");
    printf("===== ABOUT XX LIBRARY =====\n\n");
    printf("XX Library Management System\n");
    printf("Developed by: BINUS University Students\n\n");
    
    printf("Features:\n");
    printf("# User Registration & Authentication\n");
    printf("# Book Borrowing & Returning System\n");
    printf("# Real-time Stock Management\n");
    printf("# Admin Panel for Management\n");
    printf("# Advanced Search Functionality\n");
    printf("# Data Saving and Updating\n\n");
    
    printf("Contact Information:\n");
    printf("Email: library@xx.edu\n");
    printf("Phone: 081234567890\n");
    pause();
}

// MAIN LIBRARY MENU
void libraryMenu(char name[], char email[]) {
    int x;
    do {
        system("cls");
        printf("\n ===== WELCOME, %s ! =====\n\n", name);
        printf("Please choose what you're gonna do next.\n");
        printf("1. Show all list of books\n");
        printf("2. Search books\n");
        printf("3. Borrow books\n");
        printf("4. Return books\n");
        printf("5. Logout\n");
        printf("Input your choice: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        
        if (sscanf(input, "%d", &x) != 1) {
            printf("\nInvalid input! Please enter a number 1-5.\n");
            pause();
            continue; }
        
        switch (x) {
            case 1: showAllBooks(); pause(); break;               
            case 2: searchBooks(); pause(); break;                
            case 3: borrowBooks(email); break;               
            case 4: returnBooks(email); break;    
            case 5:
                printf("\nLogging out...\n");
                printf("Thank you for visiting our library, %s!\n", name);
                pause(); break; 
            default:
                printf("\nInvalid choice! Please select 1-5.\n");
                pause(); break;
        } } while (x != 5);
}

// MAIN FUNCTION
int main() { 
	loadAllData(); //Load semua data dari file saat program mulai
	int choice;
	char name[21], email[31];
	int isLogin=0;
	
	do {
		userMainMenu();
		if (scanf("%d", &choice) != 1) {
		printf("Invalid input! Please enter a number.\n");
		pause();
        continue; }

	switch (choice) {
		case 1: registerUser(); break;	
		case 2: if (loginUser(name, email)) libraryMenu(name, email); break;
		case 3: showAbout(); break;
		case 4: 
			system("cls"); 
			saveAllData(); //save all data sebelum exit
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

