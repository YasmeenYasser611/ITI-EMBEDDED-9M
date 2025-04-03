# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 4: testing uboot variable script using  qemu😊

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
        echo "Failed to get zImage from TFTP. Will open GPIO2 LED...";
        gpio set 2  # Turn on GPIO2 as an error indicator
    fi
fi

```


## testing Script


* 1- after writing script we will convert it to binary , then but it in the tftp file

![](4.png "")

* 2- before run script ensure tftp is active between qemu and the pc 

![](5.png "")
![](6.png "")
![](7.png "")


* case1 : loading script and source it without have zImage in both sd card and /srv/tftp , the script will try ro on gpio2


![](1.png "")


* case 2 : create zimage file in /srv/tftp and type anything on it 


![](2.png "")



* case 3 : open the sd card * emulated * add zimage on it , then source the script again



![](8.png "")

![](3.png "")

## adding script to bootcmd to run automatic after autoboot



![](9.png "")










