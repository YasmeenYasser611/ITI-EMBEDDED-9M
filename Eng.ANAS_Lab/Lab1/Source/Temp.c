#include "Temp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to get the temperature in Fahrenheit from the log file
int get_temp_in_f(const char *log_file) 
{ 
    if (log_file == NULL) 
    {
        perror("Null pointer"); // Error if the file path is NULL
        exit(EXIT_FAILURE); // Exit to terminate the program and free the resources
    }

    FILE *file = fopen(log_file, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE); // Exit to terminate the program and free the resources
    }

    int temp_f = -1;  // Use an integer to store the temperature
    char line[256]; // Buffer to hold each line in the file

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) 
    { 
        //printf("Line read: %s", line);  // Debugging line to print each line read

        // Check if "Temp" exists in the current line
        char *temp_ptr = strstr(line, "Temp"); 

        if (temp_ptr) 
        {  // If "Temp" is found in the line
            // Attempt to extract the temperature from the string starting at temp_ptr
            if (sscanf(temp_ptr, "Temp : %d F", &temp_f) == 1) 
            {  
                fclose(file);  // Close the file after finding the temperature
                return temp_f;  // Return the parsed temperature immediately; will return only one value
            }
        }
    }
/*
    fclose(file);  // Close the file if no temperature was found
    perror("Error: No temperature data found in the file\n");
    exit(EXIT_FAILURE); // Exit if no temperature is found in the file*/
}

// Function to convert temperature from Fahrenheit to Celsius (float result)
float convert_f_to_c(int temp_f) 
{
    return (temp_f - 32) * 5.0 / 9.0;  // Return the float result of the conversion
}
