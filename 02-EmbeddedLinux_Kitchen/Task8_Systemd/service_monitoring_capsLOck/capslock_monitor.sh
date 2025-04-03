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
