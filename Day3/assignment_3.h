/** The following assignments were given on Day 2. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define allo (char *) malloc(sizeof(char) * 100)

typedef enum boolean {false, true} bool;

// UTILITY FUNCTIONS
char *removeSpaces(char *str)
{
    // Remove all spaces from a string

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
int indexOf(char *str, char ch)
{
    // Return the first index of character `ch` in string `str`
    // Return -1 if not found

    int pos = -1;
    while(str[++pos])
    {
        if (str[pos] == ch)
            return pos;
    }
    return -1;
}
char *unindentLine(char *line)
{
    // Remove indentation (extra spaces in the prefix) of a line

    char *unindented = allo;
    int pos = -1;
    int newPos = 0;
    while(line[++pos])
    {
        if ((int) line[pos] != 32 || line[pos] != '\t')
            unindented[newPos++] = line[pos];
    }
	unindented[newPos] = '\0';
    return unindented;
}
bool typeCheck(char *val, char *datatype)
{
    // Returns true if `val` is a valid value for datatype `type`
    // Returns false otherwise
    // Does NOT check for void types

    int pos;

    if (!strcmp(datatype, "short") || !strcmp(datatype, "int") || !strcmp(datatype, "long"))
    {
        // check for all ints
        pos = -1;
        while(val[++pos])
        {
            // it can be expression with numbers, +, -, /, *, % and spaces only

            if (val[pos] == '*' || val[pos] == '/' || val[pos] == '/' || val[pos] == '%')
            {
                // this cannot happen in the beginning
                if (pos == 0)
                    return false;
                continue;
            }
            if (val[pos] != '+' && val[pos] != '-' && val[pos] && (int) val[pos]!=32
                && !((int)val[pos] >= 48 && (int)val[pos] <= 57)
                )
                return false;
        }
        return true;
    }
    
    if (!strcmp(datatype, "float") || !strcmp(datatype, "double"))
    {
        pos = -1;
        while(val[++pos])
        {
            if (val[pos] == '.')
            {
                // periods can't appear at the end
                if (val[pos+1] == '\0') return false;
                continue;
            }
            if (val[pos] == '*' || val[pos] == '/' || val[pos] == '/' || val[pos] == '%')
            {
                // this cannot happen in the beginning
                if (pos == 0)
                    return false;
                continue;
            }
            if (val[pos] != '+' && val[pos] != '-' && val[pos] && (int) val[pos]!=32
                && !((int)val[pos] >= 48 && (int)val[pos] <= 57)
                )
                return false;
        }
        return true;
    }

    if (! strcmp(datatype, "char"))
    {
        // chars can be only one letter long, plus the surrounding quotes ''
        if (val[0] != '\'' || val[2] != '\'' || val[3] != '\0') 
            return false;
        return true;
    }

    return false;
}
bool in(char *word, char *list[], int len)
{
	// check if word exists in list
	int i;
	for (i = 0; i < len; i++)
	{
		if (! strcmp(list[i], word))
			return true;
	}
	return false;
}


// ### Assignment questions begin from here ###

// Q1: Write a C program to check if another C file has the necessary prerequisites for executing a C program(such as #include<stdio.h>, int main(){},return 0;)
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


// Q4: Write a C program that takes another C file as input and check if all the functions are having proper return types.
void checkReturn(char *filename)
{
    char* line;
    size_t len = 0;
    int result;
    char *type = "none so far";
    char *temp;
    int spaceIndex;

    bool hasError = false;
    
    FILE *f = fopen(filename, "r");
    int lineNumber = 0;
    while(1)
    {
        result = getline(&line, &len, f);
        if (result == -1) break;
        lineNumber++;

        // get the return type if this line is a function decl.
        len = strlen(line);
        if (line[len-2] == ')')
        {        
            type = allo;
            spaceIndex = indexOf(line, (char)32);
            memcpy(type, &line[0], spaceIndex);
            type[spaceIndex] = '\0';

            // you don't need anything else from this line, so move on to the next
            continue;
        }

        // once you have the return type, check for the closest return statement
        if (strcmp(type, "none so far"))
        {
            line = removeSpaces(line);
            // a return statement would atleast need 6 characters
            len = strlen(line);
            if (len < 6) continue;
            // printf("Line '%s' with length %ld will be processed\n", line, len);
            
            temp = allo;
            memcpy(temp, &line[0], 6); // 'return' is 6 characters long
            temp[6] = '\0';

            // check if the statement is a return statement
            if (! strcmp(temp, "return"))
            {
                if (! strcmp(type, "void"))
                {
                    hasError = true;
                    printf("Error in line %d: return statement in void\n", lineNumber);
                }

                else // return statement in a non-void function
                {
                    // now get the return value
                    temp = allo;
                    int ind = indexOf(line, ';');
                    memcpy(temp, &line[6], ind-6);
                    temp[ind-6] = '\0';
                    // printf("Return value: '%s' in type '%s'\n", temp, type);

                    // now check if you have the proper value wrt the type
                    if (! typeCheck(temp, type))
                    {
                        hasError = true;
                        printf("Error in line %d: '%s' is not a valid return value for type '%s'\n", lineNumber, temp, type);
                    }

                    free(temp);
                }

                free(type);
                type = "none so far";
            }
        }
        
    }
    fclose(f);

    if (! hasError) printf("There are no errors in the return types of this file\n");
}


// Q5: Write a C program that should check if all the members of the \
structures are having a defined data type. If not, print an error.
void checkStruct(char *filename)
{
	// ASSUMPTION: The file contains only struct members
	char *line;
	size_t len = 0;
	int lineNumber = 0;
	int result;

	char *first5;
	char *types[] = {"int", "short", "float", "long", "double", "char"};
	char *type;
	int spaceIndex;

	FILE *f = fopen(filename, "r");

	while(1)
	{
		result = getline(&line, &len, f);
		if (result == -1) break;
		lineNumber++;

		if (! strcmp(line, "\n"))
			continue;

		// skip for lines with "struct", "{", "}"
		len = strlen(line);
		if (len >= 6)
		{
			first5 = allo;
			memcpy(first5, &line[0], 6);
			first5[6] = '\0';
			if (!strcmp("struct", first5) || !strcmp("typede", first5))
				continue;
			free(first5);
		}

		if (line[0] == '{' || line[0] == '}')
			continue;

		// assuming the rest are struct members, check if they have valid datatypes
		spaceIndex = indexOf(line, (char)32);
		line = removeSpaces(line);
		type = allo;
		memcpy(type, &line[0], spaceIndex-1);
		type[spaceIndex-1] = '\0';

		// printf("Type of this member: '%s'\n", type);
		if (! in(type, types, 6))
			printf("Error in line %d: %s is not a valid type \n", lineNumber, type);

		free(type);
	}

	fclose(f);
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



