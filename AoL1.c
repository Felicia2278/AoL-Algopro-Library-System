#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define SHIFT 3 

void dataencode(char str[], int shift) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c >= 'A' && c <= 'Z') {
            str[i] = ((c - 'A' + shift) % 26) + 'A';
        }else if (c >= 'a' && c <= 'z') {
            str[i] = ((c - 'a' + shift) % 26) + 'a';
        }
     
    }
}

int main() {
    char input[MAX_LEN + 1];

    fgets(input, sizeof(input), stdin);

    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    dataencode(input, SHIFT);
    printf("%s\n", input);

    return 0;
}