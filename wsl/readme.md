# setup WSL

0. Show the list of installed WSL distributions in your system by running `wsl --list` or `wslconfig /l` in *Windows Powershell*. \
   Where you can unregister a distribution for a clean installation with `wsl --unregister Ubuntu` or `wslconfig /u Ubuntu`.
1. List the available WSL distributions online by running `wsl --list --online`. \
   We then choose to install the lastest Ubuntu distribution with `wsl --install Ubuntu`. \
   You can find more information in the [official site](https://learn.microsoft.com/en-us/windows/wsl/).
2. Complete the Ubuntu setup by entering a user name and password, then *Powershell* will automatically open the new Ubuntu kernel.
3. We can verify the install by showing the installation version with `hostnamectl`.
4. Update Ubuntu packages with the following `sudo apt update && sudo apt upgrade && sudo apt autoremove`.
5. It is then recommended to code using Visual Studio Code. \
   If you don't have it installed, get the Windows version from their [official site](https://code.visualstudio.com/Download). \
   Then simply enter `code .` in WSL to open remote connect from Windows to WSL via VScode.
6. To access WSL files in Windows, simply enter `explorer.exe .` in WSL to open a connection. \
   Depending on your WSL version, it will either be in the user directory, or a localhost network.
7. From now on, we will run WSL via VScode using a remote connection. \
   Open VScode in Windows, then click the bottom left blue button, or `ctrl+shift+P` and enter WSL.
