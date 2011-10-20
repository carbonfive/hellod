(ns hellod.core)
(use 'lamina.core 'ring.adapter.jetty)

(defn hello [req]
  {:status 200
   :headers {"Content-Type" "text/html"}
   :body "<html><body><h1>Hello World</h1></body></html>"}) 

(defn -main [& args]
  (run-jetty hello {:port 8084}))

