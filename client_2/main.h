#define NAMESIZE 100
#define MESSAGESIZE 1000
#define NPEERS 10

void handle_error(const char* msg);
void *receive_fun(void* server_fd);
void recvdata(int socket);
void send_data_to_server(const char* msg);
void send_data_to_peer(const int peerport, const char* msg, const char* peer);
