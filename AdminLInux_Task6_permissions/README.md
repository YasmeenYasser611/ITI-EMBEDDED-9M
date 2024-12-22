# Yasmeen Yasser Mohamed
# Task6_adminLinux_ permissions :)
> 1. Create a folder called myteam in your home directory and change its
permissions to read only for the owner.

![](1.png "")

>2. Log out and log in by another user

![](2.png "")

> 3. Try to access (by cd command) the folder (myteam)

![](3.png "")

> 4. Using the command Line

### Change the permissions of oldpasswd file to give owner read and write permissions and for group write and execute and execute only for the others (using chmod in 2 different ways)

![](4.png "")

### Change your default permissions to be as above.

![](5.png "")

note: we can not set files to be executable by defult.

### What is the maximum permission a file can have, by default when it is just created? And what is that for directory.

1. **For Files:**
   - By default, the maximum permissions a newly created file can have is **`666`**.
   - This means:
     - **Owner:** Read and write (`rw-`)
     - **Group:** Read and write (`rw-`)
     - **Others:** Read and write (`rw-`)

   > **Why no execute permission?**  
   Files do not have execute permissions (`x`) by default when created because most files are data files, not executable programs. If execute permission is needed, it must be explicitly set using `chmod`.

2. **For Directories:**
   - By default, the maximum permissions a newly created directory can have is **`777`**.
   - This means:
     - **Owner:** Read, write, and execute (`rwx`)
     - **Group:** Read, write, and execute (`rwx`)
     - **Others:** Read, write, and execute (`rwx`)

   > **Why execute permission for directories?**  
   Execute permission on a directory allows users to traverse the directory, i.e., access files or subdirectories within it.

---

### How `umask` Affects These Defaults:

The **`umask`** subtracts permissions from the default maximum. For example:
- for `rw- -wx --x`:
  - Files: `666 - 631  = 046` → `rw- -wx --x`
  - Directories: `777 - 731 = 046` → `rw- -wx --x`
  
Adjusting the `umask` lets you control the default permissions for newly created files and directories.


### Change your default permissions to be no permission to everyone then create a directory and a file to verify.

![](6.png "")

### State who can access a this file if any with proof.

![](7.png "")

No one can access these files or directories, including the owner , but the root can .

> 5. Create a file with permission 444. Try to edit in it and to remove it? Note what happened.

![](8.png "")
the file is read-only. If you manage to edit the content and save it, you'll encounter a "Permission denied" error unless you force-save it using  with sudo.

![](9.png "")

If you have write access to the directory, the file will be removed without considering its permissions.
![](10.png "")

> 6. What is the difference between the “x” permission for a file and for a directory?
*  For Files:

    * The x permission means the file can be executed as a program or script.
    * For example:

        A binary executable (like /bin/ls) or a shell script can be run if it has the execute permission (chmod +x filename).
        Without x, you cannot run the file as a program, even if you can read its contents.

* For Directories

    * The x permission on a directory allows a user to traverse it.
    * For example:

        * You can access files or subdirectories inside that directory if you know their names.
        * Without x, you cannot enter the directory or list its contents (even if you have read permission on the directory).


>7. Create a new directory.
 ###  Set the sticky bit on the newly created directory.


### set the setgui bit on the created directory

![](122.png "")


### Create multiple user accounts.

![](17.png "")

### Allow these users to create files within the directory and directory.
![](123.png "")
![](124.png "")

### Attempt to delete or rename each other's files.

![](125.png "")

### Provide a clear output demonstrating the impact of the sticky bit on file deletion and renaming within the directory.

* The sticky bit prevents users from deleting or renaming files they do not own, even if they have write permissions in the directory.

    * user1 can delete or rename their own files.
    * user2 and user3 cannot delete or rename user1’s files.


### Provide a clear output for the directory created.

![](126.png "")
 


> 8. List the permission passwd command has and explain why it has S

![](11.png "")

* rwsr-xr-x:

    * rwx: The owner (root) has read, write, and execute permissions.
    * s:  indicates the setuid bit is set.
    * r-x: The group has read and execute permissions.
    * r-x: Others have read and execute permissions.

The s (setuid) bit is a special permission that allows a program to run with the privileges of its owner (in this case, root), regardless of who executes it.

> Why Does passwd Have the Setuid (s) Bit?

The passwd command needs elevated privileges because it modifies sensitive system files  that is belongs to the root , such as /etc/shadow, which stores hashed passwords. Regular users don't have write access to these files for security reasons so root do setuser id permission so the regular user could take the root permissions.