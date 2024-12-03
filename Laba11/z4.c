#include <stdio.h>  
  
void swap(int* a, int* b)  
{      
int tmp = *a;      
*a = *b;  
*b = tmp;  
}   
void bubble_sort(int* array, int size)  
{      
int i, j;  
for (i = 0; i < size - 1; ++i) {          
for (j = 0; j < size - i; ++j) {              
if (array[j] > array[j + 1]) {                  
swap(&array[j], &array[j + 1]);  
            }  
        }  
    }  
}  
int main() {  
int array[100] = {10, 15, 5, 4, 21, 7};  
bubble_sort(array, 6);  
int i;   
for (i = 0; i < 6 ; ++i) {          
printf("%d ", array[i]);  
    }      
printf("\n");  
return 0;  
}

//Ошибки:
//1.В цикле for (j = 0; j < size - i; ++j) происходит выход за границы массива при сравнении array[j] > array[j + 1] на последней итерации.
//2.Лишняя проверка в конце массива.

//Исправление:
//1.Изменить условие второго цикла на j < size - i - 1.

#include <stdio.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int* array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) { //Исправленоe условие
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

int main() {
    int array[100] = {10, 15, 5, 4, 21, 7};
    bubble_sort(array, 6);

    for (int i = 0; i < 6; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
