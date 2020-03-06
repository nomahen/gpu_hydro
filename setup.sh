#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -dir dir -sim sim"
   echo -e "\t-d Directory in ./outputs/"
   echo -e "\t-s Simulation in ./simulations/"
   exit 1 # Exit script after printing help
}

while getopts "d:s:" opt
do
	case "$opt" in
		d ) dir="$OPTARG" ;;
		s ) sim="$OPTARG" ;;
		? ) helpFunction ;;
	esac
done

# Print help function in case parameters are empty
if [ -z "$dir" ] || [ -z "$sim" ]
then
   echo "Some or all of the parameters are empty";
   helpFunction
fi

# Begin script in case all parameters are correct
echo "Runtime directory: ./runs/$dir"
echo "Simulation: $sim"
mkdir ./runs/$dir
mkdir ./runs/$dir/output

# Move standard files to run directory
cp ./standard/* ./runs/$dir

# Move simulation-specific files to run directory
cp ./simulations/$sim/sim_decs.h ./runs/$dir
cp ./simulations/$sim/sim_defs.h ./runs/$dir
cp ./simulations/$sim/sim_params.h ./runs/$dir
cp ./simulations/$sim/sim_init.c ./runs/$dir
cp ./simulations/$sim/sim_initBlock.c ./runs/$dir
