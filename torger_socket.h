#ifndef TORGER_SOCKET_H
#define TORGER_SOCKET_H

#include "runi_lisp.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

struct runi_object *torger_socket(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_set_socket_port(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_bind(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_listen(struct runi_object *env, struct runi_object *list);

// struct runi_object *torger_accept(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_close(struct runi_object *env, struct runi_object *list);

// void sigint_handler(int signo);

#endif
