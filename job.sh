#!/bin/bash

#SBATCH --job-name=mx-multiplication
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --time=00:10
#SBATCH --nodes=1
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=100M

#module load singularity
srun /usr/mpi/gcc/openmpi-4.0.4rc3/bin/mpirun -np 2 singularity run --bind /g100_scratch/usertrain/a08trb53:/scratch_local mx-multiplication.sif
