# setup Git

0. Git should already be installed in the latest Ubuntu, to verify, run `git --version`.
1. Before we configure git, you should already have a Github account. We then configure using:

   ```bash
   git config --global user.name "username"
   git config --global user.email "user@email"
   ```

2. We want to connect to Git using SSH protocol. Check that you have SSH installed: `ssh -V`. \
   You can check whether you have a public key generated, see if `ls -al $HOME/.ssh` shows a `.pub` file. \
   If not, generate one using: `ssh-keygen -t ed25519 -C "comment"`, where we usually put our email address in the comment. \
   Follow the instructions (just skip the passphrase) will create a public key for you. (ED25519 is better than RSA, so I've heard)
3. We then need to install Github CLI. For Ubuntu, we need to run the following lines found [online](https://github.com/cli/cli/blob/trunk/docs/install_linux.md).

   ```bash
   (type -p wget >/dev/null || (sudo apt update && sudo apt-get install wget -y)) \
    && sudo mkdir -p -m 755 /etc/apt/keyrings \
    && wget -qO- https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo tee /etc/apt/keyrings/githubcli-archive-keyring.gpg > /dev/null \
    && sudo chmod go+r /etc/apt/keyrings/githubcli-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
    && sudo apt update \
    && sudo apt install gh -y

   ```

   Verify with: `gh --version`
4. Now that we have a Github account, an SSH key, and Github CLI, we need to establish a secure authentication connection with `gh auth login`. \
   Use *GitHub.com*, use *SSH* protocol, use the *.pub* public key generated, and choose login with web browser, enter the code and we are done. \
   We can test the connection by cloning this repository `gh repo clone Raymond-CL/Raymond-CL`. \
   In VScode, source control should automatically detect Git and it will display commit options. Make some minor modification to this repo and try to commit&push (need comment).
