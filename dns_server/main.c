#include <stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init failed\n");
        return 1;
    }

    printf("MYSQL INIT INITIALIZED\n");

    if (mysql_real_connect(conn, "mysql_database", "root", "password", "DNS", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    printf("CONNECTION COMPLETED\n");

    if (mysql_query(conn, "SELECT * FROM data")) {
        fprintf(stderr, "mysql_query failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    printf("QUERY COMPLETED\n");

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s %s\n", row[0], row[1]); // Assuming your_table has two columns
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("DNS_SERVER DISCONNECTED\n");

    

    return 0;
}
