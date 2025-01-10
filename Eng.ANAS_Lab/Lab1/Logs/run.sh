#!/bin/bash

# Default values
TempValue=${1:-2} # Default to 2 temperature values if not provided
PresValue=${2:-3} # Default to 3 pressure values if not provided

# Generate random temperature values in Fahrenheit and write them to log.txt
for ((i = 1; i <= TempValue; i++)); do
    temp=$((RANDOM % 181 + 32)) # Random temperature between 32F and 212F
    echo "$(date) : Temp : $temp F" > /home/yasmeen/ITI_9M_EMBEDDED_systems/ITI-EMBEDDED-9M/Eng.ANAS_Lab/Lab1/Logs/temp_log.txt
done

# Generate random pressure values in hPa and write them to log.txt
for ((i = 1; i <= PresValue; i++)); do
    pressure=$((RANDOM % 101 + 950)) # Random pressure between 950 hPa and 1050 hPa
    echo "$(date) : Pressure : $pressure hPa" > /home/yasmeen/ITI_9M_EMBEDDED_systems/ITI-EMBEDDED-9M/Eng.ANAS_Lab/Lab1/Logs/pressure_log.txt
done

# Print a message indicating the process is complete
echo "Random temperature and pressure values have been written to temp_log.txt and pressure_log.txt."
