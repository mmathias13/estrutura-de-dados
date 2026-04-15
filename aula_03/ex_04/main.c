#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_STR 128

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    Queue *q = queue_construct();

    for (int i = 0; i < n; i++) {
        char cmd[20];
        scanf("%s", cmd);

        if (strcmp(cmd, "ENQUEUE") == 0) {
            char buffer[MAX_STR];
            scanf("%s", buffer);
            
            char *str = strdup(buffer); 
            queue_enqueue(q, str);
            
        } else if (strcmp(cmd, "DEQUEUE") == 0) {
            char *str = (char *)queue_dequeue(q);
            
            if (str != NULL) {
                printf("%s\n", str);
                free(str); 
            }
        }
    }

    while (queue_size(q) > 0) {
        char *str = (char *)queue_dequeue(q);
        free(str);
    }

    queue_destroy(q);

    return 0;
}