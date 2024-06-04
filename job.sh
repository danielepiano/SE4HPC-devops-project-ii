#!/bin/bash

#SBATCH --job-name=mx-multiplication
#SBATCH --output=output.txt
#SBATCH --error=error.txt

#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=dpiano01@gmail.com

#SBATCH --time=00:10
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --mem-per-cpu=100M

#module load singularity

export PATH=/usr/mpi/gcc/openmpi-4.0.4rc3/bin/:$PATH

export MAIL_TO=dpiano01@gmail.com

export WEBHOOK_URL=https://api.github.com/repos/danielepiano/SE4HPC-devops-project-ii/dispatches
GITHUB_TOKEN=$(cat ~/.github_token)
export GITHUB_TOKEN=$GITHUB_TOKEN

secs_to_human(){
    echo "$(( ${1} / 3600 )):$(( (${1} / 60) % 60 )):$(( ${1} % 60 ))"
}
start=$(date +%s)
echo "$(date -d @${start} "+%Y-%m-%d %H:%M:%S"): ${SLURM_JOB_NAME} start id=${SLURM_JOB_ID}"

# Send email about begin, success, failure via e-mail (Slurm feature)
# Send webhook to enable GitHub Action workflow to send result/failure notification via Telegram

if ( srun mpirun -np 2 singularity run --bind /g100_scratch/usertrain/a08trb53:/scratch_local mx-multiplication.sif ); \
  then ( \
    echo "$SLURM_JOB_NAME Ended after $(secs_to_human $(($(date +%s) - ${start}))) id=$SLURM_JOB_ID" \
    && JSON_CONTENT=$(sed ':a;N;$!ba;s/\n/\\n/g' output.txt | sed ':a;N;$!ba;s/\n/\\n/g') \
    && curl -L \
      -X POST \
      -H "Accept: application/vnd.github+json" \
      -H "Authorization: Bearer $GITHUB_TOKEN" \
      -H "X-GitHub-Api-Version: 2022-11-28" \
      $WEBHOOK_URL \
      -d "{\"event_type\": \"result-notification\", \"client_payload\": {\"passed\": true, \"log\": \"$JSON_CONTENT\" \"filename\": \"output.txt\"}}"
  ); \
  else ( \
    JSON_CONTENT=$(head -n 10 error.txt | sed 's/"/\\"/g' | sed ':a;N;$!ba;s/\n/\\n/g') \
    && curl -L \
      -X POST \
      -H "Accept: application/vnd.github+json" \
      -H "Authorization: Bearer $GITHUB_TOKEN" \
      -H "X-GitHub-Api-Version: 2022-11-28" \
      $WEBHOOK_URL \
      -d "{\"event_type\":\"result-notification\", \"client_payload\": {\"passed\": false, \"log\": \"$JSON_CONTENT...\", \"filename\": \"error.txt\"}}" \
    && exit $?
  );
  fi
