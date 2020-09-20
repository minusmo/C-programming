// 2020 0920 조건문
#include <stdio.h>
int main(void)
{
    int x;

    // x = -x 음수로 만듦
    if (10 < x && x < 20)
        printf("조건을 만족합니다.");
    else
    {
        printf("조건을 만족하지 않습니다.");
        printf("네 그래요");
    }

    // (10 < x && x < 20) ? printf(~~) : printf(~~~); 와 같음

    return 0;
}

/* else 문은 항상 가장 가까운 if 문과 매칭된다. -> 항상 {}를 사용하여 조건문 블록을 만들
어 구분해준다. 
C 는 들여쓰기를 무시한다.
0 는 falsy 한 값.
*/

void switchfunc(void)
{
    int number;

    goto end; // goto 문은 레이블로 점프하는 포탈이다. 절대 사용하지 말자.

    switch (number) // (제어식) 제어식의 결과 값은 항상 정수(하나의 문자)여야 한다. 변수, 부동소수점도 불가.
    {               // 문자열을 정수로 변환하는 함수를 사용하면 제어식에도 문자열 사용도 가능. ex) strcmp
    case 0:         // case 제어식의 결과값:
        printf("0");
        break;
    case 1:
        printf("1");
        break;
    default:
        printf("No match found");
    }
    return;

end: // 여기로 워프
    return;
}

void loopfunc(void)
{
    int x = 3;

    do
    {
        printf("it is 3");
    } while (x < 3); // 최소한번은 실행된다. 이럴 때 do while을 사용한다.

    int i;

    for (i = 0; i < 10; i++)
    {
        printf("&d", i);
    }
    /*
    for loop에 대한 여러가지 사실
    1.조건식에서 ;;로만 구분해 놓으면 사용이 가능하다.
    2.한번에 2개 이상의 변수도 초기화 가능하다. ex) for(i=0, k=0; ;)
    3.변수 초기화 자리에 다른 문장도 들어갈 수 있다. ex) for)(printf("hi"), i=0;;)
    4.조건 검사에는 참 거짓을 판별하는 어떤 조건식도 들어갈 수 있다.
    5.for 루프 안에도 break을 사용할 수 있다. (하나의 루프 블록만 탈출)
    6.goto문을 사용하면 원하는 시점에서 어디로든 워프 가능하다. 
    7.continue도 사용가능하다.
    */

    return;
}