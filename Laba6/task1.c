#include <stdio.h>
#define k 3//kol-vo compleks chisel
int main(){
    double A[k*2]= {1.0, 2.0, 3.0, 4.0, 5.0, 6.0}; // massive A
    double B[k*2]={7.0, -8.0, 9.0, -10.0, 11.0, -12.0}; // massive B
    double C[k*2]; //massive to save  summ A and B
    double max_real = A[0]; // max real part in massive A 
    int mnimaya_count=0; //schetchik mnymyx chastei
    double sum=0.0;// summ element of massive C

    for (int i=0; i < k*2;i++){ // проход по массивам, цикл for

        C[i] = A[i] + B[i];//sum real parts A and B to C
        sum += C[i];
        if (i%2==0 && A[i] > max_real){//poisk maks
            max_real=A[i];
        }
        
        if (i % 2 == 1 && B[i] < 0 ){
                mnimaya_count++; //schet kol-vo mnim chastei < 0 in massive B
        }
    
}
double sr_arifm = sum / (k*2);
    printf("Максимальная реальная часть в массиве A: %.2f\n", max_real);
    printf("Количество мнимых частей < 0 в массиве B: %d\n", mnimaya_count);
    printf("Среднее арифмитическое среди всех элементов массива C: %.2f\n", sr_arifm);
    return 0;
}
