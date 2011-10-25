#!/bin/bash

source "$HOME/.rvm/scripts/rvm"

run()
{
  local flavor=$1
  local desc=$2
  local version1=$3
  local version2=$4
  local rvm=$5
  local java=$6

  if [ "$rvm" != "" ]; then
    rvm $rvm
  fi

  if [ "$java" != "" ]; then
    sudo update-alternatives --set java $java > /dev/null 2>&1
  fi

  ./hellod start $flavor > /dev/null
  echo $desc
  echo "-------------"
  if [ "$version1" != ""]; then
    echo -e "\t$version1"
    $version1 2>&1 | sed s/^/\\t/
  fi

  if [ "$version2" != "" ]; then
    echo ""
    echo -e "\t$version2"
    $version2 2>&1 | sed s/^/\\t/
  fi

  echo ""
  sleep 5
  ./hellod test $flavor -n 10000 -c 50 > /dev/null
  ./hellod test $flavor -n 10000 -c 50 > /dev/null

  ./hellod test $flavor -n 10000 -c 50
  ./hellod test $flavor -n 50000 -c 200
  ./hellod stop $flavor > /dev/null

  echo "" 
}

./hellod stop all > /dev/null

OPENJDK='/usr/lib/jvm/java-6-openjdk/jre/bin/java'
SUNJDK='/usr/lib/jvm/java-6-sun/jre/bin/java'

run 'ruby' 'Ruby 1.9.2' 'ruby -v' '' '1.9.2@hellod' ''
run 'ruby' 'Ruby 1.9.3' 'ruby -v' '' '1.9.3@hellod' ''
run 'ruby' 'JRuby 1.6.4 - Sun JDK' 'ruby -v' 'java -version' 'jruby@hellod' $SUNJDK
run 'ruby' 'JRuby 1.6.4 - OpenJDK' 'ruby -v' 'java -version' 'jruby@hellod' $OPENJDK
run 'go' 'Go' '6g -V' '' '' ''
run 'node' 'Node.js' 'node -v' '' '' ''
run 'c' 'C / libev' '' '' '' ''
run 'clj-aleph' 'Clojure / Aleph - Sun JDK' 'lein version' 'java -version' '' $SUNJDK
run 'clj-aleph' 'Clojure / Aleph - OpenJDK' 'lein version' 'java -version' '' $OPENJDK
run 'clj-jetty' 'Clojure / Ring - Sun JDK' 'lein version' 'java -version' '' $SUNJDK
run 'clj-jetty' 'Clojure / Ring - OpenJDK' 'lein version' 'java -version' '' $OPENJDK
