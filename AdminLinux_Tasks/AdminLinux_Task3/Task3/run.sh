#!/bin/bash

# Check if .bashrc exists in the user's home directory
if [ -f "$HOME/.bashrc" ]; then
    echo ".bashrc file exists. "
    
    #Append the HELLO environment variable with the value of HOSTNAME
    echo "append new environment variable  HELLO"
    echo "export HELLO="${HOSTNAME}"" >> $HOME/.bashrc

    # Append a LOCAL variable with the value of whoami 
    echo "Local="$(whoami)"" >> $HOME/.bashrc
    echo "append new local variable  Local"
     

    echo "Environment variables added successfully."
else
    echo ".bashrc file does not exist. Creating it..."
 
fi

# Open a new terminal
echo "Opening a new terminal..."
gnome-terminal & 

