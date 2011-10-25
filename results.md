HelloD
============

Performance results testing with ab.  All tests run on a EC2 High CPU Extra Large, 7GB RAM, 20 EC2 Compute Units (8 virtual cores).

Before each test, I start the server and I give it 5 seconds to start up.  I think "warm it up" by running 10 runs of ab.  Then I run the following tests with ab, and I collect the results.

    ab -n 10000 -c 50  http://localhost:808x/
    ab -n 50000 -c 200 http://localhost:808x/


Ruby 1.9.2
-------------
	ruby -v
	ruby 1.9.2p290 (2011-07-09 revision 32553) [x86_64-linux]

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     4     4     5     7     7     8     9    11    14
	     4     4     4     4     7     7     8     8     8
	     4     4     4     4     7     7     8     8     8
	     4     4     4     4     8     8     9     9    10
	     4     4     4     4     7     7     8     8     8

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    11    11    11    11    12    12    13    15  3015
	    10    11    11    11    12    12    13    14  3011
	    10    11    11    11    12    12    13    13  3756
	    10    11    11    11    11    12    12    13  3295
	    11    11    11    12    12    12    13    14  3012


Ruby 1.9.3
-------------
	ruby -v
	ruby 1.9.3dev (2011-09-23 revision 33323) [x86_64-linux]

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     4     4     4     4     4     4     4     4     5
	     4     4     4     4     4     4     4     4     5
	     4     4     4     4     4     4     4     5     5
	     4     4     4     4     4     4     4     4     5
	     4     4     4     4     4     4     4     5     6

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    14    14    14    15    15    15    15    15  3014
	    14    15    15    15    15    15    15    15    18
	    14    14    14    14    15    15    15    15  3014
	    14    14    15    15    15    15    15    15    18
	    14    15    15    15    15    15    15    15    18


JRuby 1.6.4 - Sun JDK
-------------
	ruby -v
	jruby 1.6.4 (ruby-1.8.7-p330) (2011-08-23 17ea768) (Java HotSpot(TM) 64-Bit Server VM 1.6.0_26) [linux-amd64-java]

	java -version
	java version "1.6.0_26"
	Java(TM) SE Runtime Environment (build 1.6.0_26-b03)
	Java HotSpot(TM) 64-Bit Server VM (build 20.1-b02, mixed mode)

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     6     6     6     6     6     6     9     9    42
	     6     6     6     6     6     6     7    13    42
	     6     6     6     6     6     6     8    14    44
	     6     6     6     6     6     6     6     7     7
	     6     6     6     6     6     6     7    14    56

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    10    10    10    10    11    11    12    20  3721
	    10    10    10    10    11    11    12    36  6595   (9 failures)
	    10    10    10    10    11    11    12    28  6598   (45 failures)
	    10    10    10    10    11    11    11    21  6598   (49 failures)
	    10    10    10    10    11    11    11    39  6596   (54 failures)


JRuby 1.6.4 - OpenJDK
-------------
	ruby -v
	jruby 1.6.4 (ruby-1.8.7-p330) (2011-08-23 17ea768) (OpenJDK 64-Bit Server VM 1.6.0_20) [linux-amd64-java]

	java -version
	java version "1.6.0_20"
	OpenJDK Runtime Environment (IcedTea6 1.9.9) (6b20-1.9.9-0ubuntu1~10.04.2)
	OpenJDK 64-Bit Server VM (build 19.0-b09, mixed mode)

	Testing ruby with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     6     6     6     6     6     6     6     7    54
	     6     6     6     6     6     6     7    14    49
	     6     6     6     6     6     6     6     6     7
	     6     6     6     6     6     6     6     6    37
	     6     6     6     6     6     6     6     7    52

	Testing ruby with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     9     9    10    10    10    10    13    27  6225
	     9     9    10    10    10    10    10    19  6595
	     9     9     9    10    10    10    20    22  6598   (49 failures)
	     9     9    10    10    10    10    11    22  4689
	     9     9    10    10    10    10    11    21  4688


Go
-------------
	6g -V
	6g version release.r60.1 9497

	Testing go with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    12    12    12    12    14    16    17    17    18
	    12    12    12    12    13    14    17    17    18
	    12    12    12    12    12    12    15    16    17
	    11    12    12    12    12    12    16    17    18
	    11    12    12    12    12    12    12    12    13

	Testing go with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    30    31    31    31    33    38    44    45 11682
	    29    30    30    31    31    32    40    43 11688
	    29    30    31    31    33    41    44    45 11706
	    30    31    31    31    35    42    44    45 11680
	    29    30    31    31    33    41    44    45 11684


Node.js
-------------
	node -v
	v0.4.12

	Testing node with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     8    10    11    12    13    14    20    22    26
	     8    10    11    12    13    14    20    22    27
	     8    11    12    12    14    15    23    26    30
	     8    10    12    12    14    14    21    24    30
	     8    10    12    12    14    15    21    24    30

	Testing node with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    23    28    31    33    37    42    49    53  3270
	    23    28    31    33    36    40    48    51  3037
	    23    28    31    33    37    42    49    52  3050
	    23    29    32    34    37    43    50    54  9021
	    23    28    31    33    37    42    49    52  3038


C / libev
-------------
	

	Testing c with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     4     4     4     4     4     4     5     5     5
	     4     4     4     4     4     4     4     5     5
	     4     4     4     4     4     5     5     5     5
	     4     4     4     4     4     5     5     5     5
	     4     4     4     4     4     5     5     5     5

	Testing c with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    16    17    17    17    18    18    19    19    21
	    16    17    17    17    17    18    18    19    21
	    16    16    17    17    18    18    18    19    22
	    17    17    17    17    18    18    19    19    21
	    17    17    17    17    18    18    19    19    20


Clojure / Aleph - Sun JDK
-------------
	lein version
	Leiningen 1.6.1.1 on Java 1.6.0_26 Java HotSpot(TM) 64-Bit Server VM

	java -version
	java version "1.6.0_26"
	Java(TM) SE Runtime Environment (build 1.6.0_26-b03)
	Java HotSpot(TM) 64-Bit Server VM (build 20.1-b02, mixed mode)

	Testing clj-aleph with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     9    10    10    10    11    12    14    39    77
	     9    10    10    11    12    15    15    16    47
	     9    10    10    11    12    12    13    39    50
	     9    10    10    11    12    12    14    43    70
	     9    10    10    10    10    11    11    11    46

	Testing clj-aleph with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     9     9    10    10    12    12    14    45  7213
	     9     9    10    10    12    12    14    42  7805   (99 failures)
	     9    10    11    12    13    14    16    45  7207   (69 failures)
	    10    10    11    12    12    13    19    52  7504   (46 failures)
	     9    10    11    11    12    14    16    53 11076   (46 failures)


Clojure / Aleph - OpenJDK
-------------
	lein version
	Leiningen 1.6.1.1 on Java 1.6.0_20 OpenJDK 64-Bit Server VM

	java -version
	java version "1.6.0_20"
	OpenJDK Runtime Environment (IcedTea6 1.9.9) (6b20-1.9.9-0ubuntu1~10.04.2)
	OpenJDK 64-Bit Server VM (build 19.0-b09, mixed mode)

	Testing clj-aleph with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    10    11    11    12    12    12    13    42    50
	     9    10    10    10    11    11    13    14    48
	     9    10    11    11    12    13    14    41    71
	     9     9    10    10    12    12    13    44    49
	     8    10    11    11    12    12    13    47    67

	Testing clj-aleph with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	     9     9    10    10    11    12    19    47  7767   (76 failures)
	     9    10    10    11    11    12    14    44 11677   (40 failures)
	     9    10    10    11    12    12    14    47  7209   (67 failures)
	     9    10    10    11    12    13    16    47  9837   (51 failures)
	    10    10    11    11    12    12    26    53  8608   (67 failures)


Clojure / Ring - Sun JDK
-------------
	lein version
	Leiningen 1.6.1.1 on Java 1.6.0_26 Java HotSpot(TM) 64-Bit Server VM

	java -version
	java version "1.6.0_26"
	Java(TM) SE Runtime Environment (build 1.6.0_26-b03)
	Java HotSpot(TM) 64-Bit Server VM (build 20.1-b02, mixed mode)

	Testing clj-jetty with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    14    14    14    14    14    14    15    17    25
	    14    14    14    14    14    14    15    15    36
	    14    14    14    14    14    14    15    15    28
	    14    14    14    14    14    15    15    17    29
	    14    14    14    14    14    14    15    15    35

	Testing clj-jetty with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    27    30    32    41    59    61    62    64  3051
	    39    53    56    57    59    61    63    63  3058
	    45    56    58    58    59    60    62    65  3063
	    34    40    43    47    52    59    62    63  3053
	    35    52    53    55    60    61    62    64  3063


Clojure / Ring - OpenJDK
-------------
	lein version
	Leiningen 1.6.1.1 on Java 1.6.0_20 OpenJDK 64-Bit Server VM

	java -version
	java version "1.6.0_20"
	OpenJDK Runtime Environment (IcedTea6 1.9.9) (6b20-1.9.9-0ubuntu1~10.04.2)
	OpenJDK 64-Bit Server VM (build 19.0-b09, mixed mode)

	Testing clj-jetty with -n 10000 -c 50
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    14    14    14    14    14    14    15    15    39
	    13    14    14    14    14    14    15    15    35
	    14    14    14    14    14    15    15    16    29
	    14    14    14    14    14    14    15    15    34
	    14    14    14    14    14    14    15    15    34

	Testing clj-jetty with -n 50000 -c 200
	   50%   66%   75%   80%   90%   95%   98%   99%  100%
	    41    49    51    52    60    62    63    63  3051
	    41    46    49    49    51    58    60    62  3054
	    35    40    46    57    60    62    63    63  3058
	    26    35    54    57    60    61    62    66  3059
	    34    39    43    46    55    58    62    63  3041


