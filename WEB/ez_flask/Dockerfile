FROM ubuntu:18.04  

COPY ./app /

RUN apt-get update -y \ 
    && apt-get install unzip \ 
    && apt-get install -y python3-pip python3-dev \
    && pip3 install -r /app/requirements.txt

WORKDIR /

ENTRYPOINT [ "python3" ]

CMD [ "app/app.py" ]
