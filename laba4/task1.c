#include <stdio.h>
int main() {
int n, number=1;
printf("Введите значение n: ");
scanf("%d", &n);
for (int i=0;i<n;i++){
	for (int k=0;k<n;k++){
		printf("%d ",number);
		number++;
	}		
	printf("\n");
}
}

