(ns hellod.core)
(use 'lamina.core 'aleph.http 'ring.adapter.jetty)

(defn hello-world [channel request]
  (enqueue channel
    {:status 200
     :headers {"content-type" "text/html"}
     :body "<html><body><h1>Hello World</h1></body></html>"}))

(defn hello [req]
  {:status 200
   :headers {"Content-Type" "text/html"}
   :body "Hello World from Ring"}) 

(defn -main [& args]
  (start-http-server hello-world {:port 8083})
  (run-jetty hello {:port 8084}))

