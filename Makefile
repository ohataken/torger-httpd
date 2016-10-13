.c.o:
	$(CC) -Wall -Wextra -g -c $<

torger-httpd: runi_lisp.o main.o
	$(CC) -o torger-httpd $^

run: torger-httpd
	./$<
