/*
 * The above three numbers are A B C
 *Rule 110: 01101110 == (B || C) - (A && B && C)
 *Rule 124: 01111100 == (A || B) - (A && B && C)
 *Rule 30:  00011110 == (A || B || C) - (A && B) - (A && (!B) && C)
 *Rule 90:  01011010 == (A || C) - (A && C)
 */

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void createFirstLine(int *array, int arrlen, int firstline);
void nextLine(int *array, int *next, int arrlen, int rule);
int countRule(int rule, int a, int b, int c);
void writeInFile(int *array, int arrlen, FILE *fp);

int main(void)
{
    FILE *fp;
    int rule, arrlen, rows, firstline, i, j;
    int *array, * next;

    srand((unsigned)time(NULL));
    printf("which Rule do you want to use?\n1:Rule 110\n2:Rule 124\n3:Rule 30\n4:Rule 90\n");
    scanf("%d", &rule);

    printf("How many numbers do you need in first line ?\n");
    scanf("%d", &arrlen);

    array = (int*)malloc(arrlen * sizeof(int));
    next = (int*)malloc(arrlen * sizeof(int));

    printf("How many rows do you want to print?\n");
    scanf("%d", &rows);

    printf("Which mode do you want to create first line?\n1:Total Random\n2:Read on screen\n3:Read in files\n4:A certain switch on\n");
    scanf("%d", &firstline);

    fp = fopen("/home/msc19/ff19085/linux/C/week_3/RuleOut.txt", "w+");
    createFirstLine(array, arrlen, firstline);
    writeInFile(array, arrlen, fp);

    printf("\n");
    for(j = 1; j < rows; j++) {
        nextLine(array, next, arrlen, rule);
        writeInFile(next, arrlen, fp);
        for (i = 0; i < arrlen; i++) {
            array[i] = next[i];
        }

        printf("\n");
    }

    fclose(fp);
    return 0;
}

void createFirstLine(int *array, int arrlen, int firstline)
{
    int i, temp, n;
    FILE *fp;

    if(firstline == 1) {
        for (i = 0; i < arrlen; ++i) {
            temp = rand() % 2;
            array[i] = temp;
        }
    }
    else if (firstline == 2) {
        printf("Please enter the first line:\n");
        for (i = 0; i < arrlen ; ++i) {
            scanf("%d", &array[i]);
        }
    }
    else if (firstline == 3) {
        if ( (fp = fopen("/home/msc19/ff19085/linux/C/week_3/RuleIn.txt", "r")) == NULL ) {
            puts("Fail to open file!");
            exit(0);
        }
        for (i = 0; i < arrlen; ++i) {
            fscanf(fp,"%d", &array[i]);
        }
        fclose(fp);
    }
    else if (firstline == 4) {
        printf("Please enter which switch is on(<%d):\n", arrlen);
        scanf("%d", &n);
        for (i = 0; i < arrlen ; i++) {
            array[i] = 0;
        }
        array[n-1] = 1;
    }
}

void nextLine(int *array, int *next, int arrlen, int rule)
{
    int i;
    for (i = 0; i < arrlen; ++i) {
        if (i == 0) {
            next[i] = countRule(rule, 0, array[i], array[i + 1]);
        } 
        else if (i == (arrlen - 1)) {
            next[i] = countRule(rule, array[i - 1], array[i], 0);
        } 
        else {
            next[i] = countRule(rule, array[i - 1], array[i], array[i + 1]);
        } 
    }
}

int countRule(int rule, int A, int B, int C)
{
    switch (rule) {
        case 1 :
            return ((B || C) - (A && B && C));
        case 2 :
            return ((A || B) - (A && B && C));
        case 3 :
            return ((A || B || C) - (A && B) - (A && (!B) && C));
        case 4 :
            return ((A || C) - (A && C));
    }
    return -1;
}

void writeInFile(int *array, int arrlen, FILE  *fp)
{
    int i;
    for (i = 0; i < arrlen; ++i) {
        fprintf(fp, "%d ", array[i]);
    }
    fprintf(fp, "\n");
}