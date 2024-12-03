#include <stdio.h>  
  
#define SQR(x) x * x  
int main() {      
int y = 5;      
int z = SQR(y + 1);      
printf("z = %d\n", z);      
return 0;
}  

//Ошибки:
//1.Макрос SQR(x) раскрывается как x * x,что при использовании SQR(y + 1) приводит к ошибке вычисления: y + 1 * y + 1.

//Исправление:
//1.Обернуть параметры и тело макроса в скобки.

#include <stdio.h>

#define SQR(x) ((x) * (x)) // справление макроса

int main() {
    int y = 5;
    int z = SQR(y + 1);
    printf("z = %d\n", z); //Ожидаемый результат z=36
    return 0;
}
