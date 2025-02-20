FROM ubuntu:latest
RUN apt update && apt install -y openmpi-bin openmpi-common libopenmpi-dev


ENV PATH="/usr/lib/openmpi/bin:${PATH}"
ENV LD_LIBRARY_PATH="/usr/lib/openmpi/lib:${LD_LIBRARY_PATH}"

WORKDIR /MPI

COPY src/*.c .
COPY src/entrypoint.sh /

RUN mpicc *.c -o output
CMD ["/entrypoint.sh"]
