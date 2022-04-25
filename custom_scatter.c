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
    customScatter(buf, count, MPI_INT, &val, count, MPI_INT, root, MPI_COMM_WORLD);
  }
  else
  {
    customScatter(NULL, 0, MPI_INT, &val, count, MPI_INT, root, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}

int customScatter(
  void *send_buf, int send_count, MPI_Datatype send_datatype,
  void *rcv_buf, int rcv_count, MPI_Datatype rcv_datatype, 
  int send_rank, MPI_Comm communicator)
{
  int nb_proc;
  void* chunk = send_buf; 

  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

  for(int receiver = 0; receiver < nb_proc; receiver++){
    if(send_buf != NULL){
      MPI_Send(chunk, send_count, send_datatype, receiver, MPI_ANY_TAG, communicator);
      chunk += send_count;
    }
    if(rcv_buf != NULL)
      MPI_Recv(rcv_buf, rcv_count, datatype, send_rank, MPI_ANY_TAG, communicator, MPI_STATUS_IGNORE);
  }
}