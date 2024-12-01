# Yasmeen Yasser Mohamed
# Task1_adminLinux :)
>1. Initialize a new repository named "ITI-EMBEDDED-9M."

![clone repo](photos/1.png
"repo cloning")

>2. Create a branch named "Task1_adminLinux."
>3. Inside the repository, create a directory called "AdminLinux_Task1."


![create branch and make directory](photos/2.png
"")

>4. Within "AdminLinux_Task1," create a file and add your script to it.

![create bash script](photos/4.png
"")

>5. Commit the changes.
>6. Push the changes to the remote repository.

![commit changes](photos/5.png
"")

![push changes](photos/6.png
"")

>7. Merge the changes into the main branch.

![merge changes](photos/3.png
"")

>List three Linux Distributions.

* Ubuntu
* debian
* archlinux
>From the slides what is the man command used for?


~~System-wide documentation system that provides short reference manuals (pages) for individual
commands, API functions, concepts, configuration file syntax, file formats and is organized in sections
(1 for user commands, 2 for system calls...). That's the traditional Unix documentation system.~~

man command is used to get the help of any external command .

>What is the difference between rm and rmdir using man command?

rm is for remove file or directory

![rm command](photos/12.png
"")

rmdir is for remove only  emptty direcories

![rmdir command](photos/13.png
"")

>Create the following hierarchy under your home directory:

![dir1 folder](photos/14.png
"")

![docs folder](photos/15.png
"")

![Documents folder](photos/16.png
"")

>Remove dir11 with rmdir in one-step. What did you notice? And how did you
overcome that?

we cannot use rmdir because file is not empty so we use rm 

![rm dir11](photos/17.png
"")

>remove OldFiles using rmdir –p command. State what happened to the
hierarchy (Note: you are in your home directory).

The command rmdir -p  is used to remove directories, and the -p flag allows it to remove parent directories if they are empty. However, and OldFiles is actually a file rather than a directory, running this command will result in an error.

![rm OldFiles](photos/18.png
"")
to solve it i used: 
>rm ~/Documents/OldFiles

>The output of the command pwd was /home/yasmeen. Write the absolute and
relative path for the file mycv

Absolute Path: /home/yasmeen/docs

Relative Path: docs

![pwd](photos/19.png
"")

>Copy the /etc/passwd file to your home directory making its name is mypasswd

![password](photos/20.png
"")
>Rename this new file to be oldpasswd

![old password](photos/21.png
"")

>You are in /usr/bin, list four ways to go to your home directory

* cd ~
* cd 
*
   * cd ..
   * cd ..
   * cd home 

*
    * cd /
    * cd home

>List Linux commands in /usr/bin that start with letter w

![ls](photos/22.png
"")

>What command type are used for? (from the slide)

![ls](photos/23.png
"")

>Show 2 types of command file in /usr/bin that start with letter c

![ls](photos/25.png
"")

>Using man command find the command to read file. (Note: man take option)

![ls](photos/26.png
"")

>What is the usage of apropos command?

the apropos command in Linux is used to search the manual page database for a keyword 

![ls](photos/27.png
"")

# the bash script :
#!/bin/bash

#### 1. Create a directory called "myDirectory" in home folder.
mkdir ~/myDirectory

#### 2. Inside "myDirectory," create another directory named "secondDirectory."
mkdir ~/myDirectory/secondDirectory

#### 3. Within "secondDirectory," create a file named "myNotePaper."
touch ~/myDirectory/secondDirectory/myNotePaper

#### 4. Copy "myNotePaper" from "secondDirectory" to "myDirectory."
cp ~/myDirectory/secondDirectory/myNotePaper ~/myDirectory/

#### 5. Rename the copied file in "myDirectory" to "myOldNotePaper."
mv ~/myDirectory/myNotePaper ~/myDirectory/myOldNotePaper

echo "Script completed successfully!"

![](photos/7.png
"")
![](photos/8.png
"")
![](photos/9.png
"")
![](photos/10.png
"")
![](photos/11.png
"")
