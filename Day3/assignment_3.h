/** The following assignments were given on Day 2. */

#include <stdlib.h>
#define allo (char *) malloc(sizeof(char) * 100)

typedef enum boolean {false, true} bool;

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


