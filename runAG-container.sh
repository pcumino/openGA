#!/bin/bash
docker build -t "openga-container" . ;
docker run -it openga-container make main ;