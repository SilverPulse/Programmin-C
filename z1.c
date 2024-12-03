#include <stdio.h>  
#include <stdlib.h>  
  
void init(int* arr, int n)  
{  
arr = malloc(n * sizeof(int));      
int i;  
for (i = 0; i < n; ++i) {  
        arr[i] = i;  
    }  
}   
int main()  
{      
int* arr = NULL;      
int n = 10;      
init(arr, n);  
int i;  
for (i = 0; i < n; ++i) {  
printf("%d\n", arr[i]);  
}      
return 0; 
} 
//Ошибки:
//1.В функции init указатель arr передаётся по значению, из-за чего выделение памяти внутри функции не влияет на указатель в main.
//2.Память не освобождается.

//Исправление:
//1.Передать указатель на указатель (int** arr).
//2.Освободить выделенную память в конце программы.

//Задание 1 Выводит числа от 0 до 9, память корректно освобождается.

#include <stdio.h>
#include <stdlib.h>

void init(int** arr, int n) {
    *arr = malloc(n * sizeof(int)); //выделяем память по указателю
    int i;
    for (i = 0; i < n; ++i) {
        (*arr)[i] = i; //доступ к выделенной памяти через указатель на указатель
    }
}

int main() {
    int* arr = NULL;
    int n = 10;
    init(&arr, n); //передаем адрес указателя
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr); //освобождаем память
    return 0;
}
br
