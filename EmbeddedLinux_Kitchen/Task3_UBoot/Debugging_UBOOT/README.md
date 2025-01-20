# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 3: Debugging u_boot using vs code 😊


#### 1. ** open vs code **
- from run-> add configurations -> cmake Debugger -> launch.json



```c
   "configurations": 
   [
        {
            "name": "yasmeen gdb",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}/u-boot",
            "cwd": "${workspaceFolder}",
            "miDebuggerPath": "/home/yasmeen/x-tools/arm-cortexa9_yasmeen_glibc-linux-gnueabihf/bin/arm-cortexa9_yasmeen_glibc-linux-gnueabihf-gdb",
            "miDebuggerServerAddress": "localhost:1234",
            "stopAtEntry": true,
        }

    ]
```

#### 2. **choose debugger **
- choose yasmeen gdb



#### 3. **open QEMU **

![](1.png "")

#### 4. **Start debugging *
- open main.c
- make break point in printf function 
- try to type any character 
- countinue steppint tell you reach the 
![](2.png "")
![](3.png "")









