FROM mysql:latest

ENV MYSQL_ROOT_PASSWORD=password

COPY ./main.sql /docker-entrypoint-initdb.d/
