#!/bin/bash

#SBATCH --job-name=mx-multiplication
#SBATCH --output=mx-multiplication.out
#SBATCH --error=mx-multiplication.err
#SBATCH --time=00:10
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --mem-per-cpu=100M

singularity run mx-multiplication.sif