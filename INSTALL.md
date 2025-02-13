# Install

## Kubectl

```bash
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl
kubectl version --client
```

## Minikube

### Install

```bash
curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64

chmod +x ./minikube

sudo mv ./minikube /usr/local/bin/minikube

minikube version
```

### Init a driver with docker

```bash
minikube start --driver=docker
```

### First steps

```bash
minikube config set driver docker 

minikube start
minikube stop
minikube delete --purge

minikube start --nodes 2 -p multinode-cluster
minikube start --nodes 3 --driver=docker -p multinode-cluster
```

```bash
minikube ip
minikube ssh
minikube dashboard
minikube logs
```
