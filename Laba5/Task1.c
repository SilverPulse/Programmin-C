#include <stdio.h>
int main(){
    int num;
    printf("Введите число: ");
    scanf("%d", &num);
    if ((num & 15) == 0) {
        printf("%d кратно 16 .\n" , num);
    } else {
        printf("%d не кратно 16 .\n" , num); 
    }
}