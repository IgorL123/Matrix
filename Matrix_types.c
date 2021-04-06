#include "Matrix.h"
#include "stdlib.h"
#include "stdio.h"


EL finit(){
    float *data = (float* )malloc(sizeof(float));
    EL field = { data, fsum, fmulti, finv, sizeof(float) };
    return field;
}


EL fsum(EL a, EL b){
    float *sum = (float*)malloc(sizeof(float));
    sum[0] = *(float*)a.data + *(float*)b.data;
    struct EL res = finit();
    res.data = sum;
    return res;
}

EL fmulti(EL a, EL b){
    float *multi = (float*)malloc(sizeof(float));
    *multi = *(float*)a.data * *(float*)b.data;
    struct EL res = finit();
    res.data = multi;
    return res;
}

EL finv(EL a){
    float *inv = (float*)malloc(sizeof(float));
    *inv = 1 / (*(float *)a.data );
    struct EL res = finit();
    res.data = inv;
    return res;
}

EL cinit(){
    complex *data = (complex*)malloc(sizeof(complex));
    EL field = { data, csum, cmulti, cinv, sizeof(struct complex) };
    return field;
}

EL csum(EL a, EL b){
    complex *sum = (complex*)malloc(sizeof(complex));
    (*sum).I = (*(complex*)a.data).I + (*(complex*)b.data).I;
    (*sum).R = (*(complex*)a.data).R + (*(complex*)b.data).R;
    struct EL res = cinit();
    res.data = sum;
    return res;
}

EL cmulti(EL a, EL b){
    complex *multi = (complex*)malloc(sizeof(complex));
    float R1 = (*(complex*)a.data).R;
    float R2 = (*(complex*)b.data).R;
    float I1 = (*(complex*)a.data).I;
    float I2 = (*(complex*)b.data).I;
    (*multi).R = R1 * R2 - I1 * I2;
    (*multi).I = R1 * I2 + R2 * I1;
    struct EL res = cinit();
    res.data = multi;
    return res;
}

EL cinv(EL a){
    complex *inv = (complex*)malloc(sizeof(complex));
    float q = (*(complex*)a.data).I * (*(complex*)a.data).I + (*(complex*)a.data).R * (*(complex*)a.data).R;
    (*inv).R = (*(complex*)a.data).R / q;
    (*inv).I = (*(complex*)a.data).I / (-q);
    struct EL res = cinit();
    res.data = inv;
    return res;
}

struct SquareMatrixN *fInputMatrix(struct SquareMatrixN *m) {
    float *p = NULL;
    p = (float *) malloc((m->rows * m->rows) * sizeof(float));

    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->rows; j++){
            scanf_s("%f", (p + i * (m->rows) + j)); // 2D reallocation in 1D array
        }
    }
    m->data = p;
    return m;
}

struct SquareMatrixN *cInputMatrix(struct SquareMatrixN *m) {
    struct complex *p = NULL;
    p = (complex *) malloc((m->rows * m->rows) * sizeof(complex));

    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->rows; j++){
            scanf("%f %f", &(p + i * (m->rows) + j)->R, &(p + i * (m->rows) + j)->I );
        }
    }
    m->data = p;
    return m;
}