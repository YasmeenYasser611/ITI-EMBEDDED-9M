#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHARED_FILE "/dev/shm/shared_buffer"

int main() {
    // Open the shared file for writing
    FILE *file = fopen(SHARED_FILE, "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Write a message to the shared file
    char message[256];
    printf("Enter a message to write to the shared buffer: ");
    fgets(message, sizeof(message), stdin);

    fprintf(file, "%s", message);
    fclose(file);

    printf("Message written to shared buffer.\n");

    return 0;
}

