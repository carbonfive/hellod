HelloD
====================

Testing high performance HTTP "Hello World" servers.

Ruby
-----------

To run:

    gem install eventmachine http_parser.rb
    ruby -v server.rb

Node
-----------

To run:

    brew install node
    node server.js

Go
-----------

To run:

    easy_install mercurial
    brew install go
    export GOROOT=/usr/local/Cellar/go/r60.1
    make
    ./hellod

Benchmark
-----------
    ab -n 10000 -c 100 http://localhost:8080/
