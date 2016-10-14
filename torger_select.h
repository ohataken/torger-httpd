#ifndef TORGER_SELECT_H
#define TORGER_SELECT_H

#include "runi_lisp.h"

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

extern fd_set torger_readfds;

extern fd_set torger_writefds;

struct runi_object *torger_fd_zero(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_fd_set_to_readfds(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_fd_set_to_writefds(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_select(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_fd_isset_readfds(struct runi_object *env, struct runi_object *list);

struct runi_object *torger_fd_isset_writefds(struct runi_object *env, struct runi_object *list);

#endif
