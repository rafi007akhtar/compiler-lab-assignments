/** Testing all the functions written for Assignment 1 */

#include <stdio.h>
#include "assignment_1.h"

int main()
{
    int i;

    // TEST: endsWithSemiColon
    char *strings[] = {
        "ending with semicolon;",
        "not ending with semicolon",
        "int x = 5;",
        "float f = 12.63"
    };
    for (i = 0; i < 4; i++)
    {
        endsWithSemiColon(strings[i])
            ? printf("%s ends with semi-colon\n", strings[i])
            : printf("%s does not end with semi-colon\n", strings[i]);
    }

    printf("\n");

    // TEST: printADW
    char test[100];
    printf("Enter a string: ");
    gets(test);
    printADW(test);

    printf("\n");

    // TEST: printVC
    printf("Enter a string: ");
    gets(test);
    printVC(test);

    printf("\n");

    // TEST: printAllWords
    printf("Enter a string: ");
    gets(test);
    printAllWords(test);

    printf("\n");

    // TEST: isKeyword
    printf("Enter a string: ");
    gets(test);
    isKeyword(test)
        ? printf("%s is a keyword\n", test)
        : printf("%s is not a keyword\n", test);

    printf("\n");

    // TEST: printIdentifiers
    char *idens[] = {
        "int var = 5; if (var == 5) break;",
        "int _ = 12;",
        "int 123v = 81;",
        "float v@r = 10;",
        "int      var      =         5   ;",
        "int x=5;"
    };
    for (i = 0; i < 6; i++)
    {
        printIdentifiers(idens[i]);
        printf("\n");
    }

    printf("\n");

    // TEST: isAssigned
    char *idens2[] = {
        "int x=328490;",
        "float f=12.6;",
        "int var=5;",
        "int var;",
        "double d=-12.29.320;",
        "long l=-17;",
        "char c='a';",
        "char c=10;",
        "float f=1221143;"
    };
    for (i = 0; i < 9; i++)
    {
        isAssigned(idens2[i])
            ? printf("%s is correctly assigned\n", idens2[i])
            : printf("%s is incorrectly assigned\n", idens2[i]);
    }

    printf("\n");

    // TEST: tokenize
    char *str = "inta=10;";
    tokenize(str);

    printf("\n");

    // TEST: trim
    str = "int      var      =         5   ;";
    trim(str);

    return 0;
}