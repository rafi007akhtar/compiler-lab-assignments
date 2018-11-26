/** This program will test all the functions defined in assignment files */

#include <stdio.h>
#include "assignment_2.h"

int main(void)
{
    // TEST: strcpy
    char str1[] = "hello";
    puts(str1);
    char str2[] = "";
    strcpy(str2, str1);
    puts(str2);

    printf("\n");

    // TEST: strcat
    char s1[] = "hello ";
    char s2[] = "world";
    strcat(s1, s2);
    puts(s1);
    puts(s2);

    printf("\n");

    // TEST: isConst
    char *lit_test[] = {"012", "+123", "45", "-23", "3.1416", "1.2.3", "hello, world", "1+2", "4-5"};
    int i;
    for (i = 0; i < 9; i++)
    {
        isConst(lit_test[i]) 
            ? printf("%s is const\n", lit_test[i]) 
            : printf("%s is not const\n", lit_test[i]);
    }

    printf("\n");

    // TEST: isComment
    char *lines[] = {
        "winter is coming",
        "// winter is coming",
        "/* winter is coming */",
        "x = 1.5;",
        "float y;"
    };
    for (i = 0; i < 5; i++)
    {
        isComment(lines[i]) 
            ? printf("%s is a comment\n", lines[i]) 
            : printf("%s is not comment\n", lines[i]);
    }

    printf("\n");

    // TEST: isEmail
    char *emails[] = {
        "alimdrafi@gmail.com",
        "this is not an email",
        "@.",
        "here.appearsbefore@hurray",
        "this.is@yahoo.com"
    };
    for (i = 0; i < 5; i++)
    {
        isEmail(emails[i])
            ? printf("%s is a valid email\n", emails[i])
            : printf("%s is an invalid email\n", emails[i]);
    }

    printf("\n");

    // TEST: replaceBySpaces
    char str[] = "yo\nyo\byo";
    replaceBySpaces(str);
    puts(str);

    return 0;
}
