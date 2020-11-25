# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    setup.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 13:27:51 by hchorfi           #+#    #+#              #
#    Updated: 2020/11/24 13:27:52 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

### starting minikube
echo "/-----------------------------------------------------------------------/"
echo "/starting minikube"
echo "/-----------------------------------------------------------------------/"
export MINIKUBE_HOME=/Volumes/HAKUNA_MATA/1337/minikube
minikube start --driver virtualbox
minikube docker-env
eval $(minikube -p minikube docker-env)
minikubeip=$(minikube ip)
echo $minikubeip
sed -i '' "s/192.168.99.*/$minikubeip-$minikubeip/g" ./srcs/metallb-configmap.yaml

### deploy MetalLB
echo "/-----------------------------------------------------------------------/"
echo "/deploy MetalLB"
echo "/-----------------------------------------------------------------------/"
#kubectl apply -f \
#https://raw.githubusercontent.com/metallb/metallb/v0.9.5/manifests/namespace.yaml
#kubectl apply -f \
#https://raw.githubusercontent.com/metallb/metallb/v0.9.5/manifests/metallb.yaml
# On first install only
#kubectl create secret generic -n metallb-system memberlist \
#--from-literal=secretkey="$(openssl rand -base64 128)"


