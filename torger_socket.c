#include "torger_socket.h"

int torger_socketd;

int reuseaddr = 1;

struct sockaddr_in torger_sockaddr;

struct sockaddr_in torger_sockaddr_client;

socklen_t torger_addrlen_client;

struct runi_object *torger_socket(struct runi_object *env, struct runi_object *list) {
    torger_socketd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(torger_socketd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    return runi_make_integer(torger_socketd);
}

struct runi_object *torger_set_socket_port(struct runi_object *env, struct runi_object *list) {
    torger_sockaddr.sin_family = AF_INET;
    torger_sockaddr.sin_port = htons(list->car->integer);
    torger_sockaddr.sin_addr.s_addr = INADDR_ANY;
    return runi_nil;
}

struct runi_object *torger_bind(struct runi_object *env, struct runi_object *list) {
    return runi_make_integer(bind(torger_socketd, (struct sockaddr *)&torger_sockaddr, sizeof(torger_sockaddr)));
}

struct runi_object *torger_listen(struct runi_object *env, struct runi_object *list) {
    return runi_make_integer(listen(torger_socketd, 512));
}

struct runi_object *torger_accept(struct runi_object *env, struct runi_object *list) {
    return runi_make_integer(accept(torger_socketd, (struct sockaddr *)&torger_sockaddr_client, &torger_addrlen_client));
}

struct runi_object *torger_recv(struct runi_object *env, struct runi_object *list) {
    if (runi_list_length(list) != 1)
        runi_error("Malformed recv");

    struct runi_object *obj = runi_eval(env, list->car);

    if (obj->type != RUNI_INTEGER)
        runi_error("recv only takes a integer");

    char *buffer = malloc(sizeof(char) * 128);
    recv(obj->integer, buffer, 128, 0);
    return runi_make_string(buffer);
}

struct runi_object *torger_send(struct runi_object *env, struct runi_object *list) {
    if (runi_list_length(list) != 2)
        runi_error("Malformed send");

    struct runi_object *sock = runi_eval(env, list->car);
    struct runi_object *buff = runi_eval(env, list->cdr->car);

    if (sock->type != RUNI_INTEGER || buff->type != RUNI_STRING)
        runi_error("send only takes integer and string");

    return runi_make_integer(send(sock->integer, buff->string, strlen(buff->string), 0));
}

struct runi_object *torger_close(struct runi_object *env, struct runi_object *list) {
    close(torger_socketd);
    return runi_nil;
}

// void sigint_handler(int signo) {
//     torger_close();
//     exit(EXIT_FAILURE);
// }
