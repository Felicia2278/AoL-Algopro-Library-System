#include <stdio.h>

#define totalBooks 7
char books [totalBooks][250] = {"Algorithm Programming", "Basic Statistic", "Character Building", "Discrete Math", "Indonesian", "Linear Algebra", "Program Design Method"};
int stockBooks[totalBooks] = {40, 40, 40, 40, 40, 40, 40};

void showAllBooks(){
    printf("List of books:\n");
    for(int i = 0; i < totalBooks; i++){
        printf("%d. %s (Stock: %d).\n", i+1, books[i], stockBooks[i]);
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

    int main (){

    int x;
    userMenu();
    scanf("%d", &x);

    switch (x){

        case 1: 
        showAllBooks();
        break;

        case 2:
        break;

        case 3:
        break;

        case 4:
        break;

        default:
        printf("Invalid choice!\n");
    }
    return 0;
}