#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "Matrix.h"


int ftestValues(const float m1[], const float m2[], const float sum[], const float multi[], EL field){

    struct SquareMatrixN *ma1 = InitMatrix(2, field);
    struct SquareMatrixN *ma2 = InitMatrix(2, field);
    struct SquareMatrixN *ma3 = InitMatrix(2, field);
    struct SquareMatrixN *ma4 = InitMatrix(2, field);
    struct SquareMatrixN *ma5 = InitMatrix(2, field);
    struct SquareMatrixN *ma6 = InitMatrix(2, field);

    float *p1 = (float*)malloc(4 * sizeof(float));
    float *p2 = (float*)malloc(4 * sizeof(float));
    float *p3 = (float*)malloc(4 * sizeof(float));
    float *p4 = (float*)malloc(4 * sizeof(float));
    for (int i = 0; i < 4; i++){
        *(p1 + i) = m1[i];
        *(p2 + i) = m2[i];
        *(p3 + i) = sum[i];
        *(p4 + i) = multi[i];
    }

    ma1->data = (void*)p1;
    ma2->data = (void*)p2;
    ma3 = sumN(ma1, ma2, 0);
    ma4 = multiN(ma1, ma2, 1);
    ma5->data = (void*)p3;
    ma6->data = (void*)p4;

/*
    if (  (memcmp(ma3->data, ma5->data, ma3->size ) != 0) || (memcmp(ma4->data, ma5->data, ma4->size ) != 0)  ){
        return 1;
    }
*/


    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            float a1 = *(float*)matrixCell(ma3, i, j).data;
            float a2 = *(float*)matrixCell(ma5, i, j).data;
            float a3 = *(float*)matrixCell(ma4, i, j).data;
            float a4 = *(float*)matrixCell(ma6, i, j).data;

            if (a1 != a2 || a3 != a4){
                return 1;
            }
        }
    }



    return 0;
}

int ctestValues(const float m1[], const float m2[], const float sum[], const float multi[], EL field){

    struct SquareMatrixN *ma1 = InitMatrix(2, field);
    struct SquareMatrixN *ma2 = InitMatrix(2, field);
    struct SquareMatrixN *ma3 = InitMatrix(2, field);
    struct SquareMatrixN *ma4 = InitMatrix(2, field);
    struct SquareMatrixN *ma5 = InitMatrix(2, field);
    struct SquareMatrixN *ma6 = InitMatrix(2, field);

    complex *p1 = (complex*)malloc(8 * sizeof(complex));
    complex *p2 = (complex*)malloc(8 * sizeof(complex));
    complex *p3 = (complex*)malloc(8 * sizeof(complex));
    complex *p4 = (complex*)malloc(8 * sizeof(complex));
    for (int i = 0; i < 4; i++){
        (p1 + i)->R = m1[i];
        (p2 + i)->R = m2[i];
        (p3 + i)->R = sum[i];
        (p4 + i)->R = multi[i];
        (p1 + i)->I = m1[i + 4];
        (p2 + i)->I = m2[i + 4];
        (p3 + i)->I = sum[i + 4];
        (p4 + i)->I = multi[i + 4];
    }

    ma1->data = (void*)p1;
    ma2->data = (void*)p2;
    ma3 = sumN(ma1, ma2, 0);
    ma4 = multiN(ma1, ma2, 1);
    ma5->data = (void*)p3;
    ma6->data = (void*)p4;

    /*
    if (memcmp(ma3->data, p3, ma3->size ) != 0 || memcmp(ma4->data, p4, ma4->size ) != 0){
        return 1;
    }
     */
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            float a1 = (*(complex*)matrixCell(ma3, i, j).data).R;
            float a2 = (*(complex*)matrixCell(ma5, i, j).data).R;
            float a3 = (*(complex*)matrixCell(ma4, i, j).data).R;
            float a4 = (*(complex*)matrixCell(ma6, i, j).data).R;
            float a5 = (*(complex*)matrixCell(ma3, i, j).data).I;
            float a6 = (*(complex*)matrixCell(ma5, i, j).data).I;
            float a7 = (*(complex*)matrixCell(ma4, i, j).data).I;
            float a8 = (*(complex*)matrixCell(ma6, i, j).data).I;

            if (a1 != a2 || a3 != a4 || a5 != a6 || a7 != a8){
                return 1;
            }
        }
    }


    return 0;
}


int testMatrix(void){
    FILE *file;
    EL field;
    float all = 0;
    float right = 0;


    file = fopen("C:/Users/Zeden/CLionProjects/Matrix/testdata.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
    }


    for(int i = 0; i < 7; i++){
        int type;
        int res1 = fscanf(file, "%d", &type);
        if (res1 == 1){
            //printf("%d\n", type);
        }

        if (type == 1){
            float m1[4];
            float m2[4];
            float sum[4];
            float mult[4];
            field = finit();

            int res = fscanf(file, " %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ",
                             &m1[0], &m1[1], &m1[2], &m1[3], &m2[0], &m2[1], &m2[2], &m2[3], &sum[0], &sum[1],
                             &sum[2], &sum[3], &mult[0], &mult[1], &mult[2], &mult[3]  );

            if (res == 16){
                /*
                for(int j = 0; j < 4; j++ ){
                    printf("%f %f %f %f \n", m1[j], m2[j], sum[j], mult[j]);
                }
                */
                int result = ftestValues(m1, m2, sum ,mult, field);
                if (result == 0){
                    right += 1.0f;
                    printf("Success  test%d \n",i );
                }
                else{
                    printf("Fail on test%d \n",i);
                }
                all += 1.0f;
            }
        }

        if (type == 2){
            float m1[8];
            float m2[8];
            float sum[8];
            float mult[8];
            field = cinit();

            int res = fscanf(file, " %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                             &m1[0], &m1[1], &m1[2], &m1[3], &m1[4], &m1[5], &m1[6], &m1[7], &m2[0], &m2[1], &m2[2],
                             &m2[3], &m2[4], &m2[5], &m2[6], &m2[7], &sum[0], &sum[1],
                             &sum[2], &sum[3],&sum[4], &sum[5],&sum[6], &sum[7], &mult[0], &mult[1], &mult[2], &mult[3],
                             &mult[4], &mult[5], &mult[6], &mult[7]);

            if (res == 32){
                /*
                for(int j = 0; j < 8; j++ ){
                    printf("%f %f %f %f \n", m1[j], m2[j], sum[j], mult[j]);
                }
                */
                int result1 = ctestValues(m1, m2, sum ,mult, field);
                if (result1 == 0){
                    right += 1.0f;
                    printf("Success  test%d \n",i );
                }
                else {
                    printf("Fail on test%d \n",i);
                }
                all += 1.0f;
            }
        }
    }

    printf("%10.2f %% of success tests \n", (right / all * 100));
    printf("%10.1f tests were passed \n", right);
    fclose(file);

    return 0;
}