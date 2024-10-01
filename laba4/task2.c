#include <stdio.h>
int main() {
int n;
printf("Введите значение n: ");
scanf("%d", &n);
for (int i=n;i>0;i--){ // управление строками
	for (int j=0;j<n-i;j++){  //вывод пробелов перед звёздочками
		printf(" ");
	}
	for (int j=0;j<2*i-1;j++){ // вывод звездочек
		printf("*");
		
	}		
	printf("\n");
}
}

