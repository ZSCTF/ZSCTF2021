#!/bin/bash
docker rm -f helen_of_troy 
docker build -t helen_of_troy  . && \
docker run --name=helen_of_troy  --rm -p1337:80 -it helen_of_troy