#include <stdio.h>
#include <stdlib.h>

int main() {
    char *username = getenv("USERNAME");

    if (username != NULL) {
        printf("Username: %s\n", username);
    } else {
        printf("Unable to retrieve username\n");
    }

    return 0;
}