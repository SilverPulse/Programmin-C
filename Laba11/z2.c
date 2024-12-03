#include <stdio.h>  
  
typedef struct  
{  
char str[3];      
int num;  
} NumberRepr;  
  
void format(NumberRepr* number)  
{      
sprintf(number->str, "%3d", number->num);  
}   
int main()  
{  
NumberRepr number = { .num = 1025 };  
format(&number);  
printf("str: %s\n", number.str);      
printf("num: %d\n", number.num);  
return 0;  
}  

//Ошибки:
//1.В структуре NumberRepr массив str слишком мал для строки формата "%3d" (необходимо минимум 4 байта,включая символ конца строки).
//2.Число 1025 не помещается в поле шириной 3 символа.

//Исправление:
//1.Увеличить размер str до 5.
//2.Убедиться, что формат "%d" подходит для чисел.

#include <stdio.h>

typedef struct {
    char str[5]; 
    int num;
} NumberRepr;

void format(NumberRepr* number) {
    snprintf(number->str, sizeof(number->str), "%3d", number->num);
}

int main() {
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}








