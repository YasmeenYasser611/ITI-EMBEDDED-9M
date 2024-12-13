#include <stdio.h>
#include <stdlib.h>

#define SHARED_FILE "/dev/shm/shared_buffer"

int main() {
    // Open the shared file for reading
    FILE *file = fopen(SHARED_FILE, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Read the message from the shared file
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    printf("Read from shared buffer: %s\n", buffer);

    return 0;
}

