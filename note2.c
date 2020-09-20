/* // 여러 정수형

short , int, long 각각 16비트, 32비트, 32비트.

unsigned 는 0 이상의 값만. 

숫자 범위를 넘어가면 반대쪽 끝으로 돌아간다.

123u, 123, 123ul 같이 자료형을 직접 지정할 수 있다.

char은 8비트의 정수를 저장하는 자료형. 따라서 숫자도 할당 가능. 숫자 연산도 가능.

*/

#include <stdio.h>
int main(void)
{
    char a = 'A';
    char b = 65;
    char beep = '\a'; //제어문자

    printf("%c\n", a);
    printf("%c", beep);
    printf("%c\n", b);
    return 0;
}