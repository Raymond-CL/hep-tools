This is a note-to-self in case I lost my codes again.

## Setting up Git
1. I'm working mostly on [WSL](https://docs.microsoft.com/en-us/windows/wsl/install), so first thing is setup git on Ubuntu
```
sudo apt install git
```
2. Because my mouse is crappy, I try to work mostly on the keyboard, thus GitHub CLI is also important, install by following the instructions [here](https://github.com/cli/cli/blob/trunk/docs/install_linux.md):
```
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
&& sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
&& sudo apt update \
&& sudo apt install gh -y
```
3. Then we need a connection, between the computer and GitHub. [SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh) recommended.
  - check for existing key
```
ls -al ~/.ssh
```
  - if not, generate
```
ssh-keygen -t ed25519 -C "email@example.com"
```
  - passphrase is a waste of time, but you can put it in.
4. Once that is done, proceed to connect with Github.
  - login to Github first
  - authenticate GitHub CLI on the command line
```
gh auth login
```
  - follow the instructions
  - copy the code, proceed to open browser, past code, done.

## First commit
When the above is done, WSL should be able to talk to Git via a secure line.
We now proceed to set up commit for the first time:
1. create folder, it can contain a single program (big project), or multiple folders containing programs of the same category. (at least that's what I did)
```
mkdir repo1
```
2. Let's say I've written some codes in the `repo1` folder, now I'm ready to make my backup. Starting with initialization
```
git init
```
3. We don't want to sync all files, so we create a `.gitignor` file. These are the module files, object files, executables, data files and so on.
4. Then we need to add the files in `repo1` to a list of 'track changes' files
```
git add .
```
5. we commit these changes by calling
```
git commit -a -m 'some comment about this commit'
```
6. create a corresponding repository in GitHub via CLI
```
gh repo create
```
7. Following the instructions, and add remote called `origin`
8. when prompt to push commit, just confirm, and everything should be synced to Git.
9. To simplify things further, we use `git push -u origin master` instead of `git push origin master` so in the future, we can just `git push` instead of `git push origin master` all the time.

## Everyday commit and push
Later on, when working normally in the `repo1` folder, you would create new files, and/or make changes in existing files.
We need to sync those as well.
1. add new files for syncing if needed
```
git add .
```
2. then commit all changes
```
git commit -a -m 'some comment about this commit'
```
3. push those updated changes to master (if already used `git push -u origin master`)
```
git push
```

## Updated `.gitignore` or added new files
The above procedure works when we already have a project  with a list of files working. However, we some times wish to add new files or update the list of "ignored files". We can apply the following after we have an updated `.gitignore` file:
```
git rm -r --cached .
```
This removes all files and folders in the git cache, then simply add it back it again:
```
git add .
```
Then perform the usual commit and push
```
git commit -a -m 'updated .gitignore and/or added some files'
git push
```

