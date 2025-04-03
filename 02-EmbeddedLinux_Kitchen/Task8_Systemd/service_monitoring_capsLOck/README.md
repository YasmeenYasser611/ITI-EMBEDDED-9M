# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 8: monitoring capsLOck CHanges with systemd service  😊


## 1. make the logic in script 

> touch capslock_monitor.sh

>code . 

```bash

#!/bin/bash

LOG_FILE="/var/log/capslock_monitor.log"
PREV_STATE=""

get_capslock_state() {
    xset q | grep "Caps Lock:" | awk '{print $4}'
}

while true; do
    CURRENT_STATE=$(get_capslock_state)
    
    if [[ "$CURRENT_STATE" != "$PREV_STATE" ]]; then
        echo "$(date) - Caps Lock changed to: $CURRENT_STATE" >> "$LOG_FILE";
        PREV_STATE=$CURRENT_STATE
    fi
 
done


```

>chmod +x /home/yasmeen/capslock_monitor.sh


## 2. Create a Systemd Service


> 
>touch QTMonitoringCapsLOck.service
>code .

```

[Unit]
Description=Caps Lock Monitor Service
After=multi-user.target

[Service]
ExecStart=/home/yasmeen/ITI_9M_EMBEDDED_systems/ITI-EMBEDDED-9M/EmbeddedLinux_Kitchen/Task8_Systemd/service_monitoring_capsLOck/capslock_monitor.sh
Restart=always
User=yasmeen


[Install]
WantedBy=multi-user.target

```


## 3.you will need to create the logging file and chmod it

>sudo touch /var/log/capslock_monitor.log

>sudo chmod 666 /var/log/capslock_monitor.log




## 4. execute the survise 

![](1.png "")




