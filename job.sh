#!/bin/bash

#SBATCH --job-name=mx-multiplication
#SBATCH --output=mx-multiplication.out
#SBATCH --error=mx-multiplication.err
#SBATCH --time=00:10
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --mem-per-cpu=100M

#module load singularity
/usr/mpi/gcc/openmpi-4.0.4rc3/bin/mpirun -np 1 singularity run mx-multiplication.sif /bin/mx-multiplication