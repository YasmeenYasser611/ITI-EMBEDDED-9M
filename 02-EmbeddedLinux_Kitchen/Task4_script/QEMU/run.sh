# Define memory addresses
setenv loadaddr 0x62000000  # Address where zImage or test.img will be loaded

# Step 1: Check if zImage exists on SD card and load it
if fatload mmc 0:1 ${loadaddr} zImage; then
    echo "zImage exists on SD card. Loading it...";
    md ${loadaddr}  # Dump memory to verify the file
else
    echo "zImage does not exist on SD card. Trying TFTP...";

    # Step 2: Try to load zImage from TFTP
    if tftp ${loadaddr} zImage; then
        echo "zImage successfully loaded from TFTP.";
        md ${loadaddr}  # Dump memory to verify the file
    else
        echo "Failed to get zImage from TFTP. will open GPIO2 LED...";
        gpio set 2  # Turn on GPIO2 as an error indicator
        
    fi
fi

