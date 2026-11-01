#include <stdio.h>
#include "calculator.h"

int main()
{
    int marks[SUBJECT_COUNT] = {90, 85, 78, 92, 80};

    GradeResult result = calculateGrade(marks);

    printf("Total Marks: %d/500\n", result.total);
    printf("Percentage: %.2f%%\n", result.percentage);
    printf("Grade: %c\n", result.grade);

    if (result.passed)
        printf("Result: PASS\n");
    else
        printf("Result: FAIL\n");

    return 0;
}