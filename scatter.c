#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

  int val, count = 1;
  int root = 0;
  int nb_proc, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == root)
  {
    int buf[4] = {0, 100, 200, 300};
    printf("[MPI rank %d] Values scattering: %d, %d, %d, %d\n", rank, buf[0], buf[1], buf[2], buf[3]);
    MPI_Scatter(buf, count, MPI_INT, &val, count, MPI_INT, root, MPI_COMM_WORLD);
  }
  else
  {
    MPI_Scatter(NULL, 0, MPI_INT, &val, count, MPI_INT, root, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}