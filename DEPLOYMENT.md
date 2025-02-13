# Deployment

Deployment é um objeto que representa uma aplicação.
  - Gerencia/Atualiza pods
  - Faz rollback
  - Ao criar um Deployment um ReplicaSet é criado também.

## Atualizando Deployments

### RollingUpdate

- estratégia padrão de atualização do kubernetes
- atualiza os pods de forma gradual, atualiza um pod ou grupo de pods por vez

```yaml
strategy:
  type: RollingUpdate
  rollingUpdate:
    maxSurge: 1
    maxUnavailable: 2
```

- maxSurge -> Quantidade máxima de pods que podem ser criados
- maxUnavailable -> Quantidade máxima de pods que podem ficar indisponíveis

### Recreate

- irá remover todos os Pods do Deployment e criar novos Pods com a nova versão da imagem. 
- acontecerá rapidamente
- ficará indisponível durante a atualização

```yaml
  strategy:
    type: Recreate
```

## Comandos

```bash
k get deployments -l app=nginx-deployment
k get pods -l app=nginx
k get replicasets -l app=nginx-deployment

k describe deployment nginx-deployment

# Acompanhar o processo de atualização dos pods
k rollout status deployment nginx-deployment

# Rollback command
k rollout undo deployment nginx-deployment
k rollout undo deployment nginx-deployment --to-revision=1

# Rollback history
k rollout history deployment nginx-deployment
k rollout history deployment nginx-deployment --revision=1

# pausar um deployment
k rollout pause deployment nginx-deployment
k rollout resume deployment nginx-deployment

# reiniciar o Deployment, ou seja, ele vai reiniciar o Deployment recriando os Pods.
k rollout restart deployment nginx-deployment

# Criando e deletando deployment
k apply -f deployment.yaml 
k delete -f deployment.yaml

# Deletando sem o manifesto
k delete deployment nginx-deployment
```

## Exemplo Deployment nginx

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx-deployment
spec:
  replicas: 10
  selector:
    matchLabels:
      app: nginx-deployment
  # strategy: {} # estratégia que será utilizada para atualizar os Pods. Nesse caso nós estamos deixando a estratégia padrão, que é a estratégia Rolling Update, ou seja, o Deployment irá atualizar os Pods um por um. 
  # strategy:
  #   type: RollingUpdate
  #   rollingUpdate:
  #     maxSurge: 1
  #     maxUnavailable: 2
  strategy:
    type: Recreate
  template:
    metadata:
      labels:
        app: nginx-deployment
    spec:
      containers:
      - image: nginx:1.14.0
        name: nginx
        resources:
          limits:
            cpu: "0.5"
            memory: 256Mi
          requests:
            cpu: "0.25"
            memory: 128Mi
```
