#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAX_STR 128

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Stack *s = stack_construct();

    for (int i = 0; i < n; i++) {
        char cmd[20];
        scanf("%s", cmd);

        if (strcmp(cmd, "PUSH") == 0) {
            char buffer[MAX_STR];
            scanf("%s", buffer);
            
            char *str = strdup(buffer); 
            stack_push(s, str);
            
        } else if (strcmp(cmd, "POP") == 0) {
            char *str = (char *)stack_pop(s);
            if (str != NULL) {
                printf("%s\n", str);
                free(str);
            }
        }
    }

    while (stack_size(s) > 0) {
        char *str = (char *)stack_pop(s);
        free(str);
    }

    stack_destroy(s);

    return 0;
}