#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_TOKENS 100

typedef enum {
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_ASSIGN,
  TOKEN_NUMBER
} TokenType;

typedef struct {
  TokenType type;
  int value; // Only used for numbers
} Token;

// This is genuinely hard to explain, but basically, we are basically making another kind of Token struct, but this one points to what is below it, to know the order.

typedef struct AbstractTreeNode { // Basically, this definition at the start is to give it a "real" name, and the second one is the typedef shortcut.
  TokenType type;
  int value; // Only used for numbers
  struct AbstractTreeNode* left;
  struct AbstractTreeNode* right;
} AbstractTreeNode; 



void Lexer(const char *input, int *count, Token *tokensReturned) { 
    // For loop for the input  *input is just the "char string"  *count is just where the count is updated  *TokensReturned, obviously is where the Tokens are returned
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (isspace(c)) {
          continue;
        }
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

            tokensReturned[*count] = t;
            (*count)++;
        }
        else if (c == '=') {
            Token t;
            t.type = TOKEN_ASSIGN;
            t.value = 0;

            tokensReturned[*count] = t;
            (*count)++;
        }
        else if (c == '+') {
            Token t;
            t.type = TOKEN_PLUS;
            t.value = 0;
            tokensReturned[*count] = t;
            (*count)++;

            printf("PLUS_SIGN\n");
        }
        else if (c == '-') {
            Token t;
            t.type = TOKEN_MINUS;
            t.value = 0;
            tokensReturned[*count] = t;
            (*count)++;

        }

        
    }
}

AbstractTreeNode* TreeHelper(TokenType node_type, int value) {
    AbstractTreeNode* Tree = malloc(sizeof(AbstractTreeNode));
    Tree->type = node_type;
    Tree->value = value;
    Tree->left = NULL;
    Tree->right = NULL;
    return Tree;
}

AbstractTreeNode* Parser(Token MainToken[], int Amount) { // MainToken is just the TokensReturned from the Lexer, and Amount is just how many tokens there are inside.
    int CursorToToken = 0;
    if (MainToken[CursorToToken].type != TOKEN_NUMBER) {
      printf("Expression has to start with a number, got %d instead.", MainToken[CursorToToken].type);
    }
    AbstractTreeNode* tree = TreeHelper(MainToken[CursorToToken].type, MainToken[CursorToToken].value);
    CursorToToken++;
    AbstractTreeNode* operatorTree = TreeHelper(MainToken[CursorToToken].type, MainToken[CursorToToken].value);
    CursorToToken++;
    AbstractTreeNode* next_tree = TreeHelper(MainToken[CursorToToken].type, MainToken[CursorToToken].value);
    operatorTree->left = tree;
    operatorTree->right = next_tree;
    tree = operatorTree;
    return tree;
}

void DebugTree(AbstractTreeNode* tree) {
  if (!tree) {return;}

  printf("Node type: %d\nvalue %d\n\n", tree->type, tree->value);

  DebugTree(tree->left);
  DebugTree(tree->right);
}
int Evaluator(AbstractTreeNode* tree) {
  if (tree->type == TOKEN_MINUS) {
    return (tree->left->value)-(tree->right->value);
  }
  if (tree->type == TOKEN_PLUS) {
    return (tree->left->value)+(tree->right->value);
  }
}


int main(int argc, char* argv[]) {
    int count = 0;
    Token backTokens[MAX_TOKENS];
    char *input = "69-72";
    Lexer(input, &count, backTokens);
    AbstractTreeNode* ReturnedParser = Parser(backTokens, count);
    DebugTree(ReturnedParser);

    printf("Result: %d\n", Evaluator(ReturnedParser));
    
    // if (argc < 3) {
    //     fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
    //     return 1;
    // }

    // char *cli_input = argv[1];
    // char *cli_output = argv[2];

    // FILE *in = fopen(cli_input, "r");
    // if (!in) {
    //     perror("fopen input failed");
    //     return 1;
    // }

    // FILE *out = fopen(cli_output, "w");
    // if (!out) {
    //     perror("fopen output failed");
    //     fclose(in);
    //     return 1;
    // }

    // int ch;
    // while ((ch = fgetc(in)) != EOF) {
    //     fputc(ch, out);
    // }

    // fclose(in);
    // fclose(out);

    // return 0;


}
