#include <stdio.h>
/*
희소 행렬은 여러가지 방법으로 표현가능하다.
행렬은 CS에서 matrix(3,4)와 같이 소괄호로 표현한다. 배열은 [3][4]로 표현한다. 둘은 다른것!!
또한 행렬은 시작 인덱스가 1이다!!
*/

// 1.희소 행렬이지만 sequential하게 저장하는 방법.
// 이 방법은 전체 자료의 선형탐색이 필수적이거나, 특정 (행,렬)에 빠르게 정확히 빠르게 접근하지 않아도 되는 경우 유용하다.
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
(행, 열, 값)의 배열
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
*/

#define MAX_TERMS 10 // MAX_COLS * MAX_ROWS + 1
#define MAX_ROWS 3
#define MAX_COLS 3

SparseMatrix Create(int max_rows, int max_cols);
SparseMatrix transpose_sparseMatrix(SparseMatrix sparseMatrix);

typedef struct
{
    int row;
    int col;
    int val;
} SparseMatrixTerm;

typedef SparseMatrixTerm* SparseMatrix;

void main() {
    SparseMatrix sm;
    SparseMatrix transposed_sm;
    int rows = 3;
    int cols = 3;
    int elements = 3;

    sm = Create(rows, cols);
    transposed_sm = transpose_sparseMatrix(sm);

}

SparseMatrix Create(int max_rows, int max_cols) {
    SparseMatrixTerm sparseMatrix[MAX_TERMS];
    return sparseMatrix;
}

void Transpose(SparseMatrixTerm original[], SparseMatrixTerm transposed[]) {
    int n, i, j, currentb;
    n = original[0].val; //total number of elements
    transposed[0].row = original[0].col; //rows in transposed = columns in original
    transposed[0].col = original[0].row; //columns in transposed = rows in original
    transposed[0].val = n;

    if (n > 0) { // if non zero matrix
        currentb = 1;
        for (i = 0; i < original[0].col; i++) {
            // transpose by the columns in a
            for (j = 1; j <= n; j++) {
                // find elements from the current column
                if (original[j].col == i) {
                    // element is in current column, add it to transposed matrix
                    transposed[currentb].row = original[j].col;
                    transposed[currentb].col = original[j].row;
                    transposed[currentb].val = original[j].val;
                    currentb++;
                }
            }
        }
    }
}