#include "runi_lisp.h"
#include "torger_socket.h"
#include "torger_select.h"

#include <stdio.h>

int main(void) {
    printf("runi-lisp\n");

    runi_nil = runi_make_special(RUNI_NIL);
    runi_dot = runi_make_special(RUNI_DOT);
    runi_cparen = runi_make_special(RUNI_CPAREN);
    runi_true = runi_make_special(RUNI_TRUE);
    runi_symbols = runi_nil;

    struct runi_object *env = runi_make_env(runi_nil, NULL);

    runi_add_variable(env, runi_intern("t"), runi_true);
    runi_add_primitive(env, "quote", runi_prim_quote);
    runi_add_primitive(env, "list", runi_prim_list);
    runi_add_primitive(env, "setq", runi_prim_setq);
    runi_add_primitive(env, "+", runi_prim_plus);
    runi_add_primitive(env, "define", runi_prim_define);
    runi_add_primitive(env, "defun", runi_prim_defun);
    runi_add_primitive(env, "defmacro", runi_prim_defmacro);
    runi_add_primitive(env, "macroexpand", runi_prim_macroexpand);
    runi_add_primitive(env, "lambda", runi_prim_lambda);
    runi_add_primitive(env, "if", runi_prim_if);
    runi_add_primitive(env, "=", runi_prim_num_eq);
    runi_add_primitive(env, "println", runi_prim_println);
    runi_add_primitive(env, "exit", runi_prim_exit);

    runi_add_primitive(env, "socket", torger_socket);
    runi_add_primitive(env, "socket-set-port", torger_set_socket_port);
    runi_add_primitive(env, "bind", torger_bind);
    runi_add_primitive(env, "listen", torger_listen);
    runi_add_primitive(env, "accept", torger_accept);
    runi_add_primitive(env, "recv", torger_recv);
    runi_add_primitive(env, "send", torger_send);
    runi_add_primitive(env, "close", torger_close);
    runi_add_primitive(env, "fd-zero", torger_fd_zero);
    runi_add_primitive(env, "fd-set-read", torger_fd_set_to_readfds);
    runi_add_primitive(env, "fd-set-write", torger_fd_set_to_writefds);
    runi_add_primitive(env, "select", torger_select);

    for (;;) {
        struct runi_object *expr = runi_parse();
        if (!expr)
            return 0;
        if (expr == runi_cparen)
            runi_error("Stray close parenthesis");
        if (expr == runi_dot)
            runi_error("Stray dot");
        runi_print(runi_eval(env, expr));
        printf("\n");
    }

    return 0;
}
