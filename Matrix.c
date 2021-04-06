#include "string.h"
#include "Matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

struct SquareMatrixN *InitMatrix(int row, EL field) {
    assert(row > 0);

    struct SquareMatrixN *m = (struct SquareMatrixN *)malloc(sizeof(struct SquareMatrixN));
    m->rows = row;
    m->type = field;
    m->size = (m->type.size);
    m->data = malloc(m->size);

    return m;
}

struct SquareMatrixN * sumN(struct SquareMatrixN *m1, struct SquareMatrixN *m2, int tofreedata){
    struct EL type1 = m1->type;
    struct EL type2 = m2->type;
    void *data;

    assert(m1->rows == m2->rows);
    assert(type1.sum == type2.sum);

    struct SquareMatrixN *m3 = (struct SquareMatrixN *)malloc(sizeof(struct SquareMatrixN));
    m3->data = malloc(m1->size);
    data = malloc(m1->rows * m1->rows * (m1->size));

    for (int i = 0; i < m1->rows; i++){
        for (int j = 0; j < m1->rows; j++){

            struct EL el1 = matrixCell(m1, i, j);
            struct EL el2 = matrixCell(m2, i, j);
            memcpy((void*)((char*)data + (i * m1->rows + j) * type1.size), type1.sum(el1, el2).data, type1.size);
        }
    }

    m3->rows = m1->rows;
    m3->type = type1;
    m3->data = data;
    if (tofreedata){
        free(m1->data);
        free(m2->data);
    }

    return m3;
}


struct SquareMatrixN * multiN(struct SquareMatrixN *m1, struct SquareMatrixN *m2, int tofreedata){
    struct EL type1 = m1->type;
    struct EL type2 = m2->type;
    void *data;

    assert(m1->rows == m2->rows);
    assert(type1.sum == type2.sum);

    struct SquareMatrixN *m3 = (struct SquareMatrixN *)malloc(sizeof(struct SquareMatrixN));
    m3->data = malloc(m1->size);
    data = malloc(m1->rows * m1->rows * (m1->size));


    for (int i = 0; i < m1->rows; i++){
        for (int j = 0; j < m1->rows; j++){

            struct EL cell;
            for (int k = 0; k < m1->rows; k++){
                struct EL el1 = matrixCell(m1, i, k);
                struct EL el2 = matrixCell(m2, k, j);
                if (k == 0) {
                    cell = type1.multi(el1, el2);
                }
                else {
                    cell = type1.sum(type1.multi(el1, el2), cell);
                }
            }
            memcpy((void*)((char*)data + (i * m1->rows + j) * type1.size), cell.data, type1.size);
        }
    }
    m3->rows = m1->rows;
    m3->type = type1;
    m3->data = data;
    if (tofreedata){
        free(m1->data);
        free(m2->data);
    }

    return m3;
}


struct SquareMatrixN * multiScalar(struct SquareMatrixN *m, EL lambda){
    struct EL type1 = m->type;
    void *data;

    assert(type1.multi == lambda.multi);
    assert(type1.size == lambda.size);

    struct SquareMatrixN *m1 = (struct SquareMatrixN *)malloc(sizeof(struct SquareMatrixN));
    m1->data = malloc(m->size);
    data = malloc(m->rows * m->rows * (m->size));

    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->rows; j++ ){

            struct EL el1 = matrixCell(m, i, j);
            memcpy((void*)((char*)data + (i * m->rows + j) * type1.size), type1.multi(el1, lambda).data, type1.size);
        }
    }
    m1->rows = m->rows;
    m1->type = type1;
    m1->data = data;
    free(m->data);

    return m1;
}

struct SquareMatrixN *transpose(struct SquareMatrixN *m){
    struct EL type1 = m->type;
    void *data;

    struct SquareMatrixN *m1 = (struct SquareMatrixN *)malloc(sizeof(struct SquareMatrixN));
    m1->data = malloc(m->size);
    data = malloc(m->rows * m->rows * (m->size));

    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->rows; j++ ){

            struct EL el1 = matrixCell(m, i, j);
            memcpy((void*)((char*)data + (j * m->rows + i) * type1.size), el1.data , type1.size);
        }
    }
    m1->rows = m->rows;
    m1->type = type1;
    m1->data = data;
    free(m->data);

    return m1;
}



struct SquareMatrixN * fPrettyPrint(struct SquareMatrixN *m){
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->rows; j++){
            printf("%f ", *((float*)(m->data) + (i * m->rows + j)));
        }
        printf("\n");
    }
    return 0;
}

struct SquareMatrixN * cPrettyPrint(struct SquareMatrixN *m){
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->rows; j++){
            printf("(%f %f) ", ((complex *)(m->data) + (i * m->rows + j))->R, ((complex *)(m->data) + (i * m->rows + j))->I  );
        }
        printf("\n");
    }
    return 0;
}




EL matrixCell(struct SquareMatrixN *m, int row, int columns){
    assert(m->rows > row);
    assert(m->rows > columns);
    assert(row >= 0 && columns >= 0);

    struct EL res = m->type;
    char *c = ((char*)(m->data) + (row * m->rows + columns)*m->type.size );
    res.data = (void*)c;

    return res;
}
