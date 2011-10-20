HelloD
====================

Testing high performance HTTP "Hello World" servers.

Ruby - port 8080
-----------

    gem install eventmachine http_parser.rb
    ruby ruby/server.rb

Node - port 8081
-----------

    brew install node
    node node/server.js

Go - port 8082
-----------

    brew install go
    export GOROOT=/usr/local/Cellar/go/r60.1
    cd go
    make
    ./hellod

Clojure - port 8083
-----------

    Install Leiningen from https://github.com/technomancy/leiningen
    cd clj ; lein run

Benchmark
-----------
    ab -n 10000 -c 100 http://localhost:8080/

or 8081 or 8082...
