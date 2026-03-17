#include <ctype.h>
#include <stdio.h>

typedef enum {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASSIGN,
    TOKEN_NUMBER
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

void tokenizater(const char *input) {
    // For loop for the input
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (isdigit(c)) { // Case for being a number
            int num = 0;  // start accumulator at 0
            while (isdigit(input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            i--;
            Token t;
            t.type = TOKEN_NUMBER;
            t.value = num;
            
            printf("NUMBER: %d\n", t.value);
        }
        else if (c == '=') {
            Token t;
            t.type = TOKEN_ASSIGN;

            printf("EQUAL_SIGN\n");
        }
        else if (c == '+') {
            Token t;
            t.type = TOKEN_PLUS;

            printf("PLUS_SIGN\n");
        }
        else if (c == '-') {
            Token t;
            t.type = TOKEN_MINUS;

            printf("MINUS_SIGN\n");
        }

        
    }
}

int main() {
    char *input = "5-3=10";
    tokenizater(input);
}