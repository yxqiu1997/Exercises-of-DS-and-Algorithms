#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26
#define SHORTWORD 4
#define _toupper(c) ((c) + 'A' - 'a')

int *createPrime(int *prime);
unsigned long countMul(char *word, int *prime);

int main(int argc, char **argv)
{
    int *prime = (int *)malloc(sizeof(int) * ALPHABET);
    FILE *fphead, *fpend;
    char *head = (char *)malloc(SHORTWORD * sizeof(char));
    char *end = (char *)malloc(SHORTWORD * sizeof(char));
    int i;
    unsigned long multiply = 1, headMul, endMul;

    if(argc == 2) {
        prime = createPrime(prime);
        multiply = countMul(argv[1], prime);
        fphead = fopen("eng_370k_shuffle.txt", "r");
        fpend = fopen("eng_370k_shuffle.txt", "r");
        
        do {
            fscanf(fphead, "%s", head);
            headMul = countMul(head, prime);
            do {
                fscanf(fpend, "%s", end);
                endMul = countMul(end, prime);
                if (multiply == (endMul * headMul) && (endMul != headMul)) {
                    for (i = 0; i < strlen(head); i++) {
                        printf("%c", (i == 0) ? _toupper(head[i]) : head[i]);
                    }
                    for (i = 0; i < strlen(end); i++) {
                        printf("%c", (i == 0) ? _toupper(end[i]) : end[i]);
                    }
                    printf("\n");
                }
            }while (!feof(fpend));
            fseek(fpend, 0, SEEK_SET);
        }while (!feof(fphead));
    }
    else {
        printf("ERROR: Incorrect usage\n");
    }

    return 0;
}

int *createPrime(int *prime)
{
    int temp, cnt = 0, flag = 0, sqt;
    for (temp = 2; cnt < ALPHABET; temp++) {
        for (sqt = 2; ((sqt < temp) && (flag == 0)); sqt++) {
            if (temp % sqt == 0) {
                flag = 1;
            } 
        }
        if((sqt >= temp) && (flag == 0)) {
            *(prime + cnt) = temp;
            cnt++;
        }
        flag = 0;
    }

    return prime;
}

unsigned long countMul(char *word, int *prime)
{
    int i;
    unsigned long mul = 1;
    for (i = 0; i < strlen(word); i++) {
        mul *= prime[word[i] - 'a'];
    }
    
    return mul;
}