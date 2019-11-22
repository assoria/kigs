#! /bin/bash

export myDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export targetName="Unix Makefiles"


echo selected target : $targetName
echo current dir     : $myDir

if [ ! -d "$myDir/../../Build" ]; then
  mkdir  "$myDir/../../Build"
fi

if [ ! -d "$myDir/../../Build/solutionMacOS" ]; then
  mkdir  "$myDir/../../Build/solutionMacOS"
fi

cd "$myDir/../../Build/solutionMacOS/"

echo launching cmake 
cmake ../../kigs/Scripts/ -DMACOS=TRUE -G"$targetName" 
