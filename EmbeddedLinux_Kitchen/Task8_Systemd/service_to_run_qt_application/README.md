# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 8: create systemd service that run qt application 😊


## 1. make the service 

> touch QTCapsLOckControl.service

>code . 


## 2. you will need to know the path of the executable of the qt app and make sure it is executable 

![](2.png "")


## 3.type the service 

``` 

[Unit]
Description=Caps Lock Light Controller
Documentation=https://github.com/YasmeenYasser611/ITI_9M_QT/tree/main/CapsLock_Task3
After=multi-user.target

[Service]
ExecStart=/home/yasmeen/ITI_9M_EMBEDDED_systems/ITI_9M_QT/CapsLock_Task3/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/appcaosLock
#working directory that contain the images path
WorkingDirectory=/home/yasmeen/ITI_9M_EMBEDDED_systems/ITI_9M_QT/CapsLock_Task3/build/Desktop_Qt_6_5_3_GCC_64bit-Debug
Restart=on-failure
User=yasmeen
Group=yasmeen
#check your displat by echo $DISPLAY
Environment=DISPLAY=:1
#Without this, Qt may fail to start because it won’t be able to access runtime resources like Wayland or X11 sockets,qt need this directory to store session-related data
Environment=XDG_RUNTIME_DIR=/run/user/1000
#Tells Qt to use the X11 (XCB) backend for rendering the GUI.
Environment=QT_QPA_PLATFORM=xcb

[Install]
WantedBy=multi-user.target

```



## 4. execute the survise 

![](3.png "")


> the qt app will run .


