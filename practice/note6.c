/*
제 10장 배열 
*/

void getQuarters(const int array[], int arr[]); // 이렇게 하면 인수로 넘겨진 배열이 읽기 전용이 된다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{

    int grade[5];
    char a, b[3];
    int c[4], d[5];
    int f[4] = {10, 20, 30, 40};
    int teamsFirst[4] = {1, 2, 3, 4};
    int teamsSecond[4] = {5, 6, 7, 8};
    int dimensionTwo[2][2];
    int dimensionThree[3][3][3];
    // 초기값이 없는 지역 변수형 배열 ex) int array[3] 과 같은 경우는 값이 쓰레기 값으로 초기화 되고,
    // 초기화 시에 값이 모두 채워지지 않은 경우는 나머지 값이 0으로 초기화 된다.
    // 인덱스 범위를 넘어가는 인덱스로 접근을 하면 치명적인 오류를 발생 시킬 수 있다.
    // 컴파일은 되지만 잘못된 값이 사용 될 수 있다.
    // 잘못된 인덱스를 사용하여 잘못된 메모리에 값을 저장한 경우에는, 최악의 경우 시스템 중단까지 이어지는 오류를 발생시킬수있다.
    // 초기화 외에는 중괄호를 사용할 수 없다.
    // C에서는 한 배열을 다른 배열로 통째로 복사하는 것을 허용하지 않는다. 따라서 반복문을 사용하여 하나하나 값을 대입해 주어야 한다.
    // 두 배열을 비교할 때에는, 각각의 원소를 반복문을 사용하여 하나하나 비교해 주어야 한다.
    // 배열의 크기 구하기: sizeof 연산자를 활용하여, 배열 전체의 크기를 배열 원소의 크기로 나누어서 구할 수 있다.
    // size = sizeof(array) / sizeof(array[0])
    // 선택정렬하는 법 알아두기.
    // 순차 탐색하는 법. 이진탐색(이미 정렬된 배열에 한함)하는 법 알아두기
    // 2차원 배열의 초기화의 경우, 행에 해당하는 배열의 원소의 개수는 반드시 지정해줘야한다.
    // 초기값을 지정하지 않은 경우에는 배열이 전역변수인 경우에는 0으로, 지역변수인 경우에는 쓰레기 값으로 초기화된다.
    // 2차원 배열의 경우에는, 배열을 인수로 넘길때 행에 해당하는 배열의 원소의 개수를 반드시 지정하여 넘겨주어야한다. 
    getQuarters(teamsFirst, teamsSecond);
    return 0;
}

void getQuarters(const int array[], int arr[])
{
    int random;
    int size;
    int randomArr[4];
    int arrlength;
    int pointer;

    size = sizeof(arr) / sizeof(arr[0]);

    int randomArr[4] = {0, 0, 0, 0};

    arrlength = 0;
    pointer = 0;

    while (arrlength < 4)
    {
        random = rand() % size;
        if (randomArr[pointer] == 0 && arr[random] != 0)
        {
            randomArr[pointer] = arr[random];
            arr[random] = 0;
            pointer += 1;
            arrlength += 1;
        }
    }

    int i;
    for (i = 0; i < 4; i++)
    {
        printf("%d", array[i]);
        printf("%d\n", randomArr[i]);
    }
}