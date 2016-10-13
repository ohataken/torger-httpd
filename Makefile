.c.o:
	$(CC) -Wall -Wextra -g -c $<

torger-httpd: main.o
	$(CC) -o torger-httpd $^

run: torger-httpd
	./$<
