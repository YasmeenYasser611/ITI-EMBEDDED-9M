#ifndef PRESSURE_H
#define PRESSURE_H

// Function to get the pressure in hPa from the script output
int get_pressure_in_hpa(const char *log_file);

// Function to convert pressure from hPa to Pa
int convert_hpa_to_pa(int pressure_hpa);

#endif // PRESSURE_H
