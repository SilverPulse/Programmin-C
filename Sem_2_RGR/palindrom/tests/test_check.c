#include "../src/preprocess.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *result = preprocess_text("А роза, упала на лапу Азора!");
    assert(result);
    printf("Результат: %s\n", result);
    assert(strcmp(result, "арозаупаланалапуазора") == 0);
    free(result);
    return 0;
}
