# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install-brew.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 16:52:43 by hchorfi           #+#    #+#              #
#    Updated: 2020/11/21 16:52:45 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

<<test
INSTALL_PATH="/Volumes/HAKUNA_MATA/1337/Cursus"

mkdir $INSTALL_PATH/.brew
curl -fsSL https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C $INSTALL_PATH/.brew
mkdir -p /tmp/.$(whoami)-brew-locks
mkdir -p $INSTALL_PATH/.brew/var/homebrew
ln -s /tmp/.$(whoami)-brew-locks $INSTALL_PATH/.brew/var/homebrew/locks
echo "export PATH=$INSTALL_PATH/.brew/bin:$PATH" >> ~/.bashrc
echo "export PATH=$INSTALL_PATH/.brew/bin:$PATH" >> ~/.zshrc
ln -s $INSTALL_PATH/.brew $HOME/.brown
brew update && brew upgrade
mkdir -p /tmp/.$(whoami)-brew-locks
echo "export PATH=$HOME/.brown/bin:$PATH" >> ~/.bashrc
echo "export PATH=$HOME/.brown/bin:$PATH" >> ~/.zshrc
test

mkdir /goinfre/$1/.brew && curl -fsSL https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C /goinfre/$1/.brew
mkdir -p /tmp/.$(whoami)-brew-locks
mkdir -p /goinfre/$1/.brew/var/homebrew
ln -s /tmp/.$(whoami)-brew-locks /goinfre/$1/.brew/var/homebrew/locks
echo 'export PATH="/goinfre/$1/.brew/bin:$PATH"' >> ~/.bashrc
echo 'export PATH="/goinfre/$1/.brew/bin:$PATH"' >> ~/.zshrc
ln -s /goinfre/$1/.brew ~/.brown
brew update && brew upgrade
mkdir -p /tmp/.$(whoami)-brew-locks
echo 'export PATH="$HOME/.brown/bin:$PATH"' >> ~/.bashrc
echo 'export PATH="$HOME/.brown/bin:$PATH"' >> ~/.zshrc
brew install docker && brew install docker-machine
docker-machine create --driver virtualbox default
docker-machine env default
eval $(docker-machine env default)
