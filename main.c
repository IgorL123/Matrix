#include <stdio.h>
#include "Matrix.h"

#define FIELD ( (type == 1) ? finit() : cinit() )
#define printM(m) ( (type == 1) ? fPrettyPrint(m) : cPrettyPrint(m) )
#define inputM(m) ((type == 1) ? fInputMatrix(m) : cInputMatrix(m) )

int main(void) {

    unsigned int key = 0;
    unsigned int type;
    int n = 0;
    EL field;

    while (key >= 0){
        int cont;

        if (key > 0){
            printf("Continue? (1 - Yes/0 - NO): \n");
            scanf("%d", &cont);
            if (cont == 0){
                return 0;
            }
        }

        printf(" Choose the operation: \n");
        printf("1. Sum \n2. Multiply \n3. Multiply by a scalar \n4. Transpose \n5. Tests \n6. Exit \n");
        scanf("%d", &key);

        if (key == 6) {
            return 0;
        }
        if (key == 5){
            testMatrix();
        }

        if (key != 5 ){

            printf("Input the type of matrix: 1 - float; 2 - complex; \n");
            scanf("%d", &type);

            field = FIELD;
        }

        if (key == 1) {
            printf("Input the size of matrix: \n");
            scanf("%d", &n);
            struct SquareMatrixN *m1 = InitMatrix(n, field);
            struct SquareMatrixN *m2 = InitMatrix(n, field);
            struct SquareMatrixN *m3;
            printf("Input first matrix: \n");
            inputM(m1);
            printf("-------------------------\n");
            printM(m1);
            printf("Input second matrix: \n");
            inputM(m2);
            printf("-------------------------\n");
            printM(m2);
            printf("-------------------------\n");
            m3 = sumN(m1, m2, 1);
            printf("Result of sum: \n");
            printM(m3);
            printf("-------------------------\n");
        }

        if (key == 2){
            printf("Input the size of matrix: \n");
            scanf("%d", &n);
            struct SquareMatrixN *m1 = InitMatrix(n, field);
            struct SquareMatrixN *m2 = InitMatrix(n, field);
            struct SquareMatrixN *m3;
            printf("Input first matrix: \n");
            inputM(m1);
            printf("-------------------------\n");
            printM(m1);
            printf("Input second matrix: \n");
            inputM(m2);
            printf("-------------------------\n");
            printM(m2);
            printf("-------------------------\n");
            m3 = multiN(m1, m2, 1);
            printf("Result of multiply: \n");
            printM(m3);
            printf("-------------------------\n");

        }

        if (key == 3){
            float lambda;
            printf("Input the size of matrix: \n");
            scanf("%d", &n);
            struct SquareMatrixN *m1 = InitMatrix(n, field);
            struct SquareMatrixN *m3;
            printf("Input your matrix: \n");
            inputM(m1);
            printf("-------------------------\n");
            printM(m1);
            printf("-------------------------\n");
            printf("Input a scalar: \n");
            scanf_s("%f", &lambda);
            struct EL ELl = FIELD;
            float *p = &lambda;
            ELl.data = (void*)p;
            m3 = multiScalar(m1, ELl);
            printf("Result of multiply by a scalar: \n");
            printM(m3);
            printf("-------------------------\n");
        }

        if (key == 4){
            printf("Input the size of matrix: \n");
            scanf("%d", &n);
            struct SquareMatrixN *m1 = InitMatrix(n, field);
            struct SquareMatrixN *m2;
            printf("Input your matrix: \n");
            inputM(m1);
            printf("-------------------------\n");
            printM(m1);
            printf("-------------------------\n");
            m2 = transpose(m1);
            printf("Result of transpose: \n");
            printM(m2);
            printf("-------------------------\n");

        }


    }

}