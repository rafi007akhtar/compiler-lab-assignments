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
    
    
    return 0;
}
