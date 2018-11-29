/** The following assignments were given on Day 2. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
        
        // check header
        if (line[0] == '#')
        {
            if (!strcmp("#include<stdio.h>\n", removeSpaces(line)))
            {
                checkHeader = true;
                continue;
            }
        }

        // check main
        if (! strcmp("int main()\n", line) || 
            ! strcmp("int main(void)\n", line) ||
            ! strcmp("int main(int argc, char *argv[])\n", line)
            )
        {
            checkMain = true;
            continue;
        }

        // check open brace
        if (!strcmp("{\n", line) && checkMain == true)
        {
            openBrace = true;
            continue;
        }
        
        // check close brace
        if (!strcmp("}\n", line) && openBrace == true)
        {
            closeBrace = true;
            continue;
        }

        // check return
        if (checkReturn == false)
        {
            if (
                (!strcmp("return0;\n", removeSpaces(line)) &&
                strcmp("return0;\n", line)) ||
                (!strcmp("return(0);\n", removeSpaces(line)) &&
                strcmp("return(0);\n", line))
            )
                checkReturn = true;
                continue;
        }

        // if already encountered all these, don't check anymore
        if (checkMain && checkReturn && openBrace && closeBrace && checkHeader)
            return true;
    }

    fclose(f);

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


// Q3: Write a C program which will take a C file as input and 
//     find out the total memory space required for allocating 
//     all the variables and check if it exceeds a certain limit
//     (which is taken as user input).
int varSize(char *filename)
{
    size_t len = 0;
    char *line;
    int result;

    int pos;
    char *type;
    size_t size = 0;
    int intCount, floatCount, longCount, doubleCount, charCount;
    intCount = floatCount = longCount = doubleCount = charCount = 0;

    FILE *f = fopen(filename, "r");

    while(1)
    {
        result = getline(&line, &len, f);
        if (result == -1) break;

        pos = -1;
        while(line[++pos])
        {
            type = allo;

            if(pos + 3 < len)
            {
                memcpy(type, &line[pos], 3);
                type[3] = '\0';
                if (! strcmp("int", type))
                intCount++;
            }

            if(pos + 4 < len)
            {
                memcpy(type, &line[pos], 4);
                type[4] = '\0';
                if (! strcmp("long", type))
                    longCount++;
                if (! strcmp("char", type))
                    charCount++;
            }
            
            if (pos + 5 < len)
            {
                memcpy(type, &line[pos], 5);
                type[5] = '\0';
                if (! strcmp("float", type))
                    floatCount++;
                if (! strcmp("double", type))
                    doubleCount++;
            }

            if (pos + 6 < len)
            {
                memcpy(type, &line[pos], 6);
                type[6] = '\0';
                if (! strcmp("double", type))
                    doubleCount++;
            }

            free(type);
        }
    }

    fclose(f);

    intCount--; // subtracting an int for int main

    // printf("Ints: %d \nFloats: %d \nLongs: %d \nChars: %d \nDoubles: %d\n", intCount, floatCount, longCount, charCount, doubleCount);

    int totalSize = (
        (intCount*sizeof(int)) + 
        (floatCount*sizeof(float)) + 
        (charCount*sizeof(char)) +
        (longCount*sizeof(long)) +
        (doubleCount*sizeof(double)) 
    );

    return totalSize;
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
            {
                free(temp);
                return true;
            }
            free(temp);
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

// Q7: Write a C program that will check whether all the variables declared in an input file are initialized or not. 
//     If not, initialize them with 0.
void initialize(char *filename)
{
    char *line;
    int result;
    size_t len = 0;
    int pos;

    FILE *f = fopen(filename, "r");

    char *assinged;
    bool isAssigned;

    // copy the results to an intermediate temp file
    FILE *temp = fopen("temp.c", "w+");
    fclose(temp);
    while(1)
    {
        result = getline(&line, &len, f);
        if (result == -1) break;

        pos = -1;
        isAssigned = false;

        while(line[++pos])
        {
            if (line[pos] == '=')
            {
                isAssigned = true;
                break;
            }
        }

        
        if (! isAssigned)
        {
            temp = fopen("temp.c", "a+");
            assinged = allo;

            len = strlen(line);
            memcpy(assinged, &line[0], len-2);
            assinged[len-2] = '=';
            assinged[len-1] = '0';
            assinged[len] = ';';
            assinged[len+1] = '\n';
            assinged[len+2] = '\0';

            fprintf(temp, "%s", assinged);
            free(assinged);
            fclose(temp);
        }
        else 
        {
            temp = fopen("temp.c", "a+");
            fprintf(temp, "%s", line);
            fclose(temp);
        }
    }
    fclose(f);

    // now copy the results of temp to the program file freshened-up
    f = fopen(filename, "w+"); // clear its contents
    temp = fopen("temp.c", "r"); // copy this file's contents
    while(1)
    {
        result = getline(&line, &len, temp);
        if (result == -1) break;
        fprintf(f, "%s", line);
    }
    fclose(f);
    fclose(temp);

    // now delete temp
    remove("temp.c");
}


