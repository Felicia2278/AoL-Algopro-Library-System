#include <stdio.h>

#define totalBooks 7
char books [totalBooks][250] = {"Algorithm Programming", "Basic Statistic", "Character Building", "Discrete Math", "Indonesian", "Linear Algebra", "Program Design Method"};
int stockBooks[totalBooks] = {40, 40, 40, 40, 40, 40, 40};
int maxStock[totalBooks] = {40, 40, 40, 40, 40, 40, 40};

int borrowedCount[totalBooks] = {0};
int returnedCount[totalBooks] = {0};


void header() {
    printf("=====================================\n");
    printf("   WELCOME TO OUR MINI LIBRARY\n");
    printf("=====================================\n");
}


void showAllBooks(){
    printf("List of books:\n");
    for(int i = 0; i < totalBooks; i++){
        printf("%d. %s (Stock: %d).\n", i + 1, books[i], stockBooks[i]);
    }
}

    void userMenu(){

    printf("Welcome to (user name).\n");
    printf("Please choose what you gonna do next.\n");
    printf("1. Show all list of books\n");
    printf("2. Borrow books\n");
    printf("3. Return books\n");
    printf("4. Library report\n");
    printf("5. Logout\n");
    printf("Input your choice: ");

    }

    void pause(){
        printf("Press enter to continue.\n");
        getchar();
        getchar();
    }

    void borrowBooks(){
        int choice, qty;

        do {

        showAllBooks();
        printf("Choose book number to borrow: (type 0 to finish). ");
        scanf("%d", &choice);
        

        if(choice == 0){
            break;
        }

        if(choice < 1 || choice > totalBooks){
            printf("Invalid book number!\n");
            continue;
        }

        printf("How many copies?\n");
        scanf("%d", &qty);
        
        if(qty <= 0){
            printf("Invalid quantity!\n");
        }
        else if (stockBooks[choice - 1] < qty){
            printf("Sorry this book is out of stock.\n");
        }
        else {
            stockBooks[choice - 1] -= qty;
            borrowedCount[choice - 1] += qty;
            printf("You have borrowed %d book(s) of %s\n", qty, books[choice - 1]);
            }
        } while (choice != 0);
    }

    void returnBooks(){
        int choice, qty;

        do{

        showAllBooks();
        printf("Choose book number to return: (type 0 to finish). ");
        scanf("%d", &choice);
        

        if(choice == 0){
            break;
        }

        if(choice < 1 || choice > totalBooks){
            printf("Invalid book number!\n");
            continue;
        }
        
        printf("How many copies?\n");
        scanf("%d", &qty);

        if(qty <= 0){
            printf("Invalid quantity!\n");
        }
        else if(stockBooks[choice - 1] + qty > maxStock[choice - 1]){
            printf("Return quantity exceeds borrowed amount.\n");
        }
        else {
            stockBooks[choice - 1] += qty;
            returnedCount[choice - 1] += qty;
            printf("You have returned %d book(s) of %s\n", qty, books[choice - 1]);
            }
        } while(choice != 0);
    }

    void libraryReport() {
    printf("\n===== LIBRARY REPORT =====\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("%d. %s | Borrowed: %d | Returned: %d\n",
               i + 1,
               books[i],
               borrowedCount[i],
               returnedCount[i]);
    }
}

    
    int main (){

    header();

    int x;

    do {

    userMenu();
    scanf("%d", &x);

    switch (x){

        case 1: 
        showAllBooks();
        pause();
        break;

        case 2:
        borrowBooks();
        pause();
        break;

        case 3:
        returnBooks();
        pause();
        break;

        case 4:
        libraryReport();
        pause();
        break;

        case 5:
        printf("Thank you for coming.\n");
        break;

        default:
        printf("Invalid choice!\n");
        }
    }   while(x != 5);
    return 0;
}