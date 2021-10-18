#!/bin/bash
docker rm -f one_word
docker build -t one_word . && \
docker run --name=one_word --rm -p1337:80 -it one_word