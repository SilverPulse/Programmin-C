//главная функция программы
#include "time_structure.h"//подключение заголовочного файла time_structure.h, который содержит определения структуры Time и прототипы функций используемых в программе.
#include <stdio.h>//библиотке ввода / вывода

int main() {
    struct Time startTime, endTime; //объявление начала и заверешения времени работы
    struct Time dailyWorkTime, weeklyWorkTime = {0, 0};//объявление длительности рабочего дня,суммарное рабочее время за неделю,которое сразу инициализируем значениями {0, 0} 0 часов 0 минут 

    //Ввод времени начала и завершения работы за день
    printf("Введите время начала работы (часы и минуты): ");
    startTime = inputTime();
    printf("Введите время завершения работы (часы и минуты): ");
    endTime = inputTime();

    //Вычисление рабочего времени за день с помощью вызова функции
    dailyWorkTime = calculateDailyWorkTime(startTime, endTime);

    //Вычисление времени работы за неделю 
    weeklyWorkTime = calculateWeeklyWorkTime(dailyWorkTime);

    printf("Общее время работы прибора за неделю: %02d часов %02d минут\n",//%02d-означает,что числа будут выведены с ведущим нулем,если они меньше двух знаков(например 09 вместо9)
           weeklyWorkTime.hours, weeklyWorkTime.minutes);

    return 0;
}
