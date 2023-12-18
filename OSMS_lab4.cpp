#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5

void shiftSequence(int* sequence, int length) {
    int tmp = sequence[length - 1];
    for (int i = 0; i < length; i++) {
        sequence[length - i - 1] = sequence[length - i - 2];
    }
    sequence[0] = tmp;
}

void calculateAutocorrelation(int* sequence, int* shiftedSequence, float* correlation, int length) {
    float result = 0;
    for (int i = 0; i < length; i++) {
        result += (sequence[i] == shiftedSequence[i]) ? 1.0 : -1.0;
    }
    *correlation = result / length;
}

void calculateCrosscorrelation(int* sequence1, int* sequence2, float* correlation, int length) {
    float result = 0.0;
    for (int i = 0; i < length; i++) {
        result += sequence1[i] * sequence2[i];
    }
    *correlation = result;
}

void generateGoldSequence(int* registerX, int* registerY, int* sequence, int length) {
    for (int i = 0; i < length; i++) {
        sequence[i] = (registerX[N - 1] + registerY[N - 1]) % 2;
        shiftSequence(registerX, N);
        shiftSequence(registerY, N);
    }
}

void printShiftTable(int shift, int* shiftedSequence, int* sequence, int length) {
    int i, j;
    float correlation;
    printf("\nShift");
    for (i = 1; i <= length; i++) {
        printf("|%2d", i);
    }
    printf("|Correlation|");
    for (i = 0; i <= shift; i++) {
        printf("\n");
        printf("| %2d ", i);
        for (j = 0; j < length; j++) {
            printf("|%2d", shiftedSequence[j]);
        }
        calculateAutocorrelation(sequence, shiftedSequence, &correlation, length);
        printf("|%5.1f     |", correlation);
        shiftSequence(shiftedSequence, length);
    }
    printf("\n-------------------------------------\n");
}

int main() {
    int i = 0;
    int sequenceLength = pow(2, N) - 1;

    int* sequence1 = (int*)malloc(sequenceLength * sizeof(int));
    int* sequence2 = (int*)malloc(sequenceLength * sizeof(int));
    int* shiftedSequence = (int*)malloc(sequenceLength * sizeof(int));

    int registerX[N] = { 0, 0, 0, 1, 0 };
    int registerY[N] = { 0, 1, 0, 0, 1 };
    int registerX1[N] = { 0, 0, 0, 1, 1 };
    int registerY1[N] = { 0, 0, 1, 0, 0 };

    printf("\nFirst Gold's sequence :\n");
    generateGoldSequence(registerX, registerY, sequence1, sequenceLength);
    for (i = 0; i < sequenceLength; i++) {
        printf("%d", sequence1[i]);
    }
    printf("\n\n");
    for (i = 0; i < sequenceLength; i++) {
        shiftedSequence[i] = sequence1[i];
    }
    printShiftTable(sequenceLength, shiftedSequence, sequence1, sequenceLength);

    printf("\nSecond Gold's sequence :\n");
    generateGoldSequence(registerX1, registerY1, sequence2, sequenceLength);
    for (i = 0; i < sequenceLength; i++) {
        printf("%d", sequence2[i]);
    }
    printf("\n\n");

    float correlation;
    calculateCrosscorrelation(sequence1, sequence2, &correlation, sequenceLength);
    printf("\nCorrelation between the first and second sequence >> %.0f\n", correlation);

    free(sequence1);
    free(sequence2);
    free(shiftedSequence);

    return 0;
}
