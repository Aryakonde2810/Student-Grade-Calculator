#ifndef CALCULATOR_H
#define CALCULATOR_H

#define SUBJECT_COUNT 5

typedef struct {
    int total;
    float percentage;
    char grade;
    int passed;
} GradeResult;

GradeResult calculateGrade(int marks[SUBJECT_COUNT]);

#endif