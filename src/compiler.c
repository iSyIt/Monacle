#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_TOKENS 100

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

void Lexer(const char *input, int *count, Token *TokensReturned) { 
    // For loop for the input  *input is just the "char string"  *count is just where the count is updated  *TokensReturned, obviously is where the Tokens are returned
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

            TokensReturned[*count] = t;
            (*count)++;
        }
        else if (c == '=') {
            Token t;
            t.type = TOKEN_ASSIGN;
            t.value = 0;

            TokensReturned[*count] = t;
            (*count)++;
        }
        else if (c == '+') {
            Token t;
            t.type = TOKEN_PLUS;
            t.value = 0;
            TokensReturned[*count] = t;
            (*count)++;

            printf("PLUS_SIGN\n");
        }
        else if (c == '-') {
            Token t;
            t.type = TOKEN_MINUS;
            t.value = 0;
            TokensReturned[*count] = t;
            (*count)++;

        }

        
    }
}


int main(int argc, char* argv[]) {
    // int count = 0;
    // Token backTokens[MAX_TOKENS];
    // char *input = "5-3=10";
    // Lexer(input, &count, backTokens);
    // // Print the Array
    // for (int i = 0; i<count; i++) {
    //     printf("Value: %d\nType: %d\n\n", backTokens[i].value, backTokens[i].type);
    // }
    if (argc < 2) {
        fprintf(stderr, "Bro ur legit dumb asf. It's %s <input>\n", argv[0]);
        return 1;
    }
    char *cli_input = argv[1];
    char *cli_output = argv[2];


    char output_file;
    FILE *file_pointer = fopen(cli_input, "r");
    while ((output_file = fgetc(file_pointer)) != EOF) {
        printf("%c", output_file);
    }


}
