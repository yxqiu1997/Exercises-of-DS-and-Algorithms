#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define MAXlength 46

char **readInLine(FILE *fp, char **array, int cnt);
char **insert(char **array, char *temp, int cnt);
int compare(char *a, char *b);
void change(char *a, char *b);
int tomin(int x, int y);
void printArray(char **array, int cnt);
int countWords(FILE *fp, int cnt);
int isLetter(char c);
char **insertSort(char **array, int cnt);
int weight(int first, int last, char **array, int cnt);
int countLen(char *c);

int main(void)
{
    clock_t startTime, endTime;
    startTime = clock();
    char **array = (char **)malloc(sizeof(char *));
    int cnt = 0;
    FILE *fp = fopen("test.txt", "r");

    array = readInLine(fp, array, cnt);
    cnt = countWords(fp, cnt);
    printArray(array, cnt);
    endTime = clock();
    printf("Total time is:%lf\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
}

char **readInLine(FILE *fp, char **array, int cnt)
{
    char *temp = (char *)malloc(sizeof(char) * MAXlength);
    while (!feof(fp)) {
        fscanf(fp, "%s", temp);
        cnt++;
        array = insert(array, temp, cnt);
    }

    return array;
}

char **insert(char **array, char *temp, int cnt)
{
    int i, length = strlen(temp);
    array = (char **)realloc(array, sizeof(char *) * cnt);
    *(array + cnt - 1) = (char *)malloc(sizeof(char) * length);
    for (i = 0; i < length; i++) {
        *(*(array + cnt - 1) + i) = *(temp + i);
    }
    return insertSort(array, cnt);
}

int countLen(char *c)
{
    int cnt = 0;
    while(*(c + cnt) <= 'z' && *(c + cnt) >= 'a') {
        cnt++;
    }

    return cnt;
}

int compare(char *a, char *b)
{
    int lengtha = countLen(a);
    int lengthb = countLen(b);
    int min = tomin(lengtha, lengthb);
    int i;

    for (i = 0; i<min; i++) {
        if ((*(a + i) - *(b + i)) < 0) {
            return 1;
        }
        else if ((*(a + i) - *(b + i)) > 0) {
            return 0;
        }
    }

    return (lengthb > lengtha) ? 1 : 0;

}

int tomin(int x, int y)
{
    return (x > y) ? y : x;
}

void change(char *a, char *b)
{
    int lengtha = countLen(a);
    int lengthb = countLen(b);
    int i;
    char *tempa = (char *)malloc(sizeof(char) * lengtha);
    char *tempb = (char *)malloc(sizeof(char) * lengthb);

    for (i = 0; i < lengtha; i++) {
        *(tempa + i) = *(a + i);
    }
    for (i = 0; i < lengthb; i++) {
        *(tempb + i) = *(b + i);
    }
    a = (char *)realloc(a, sizeof(char) * lengthb);
    b = (char *)realloc(b, sizeof(char) * lengtha);
    for (i = 0; i < lengthb; i++) {
        *(a + i) = *(tempb + i);
    }
    for (i = 0; i < lengtha; i++) {
        *(b + i) = *(tempa + i);
    }
}

void printArray(char **array, int cnt)
{
    int i, j, length;
    for (i = 0; i < cnt; i++) {
        length = strlen(*(array + i));
        for (j = 0; j < length; j++) {
            if (isLetter(*(*(array + i) + j))) {
                printf("%c", *(*(array + i) + j));
            }
        }
        printf("\n");
    }
}

int countWords(FILE *fp, int cnt)
{
    char *temp = (char *)malloc(sizeof(char) * MAXlength);
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) {
        fscanf(fp, "%s", temp);
        cnt++;
    }

    return cnt;
}

int isLetter(char c)
{
    if ((c - 'a' >= 0) && ('z' - c <= 0)) {
        return 1;
    }
    if((c - 'A' >= 0) && ('Z' - c <= 0)) {
        return 1;
    }

    return 0;
}

char **insertSort(char **array, int cnt)
{
    int first = 0;
    int last = cnt - 1;
    int mid = 0;
    int p = cnt - 1;
    int i;

    while (first < last) {
        mid = weight(first, last, array, cnt);
        if(compare(*(array + p), *(array + mid))) {
            last = mid;
        }
        else {
            first = mid + 1;
        }
    }
    for (i = cnt - 1; i > first; i--) {
        change(*(array + i), *(array + i - 1));
    }

    return array;
}

int weight(int first, int last, char **array, int cnt)
{
    int pos = 0, res;
    while (*(*(array + first) + pos) == *(*(array + last) + pos)) {
        pos++;
    }

    res = first + (*(*(array + cnt - 1) + pos) - *(*(array + first) + pos))\
        / (*(*(array + last) + pos) - *(*(array + first) + pos))*(last - first) - 1;
    return (res < 0) ? 0 : res;
}