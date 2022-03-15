#include "base.h"

// need to supply else raises warning that array decays
bool isValidToken(char token[], char arr[][LIMIT], int n)
{
    n /= LIMIT;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(token, arr[i]) == 0)
        {
            // printf("%s %s\n", token, arr[i]);
            return true;
        }
    }
    return false;
}

int findSymbol(char token[])
{
    // printf("token(%ld): %s\n", strlen(token),token);
    if (isValidToken(token, arithmeticOps, sizeof(arithmeticOps)))
    {
        printf("Arithmetic Op");
    }
    else if (isValidToken(token, arithmeticAssignmentOps, sizeof(arithmeticAssignmentOps)))
    {
        printf("Arithmetic Assignment Op");
    }
    else if (isValidToken(token, relationalOps, sizeof(relationalOps)))
    {
        printf("Relational Op");
    }
    else if (isValidToken(token, bitwiseOps, sizeof(bitwiseOps)))
    {
        printf("Bitwise Op");
    }
    else if (isValidToken(token, unaryOps, sizeof(unaryOps)))
    {
        printf("Unary Op");
    }
    else if (isValidToken(token, assignmentOp, sizeof(assignmentOp)))
    {
        printf("Assignment Op");
        return 1;
    }
    else if (isValidToken(token, specialCharacters, sizeof(specialCharacters)))
    {
        printf("Special Characters");
    }
    return 0;
}

Table table[LIMIT / 2];
int len_table = 0;
void create(char keyword[], char identifier[], char value[])
{
    // printf("Inserting...\n");
    strcpy(table[len_table].identifierName, identifier);
    strcpy(table[len_table].type, keyword);
    strcpy(table[len_table].value, value);

    int numberOfBytes = 0;
    if (!strcmp("char", keyword))
        numberOfBytes = 1;
    else if (!strcmp("int", keyword))
        numberOfBytes = 2;
    else if (!strcmp("float", keyword))
        numberOfBytes = 4;
    else if (!strcmp("double", keyword))
        numberOfBytes = 8;
    else
        return;

    table[len_table].bytes = numberOfBytes;

    int start = 1000;
    if (len_table > 0)
        start = table[len_table - 1].address + table[len_table - 1].bytes;

    table[len_table].address = start;
    len_table++;
}

void insert(char keyword[], char identifier[], char value[])
{
    strcpy(table[len_table - 1].value, value);
}

void printTable()
{
    printf("\n\nSymbol table:\n");
    printf("Number of variables = %d\n", len_table);
    printf("+---------------+------+--------+---------------+-------+\n");
    printf("|IdentifierName\t|Type\t|Bytes\t|Address\t|Value\t|\n");
    printf("+---------------+------+--------+---------------+-------+\n");
    for (int i = 0; i < len_table; i++)
    {
        printf("|%s\t\t|%s\t|%d\t|%d\t\t|%s\t|\n", table[i].identifierName, table[i].type, table[i].bytes, table[i].address, table[i].value);
        printf("+---------------+-------+-------+---------------+-------+\n");
    }
}

int main()
{

    char fileName[100];
    printf("Enter fileName: ");
    scanf(" %[^\n]*c", fileName);

    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Unable to find %s...\n", fileName);
    }
    else
    {
        // Read line-by-line
        int bytes = 0, j = 0, isIdentifier = 0, isAssignment = 0;
        char line[LIMIT], token[LIMIT], identifier[LIMIT], keyword[LIMIT], ch;

        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line, "\r\n")] = 0;
            // printf("line = %s\n", line);

            for (int i = 0; i < strlen(line); i++)
            {
                ch = line[i];

                if (ch == ' ' || ch == '\t' || ch == '\n')
                    continue;

                // printf("ch: %c\n", ch);

                if (isalpha(ch))
                {
                    j = 0;
                    ch = line[i++];
                    do
                    {
                        token[j++] = ch;
                        ch = line[i++];
                    } while (isalnum(ch) && i <= strlen(line));
                    token[j] = '\0';
                    i--;

                    // printf("token = %s\n", token);

                    if (isValidToken(token, keywords, sizeof(keywords)))
                    {
                        printf("%s\t", token);
                        printf("\t\t\tKeyword\n");
                        strcpy(keyword, token);
                    }
                    else if (line[i] == '(')
                    {
                        ch = line[i++];
                        do
                        {
                            token[j++] = ch;
                            ch = line[i++];
                        } while (ch != ';' && i <= strlen(line));
                        token[j] = '\0';
                        i--;

                        printf("%s\t", token);
                        printf("\t\t\tFunction\n");
                    }
                    else
                    {
                        printf("%s\t", token);
                        printf("\t\t\tIdentifier\n");
                        strcpy(identifier, token);
                        isIdentifier = 1;
                        create(keyword, identifier, "-");
                    }
                }
                else if (isdigit(ch))
                {
                    j = 0;
                    ch = line[i++];
                    do
                    {
                        token[j++] = ch;
                        ch = line[i++];
                    } while ((isdigit(ch) || ch == '.') && i <= strlen(line));
                    token[j] = '\0';
                    i--;

                    printf("%s\t", token);

                    if (strstr(token, "."))
                    {
                        printf("\t\t\tDecimal Number\n");
                    }
                    else
                    {
                        printf("\t\t\tInteger\n");
                    }

                    if (isIdentifier && isAssignment)
                    {
                        insert(keyword, identifier, token);
                        isIdentifier = 0;
                        isAssignment = 0;
                    }
                }
                else if (ch == '\"' || ch == '\'')
                {
                    char end = '\'';
                    if (ch == '\"')
                        end = '\"';

                    j = 0;
                    token[j++] = ch;
                    i++;
                    for (; line[i] != end && i <= strlen(line); j++)
                        token[j] = line[i++];
                    token[j] = end;
                    token[j + 1] = '\0';
                    i++;

                    printf("%s\t", token);
                    // printf("line[]=%c end=%c\n", line[i - 1], end);

                    if (end == '\'')
                    {
                        printf("\t\t\tCharacter constant\n");
                    }
                    else
                    {
                        printf("\t\t\tString constant\n");
                    }

                    if (isIdentifier && isAssignment)
                    {
                        insert(keyword, identifier, token);
                        isIdentifier = 0;
                        isAssignment = 0;
                    }
                }
                else if (ch == '/')
                {
                    // printf("ch: %c\n", ch);
                    j = 0;
                    token[j++] = ch;
                    ch = line[++i];
                    // printf("ch: %c\n", ch);
                    if (ch == '/')
                    {
                        for (; i < strlen(line); j++)
                            token[j] = line[i++];
                        token[j] = '\0';

                        printf("%s \t\t\t\t Single Line Comment\n", token);
                    }
                }
                else if (ch == '#')
                {
                    j = 0;
                    ch = line[i++];
                    do
                    {
                        token[j++] = ch;
                        ch = line[i++];
                    } while (ch != '\n' && i <= strlen(line));
                    token[j] = '\0';
                    i--;
                    // printf("%d %s\n", strlen("token"), "token");
                    printf("%s\t", token);
                    printf("\t\t\tPreprocessor directive\n");
                }
                else
                {
                    j = 0;
                    ch = line[i++];
                    do
                    {
                        token[j++] = ch;
                        ch = line[i++];
                    } while (!isalnum(ch) && i <= strlen(line) && ch != '\t' && ch != ' ');
                    token[j] = '\0';
                    i--;

                    printf("%s\t\t\t\t", token);

                    isAssignment = findSymbol(token);
                    printf("\n");
                }
                i--;
                // printf("isAssignment = %d isIdentifier = %d keyword = %s identifier = %s\n", isAssignment, isIdentifier, keyword, identifier);
            }
        }
    }
    printTable();
    fclose(file);

    return 0;
}