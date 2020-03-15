#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -dir dir -sim sim -ver ver"
   echo -e "\t-d Directory in ./outputs/"
   echo -e "\t-s Simulation in ./simulations/"
   echo -e "\t-v Version in ./standard/"
   exit 1 # Exit script after printing help
}

while getopts "d:s:v:" opt
do
	case "$opt" in
		d ) dir="$OPTARG" ;;
		s ) sim="$OPTARG" ;;
		v ) ver="$OPTARG" ;;
		? ) helpFunction ;;
	esac
done

# Print help function in case parameters are empty
if [ -z "$dir" ] || [ -z "$sim" ] || [ -z "$ver"]
then
   echo "Some or all of the parameters are empty";
   helpFunction
fi

# Begin script in case all parameters are correct
echo "Runtime directory: ./runs/$dir"
echo "Simulation: $sim"
echo "Version: $ver"
mkdir ./runs/$dir
mkdir ./runs/$dir/output

# Move standard files to run directory
cp ./standard/$ver/* ./runs/$dir

# Move simulation-specific files to run directory
cp ./simulations/$sim/sim_decs.h ./runs/$dir
cp ./simulations/$sim/sim_defs.h ./runs/$dir
cp ./simulations/$sim/sim_params.h ./runs/$dir
cp ./simulations/$sim/sim_init.c ./runs/$dir
cp ./simulations/$sim/sim_initBlock.c ./runs/$dir
