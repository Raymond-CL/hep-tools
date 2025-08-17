# Setting up WSL

This guide provides a **step-by-step procedure** for installing and configuring **Windows Subsystem for Linux (WSL)** on Windows, using **Ubuntu** as the example distribution.

It also includes instructions for setting up a development workflow with **Visual Studio Code**.

## Install WSL

For detailed reference, see the official [WSL documentation](https://learn.microsoft.com/en-us/windows/wsl/).

### Default Installation

If you are new to WSL, the simplest option is to perform the default installation.

1. Open **Windows PowerShell** (press `Windows`, type `powershell`, and press `Enter`).
2. Run:

   ```powershell
   wsl --install
   ```

   This command enables the WSL feature and installs the default Ubuntu distribution.

### Choosing a Linux Distribution

If you prefer a different Linux distribution:

* List installed distributions with `wsl --list` or `wslconfig /l`.
* Unregister (remove) an existing distribution with `wsl --unregister Ubuntu` or `wslconfig /u Ubuntu`.
* List available distributions online with `wsl --list -- online`.
* Install a specific distribution (e.g., latest Ubuntu) with `wsl --install Ubuntu`.

### Manual Installation

On older versions of Windows, WSL must be enabled manually:

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

You can set the default WSL version with `wsl --set-default-version <1|2>`.

**Key differences:**

* **WSL 1** – Faster file sharing with Windows; limited Linux kernel support.
* **WSL 2** – Runs in a lightweight VM with a full Linux kernel; slightly slower file access but better compatibility and performance for most workloads.

**Recommendation:** Use **WSL 2** unless you have specific reasons to choose WSL 1.

### Completing the Installation

1. When prompted, create a username and password for your Linux system.
2. Verify the installation version with `hostnamectl` in WSL terminal.
3. Update Ubuntu packages with `sudo apt update && sudo apt upgrade && sudo apt autoremove` command.

## Install Visual Studio Code

Download and install VS Code from the [official website](https://code.visualstudio.com/).

### Connecting VS Code to WSL

After VS Code is installed:

1. In your WSL terminal, run `code .`

   This installs the **Remote - WSL** extension and opens VS Code from within WSL.

2. Alternatively, open VS Code, click the bottom-left **`><`** button, or search for “**Connect to WSL**” in the command palette.

### Accessing WSL Files

* WSL 1 and WSL 2 have different internal paths, but you can open the current directory in Windows Explorer by running `explorer.exe .` .

  The dot (`.`) refers to the current directory.

## About System Resources

Installing WSL effectively sets up a Linux environment inside Windows.

* **Idle resource usage:** When no processes are running, WSL consumes negligible CPU and releases most memory back to Windows.
* **Active processes:** Any computation inside WSL uses system resources just like native Windows applications. These processes also appear in the Windows Task Manager.
* **After closing VS Code:** Closing VS Code does not terminate running WSL processes. Tasks launched via the terminal (especially with `nohup` or inside `tmux/screen`) will continue until they finish or are killed.
* **Shutdown behavior:** WSL remains running in the background after processes complete, but idle. You can shut it down manually:

  ```powershell
  wsl --shutdown
  ```
