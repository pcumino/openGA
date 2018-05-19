#!/usr/bin/env bash
clear;
echo ""
echo "Waiting for update of the file '$1'..."
fswatch [opts] -0 $1 | \
  xargs -0 -n1 -I{} sh runAG-container.sh $1;
