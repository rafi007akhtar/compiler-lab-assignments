/** The following assignments were given on Day 2. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define allo (char *) malloc(sizeof(char) * 100)

typedef enum boolean {false, true} bool;

// Q1: Write a C program to check if another C file has the necessary prerequisites for executing a C program(such as #include<stdio.h>, int main(){},return 0;)
char *removeSpaces(char *str)
{
    char *trimmed = allo;
    int pos = -1;
    int trimI = 0;
    while(str[++pos])
    {
        if ((int) str[pos] == 32 || str[pos] == '\t')
            continue;
        trimmed[trimI++] = str[pos];
    }
    trimmed[trimI] = '\0';
    return trimmed;
}
bool checkPrerequisites(char *filename)
{
    FILE *f;

    f = fopen(filename, "r");
    size_t len = 0;
    char *line;
    int result;

    bool checkMain, checkReturn, openBrace, closeBrace, checkHeader;
    checkMain = checkReturn = checkHeader = closeBrace = false;

    while(1)
    {
        result = getline(&line, &len, f);
        if (result == -1)
            break;
        
        if (line[0] == '#')
        {
            // check header
            if (!strcmp("#include<stdio.h>", removeSpaces(line)))
            {
                checkHeader = true;
                continue;
            }
        }

        if (! (strcmp("int main()", line) || 
               strcmp("int main(void)", line) ||
               strcmp("int main(int argc, char *argv[]", line))
            )
        {
            checkMain = true;
            continue;
        }

        if (!strcmp("{", line) && checkMain == true)
        {
            openBrace = true;
            continue;
        }
        
        if (!strcmp("}", line) && openBrace == true)
        {
            closeBrace = true;
            continue;
        }

        if (!strcmp("return 0;", line) || !strcmp("return (0);", line))
        {
            checkReturn = true;
            continue;
        }

        if (checkMain && checkReturn && openBrace && closeBrace && checkHeader)
            return true;

    }

    fclose(f);

    if (checkHeader == true) printf("IO Header's here!\n");

    return (checkHeader && checkMain && openBrace && closeBrace && checkReturn);

}


// Q2: Write a C program that will replace a calloc() function to malloc() function with appropriate parameters.
//      E.g.- 
//      Input: calloc(5,sizeof(float)), 
//      Output: malloc(5* sizeof(float))
char* calToMal(char *str)
{
    char *test = allo;
    int pos = -1;
    int testI = 0;

    while(str[++pos])
    {
        // change the 'c' in "calloc" to 'm' for "malloc"
        if (pos == 0)
            test[testI++] = 'm';
        
        // change the comma to multiply
        else if (str[pos] == ',')
            test[testI++] = '*';
        
        else test[testI++] = str[pos];
    }
    test[testI] = '\0';

    return test;
}


// Q6: Write a C program that will check whether the input string is containing “Monday” in it.

bool hasMonday(char *str)
{

    char *temp = allo;
    char *word = "Monday";
    int pos, tPos;

    pos = tPos = -1;
    while(str[++pos])
    {
        // when you reach the end
        if (str[pos+1] == '\0')
        {
            temp[++tPos] = str[pos];
            temp[++tPos] = '\0';
            if (! strcmp(temp, word))
                return true;
            return false;
        }

        // when you are anywhere but the end
        if ((int) str[pos] == 32)
        {
            temp[++tPos] = '\0';
            if (! strcmp(temp, word))
                return true;
            free(temp);
            temp = allo;
            tPos = -1;
            continue;
        }
        temp[++tPos] = str[pos];
    }
}


