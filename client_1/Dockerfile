FROM gcc:latest

COPY ./main.c /app/

WORKDIR /app

RUN gcc -o main main.c -lpthread

CMD ["./main"]