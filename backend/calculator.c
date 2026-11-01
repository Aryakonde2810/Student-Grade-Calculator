#include "calculator.h"

GradeResult calculateGrade(int marks[SUBJECT_COUNT])
{
    GradeResult result;

    result.total = 0;
    result.passed = 1;

    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        result.total += marks[i];

        if (marks[i] < 35)
        {
            result.passed = 0;
        }
    }

    result.percentage = result.total / 5.0f;

    if (result.percentage >= 90)
        result.grade = 'A';
    else if (result.percentage >= 80)
        result.grade = 'B';
    else if (result.percentage >= 70)
        result.grade = 'C';
    else if (result.percentage >= 60)
        result.grade = 'D';
    else if (result.percentage >= 40)
        result.grade = 'E';
    else
        result.grade = 'F';

    return result;
}