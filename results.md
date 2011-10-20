HelloD
============

Performance results testing with ab.  All tests run on a MBP Core i5, 4GB RAM, OS X Lion with:

    ab -n 10000 -c 50 http://127.0.0.1:8080/

The java version:

    java version "1.6.0_26"
    Java(TM) SE Runtime Environment (build 1.6.0_26-b03-383-11A511)
    Java HotSpot(TM) 64-Bit Server VM (build 20.1-b02-383, mixed mode)


Clojure 1.2.1
----------------

Not the fastest and not the most consistent but no red flags.

    Time taken for tests:   2.650 seconds
    Requests per second:    3773.84 [#/sec] (mean)
    Time per request:       13.249 [ms] (mean)
    Time per request:       0.265 [ms] (mean, across all concurrent requests)
    Transfer rate:          560.18 [Kbytes/sec] received

    Percentage of the requests served within a certain time (ms)
      50%     13
      66%     14
      75%     15
      80%     16
      90%     19
      95%     21
      98%     23
      99%     26
     100%     36 (longest request)


Ruby 1.9.3-rc1
----------------

Incredibly fast but that 100% time is probably due to Ruby's primitive "stop the world" GC,
which is a killer in the real world.

    Time taken for tests:   1.155 seconds
    Requests per second:    8659.67 [#/sec] (mean)
    Time per request:       5.774 [ms] (mean)
    Time per request:       0.115 [ms] (mean, across all concurrent requests)
    Transfer rate:          1141.66 [Kbytes/sec] received

    Percentage of the requests served within a certain time (ms)
      50%      4
      66%      5
      75%      5
      80%      5
      90%      6
      95%      6
      98%      7
      99%     18
     100%    235 (longest request)


Go 60.1
----------------

Not the fastest but incredibly consistent.  No GC pauses here.

    Time taken for tests:   2.156 seconds
    Requests per second:    4638.74 [#/sec] (mean)
    Time per request:       10.779 [ms] (mean)
    Time per request:       0.216 [ms] (mean, across all concurrent requests)
    Transfer rate:          674.97 [Kbytes/sec] received

    Percentage of the requests served within a certain time (ms)
      50%     11
      66%     11
      75%     11
      80%     11
      90%     11
      95%     12
      98%     13
      99%     14
     100%     19 (longest request)

JRuby 1.6.4-1.9
----------------

Pretty fast and consistent once the JIT has warmed up.

    Time taken for tests:   1.443 seconds
    Requests per second:    6929.94 [#/sec] (mean)
    Time per request:       7.215 [ms] (mean)
    Time per request:       0.144 [ms] (mean, across all concurrent requests)
    Transfer rate:          913.62 [Kbytes/sec] received

    Percentage of the requests served within a certain time (ms)
      50%      7
      66%      7
      75%      7
      80%      7
      90%      9
      95%     11
      98%     13
      99%     16
     100%     19 (longest request)


Node.js 0.4.12
------------------

Good speed, poor consistency.

    Time taken for tests:   1.819 seconds
    Requests per second:    5497.75 [#/sec] (mean)
    Time per request:       9.095 [ms] (mean)
    Time per request:       0.182 [ms] (mean, across all concurrent requests)
    Transfer rate:          724.80 [Kbytes/sec] received

    Percentage of the requests served within a certain time (ms)
      50%      8
      66%     10
      75%     11
      80%     12
      90%     13
      95%     15
      98%     20
      99%     25
     100%     76 (longest request)
