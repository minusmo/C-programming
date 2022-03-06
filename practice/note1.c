/* // 정수 10 ,8, 16 진법 가능
 int c = 3;

 // 소수
 double b = 3.5;
 float f = 4.5;

 // 문자 하나
 char a = 'a';

 // 여러 문자
 char d = "abcd";

 // const 사용 가능
 const double e = 5.5; */

// main 함수는 반드시 유일하게 존재해야한다. 가장 처음으로 실행되는 함수.

#include <stdio.h> //프리프로세서 지정. 데코래이터 같은 것.
int main(void)
{
    int x;
    int y;
    int sum;

    printf("더할 값 1:");
    scanf("%d", &x);

    printf("더할 값 2:");
    scanf("%d", &y);

    sum = x + y;

    printf("더한 값은 %d 입니다.", sum);

    //printf("hi\n I am a man \n dude.");
    return 0;
}