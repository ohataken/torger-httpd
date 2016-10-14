(socket)
(socket-set-port 8080)
(bind)
(listen)

(define sockd -1)

(defun accept-and-receive ()
  (setq sockd (accept))
  (println (recv sockd))
  (send sockd "HTTP/1.1 200 OK\n\r")
  (send sockd "Content-Length: 11\n\r")
  (send sockd "\r\n")
  (send sockd "hello world\r\n")
  (accept-and-receive))

(accept-and-receive)
