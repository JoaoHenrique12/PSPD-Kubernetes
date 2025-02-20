#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);  // Inicializa MPI

  int world_size, world_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);  // Número total de processos
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  // ID do processo atual

  printf("Hello from process %d out of %d\n", world_rank, world_size);

  MPI_Finalize();  // Finaliza MPI
  return 0;
}
