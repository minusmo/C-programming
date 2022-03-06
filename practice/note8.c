/*
12장 문자열. 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>  //문자를 검사하는 함수의 라이브러리 헤더
#include <stdlib.h> //전용함수를 사용하기 위한 라이브러리 헤더
int main(void)
{
    char string[7] = "string";    // 마지막에 NULL문자가 들어가야 하기 때문에 문자의 개수보다 하나 크게 배열의 크기를 지정한다.
    strcpy(string, "new string"); // 변수에 직접 값을 대입하는 것으로는 값을 할당하는 것이 불가능하기 때문에 원소하나하나를 접근해서 바꿔주거나 이와 같이 합수를 사용한다.
    /*
    문자열의 입출력을 도와주는 함수들
    int getchar(void), void putchar(int c),
    int getche(void), void putche(int c), => 버퍼 사용 안함
    char gets(char *s), int puts(const char *s)
    그외에도 여러가지 문자열을 다루는 데 도움이되는 함수들이 있다. 나중에 필요할때 검색해서 참고. 
    */
    return 0;
}