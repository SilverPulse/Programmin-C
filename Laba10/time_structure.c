//функции по обработке времени
#include "time_structure.h" //подключение заголовочного файла time_structure.h, который содержит определения структуры Time и прототипы функций используемых в программе.
#include <stdio.h>//библиотке ввода/вывода

//Функция для ввода времени
struct Time inputTime() {
    struct Time t;
    scanf("%d %d", &t.hours, &t.minutes);
    return t;
}

//Функция для вычисления рабочего времени за день
struct Time calculateDailyWorkTime(struct Time start, struct Time end) {
    struct Time workTime;

    //Преобразование времени в минуты
    int startMinutes = start.hours * 60 + start.minutes;
    int endMinutes = end.hours * 60 + end.minutes;

    //Разница во времени
    int workMinutes = endMinutes - startMinutes;

    //Преобразование обратно в часы и минуты
    workTime.hours = workMinutes / 60;
    workTime.minutes = workMinutes % 60;

    return workTime;
}

//Функция для вычисления общего рабочего времени за неделю
struct Time calculateWeeklyWorkTime(struct Time dailyWork) {
    struct Time weeklyWork;

    //Умножение времени за день на 7
    int totalMinutes = (dailyWork.hours * 60 + dailyWork.minutes) * 7;

    //Преобразование обратно в часы и минуты
    weeklyWork.hours = totalMinutes / 60;
    weeklyWork.minutes = totalMinutes % 60;

    return weeklyWork;
}
