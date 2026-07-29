#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    long long int i;
    long long int num_steps = 100000000;
    double step;
    double x;
    double sum = 0.0;
    double pi = 0.0;
    double local_pi;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    step = 1.0 / (double) num_steps;

    for(i = rank; i < num_steps; i += size)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    local_pi = step * sum;

    MPI_Reduce(&local_pi,
               &pi,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("\n");
        printf("=============================\n");
        printf(" Raspberry Pi Supercomputer\n");
        printf("=============================\n");
        printf("Nodes Used : %d\n", size);
        printf("Estimated PI : %.15f\n", pi);
        printf("=============================\n");
    }

    MPI_Finalize();

    return 0;
}
