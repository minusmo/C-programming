/*
13장 구조체 
*/

#include <stdio.h>
int main(void)
{
    struct milk
    {
        int protein;
        int fat;
        int water;
    };

    struct milk *p;

    struct milk seoul = {2, 3, 5};

    p->protein = 1;
    (*p).fat = 2;

    struct coffee
    {
        int caffein;
        int fat;
        int water;
        struct coffee *h; //자기 자신의 포인터
    } onion = {1, 1, 5};

    union shareroom
    {
        int a;
        int b; // 2개의 변수는 같은 메모리 공간을 공유한다. 따라서 한번에 하나의 변수만이 공간을 차지할 수 있다.
               // 구조체와 동일하게 초기화하고 값을 대입할 수 있다. 주로 같은 값을 다른 표현 방법으로(진법등) 보고싶은 경우에 사용된다.
    };

    enum milktype
    {
        Choco,
        Almond,
        Plain
    }; // enum은 정의 된 값들중 하나의 값만을 취할 수 있는 자료형이다. 인덱스를 가진다.
    enum milktype einstein = Choco;

    typedef int INT32;        // 타입을 다른 이름으로 재정의 하는 방식. 여러모로 유용하다. 장점 1. 이식성이 높다 2. #define 보다 낫다. 3. 문서화의 역할도 가능하다.
    typedef struct milk MILK; // 이처럼 사용도 가능. 알아보기 쉽게 타입을 재정의하거나, 선언을 축약하기 위해 사용된다.

    return 0;
}