# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 4: testing uboot variable script using RPI 3B+😊

# U-Boot Script for Loading zImage with Fallback Mechanism

This U-Boot script performs the following tasks:
1. **Checks if `zImage` exists on the SD card**:
   - If it does, it loads `zImage` into memory.
2. **If `zImage` is not found on the SD card, attempts to load it via TFTP**:
   - If successful, it loads `zImage` into memory.
3. **If `zImage` is not found on the SD card and cannot be loaded via TFTP**:
   - Turns on GPIO2 as an error indicator 

## U-Boot Script

```bash
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


```


## testing Script


* 1- after writing script we will convert it to binary , then but it in the tftp file

![](6.png "")

* 2- before run script ensure tftp is active 

if it didnot want to ping ensure that :

sudo ip a add 192.168.1.17/24 dev eno1 

sudo ifconfig eno1 up

sudo ethtool eno1   ***theck the link detected is yes 

if no :

sudo ifconfig eno1 down

sudo ifconfig eno1 up

then it will be yes :)


![](1.png "")

* 3- test the script 

![](2.png "")


* 4- test the bootcmd variable 

![](3.png "")

* 5- try to reset and there is no zimage in sd card the gpio2 will turn on 


![](4.png "")




* 6-try to reset and the sd card contain zImage

![](5.png "")












