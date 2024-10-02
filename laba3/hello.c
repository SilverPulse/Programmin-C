#include <stdio.h>
int main (){
int k=0,m=1,n;
printf("Введите значение n: ");
scanf("%d", &n);
while  (m<=n){
	k++;
	m=m*2;
}
printf("%d\n",k-1);
}
