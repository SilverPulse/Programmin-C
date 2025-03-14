//опредления структуры и прототипы функций
#ifndef TIME_UTILS_H //Директива препроцессора.Проверяет определен ли макрос TIME_UTILS_H. Если нет,то продолжается выполнение кода.Это предотвращает повторное включение файла и последующее дублирование определений,которое может привести к ошибкам компиляции.
#define TIME_UTILS_H //Если макрос TIME_UTILS_H еще не определен,то он определятеся.Это сигнал для отсальных частей программы,что данный заголовочный файл уже включен.

//Определение структуры Время
struct Time {
    int hours;
    int minutes;
};
//struct - это тип данных,который позволяет объединить несколько различных типов данных в один.
//Прототипы функций
struct Time inputTime(); 
struct Time calculateDailyWorkTime(struct Time start, struct Time end);
struct Time calculateWeeklyWorkTime(struct Time dailyWork);

#endif //TIME_UTILS_H //Завершает блок #ifndef / #define, начатый в первых строках.Это указывает,что определения внутри файла заканчиваются,если макрос TIME_UTILS_H был установлен.