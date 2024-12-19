# Yasmeen Yasser Mohamed
# Task6_adminLinux_Users :)

## Section 1:
     What is a Bash script that creates a user named 'yourName' and adds them to the
    'FamilyName' group, checking for existing user and group, and displaying
    relevant information for the user and group


![](tryScript.png "")

> Explanation:


    * Check for the Group:
        The getent group command checks if the group exists.
        If the group doesn't exist, it uses groupadd to create the group.

    * Check for the User:
        The id command checks if the user exists.
        If the user doesn't exist, it uses useradd to create the user, setting the group as their primary group (-g).

    * Display Information:
        The id command displays detailed information about the user (e.g., user ID, group ID, and associated groups).
        The getent group command shows details of the group.

    * User Home Directory:
        The -m option in useradd ensures that a home directory is created for the user.

## Section 2:
 
 1. Create a supplementary (Secondary) group called pgroup with group ID of 30000
 ![](s2_1.png "")

 2. Lock any user created account so he can't log in
 ![](s2_2.png "")

 3. Delete user account
 ![](s2_3.png "")

 4. Delete group account
 ![](s2_4.png "")

 5. State the difference between adduser and useradd with example shown.
 ### useradd: Low-Level Command

> Description: 
    
    useradd is a low-level, system utility for creating a user account. It does not set up things like home directories or default configurations unless explicitly instructed(get installed by defuilt in the system ).

>Key Features:

* Does not automatically create a home directory unless the -m option is used.
* Does not prompt for additional details (password, full name, shell, etc.) unless specified in the command.
* Ideal for scripting and advanced control.

> Example:

 ![](s2_5.1.png "")

### adduser: High-Level Command

> Description: 
    
    adduser is a higher-level perl script that simplifies user creation. It is more user-friendly and sets up everything needed for the user (e.g., home directory, password, and default configurations) it use the useradd command .

> Key Features:
        
* Automatically creates the home directory.
* Prompts interactively for details such as full name, password, and shell.
* Suitable for interactive use by administrators.

> Example:

 ![](s2_5.2.png "")

 ## Summary of Key Differences

 | **Feature**                | **`useradd`**                      | **`adduser`**                       |
|-----------------------------|-------------------------------------|--------------------------------------|
| **Level**                  | Low-level utility                  | High-level perl script                   |
| **Home Directory Creation**| Not created by default (`-m` flag) | Created automatically               |
| **Interactive Prompts**    | None (everything must be specified)| Prompts for password and details    |
| **Ease of Use**            | Requires more options to configure | User-friendly and easier to use     |
| **Default Configurations** | Minimal setup                      | Full default setup (e.g., skeleton files) |