FROM ubuntu:18.04  

COPY ./app/ /app

WORKDIR /app/

RUN mv -f ./sources.list /etc/apt/sources.list

RUN  apt-get update -y \ 
    && apt-get install unzip \ 
    && apt-get install -y python3-pip python3-dev \
    && pip3 install -r ./requirements.txt



ENTRYPOINT [ "python3" ]

EXPOSE 8080

CMD [ "./app.py" ]
