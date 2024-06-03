#!/bin/bash

#SBATCH --job-name=mx-multiplication
#SBATCH --output=mx-multiplication.out
#SBATCH --error=mx-multiplication.err
#SBATCH --time=00:10
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=100M

module load singularity
srun singularity run mx-multiplication.sif