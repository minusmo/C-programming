#include <stdio.h>
/*
희소 행렬은 여러가지 방법으로 표현가능하다.
행렬은 CS에서 matrix(3,4)와 같이 소괄호로 표현한다. 배열은 [3][4]로 표현한다. 둘은 다른것!!
또한 행렬은 시작 인덱스가 1이다!!
*/

// 1.희소 행렬이지만 sequential하게 저장하는 방법.
// 이 방법은 전체 자료의 선형탐색이 필수적이거나, 특정 (행,열)에 빠르게 정확히 빠르게 접근하지 않아도 되는 경우 유용하다.
int matrix1[9] = {1, 0, 0, 0, 0, 2, 0, 3, 0};

// 2.최대 크기를 갖는 행을 기준으로 열 크기 * 최대 행의 크기의 1차원 배열을 선언하는 방법.
// 이 방법은 정해진 크기만큼의 메모리(행의 크기)를 불러오는 작업에서 효율적이다. 또한 희소행렬을 (행, 열, 값)으로 표현시에 빠르게 
// 메모리 공간에서 접근 가능하다.
// 그러나 사용하지 않는 공간을 미리 할당하므로 공간의 낭비가 있다.
int matrix2[9] = {1,0,0, 0,0,2, 0,3,0};

// 3.최대 크기를 갖는 행을 기준으로 열 크기 * 최대 행의 크기의 2차원 배열들의 배열을 선언하는 방법.
// 이 방법은 특정 행에 빠르게 접근하는 작업에서 효율적이다. 또한 행이 명시적으로 나누어져 있기 때문에, 메모리가 부족할 시에 부분적으로 메모리(캐시나 레지스터 등)에 로드하여 사용할 수 있다.
// 그러나 역시 사용하지 않는 공간을 미리 할당하므로 공간의 낭비가 있다.
int matrix3[3][3] = {{1,0,0}, {0,0,2}, {0,3,0}};

/*
희소행렬은 0이 아닌 요소가 공간을 절반이상 차지하므로,
다음과 같이 표현하는 것이 효율적이다.
<행, 열, 값>의 배열
다음은 위의 희소 행렬을 다르게 표현한 것이다.
C 언어에서는 Row-Major-Order: 행을 기준으로 오름차순 정렬을 지원한다.
*/
int sparseMatrix[3][3] = {{1,1,1}, {2,3,2}, {3,2,3}};

// 이렇게 표현할 수도 있지만, 더 적절한 표현과 정보의 저장을 위해 구조체를 정의하여
// 사용하는 것이 좋겠다.
/*
희소행렬은 보통 4가지 함수를 구현해야 하는데,
1. Create: 희소 행렬을 생성하는 함수
2. Transpose: 희소 행렬의 전치 행렬을 생성하는 함수
3. Add: 두 개의 희소 행렬을 더하는 함수
4. Multipy: 두 개의 희소 행렬을 곱하는 함수
이다.

희소행렬은 희소행렬의 
원소 집합 <행, 열, 값>의 구조체와
이를 저장하는 배열로 표현된다.
이 배열의 크기는 행렬의 최대 크기 + 1 이다.
그 이유는, 배열의 첫번째 원소에 <전체 행의 수, 전체 열의수, 전체 0이 아닌 원소의 수> 를 저장하기 때문이다.
그리고 자연스레 행렬의 첫번째 인덱스도 1이 된다.
*/

#define MAX_TERMS 10 // MAX_COLS * MAX_ROWS + 1
#define MAX_ROWS 3
#define MAX_COLS 3


typedef struct
{
    int row;
    int col;
    int val;
} SparseMatrixTerm;

typedef SparseMatrixTerm* SparseMatrix;

SparseMatrix Create(int max_rows, int max_cols);
void Transpose(SparseMatrix original, SparseMatrix transposed);
void fastTranspose(SparseMatrix original, SparseMatrix transposed);
void MatrixMultiplication(SparseMatrix m1, SparseMatrix m2, SparseMatrix m3);

void main() {
    SparseMatrix sm;
    SparseMatrix transposed_sm;
    int rows = 3;
    int cols = 3;
    int elements = 3;

    sm = Create(rows, cols);
    Transpose(sm, transposed_sm);

}

SparseMatrix Create(int max_rows, int max_cols) {
    SparseMatrixTerm *sparseMatrix[MAX_TERMS];
    return sparseMatrix;
}

void Transpose(SparseMatrixTerm original[], SparseMatrixTerm transposed[]) {
    int n, i, j, currentTransposedIndex;
    n = original[0].val; //total number of elements
    transposed[0].row = original[0].col; //rows in transposed = columns in original
    transposed[0].col = original[0].row; //columns in transposed = rows in original
    transposed[0].val = n;

    if (n > 0) { // if non zero matrix
        currentTransposedIndex = 1;
        for (i = 0; i < original[0].col; i++) {
            // transpose by the columns in original
            for (j = 1; j <= n; j++) {
                // find elements from the current column
                if (original[j].col == i) {
                    // element is in current column, add it to transposed matrix
                    transposed[currentTransposedIndex].row = original[j].col;
                    transposed[currentTransposedIndex].col = original[j].row;
                    transposed[currentTransposedIndex].val = original[j].val;
                    currentTransposedIndex++;
                }
            }
        }
    }
}

void MatrixMultiplication(SparseMatrix m1, SparseMatrix m2, SparseMatrix m3) {
    int i, j, column;
    int totalM1Values = m1[0].val;
    int totalM2Values = m2[0].val;
    int totalM3Values = 0;
    int rows_m1 = m1[0].row, cols_m1 = m1[0].col;
    int cols_m2 = m2[0].col;
    int row_begin = 1, row = m1[1].row, sum = 0;
    SparseMatrixTerm new_m2[MAX_TERMS];

    if (cols_m1 != m2[0].row) {
        fprintf(stderr, "Incompatible matrices\n");
        exit(1);
    }
    Transpose(m2, new_m2);
    // set boundary condition
    m1[totalM1Values+1].row = rows_m1;
    new_m2[totalM2Values+1].row = cols_m2;
    new_m2[totalM2Values+1].col = 0;

    for (i = 1; i <= totalM1Values;) {
        column = new_m2[1].row;
        for (j = 1; j <= totalM2Values+1;) {
            // multiply row of m1 by column of m2
            if (m1[i].row != row) {
                storesum(m3, &totalM3Values, row, column, &sum);
                i = row_begin;
                for (; new_m2[j].row == column; j++) {
                    column = new_m2[j].row;
                }
            }
            else if (new_m2[j].row != column) {
                storesum(m3, &totalM3Values, row, column, &sum);
                i = row_begin;
                column = new_m2[j].row;
            }
            else switch (COMPARE(m1[i].col, new_m2[j].col)) {
                case -1://go to next term in m1
                    i++;
                    break;
                case 0://add terms, go to next term in m1 and m2
                    sum += (m1[i++].val * new_m2[j++].val);
                    break;
                case 1://advance to next term in b
                    j++;
            }
        }// end of for j <= totalM2Value+1

        for (; m1[i].row == row; i++) {
            row_begin = i;
            row = m1[i].row;
        }
    }//end of for i <= totalM1Value
    m3[0].row = rows_m1;
    m3[0].col = cols_m2;
    m3[0].val = totalM3Values;
}

void fastTranspose(SparseMatrix original, SparseMatrix transposed) {
    // terms in rows of transposed matrix, starting position of rows of transposed matrix
    int row_terms[MAX_COLS], starting_pos[MAX_COLS];
    int i, j, num_cols = original[0].col, num_terms = original[0].val;
    transposed[0].row = num_cols;
    transposed[0].col = original[0].row;
    transposed[0].val = num_terms;

    if (num_terms > 0) {
        // if non-zero matrix, do the transposing
        // the first 2 for loops: compute values for row_terms
        for (i=0; i < num_cols; i++) {
            // initialize row terms in transposed matrix
            row_terms[i] = 0;
        }
        for (i=1; i <= num_terms; i++) {
            // compute row terms in transposed matrix for each column in original matrix
            row_terms[original[i].col]++;
        }
        starting_pos[0] = 1;
        // the third for loop: computation of starting_pos
        for (i=1; i < num_cols; i++) {
            // starting point(position) of row i-1 + number of elements in row i-1
            starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
        }
        // last for loop: place the triples into the transposed matrix
        for (i=1; i <= num_terms; i++) {
            j = starting_pos[original[i].col]++;
            transposed[j].row = original[i].col;
            transposed[j].col = original[i].row;
            transposed[j].val = original[i].val;
        }
    }
}