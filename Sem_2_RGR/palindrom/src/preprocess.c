#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h> // для работы с широкими символами (wchar_t)
#include <wctype.h> // для iswalpha, towlower (функции для wide-char
#include "preprocess.h"

// Это функция принимает строку в кодировке UTF-8 (const char* input) и возвращает новую строку

// Преобразовать его в юникод (wchar_t).
// Оставить только буквы
// Привести их к нижнему регистру
//Вернуть результат как новую строку в кодировке UTF-8

char* preprocess_text(const char* input) {
    setlocale(LC_ALL, "");

    size_t wlen = mbstowcs(NULL, input, 0); // Вычисляем длину wide-строки
    if (wlen == (size_t)-1) return NULL; // Если ошибка — возвращаем NULL

    wchar_t* wbuffer = malloc((wlen + 1) * sizeof(wchar_t)); // Выделяем память
    if (!wbuffer) return NULL; // Если не удалось — возвращаем NULL

    mbstowcs(wbuffer, input, wlen + 1); // Преобразуем UTF-8 → wchar_t

    wchar_t* filtered = malloc((wlen + 1) * sizeof(wchar_t)); // Буфер для результата
    if (!filtered) {
        free(wbuffer); // Освобождаем временный буфер
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < wlen; i++) {
        if (iswalpha(wbuffer[i])) { // проверяет, является ли символ буквой (включая Unicode-буквы, если локаль установлена правильно).
            filtered[j++] = towlower(wbuffer[i]); //Если да — переводим в нижний регистр с помощью towlower() и добавляем в filtered
        }
    }
    filtered[j] = L'\0'; //вершаем строку символом конца строки L'\0'
    free(wbuffer);

    size_t utf8len = wcstombs(NULL, filtered, 0); //Подсчитаем, сколько байт потребуется для хранения строки filtered в кодировке UTF-8.
    char* result = malloc(utf8len + 1); //Выделяем память под итоговую строку в кодировке UTF-8. 
    if (!result) {
        free(filtered);
        return NULL; //Если память выделить не удалось — освобождаем filtered и возвращаем NULL.
    }
    wcstombs(result, filtered, utf8len + 1); //Преобразуем широкую строку filtered обратно в строку в кодировке UTF-8 и сохраняем в result. 
    free(filtered);
    return result;
}
