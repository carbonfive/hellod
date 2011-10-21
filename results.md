HelloD
============

Performance results testing with ab.  All tests run on a EC2 High CPU Extra Large, 7GB RAM, 20 EC2 Compute Units (8 virtual cores).  I run two, increasingly rigorous tests.

    ab -n 10000 -c 50  http://localhost:808x/
    ab -n 50000 -c 200 http://localhost:808x/

The operating system:

	Ubuntu 10.04

The java version:

    java version "1.6.0_20"
	OpenJDK Runtime Environment (IcedTea6 1.9.9) (6b20-1.9.9-0ubuntu1~10.04.2)
	OpenJDK 64-Bit Server VM (build 19.0-b09, mixed mode)
	
	
For each test run, I execute ab six times.  The first time is to warm the server up, and the other five I record.
This functionality is built in to the hellod script (and hellod.rb) at the root of the repo.


Ruby 1.9.2
----------
ruby 1.9.2p290 (2011-07-09 revision 32553) c

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     4     4     4     4     7     7     7     8     8
	     4     4     4     4     7     7     8     8     9
	     4     4     4     4     7     7     8    10    10
	     4     4     4     6     7     8    10    11    13
	     4     4     4     4     7     7     7     8     8

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    10    11    11    11    12    13    14    15  3012
	    10    11    11    12    12    13    13    14  3011
	    11    11    12    12    12    13    13    14  3016
	    10    11    11    11    12    13    14    17  3015
	    10    11    11    11    12    12    13    15  3013


Ruby 1.9.3
----------
ruby 1.9.3dev (2011-09-23 revision 33323) c

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     4     4     4     4     4     4     4     4     5
	     4     4     4     4     4     4     4     4     5
	     4     4     4     4     4     4     7    10    12
	     4     4     4     4     4     4     4     5     5
	     4     4     4     4     4     4     5     5     5

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    15    16    16    16    16    16    17    17    19
	    16    16    16    16    16    17    17    17    18
	    15    16    16    16    16    16    16    16    19
	    16    16    16    16    16    16    17    17    18
	    15    16    16    16    16    16    16    17    34


JRuby 1.6.4
-----------
jruby 1.6.4 (ruby-1.8.7-p330) (2011-08-23 17ea768) (OpenJDK 64-Bit Server VM 1.6.0_20) c

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     6     6     7     7     8     8     9     9    45
	     6     6     6     6     6     6     7     7    50
	     6     6     6     6     6     6     7     8    46
	     5     6     6     6     6     6     6     6    41
	     6     6     6     6     7    10    11    15    54

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     9     9     9     9    10    10    10    20  4688
	     9     9     9     9    10    10    11    31  4687
	     9     9     9     9    10    10    11    35  4684
	     9     9     9     9    10    10    10    22  6606   (51 failures)
	     9     9     9     9     9    10    10    23  4688


go
-----
6g version release.r60.1 9497

	Testing go with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    12    12    13    13    13    14    14    15    20
	    12    13    13    14    14    15    16    16    18
	    12    12    12    13    13    14    16    16    18
	    12    13    13    13    14    15    15    15    16
	    12    12    13    13    14    15    16    16    17

	Testing go with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    30    32    32    33    35    37    38    39 11680
	    31    32    33    33    34    36    38    39 20641
	    31    32    32    33    34    34    35    36 11685
	    32    32    33    33    35    37    40    41 20641
	    30    32    33    34    36    37    40    42 11678


Node.js
-------
v0.4.12

	Testing node with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     7     9    10    11    12    12    20    23    27
	     7     9    10    10    12    12    19    22    27
	     7     9    10    11    12    12    20    22    27
	     7     9    10    10    12    12    19    22    26
	     7     9    10    10    11    12    19    22    26

	Testing node with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    20    24    27    28    31    36    43    47  3274
	    20    24    27    28    31    37    44    47  3309
	    20    24    27    28    31    36    42    46  3025
	    20    24    27    28    31    36    43    47  3021
	    20    24    27    28    31    37    43    46  3303


Clojure (with Aleph)
--------------------
Leiningen 1.6.1.1 on Java 1.6.0_20 OpenJDK 64-Bit Server VM

	Testing clj-aleph with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     8     9    10    10    11    11    12    13    47
	     9    10    10    11    11    11    12    43    52
	     9    10    11    11    11    11    12    43    47
	     8    11    12    12    13    13    14    52    59
	     8     9    10    10    11    12    13    13    47

	Testing clj-aleph with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     9    10    10    11    12    14    15    47  7212   (48 failures)
	     9    10    11    11    12    12    14    47  7213   (72 failures)
	     9    10    10    10    11    12    13    45  7211   (79 failures)
	    10    10    11    11    13    13    15    52 11084   (70 failures)
	     9    10    10    10    11    12    15    50  7211   (36 failures)


Clojure (with Jetty)
--------------------
Leiningen 1.6.1.1 on Java 1.6.0_20 OpenJDK 64-Bit Server VM

	Testing clj-jetty with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    11    11    11    11    12    12    12    12    12
	    11    11    11    11    12    12    13    13   121
	    11    11    11    11    11    11    12    12    14
	    11    11    11    11    11    12    12    12    12
	    10    10    11    11    11    11    12    12    12

	Testing clj-jetty with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    47    47    48    48    48    49    49    50   149
	    46    46    47    47    48    48    49    50   261
	    46    47    47    47    48    48    49    50   134
	    46    47    48    48    49    49    50    51  3048
	    35    46    46    47    47    48    48    49  3040


