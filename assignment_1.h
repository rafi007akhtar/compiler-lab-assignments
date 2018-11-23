/** The following assignments were given on Day 1. */
#include <stdlib.h>
#include <string.h>
#define allo (char *) malloc(sizeof(char)*100)

typedef enum boolean {false, true} bool;

// Q1: Check if a string ends in semi-colon
bool endsWithSemiColon(char *str)
{
    int pos = -1;
    while(str[++pos]);
    if (str[pos-1] == ';') return true;
    else return false;
}

// Q2: Print all alphabets, digits and whitespaces in a string, and their counts
void printADW(char *str)
{
    int whiteCount = 0;
    int digitCount = 0;
    int alphaCount = 0;

    char *digits = allo;
    char *alphas = allo;
    int ch;

    int pos = -1;
    int i; 

    while(str[++pos])
    {
        ch = (int)str[pos];
        if ((ch >= 7 && ch <= 13) || ch == 32) // white spaces
            whiteCount++;
        else if ((ch >= 65 && ch <= 91) || (ch >= 97 && ch <= 122)) // alphabets
            alphas[alphaCount++] = (char)ch;
        else if (ch >= 48 && ch <= 57) // digits
            digits[digitCount++] = (char)ch;
    }
    alphas[alphaCount] = '\0';
    digits[digitCount] = '\0';

    // print the alphabets
    printf("Number of alphabets: %d\n", alphaCount);
    printf("Alphabets: ");
    for (i = 0; i <= alphaCount; i++) printf("%c ", alphas[i]);
    printf("\n");

    // print the digits
    printf("Number of digits: %d\n", digitCount);
    printf("Digits: ");
    for (i = 0; i <= digitCount; i++) printf("%c ", digits[i]);
    printf("\n");
    
    // print the whitespace count
    printf("Number of whitespaces: %d\n", whiteCount);    
}

// Q3: Print vowels and consonants in a string along with their positions
void printVC(char *str)
{
    int pos = -1;
    char ch;

    printf("VOWELS \n--------\n");
    while(str[++pos])
    {
        ch = str[pos];
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
            ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            printf("%c in position %d\n", ch, pos);
    }

    pos = -1;
    printf("\nCONSONANTS \n--------\n");
    while(str[++pos])
    {
        ch = str[pos];
        if (!(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
            ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'))
        {
            int p = ch;
            if ((p >= 65 && p <= 91) || (p >= 91 && p <= 122))
                printf("%c in position %d\n", ch, pos);
        }
    }
}

// Q4: Take a string, extract individual words, and print them
void printAllWords(char *str)
{
    int p = -1;
    int ch;
    while(str[++p])
    {
        ch = str[p];
        if (ch == 32)
            printf("\n");
        else printf("%c", ch);
    }
}

// Q6: Identify if a string is a keyword or not
bool isKeyword(char *str)
{
    char *keywords[] = {
        "auto",	"break",	"case",	"char",
        "const",	"continue",	"default",	"do",
        "double",	"else",	"enum",	"extern",
        "float",	"for",	"goto",	"if",
        "int",	"long",	"register",	"return",
        "short",	"signed",	"sizeof",	"static",
        "struct",	"switch",	"typedef",	"union",
        "unsigned",	"void",	"volatile",	"while"
    };

    // TODO: Change the following linear search into binary for shorter time complexity
    int i;
    for (i = 0; i < 32; i++)
    {
        if (! strcmp(keywords[i], str))
            return true;
    }
    return false;
}

// Q7: Recognize all identifiers in a string

bool isIdentifier(char *str)
{
    int pos;

    int firstChar = str[0]; // first character can be an alphabet or an underscore
    if (! 
        (str[0] == '_' || 
        (firstChar >= 65 && firstChar <= 91) || 
        (firstChar >= 97 && firstChar <= 122))
    )
        return false;
    
    // now scan the string from 1 till end
    // you should encounter only digits, underscores and/or alphabets
    pos = 0;
    int temp;
    while(str[++pos])
    {
        temp = str[pos];
        if (! 
            (str[pos] == '_' || 
            (temp >= 65 && temp <= 91) || 
            (temp >= 97 && temp <= 122) ||
            (temp >= 48 && temp <= 57))
        )
            return false;
    }

    // all tests passed if reached this far
    return true;
}
void printIdentifiers(char *str)
{
    int pos = -1;
    int first, last;
    char iden[100];

    while(str[++pos])
    {
        if (str[pos] == '=')
        {
            if (str[pos+1] == '=') // '==' is a conditional, so skip
                continue;
            
            last = pos;
            // iterate back through the string until you encounter an identifier
            // that will happen when all the whitespaces are scanned
            while( ((int)str[--last]) == 32 );

            // now temp points to last position of the identifier string
            // we need to get the first position
            first = last;
            while( ((int)str[--first]) != 32 );
            first++; // now first points to the first position of identifier string

            // str[first to last] = identifier
            memcpy(iden, &str[first], last-first+1);
            iden[last-first+2] = '\0';

            // check if the identifier follows the C rules of identifiers
            if (isIdentifier(iden)) printf("%s ", iden);
        }
    }
}

// Q8: Check whether an identifier is assigned a valid value
bool isAssigned(char *str)
{
    // get the name of the datatype, which is str from 0 to the first space
    int pos = -1;
    char datatype[100];
    while(str[++pos])
    {
        if ((int) str[pos] == 32)
            break;
    }
    memcpy(datatype, &str[0], pos);
    datatype[pos+1] = '\0';

    // now, get  the value of the variable, which appears after '=' and before ';'
    char val[100];
    int ind1, ind2;
    ind1 = ind2 = -1;
    while (str[++pos])
    {
        if (str[pos] == '=')
            ind1 = pos + 1; // assuming no spaces b/w '=' and value
        if (str[pos] == ';')
        {
            ind2 = pos-1;
            break;
        }
    }

    // if no '=' exists, there is no assignment done
    if (ind1 == -1 || ind2 == -1) return false;

    memcpy(val, &str[ind1], ind2-ind1+1);
    val[ind2-ind1+2] = '\0';

    // printf("Type: %s \nVal: %s\n", datatype, val);

    /* datatypes: 
        [x] short, 
        [x] int, 
        [x] float, 
        [x] char, 
        [x] long, 
        [x] double
    not supporting combined types like long int or const int
    */

    if (!strcmp(datatype, "short") || !strcmp(datatype, "int") || !strcmp(datatype, "long"))
    {
        // check for all ints
        pos = -1;
        while(val[++pos])
        {
            if (val[pos] == '-' || val[pos] == '+')
            {
                // this can happen only in the beginning
                if (pos > 0)
                    return false;
                continue;
            }
            if ((int) val[pos] < 48 || (int) val[pos] > 57)
                return false;
        }
    }
    
    int periodCount = 0;
    if (!strcmp(datatype, "float") || !strcmp(datatype, "double"))
    {
        pos = -1;
        while(val[++pos])
        {
            if (val[pos] == '-' || val[pos] == '+')
            {
                // this can happen only in the beginning
                if (pos > 0)
                    return false;
                continue;
            }
            if (val[pos] == '.')
            {
                // periods in a float should appear only once
                periodCount++;
                if (periodCount > 1) return false;
                continue;
            }
            
            // check for all floats
            if ((int) val[pos] < 48 || (int) val[pos] > 57)
            {
                printf("Biting the dust here with char %c at pos. %d and ASCII %d\n", val[pos], pos, val[pos]);
                return false;
            }
        }
    }

    if (! strcmp(datatype, "char"))
    {
        // chars can be only one letter long, plus the surrounding quotes ''
        if (val[0] != '\'' || val[2] != '\'' || val[3] != '\0') 
            return false;
    }

    return true;
}
