#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

  int buf, count = 1;
  int root = 0;
  int nb_proc, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == root){
    buf = 13;
    printf("[MPI rank %d] Sending from root value %d\n", rank, buf);
  }

  MPI_Bcast(&buf, count, MPI_INT, root, MPI_COMM_WORLD);

  if (rank != root){
    printf("[MPI rank %d] Receiving from root value %d\n", rank, buf);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}