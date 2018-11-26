/** The following assignments were given on Day 2. */
#include <stdlib.h>
#define allo (char *) malloc(sizeof(char)*100)

typedef enum boolean {false, true} bool; // created my own bool datatype

// Q1: Write a C program to implement strcpy() function.
void strcpy(char *dest, char *source)
{
    char c = 0;
    int p = 0;
    while (source[c])
        dest [p++] = source[c++];
    dest[p] = '\0';
}

// Q2: Write a C program to implement strcat() function.
void strcat(char *str1, char *str2)
{
    int n1, n2;

    // figure out where str1 ends
    n1 = 0;
    while(str1[n1])
        n1++;
    
    // concatenate contents of str2[n2:] to str1[n1]
    n2 = 0;
    while(str2[n2])
        str1[n1++] = str2[n2++];
    str2[n2] = '\0';
}

// Q3: Input a string and write a C program to find if another string is present in it. 
//     If present, print the starting and ending position where the sub-string exists. 
int whereSubstring(char *word, char *str)
{
    // Return the position in str where word is present
    // Return -1 if not present

    char *temp = allo;
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
                return pos-tPos;
            return -1;
        }

        // when you are anywhere but the end
        if ((int) str[pos] == 32)
        {
            temp[++tPos] = '\0';
            if (! strcmp(temp, word))
                return pos-tPos;
            free(temp);
            temp = allo;
            tPos = -1;
            continue;
        }
        temp[++tPos] = str[pos];
    }
}


// Q4: Write a program to recognize constants.
bool isConst(char *str)
{
    // 43 = '+', 45 = '-', 48 to 57 = '0' to '9', 46 = '.'

    int flag = true;
    int pos = 0;
    int ch; 
    int periodCount = 0;

    while(str[pos])
    {
        ch = (int)str[pos];
        if (ch == 46) // check for period (.)
        {
            periodCount++;

            // periods cannot occur more than once, eg: 123.12.4 is invalid
            // periods cannot appear at the end, eg: 123124. is invalid
            if (periodCount > 1 || !str[pos+1])
            {
                flag = false; 
                break;
            }            
        }
        else if (ch == 43 || ch == 45) // check for + and -
        {
            // they can only occur in the beginning 
            if (pos > 0)
            {
                flag = false;
                break;
            }
        }   
        else if (ch >=48 && ch <= 57)
        {
            pos++;
            continue;
        }
        else
        {
            flag = false;
            break;
        }
        pos++;
    }

    return flag;
}

// Q5: Write a C program to identify whether a given line is a comment or not.
bool isComment(char *line)
{
    bool flag = false;

    // check for single-line comments
    if (line[0] == '/' && line[1] == '/')
        return true;
    
    // check for multi-line comments
    if (line[0] == '/' && line[1] == '*')
        return true;

    // otherwise, it is not a comment
    return false;
}

// Q8: Write a C program which can recognize whether an email address is valid or not.
bool isEmail(char* email)
{
    /* TESTS:
      * for @
      * for .
    */

    int atPos = -1; // signifies @ is not present
    int periodPos = -1; // signifies . is not present

    int emailPos = -1;
    while(email[++emailPos])
    {
        if (email[emailPos] == '@')
        {
            atPos = emailPos; // @ exists!
            break;
        }
    }

    // there should be atleast 1 character before @
    if (atPos < 1) return false;

    // once the @ has been encountered, continue to search for period
    while(email[++emailPos])
    {
        if (email[emailPos] == '.')
        {
            periodPos = emailPos;
            break;
        }
    }

    // if no period is encountered, it's not a valid email
    if (periodPos == -1) return false;
    // if there are no characters between @ and . it's not a valid email
    if (periodPos == emailPos+1) return false;
    // if the period encountered is the last character, it's not a valid email
    if (!email[periodPos+1]) return false;

    // otherwise, it's a valid email!
    return true;
}

// Q9: Write a C program that will take a C string as input and output 
// a string which will have \n and \b replaced by corresponding spaces.
void replaceBySpaces(char *str)
{
    int pos = 0;

    while(str[pos])
    {
        if (str[pos] == '\n' || str[pos] == '\b')
            str[pos] = (int)32;
        pos++;
    }
}

void printString(char *str)
{
    int pos = 0;
    while(str[pos])
        printf("%c", str[pos++]);
}
