#include <stdio.h>

#define totalBooks 7
char books [totalBooks][250] = {"Algorithm Programming", "Basic Statistic", "Character Building", "Discrete Math", "Indonesian", "Linear Algebra", "Program Design Method"};
int stockBooks[totalBooks] = {40, 40, 40, 40, 40, 40, 40};

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
    printf("4. Logout\n");
    printf("Input your choice: ");

    }

    void pause(){
        printf("Press enter to continue.\n");
        getchar();
        getchar();
    }

    void borrowBooks(){
        int choice;

        showAllBooks();
        printf("Choose book number to borrow: ");
        scanf("%d", &choice);
        getchar();

        if(choice < 1 || choice > totalBooks){
            printf("Invalid book number!\n");
        }
        else if (stockBooks[choice - 1] == 0){
            printf("Sorry this book is out of stock.\n");
        }
        else {
            stockBooks[choice - 1]--;
            printf("You successfully borrowed [%s].\n", books[choice - 1]);
        }
    }

    void returnBooks(){
        int choice;

        showAllBooks();
        printf("Choose book number to return: ");
        scanf("%d", &choice);
        getchar();

        if(choice < 1 || choice > totalBooks){
            printf("Invalid book number!\n");
        }
        else if(stockBooks[choice - 1] == 40){
            printf("Error! This book was not borrowed.\n");
        }
        else {
            stockBooks[choice - 1]++;
            printf("You successfully returned [%s].\n", books[choice - 1]);
        }
    }

    int main (){

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
        printf("Thank you for coming.\n");
        break;

        default:
        printf("Invalid choice!\n");
        }
    }   while(x != 4);
    return 0;
}