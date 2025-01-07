#include <unistd.h>
#include <stdarg.h>

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    int index = 0;

    for (const char *ptr = format; *ptr != '\0'; ptr++) {
        if (*ptr == '%') {
            ptr++;  // Move to the format specifier
            if (*ptr == 'd') { // Handle integers
                int num = va_arg(args, int);
                char num_buffer[20];
                int len = 0;

                // Convert integer to string
                if (num < 0) {
                    buffer[index++] = '-';
                    num = -num;
                }
                do {
                    num_buffer[len++] = (num % 10) + '0';
                    num /= 10;
                } while (num > 0);

                // Append the reversed number
                while (len--) {
                    buffer[index++] = num_buffer[len];
                }
            } else if (*ptr == 's') { // Handle strings
                char *str = va_arg(args, char *);
                while (*str) {
                    buffer[index++] = *str++;
                }
            } else if (*ptr == 'c') { // Handle characters
                char c = (char)va_arg(args, int);
                buffer[index++] = c;
            } else {
                // Handle unknown format specifier (write it literally)
                buffer[index++] = '%';
                buffer[index++] = *ptr;
            }
        } else {
            buffer[index++] = *ptr; // Copy normal characters
        }
    }

    va_end(args);

    // Write the buffer to stdout
    write(1, buffer, index);
}

int main() {
    my_printf("Hello, %s! You are %d years old.\n", "yasmeen yasser", 22);
    my_printf("Character test: %c\n", 'Y');
    return 0;
}

