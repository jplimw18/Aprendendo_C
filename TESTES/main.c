#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef float sample[3];

sample add_train[] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 10},
};

sample *train = add_train;
size_t train_count = 4;
// #define train_count (sizeof(train)/sizeof(train[0]))

float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}

float rand_float() {
    return (float) rand() / (float) RAND_MAX;
}

float cost(float w1, float w2, float b) {
    float result = 0.0f;

    for (size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(w1*x1 + w2*x2 + b);
        float d = y - train[i][2];
        result += d * d;
    }

    result /= train_count;
    return result;
}

int main(void) {
    srand(time(0));
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float() * 3.f;

    float eps = 1e-1;
    float rate = 1e-1;


    for(size_t i = 0; i < 100*100; ++i) {
        float c = cost(w1, w2, b);

        float dw1 = (cost(w1 + eps, w2, b) - c) / eps;
        float dw2 = (cost(w1, w2 + eps, b) - c) / eps;
        float db = (cost(w1, w2, b + eps) - c) / eps;

        w1 -= rate * w1;
        w2 -= rate * w2;
        b  -= rate * b;
    } 

    for(size_t i = 0; i < (train_count / 2); ++i) {
        for(size_t j = 0; j < (train_count / 2); ++j) {
            printf("%zu + %zu = %f\n", i, j, sigmoidf(i * w1 + j * w2 + b));
        }
    }

    return 0;
}