// 8강 함수의 정의

void sub(int x); //함수 원형: 컴파일러에게 함수를 미리 선언하는 것. 일종의 hoisting을 위한 장치. 주로 헤더파일에 선언

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) //함수 헤더
{              //함수 바디
    int y;
    double z;
    rand();   // 난수를 RAND_MAX까지 생성
    srand(1); // seed(인수)를 받아서 난수를 생성
    y = asin(1);
    z = fabs(-3.5); // fabs는 실수를 인수로 받는다. abs는 정수.
    return 0;
}
