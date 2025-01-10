#include "Pressure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to get the pressure in hPa from the log file
int get_pressure_in_hpa(const char *log_file) 
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

    int pressure_hpa = -1;  // Use an integer to store the pressure
    char line[256]; // Buffer to hold each line in the file

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) 
    { 
        //printf("Line read: %s", line);  // Debugging line to print each line read

        // Check if "Pressure" exists in the current line
        char *pressure_ptr = strstr(line, "Pressure"); 

        if (pressure_ptr) 
        {  // If "Pressure" is found in the line
            // Attempt to extract the pressure from the string starting at pressure_ptr
            if (sscanf(pressure_ptr, "Pressure : %d hPa", &pressure_hpa) == 1) 
            {  
                fclose(file);  // Close the file after finding the pressure
                return pressure_hpa;  // Return the parsed pressure immediately; will return only one value
            }
        }
    }

    fclose(file);  // Close the file if no pressure data was found
    perror("Error: No pressure data found in the file\n");
    exit(EXIT_FAILURE); // Exit if no pressure is found in the file
}

// Function to convert pressure from hPa to Pa
int convert_hpa_to_pa(int pressure_hpa) 
{
    return pressure_hpa * 100; // Return the pressure in Pa (1 hPa = 100 Pa)
}
