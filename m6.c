#include   <stdio.h>
#include   <mpi.h>
#include <string.h>
#include <stdlib.h>
  
  void main(int argc, char *argv[])
  {
	int rank,size;
	int param[6],mine;
	int part_str_len = 12;

  	char *my_string;
  	char *rcv_string;

	int sndcnt,rcvcnt,msndcnt,mrcvcnt;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if ((my_string = malloc(part_str_len*sizeof(char))) == NULL){
    MPI_Abort(MPI_COMM_WORLD,1);
  }
  if ((rcv_string = malloc(part_str_len*size*sizeof(char))) == NULL){
    MPI_Abort(MPI_COMM_WORLD,1);
  }

	sndcnt=1;
	msndcnt=12;
	mine=rank;
	strcpy(my_string,"Hello world");

  
 	if(rank==0) 
	{ 
	rcvcnt=1;
	mrcvcnt=12;
	}

	MPI_Gather(&mine,sndcnt,MPI_INT,param,rcvcnt,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Gather(my_string,msndcnt,MPI_CHAR,rcv_string,mrcvcnt,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0)
{
		for(i=0;i<size;i++) {
		  printf(" gathering process id:%d received %d and %s from process id:%d  \n",rank,param[i],&rcv_string[part_str_len*i],i); 
		}
}
		
	MPI_Finalize();
}
