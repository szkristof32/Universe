#!/bin/bash

chmod +x vendor/premake/premake5

if [[ $# -eq 0 ]]; then project="gmake";
else project=$1; fi

./vendor/premake/premake5 $project
