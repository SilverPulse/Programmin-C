#include <stdio.h>
void main(){
int d;
int a;
printf("Type Year: ");
scanf(" %d",&a);
if (a%400==0){printf("Yes\n");}
else if (a%100==0){printf("No \n");}
else if (a%4==0){printf("Yes \n");}
else{printf("Yes \n");}

}
