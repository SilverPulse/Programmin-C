#include <stdio.h>
int main(){
    int a;
    printf("Введите целое число: "); // ввод целого числа
    scanf("%d" , &a);

    if (a==0){   // если число 0, то программа завершает выполненеие    
        printf("Число 0 не содержит единичных битов.\n");

    }
    int position = 1; // отслеживаем номер бита (начинаем с 1)
    while ((a&1) == 0){ // с циклом while проверяем является ли младший бит =0, если да то число а сдвигается вправо и position +1
        a>>=1;
        position++;
    }
    
    printf("Номер первого (последнего) справа единичного бита: %d\n",position);
}