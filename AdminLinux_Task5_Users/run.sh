#!/bin/bash

# Variables for user and group names
USER_NAME="yourName"
GROUP_NAME="FamilyName"

# Function to display information for the user
display_user_info() {
    echo "User Info:"
    id "$USER_NAME"
}

# Function to display information for the group
display_group_info() {
    echo "Group Info:"
    getent group "$GROUP_NAME"
}

# Check if the group exists, create it if it doesn't
if getent group "$GROUP_NAME" > /dev/null 2>&1; then
    echo "Group '$GROUP_NAME' already exists."
else
    echo "Creating group '$GROUP_NAME'..."
    groupadd "$GROUP_NAME"
    echo "Group '$GROUP_NAME' created successfully."
fi

# Check if the user exists, create them if they don't
if id "$USER_NAME" > /dev/null 2>&1; then
    echo "User '$USER_NAME' already exists."
else
    echo "Creating user '$USER_NAME'..."
    useradd -m -g "$GROUP_NAME" "$USER_NAME"
    echo "User '$USER_NAME' created successfully."
fi

# Display relevant information for the user and group
display_user_info
display_group_info

