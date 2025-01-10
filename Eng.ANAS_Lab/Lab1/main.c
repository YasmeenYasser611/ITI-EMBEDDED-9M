#include <stdio.h>
#include <stdlib.h>
#include "Temp.h"      // Include the header for temperature functions
#include "Pressure.h"  // Include the header for pressure functions

int main() 
{
    const char *Templog_file = "/home/yasmeen/ITI_9M_EMBEDDED_systems/ITI-EMBEDDED-9M/Eng.ANAS_Lab/Lab1/Logs/temp_log.txt";  // Path to the temp log file
    const char *Pressurelog_file = "/home/yasmeen/ITI_9M_EMBEDDED_systems/ITI-EMBEDDED-9M/Eng.ANAS_Lab/Lab1/Logs/pressure_log.txt";  // Path to the Pressurelog_file

    // Test get_temp_in_f function
    int temp_f = get_temp_in_f(Templog_file);
    printf("Temperature in Fahrenheit: %d F\n", temp_f);

    // Test convert_f_to_c function
    float temp_c = convert_f_to_c(temp_f);
    printf("Converted temperature in Celsius: %.2f C\n", temp_c);

    // Test get_pressure_in_hpa function
    int pressure_hpa = get_pressure_in_hpa(Pressurelog_file);
    printf("Pressure in hPa: %d hPa\n", pressure_hpa);

    // Test convert_hpa_to_pa function
    int pressure_pa = convert_hpa_to_pa(pressure_hpa);
    printf("Converted pressure in Pa: %d Pa\n", pressure_pa);

    return 0;
}
