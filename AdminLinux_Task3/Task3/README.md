# Yasmeen Yasser Mohamed
# Task3_adminLinux :)
# Section 1:
> Write a Bash script that checks IF the .bashrc file exists in the user's home
directory. If it does, append new environment variables to the file: one called
HELLO with the value of HOSTNAME, and another local variable called LOCAL
with the value of the whoami command. Additionally, the script should include a
command to open another terminal at the end. Describe what happens when the
terminal is opened.

![](pics/q1.png
"")

When the new terminal is opened, it sources the .bashrc file in the user's home directory ,The HELLO environment variable will be set to the value of the current machine's hostname .
The Local variable will be set to the username of the current user .

# Section 2:

>1. List the user commands and redirect the output to /tmp/commands.list

![](pics/q2_1.png
"")

>2.Edit in your profile to display date at login and change your prompt permanently.

![](pics/q2_2.png
"")

>3. What is the command to count the word in a file or number of file in directory.

![](pics/q2_3.png
"")

>a. Count the number of user commands


![](pics/q2_3_a.png
"")

>4. What happens if you execute:

     a. cat filename1 | cat filename2

The second cat filename2 doesn't actually use the piped input from the first command because it is overridden by the explicit filename2 passed to cat,As a result, only the contents of filename2 are displayed because the second cat ignores the piped input.

     b. ls | rm


![](pics/q2_4_b.png
"")

ls: This lists the files and directories in the current directory.
|: The pipe takes the output of ls and sends it to the rm command as its input.

rm doesn't read input from stdin (standard input) in this way, so this command will not work 

     c. ls /etc/passwd | wc –l

* ls /etc/passwd:

    This lists the file /etc/passwd.
    Since /etc/passwd is a single file, the output will be:

> /etc/passwd

* |:
        The output from ls /etc/passwd is piped into the wc -l command.

* wc -l:
        This counts the number of lines in the piped input.
        Since the ls command outputs one line (the name of the file /etc/passwd), the result will always be 1.

* Output:

The output of the command will be: 1

![](pics/q2_4_c.png
"")

>5-Write a command to search for all files on the system that, its name is “.profile”.

![](pics/q2_5.png
"")


> 6-List the inode numbers of /, /etc, /etc/hosts.

![](pics/q2_6.png
"")

>7-Create a symbolic link of /etc/passwd in /boot.

![](pics/q2_7.png
"")
>8-Create a hard link of /etc/passwd in /boot. Could you? Why?

yes i could , Hard links must exist within the same filesystem or partition, and i have the 2 files in the same partitions.

![](pics/q2_8.png
"")

>9-Echo \ it will jump to the next line, and will print >
Notice the prompt ”>” what is that? and how can you change it from “>” to “:”.
NOTE: search the usage of PS1



* The \ is a line continuation character:
        The backslash \ tells the shell that the current command continues onto the next line.
        When you press Enter, the shell expects more input to complete the command, so it displays the secondary prompt, which is > by default.

* The > prompt:
        The > is the default secondary prompt (also called PS2) in the shell.
        It indicates that the shell is waiting for more input to complete the current command.

>How to Change the > to :

![](pics/q2_9.png
"")

>What About PS1?

* PS1 is the primary prompt that you see when the shell is ready for a new command (e.g., user@host:~$).
* You can customize PS1 to modify the look of your main prompt, but it doesn’t affect the secondary prompt.