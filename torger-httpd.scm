(socket)
(socket-set-port 8080)
(bind)
(listen)

(define sockd -1)

(defun accept-and-receive ()
  (setq sockd (accept))
  (println (recv sockd))
  (send sockd "hello world")
  (accept-and-receive))

(accept-and-receive)
