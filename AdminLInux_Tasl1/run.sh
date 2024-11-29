#!/bin/bash

# 1. Create a directory called "myDirectory" in home folder.
mkdir ~/myDirectory

# 2. Inside "myDirectory," create another directory named "secondDirectory."
mkdir ~/myDirectory/secondDirectory

# 3. Within "secondDirectory," create a file named "myNotePaper."
touch ~/myDirectory/secondDirectory/myNotePaper

# 4. Copy "myNotePaper" from "secondDirectory" to "myDirectory."
cp ~/myDirectory/secondDirectory/myNotePaper ~/myDirectory/

# 5. Rename the copied file in "myDirectory" to "myOldNotePaper."
mv ~/myDirectory/myNotePaper ~/myDirectory/myOldNotePaper

echo "Script completed successfully!"


