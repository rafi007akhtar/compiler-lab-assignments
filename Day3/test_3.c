#include <stdio.h>
#include "assignment_3.h"

int main(void)
{
    int i;

    // TEST: checkPrerequisites
    char *test_cases_1[] = {"incorrect.c", "hello-world.c"};
    for (i = 0; i < 2; i++)
        checkPrerequisites(test_cases_1[i])
            ? printf("Program %s has prerequisites\n", test_cases_1[i])
            : printf("Program %s does not have prerequisites\n", test_cases_1[i]);

    printf("\n");

    // TEST: calToMal
    char *test_cases_2[] = {
        "calloc(5,sizeof(float))",
        "calloc (120, sizeof(int))",
        "calloc (100, sizeof (char))"
    };
    for (i = 0; i < 3; i++)
        printf("%s\n", calToMal(test_cases_2[i]));
    
    printf("\n");


    // TEST: varSize
    int size = varSize("findSize.c");
    printf("Size of variables in findSize.c = %d bytes\n", size);

    printf("\n");

    // TEST: checkReturn
    checkReturn("return_types.c");

    printf("\n");

    // TEST: hasMonday
    char *test_cases_6[] = {
        "Monday - 1 Day",
        "Tuesday - 2 Day",
        "Wednesday - when, what day?",
        "Thursday! The third day.",
        "Satuday night, big night, date night, SA-TUR-DAY night",
        "It's Sunday! It's God's day."
    };
    for (i = 0; i < 6; i++)
    {
        hasMonday(test_cases_6[i])
            ? printf("%s has Monday\n", test_cases_6[i])
            : printf("%s does not have Monday\n", test_cases_6[i]);
    }

    printf("\n");

    // TEST: initialize
    // initialize("initialize.c"); // TODO: Uncomment this line before pushing!
    printf("Variables in file initialize.c have been initialized\n");

    printf("\n");

    return 0;
}
