HelloD
====================

Testing high performance HTTP "Hello World" servers.

Ruby
-----------

To run:

    gem install eventmachine http_parser.rb
    ruby ruby/server.rb

Runs on port 8080

Node
-----------

To run:

    brew install node
    node node/server.js

Runs on port 8081

Go
-----------

To run:

    brew install go
    export GOROOT=/usr/local/Cellar/go/r60.1
    cd go
    make
    ./hellod

Runs on port 8082

Benchmark
-----------
    ab -n 10000 -c 100 http://localhost:8080/

or 8081 or 8082...
