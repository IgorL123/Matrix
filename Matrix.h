#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#endif //MATRIX_MATRIX_H
#include "stdint.h"

typedef struct EL EL;

struct EL
{
    void *data;
    EL (*sum)(EL x, EL y);
    EL (*multi)(EL x, EL y);
    EL (*inv)(EL x);
    size_t size;
};

typedef struct complex {
    float R;
    float I;
} complex ;

EL finit();
EL fsum(EL a,EL b);
EL fmulti(EL a, EL b);
EL finv(EL a);

EL cinit();
EL csum(EL a, EL b);
EL cmulti(EL a, EL b);
EL cinv(EL a);


typedef struct SquareMatrixN {

    int rows;
    void *data;
    EL type;
    size_t size;

} MatrixN ;


struct SquareMatrixN * InitMatrix(int, EL);
struct SquareMatrixN * fPrettyPrint(struct SquareMatrixN *);
struct SquareMatrixN * cPrettyPrint(struct SquareMatrixN *);
struct SquareMatrixN * sumN(struct SquareMatrixN *, struct SquareMatrixN *, int);
struct SquareMatrixN * multiN(struct SquareMatrixN *, struct SquareMatrixN *, int);
struct SquareMatrixN * multiScalar(struct SquareMatrixN *, EL);
struct SquareMatrixN * fInputMatrix(struct SquareMatrixN *);
struct SquareMatrixN * cInputMatrix(struct SquareMatrixN *);
struct SquareMatrixN * transpose(struct SquareMatrixN *);
int testMatrix();
EL matrixCell(struct SquareMatrixN *, int, int);


