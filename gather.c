#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

  int count = 1;
  int root = 0;
  int nb_proc, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int val = rank * 100;

  if (rank == root)
  {
    int buf[4];
    MPI_Gather(&val, count, MPI_INT, buf, count, MPI_INT, root, MPI_COMM_WORLD);
    printf("[MPI rank %d] Values collected: %d, %d, %d, %d\n", rank, buf[0], buf[1], buf[2], buf[3]);
  }
  else
  {
    MPI_Gather(&val, count, MPI_INT, NULL, 0, MPI_INT, root, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}