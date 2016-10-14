.c.o:
	$(CC) -Wall -Wextra -g -c $<

torger-httpd: runi_lisp.o torger_socket.o torger_select.o main.o
	$(CC) -o torger-httpd $^

run: torger-httpd
	cat torger-httpd.scm | ./$<
