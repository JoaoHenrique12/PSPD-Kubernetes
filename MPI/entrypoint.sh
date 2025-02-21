#! /bin/sh

/usr/sbin/sshd -D
# mpirun --allow-run-as-root -np 5 --oversubscribe /MPI/output
#
# echo "Fim do processamento"
#
# sleep infinity
