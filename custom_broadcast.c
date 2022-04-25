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

  if (rank == root)
  {
    buf = 13;
    printf("[MPI rank %d] Sending from root value %d\n", rank, buf);
  }

  customBroadcast(&buf, count, MPI_INT, root, MPI_COMM_WORLD);

  if (rank != root)
  {
    printf("[MPI rank %d] Receiving from root value %d\n", rank, buf);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}

int customBroadcast(void *buf, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
{
  int nb_proc, rank;
  int sender = root, receiver;
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == root){
    for(receiver = 0; receiver < nb_proc; receiver++)
      if (receiver != root)
        MPI_Send(buf, count, datatype, receiver, MPI_ANY_TAG, communicator);
  }
  else {
    MPI_Recv(&buf, count, datatype, sender, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
}