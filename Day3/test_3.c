#include <stdio.h>
#include "assignment_3.h"

int main(void)
{
    int i;

    // TEST: calToMal
    char *test_cases_2[] = {
        "calloc(5,sizeof(float))",
        "calloc (120, sizeof(int))",
        "calloc (100, sizeof (char))"
    };
    for (i = 0; i < 3; i++)
        printf("%s\n", calToMal(test_cases_2[i]));
    
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

    return 0;
}
