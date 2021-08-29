#!/bin/bash
docker rm -f ez_trick 
docker build -t ez_trick  . && \
docker run --name=ez_trick  --rm -p1337:80 -it ez_trick
