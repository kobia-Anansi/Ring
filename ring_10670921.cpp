#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[]){
int world_rank; int world_size; int number;

MPI_Init(&argc, &argv);    
world_rank = MPI::COMM_WORLD.Get_rank();
world_size = MPI::COMM_WORLD.Get_size();

if (world_rank == 0){
    number = 1;
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Recv(&number, 1, MPI_INT, world_size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout<< "Process " <<world_rank << " received number " << number << " from process " << world_size-1 <<endl;
}else if (world_rank==world_size-1){
    MPI_Recv(&number, 1, MPI_INT, world_rank-1, 0, MPI_COMM_WORLD,
    MPI_STATUS_IGNORE);
    MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);   
    cout<< "Process " <<world_rank << " received number " << number << " from process " << world_rank-1 <<endl;
}else{
    MPI_Recv(&number, 1, MPI_INT, world_rank-1, 0, MPI_COMM_WORLD,
    MPI_STATUS_IGNORE);
    MPI_Send(&number, 1, MPI_INT, world_rank+1, 0, MPI_COMM_WORLD);   
    cout<< "Process " <<world_rank << " received number " << number << " from process " << world_rank-1 <<endl;
}
MPI_Finalize();

}