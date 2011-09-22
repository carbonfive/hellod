HelloD
====================

Testing high performance HTTP "Hello World" servers.

Ruby
-----------

To run:

    gem install eventmachine http_parser
    ruby -v server.rb

Node
-----------

To run:

    brew install node
    node server.js


Benchmark
-----------

    ab -n 10000 -c 100 http://localhost:8080/
