# O que é Kubernetes

- Orquestrador de contêineres, desenvolvido pela Google. Borg, Omega e Kubernetes;
- k8s ("kates"), termo grego significa timoneiro;

## Container Engine (CE)

- Gerencia imagens e volumes
- Garantir que os recursos utilizados pelos containers estão devidamente isolados
- Vida do container, storage, network

Opções de container engine: Docker, CRI-O, Podman

## OCI (Open Container Iniciative)

- Padronizar a criação de containers
- runc é um container runtime de baixo nível

## Container Runtime (CR)

- O container runtime é usado pelo container engine

Tipos de CR

- Low-level: executado diretamente pelo kernel (runc, crun, runsc)
- High-level: executado por um Container Engine (containerd, CRI-O, Podman)
- Sandbox e Virtualized: executado por um Container Engine e executam containers de forma segura. 
  - Sandbox: unikernel ou proxy para falar com o kernel; exemplo: gVisor; 
  - Virtualized: executado por maquinas virtuais, menos performance; exemplo: Kata Container

## Executando k8s localmente

- Kind, Minikube (use apenas para finalidades didáticas)
- MicroK8S, canonical, pode usar em produção
- K3s, concorrente do MicroK8S, pode ser executado até em uma raspberry pi
- K0s (kay-zero-ess), funciona em um único binário, pode ser usado em produção

## Arquitetura k8s

- Modelo control plane/workers;
- Minimo de 3 nos:
  - control-plane: responsavel pelo gerenciamento do cluster
  - workers: executar as aplicações

- API Server: usa JSON e HTTP REST, kubectl;
- etcd: datastore chave-valor distribuído pelo k8s para armazenar
especificações, status e config. Executado em control plane;
- Scheduler: seleciona o nó que irá hospedar um determinado pod; pode levar
em consideração políticas definidas pelo usuário;
- Controller Manager: garante que o cluster esteja no último estado definido no etcd
- Kubelet: agente do k8s executado nos workers; gerenciar efetivamente os pods, obedece
o que foi definido pelo controller;
- Kube-proxy: proxy e load-balancer; roteamento de requisições para os pods corretos;
cuida da rede do nó;

## Conceitos-chave do k8s

- Pod: é o menor objeto do k8s, ele não trabalha com containers diretamente, mas organiza-os
dentro de pods, que são abstrações que dividem os mesmos recursos ( endereços, volumes,
ciclos de CPU). Um pod pode possir vários contêineres;
- ReplicaSets: responsável por garantir a quantidade de pods em execução no nó
- Services: expor a comunicação através de um ClusterIP, NodePort ou LoadBalancer para distribuir
as requisições entre os diversos pods daquele Deployment;
- Deployment: um dos principais controllers usados; junto com o ReplicaSets garante um determinado
número de replicas. Gerencia o ciclo de vida da aplicação:  imagem, porta, volumes e variáveis de
ambiente, podem ser especificados em arquivos do tipo yaml ou json; posteriormente podem ser passados
como parâmetro para o kubectl; criar, executar e remover o deployment.

## Control Plane

- gerenciar namespaces, deployments, services, configmaps, secrets, etc.
- gerenciar workers do cluster
- gerenciar rede do cluster
- etcd armazena as informações de configuração de todos os componentes do control plane
  - Design distribuido
  - tolerar falhas
  - comunicação segura entre os componentes do cluster usando TLS
- scheduler é o componente responsável por decidir em qual nó os pods serão executados,
se necessário, ajusta a distribuição dos pods para garantir a melhor utilização dos recursos
e manter a harmonia entre os componentes.
- controller manager gerenciar os diferentes controladores que regulam o estado do cluster e 
mantêm tudo funcionando
- api-server componente central que expõe a API do Kubernetes, permitindo que outros componentes
do control plane, como o controller-manager e o scheduler, bem como ferramentas externas, se
comuniquem e interajam com o cluster.

## Worker

- kubelet é o agente que funciona em cada nó do cluster, garantindo que os containers estejam funcionando
conforme o esperado dentro dos pods.
- kube-proxy, que é o componente responsável fazer ser possível que os pods e os services se comuniquem 
entre si e com o mundo externo.

## ReplicaSet

é quem vai criar os Pods que estão dentro do Deployment;
É possível criar um ReplicaSet sem um Deployment, mas não é uma boa prática;

## DaemonSet

O DaemonSet é muito útil para executar Pods que precisam ser executados em todos
os nós do cluster, como por exemplo, um Pod que faz o monitoramento de logs, ou um
Pod que faz o monitoramento de métricas.

- Execução de agentes de monitoramento
- Execução de um proxy de rede em todos os nós do cluster
