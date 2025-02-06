# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 7: ssh with systemv init process 😊


## 1. compile build root but ensure to activate the ssh options 


## 2. connect the rpi and set the ethernet ip 

![](1.png "")

## 3. set the ps ethernet ip then ssh to the rpi ethernet 
![](3.png "")

## 4.if you want from the rpi tp ping your pc 

![](2.png "")


# some problems may face you from the pc side :

make sure from the ip

![](4.png "")
 
make sure the ssh port is listen 
![](5.png "")


# some problems may face you from the rpi side :

make sure to uncommemt like this 

![](6.png "")

aftere that do:
/etc/init.d/S50sshd restert

![](7.png "")

try to ping pc it will work if not di ifconfig to make sure your ip 

# script to do this :
 > edit in inittab to run the script in all levels

![](8.png "")

> ensure to make script executable and make symboliv link on it 

![](9.png "")

>the script: 

![](10.png "")


# just connect the eth cable and ssh 
![](11.png "")





### not in qemu you will edit the qemu build rooot script :
![](12.png "")