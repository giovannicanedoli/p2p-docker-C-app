FROM gcc:latest

COPY ./main.c /app/

WORKDIR /app

RUN gcc -o main main.c -lmysqlclient

CMD ["./main"]