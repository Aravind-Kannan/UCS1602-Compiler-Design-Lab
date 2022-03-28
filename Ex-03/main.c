#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LIMIT 20

typedef struct productionRule{
    char lhs[LIMIT];
    char rhs[LIMIT];
} prodRule;

void printProdRule(prodRule p[], int len) {
    for(int i = 0; i < len; i++)
        printf("%s ---> %s\n", p[i].lhs, p[i].rhs);
}

bool isBetaPresent(char lhs[], char rhs[]){
    char temp[LIMIT];
    strcpy(temp, rhs);

    char *token;
    char delimit[2] = "|";
    token = strtok(temp, delimit);

    while(token != NULL)
    {
        if(!(isupper(lhs[0]) && isupper(token[0]) && lhs[0] == token[0]))
            return true;
        token = strtok(NULL, delimit);
    }

    return false;
}

int main()
{
    int input_len = 0, output_len = 0;
    prodRule input[LIMIT], output[LIMIT * 2];

    printf("Enter number of production rules: "); scanf("%d", &input_len);

    for(int i = 0; i < input_len; i++)
    {
        printf("Rule %d:- \n", i);
        printf("Enter LHS: "); scanf(" %[^\n]*c", input[i].lhs);
        printf("Enter RHS: "); scanf(" %[^\n]*c", input[i].rhs);
    }

    printf("Input production rules:\n");
    printProdRule(input, input_len);

    char delimit[2] = "|";

    for(int i = 0; i < input_len; i++)
    {
        if(isBetaPresent(input[i].lhs,input[i].rhs))
        {
            char *token;
            token = strtok(input[i].rhs,delimit);
            int flag = 0, k = 0;
            while(token != NULL)
            {
                char newNonTerm[LIMIT];
                sprintf(newNonTerm, "%c'", input[i].lhs[0]);
                if(isupper(input[i].lhs[0]) && isupper(token[0]) && input[i].lhs[0] == token[0])
                {
                    for(k = 0; k < output_len; k++)
                        if(strcmp(output[k].lhs, newNonTerm) == 0)
                            break;

                    strcpy(output[k].lhs, newNonTerm);

                    char temp[LIMIT] = "";
                    for(int j = 1; j < strlen(token); j++)
                        temp[j - 1] = token[j];

                    if(k != output_len)
                        sprintf(output[k].rhs, "%s|%s%s", output[k].rhs, temp, newNonTerm);
                    else
                        sprintf(output[k].rhs, "%s%s", temp, newNonTerm);
                    
                    if(k == output_len)
                        strcat(output[k].rhs, "|Ɛ");
                    
                    flag = 1;
                }
                else
                {
                    for(k = 0; k < output_len; k++)
                        if(strcmp(input[i].lhs, output[k].lhs) == 0)
                            break;

                    strcpy(output[k].lhs, input[i].lhs);

                    if(k != output_len)
                        strcat(output[k].rhs, "|");
                    strcat(output[k].rhs, token);

                    if(flag == 1)
                        strcat(output[k].rhs, newNonTerm);
                }

                if(k == output_len)
                    output_len++;

                token = strtok(NULL, delimit);
            }
        }
        else
        {
            strcpy(output[output_len].lhs, input[i].lhs);
            strcpy(output[output_len].rhs, input[i].rhs);
            output_len++;
        }
        
    }

    printf("Modified production rules:\n");
    printProdRule(output, output_len);

    return 0;
}