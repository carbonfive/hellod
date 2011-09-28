package main

import (
  "fmt"
  "http"
  "strconv"
)

var html []byte = []byte("<html><body><h1>Hello World</h1></body></html>\r\n")
var html_length int = len(html);

func main() {
  http.HandleFunc("/", HelloServer)
  err := http.ListenAndServe(":8082", nil)
  if err != nil {
    fmt.Println("ListenAndServe: ", err.String())
  }
}

func HelloServer(w http.ResponseWriter, req *http.Request) {
  // Emit JSON stringified request headers, only we can't.
  // Seems to be a bit of of a work-in progress; see http://golang.org/src/pkg/http/request.go
  w.Header().Set("Content-Type", "text/html")
  w.Header().Set("Content-Length", strconv.Itoa(html_length))
  w.Write(html);
}
