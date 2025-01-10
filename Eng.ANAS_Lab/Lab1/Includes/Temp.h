#ifndef TEMP_H
#define TEMP_H

// Function to get the temperature in Fahrenheit from the script output
int get_temp_in_f(const char *log_file);


// Function to convert temperature from Fahrenheit to Celsius
float convert_f_to_c(int temp_f) ;

#endif // TEMP_H
