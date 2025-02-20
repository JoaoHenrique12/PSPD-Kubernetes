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

# Caso tenha algum problema com a inicialização do cluster, tente alterar a quantia de recursos de cada pod
# e o número de dodes
minikube config set cpus 4
minikube config set memory 4g
minikube start --nodes 2 -p multinode-cluster
```

```bash
minikube ip
minikube ssh
minikube dashboard
minikube logs
```

## Configurando registry local

```bash
# Para conseguir publicar imagens no seu proprio servidor local
# Sem necessidade de subir elas para o docker-hub
minikube addons enable registry -p multinode-cluster
```

```bash
# Altere esta configuracao para permitir que o docker envie imagens
# para o seu registry local
sudo nano /etc/docker/daemon.json

{
  "insecure-registries": ["192.168.49.2:5000"]
}
```

```bash
# Faca o build da imagen desejada e empurre ela para o registry local
docker push 192.168.49.2:5000/mpi-image
```

```bash
# Indicando o nome da imagem no seu arquivo de Deployment
containers:
- name: mpi-container
  image: localhost:5000/mpi-image # Localhost funciona porque o registry do minicube é local
```

### Atualizando a imagen no registry

Feito toda vez que o codigo e alterado

```bash
docker build -t mpi-image .
docker tag mpi-image 192.168.49.2:5000/mpi-image:latest
docker push 192.168.49.2:5000/mpi-image:latest
```

## Metricas

```bash
# Com isso o dashboard mostra o uso de CPU e memoria dos pods
minikube -p multinode-cluster addons enable metrics-server
```

```bash
# stress test
sudo apt install stress
stress --vm 1 --vm-bytes 100M --cpu 1
```
