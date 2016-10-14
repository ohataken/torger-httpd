#include "torger_select.h"

fd_set torger_readfds = {};

fd_set torger_writefds = {};

struct runi_object *torger_fd_zero(struct runi_object *env, struct runi_object *list) {
    FD_ZERO(&torger_readfds);
    FD_ZERO(&torger_writefds);
    return runi_nil;
}

struct runi_object *torger_fd_set_to_readfds(struct runi_object *env, struct runi_object *list) {
    if (runi_list_length(list) != 1) {
        runi_error("Malformed torger_fd_set_to_readfds");
    }

    struct runi_object *obj = runi_eval(env, list->car);

    if (obj->type != RUNI_INTEGER) {
        runi_error("torger_fd_set_to_readfds only takes a integer");
    }

    FD_SET(obj->integer, &torger_readfds);
    return runi_nil;
}

struct runi_object *torger_fd_set_to_writefds(struct runi_object *env, struct runi_object *list) {
    if (runi_list_length(list) != 1) {
        runi_error("Malformed torger_fd_set_to_writefds");
    }

    struct runi_object *obj = runi_eval(env, list->car);

    if (obj->type != RUNI_INTEGER) {
        runi_error("torger_fd_set_to_writefds only takes a integer");
    }

    FD_SET(obj->integer, &torger_writefds);
    return runi_nil;
}

struct runi_object *torger_select(struct runi_object *env, struct runi_object *list) {
    return runi_make_integer(select(65535, &torger_readfds, &torger_writefds, NULL, NULL));
}

struct runi_object *torger_fd_isset_readfds(struct runi_object *env, struct runi_object *list) {
    if (runi_list_length(list) != 1) {
        runi_error("Malformed torger_fd_isset_readfds");
    }

    struct runi_object *obj = runi_eval(env, list->car);

    if (obj->type != RUNI_INTEGER) {
        runi_error("torger_fd_isset_readfds only takes a integer");
    }

    return runi_make_integer(FD_ISSET(obj->integer, &torger_readfds));
}

struct runi_object *torger_fd_isset_writefds(struct runi_object *env, struct runi_object *list) {
    if (runi_list_length(list) != 1) {
        runi_error("Malformed torger_fd_isset_writefds");
    }

    struct runi_object *obj = runi_eval(env, list->car);

    if (obj->type != RUNI_INTEGER) {
        runi_error("torger_fd_isset_writefds only takes a integer");
    }

    return runi_make_integer(FD_ISSET(obj->integer, &torger_writefds));
}
