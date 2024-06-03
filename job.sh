#!/bin/bash

#SBATCH --job-name=mx-multiplication
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --time=00:10
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --mem-per-cpu=100M

#module load singularity
srun singularity exec mx-multiplication.sif mx-multiplication
