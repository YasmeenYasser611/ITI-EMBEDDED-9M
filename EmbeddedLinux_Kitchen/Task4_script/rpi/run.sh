# Define memory addresses
setenv loadaddr 0x00080000  # Address where zImage or test.img will be loaded

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
        echo "Failed to get zImage from TFTP. Loading yasmeen file from SD card which will open GPIO2 LED...";

        # Step 3: Load fallback file 'test.img' from the SD card
        if fatload mmc 0:1 ${loadaddr} test.img; then
            echo "test.img file loaded successfully. GPIO2 will be turned on.";
            go ${loadaddr}  # Execute the binary at ${loadaddr}
        else
            echo "Failed to load test.img file from SD card. GPIO2 is ON as an error indicator.";
        fi
    fi
fi

