#! /bin/sh

/usr/sbin/sshd -D
# mpirun --allow-run-as-root /MPI/output input.txt
#
# echo "Fim do processamento"
#
# sleep infinity
