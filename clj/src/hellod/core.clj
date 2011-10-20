(ns hellod.core)
(use 'lamina.core 'aleph.http)

(defn hello-world [channel request]
  (enqueue channel
    {:status 200
     :headers {"content-type" "text/html"}
     :body "<html><body><h1>Hello World</h1></body></html>"}))

(defn -main [& args]
  (start-http-server hello-world {:port 8083}))
