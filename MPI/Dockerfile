FROM ubuntu:latest

# Install ssh server
RUN apt update && apt install -y openssh-server
RUN mkdir /var/run/sshd

## Insecure, just set root password to root.
RUN echo 'root:root' |chpasswd
RUN sed -ri 's/^PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config

## Add ssh keys to container
RUN mkdir -p /root/.ssh
ADD id_rsa /root/.ssh
RUN chmod  600 /root/.ssh/id_rsa
ADD id_rsa.pub /root/.ssh
ADD authorized_keys /root/.ssh
RUN echo "StrictHostKeyChecking no" >> /etc/ssh/ssh_config

EXPOSE 22

# Install MPI things
RUN apt update && apt install -y openmpi-bin openmpi-common libopenmpi-dev


ENV PATH="/usr/lib/openmpi/bin:${PATH}"
ENV LD_LIBRARY_PATH="/usr/lib/openmpi/lib:${LD_LIBRARY_PATH}"

WORKDIR /MPI

COPY src/*.c .
COPY entrypoint.sh /

RUN mpicc *.c -o output
CMD ["/entrypoint.sh"]
