// 9강 변수
// 전역변수의 생존기간: 프로그램 시작 부터 종료까지
// 전역변수의 사용은 지양.

/*
생존시간에 대하여.
정적할당: 프로그램 실행 내내 변수의 저장공간과 값이 유지되는 것.
자동할당: 블록 스코프내에서만 변수의 저장공간과 값이 유지되는 것.

변수를 선언할 때 유형 지정자를 사용하면 변수의 저장공간 할당 방법을 지정할 수 있다.
auto, static: 지역변수이나 저장공간은 함수외부(전역)이 됨, register: 레지스터 변수 설정(읽고쓰기가 아주빠름), extern: 현재 범위 외(스코프, 파일등)의 장소에서 할당된 변수임을 지정. 따라서 지역변수에는 접근이 불가.

linkage(연결): 다른 범위에 속하는 변수들을 서로 연결하는 것을 의미.
C에서 변수는 외부연결, 내부연결, 무연결 중 반드시 하나에 속함.
지역변수는 연결을 가지지 않는다. 즉 무연결.
전역변수만이 연결을 가지는데, static으로 지정했다면 해당 파일 내부에서만 사용가능한 내부연결,
그렇지 않다면 외부에서도 사용가능한 외부연결이된다. 이 경우, 변수 초기화는 해당 파일에서만 가능하고 불러오는 다른 파일에서는 값을 이용하는 것만 가능하다. 
*/

int gcd(int x, int y);
int hanoi(int n);
void move_ring(int m, int stick1[], int stick2[], int stick3[]);

#include <stdio.h>
int main(void)
{
    // int array[3];
    // int i;

    // for (i = 0; i < 3; i++)
    // {
    //     array[i] = i;
    //     printf("%d", array[i]);
    // }
    hanoi(3);

    return 0;
}

// 최대공약수를 재귀함수로 구하기 x와 y의 최대공약수는(x가 y보다 클때) y와 x%y의 최대공약수와 같다는 것을 이용.
int gcd(int x, int y)
{
    if (y == 0)
    {
        return x;
    }
    else
    {
        return gcd(y, x % y);
    }
}

int hanoi(int n)
{
    int stick_1[n];
    int stick_2[n];
    int stick_3[n];
    int i;

    for (i = 0; i < n; i++)
    {
        stick_1[i] = i;
        stick_2[i] = 7;
        stick_3[i] = 7;
    }

    move_ring(n, stick_1, stick_2, stick_3);

    return 0;
}

void move_ring(int m, int stick1[], int stick2[], int stick3[])
{
    // int m;
    // char stick1[];
    // char stick2[];
    // char stick3[];

    if (m == 1)
    {
        int z;

        for (z = 2; z >= 0; z--)
        {
            if (z == 0)
            {
                stick3[0] = stick1[0];
                stick1[0] = 7;
                break;
            }
            if (stick3[z - 1] != 7 && stick3[z] == 7)
            {
                stick3[z] = stick1[0];
                stick1[0] = 7;
                break;
            }
        }

        printf("%d", stick1[0]);
        printf("%d", stick1[1]);
        printf("%d", stick1[2]);

        printf("\n");

        printf("%d", stick2[0]);
        printf("%d", stick2[1]);
        printf("%d", stick2[2]);

        printf("\n");

        printf("%d", stick3[0]);
        printf("%d", stick3[1]);
        printf("%d", stick3[2]);

        printf("\n");
        printf("\n");

        return;
    }
    else
    {
        move_ring(m - 1, stick1, stick3, stick2);

        int z;

        for (z = 2; z >= 0; z--)
        {
            if (z == 0)
            {
                stick3[0] = stick1[0];
                stick1[0] = 7;
                break;
            }
            if (stick3[z - 1] != 7 && stick3[z] == 7)
            {
                stick3[z] = stick1[0];
                stick1[0] = 7;
                break;
            }
        }

        move_ring(m - 1, stick2, stick1, stick3);
    }

    return;
}