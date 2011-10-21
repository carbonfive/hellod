#!/bin/bash

short="-n 10000 -c 50"
long="-n 50000 -c 200"

source "$HOME/.rvm/scripts/rvm"

./hellod stop all > /dev/null

rvm 1.9.2@hellod
./hellod start ruby > /dev/null
echo "Ruby 1.9.2" 
echo "----------" 
echo `ruby -v`
echo ""
./hellod test ruby $short 
./hellod test ruby $long
./hellod stop ruby > /dev/null
echo ""

rvm 1.9.3@hellod
./hellod start ruby > /dev/null
echo "Ruby 1.9.3"
echo "----------"
echo `ruby -v`
echo ""
./hellod test ruby $short
./hellod test ruby $long
./hellod stop ruby > /dev/null
echo ""

rvm jruby@hellod
./hellod start ruby > /dev/null
sleep 10
echo "JRuby 1.6.4"
echo "-----------"
echo `ruby -v`
echo ""
./hellod test ruby $short
./hellod test ruby $long
./hellod stop ruby > /dev/null
echo ""

./hellod start go > /dev/null
echo "go"
echo "-----"
echo `6g -V`
echo ""
./hellod test go $short
./hellod test go $long
./hellod stop go > /dev/null
echo ""

./hellod start node > /dev/null
echo "Node.js"
echo "-------"
echo `node -v`
echo ""
./hellod test node $short
./hellod test node $long
./hellod stop node > /dev/null
echo ""

./hellod start clj-aleph > /dev/null
sleep 10
echo "Clojure (with Aleph)"
echo "--------------------"
echo `lein version`
echo ""
./hellod test clj-aleph $short
./hellod test clj-aleph $long
./hellod stop clj-aleph > /dev/null
echo ""

./hellod start clj-jetty > /dev/null
sleep 10
echo "Clojure (with Jetty)"
echo "--------------------"
echo `lein version`
echo ""
./hellod test clj-jetty $short
./hellod test clj-jetty $long
./hellod stop clj-jetty > /dev/null
echo ""
