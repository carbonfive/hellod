HelloD
============

Performance results testing with ab.  All tests run on a EC2 High CPU Extra Large, 7GB RAM, 20 EC2 Compute Units (8 virtual cores)

    ab -n 10000 -c 50 http://localhost:8080/

The operating system:

	Ubuntu 10.04

The java version:

    java version "1.6.0_20"
	OpenJDK Runtime Environment (IcedTea6 1.9.9) (6b20-1.9.9-0ubuntu1~10.04.2)
	OpenJDK 64-Bit Server VM (build 19.0-b09, mixed mode)
	
	
For each test run, I execute ab six times.  The first time is to warm the server up, and the other five I record.
This functionality is built in to the hellod script (and hellod.rb) at the root of the repo.


Ruby 1.9.2p290
---------------

	Testing ruby with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
    	4    4    4    4    7    7    8    8    9
    	4    4    4    4    7    8    8    8    8
    	4    4    4    4    7    8    8    8   10
    	4    4    4    4    7    8    8    9   64
    	4    4    4    4    8    8    9    9   10


Ruby 1.9.3-rc1
----------------

	Testing ruby with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
    	4    4    4    4    4    4    4    4    5
    	4    4    4    4    4    4    4    4    4
    	4    4    4    4    4    4    4    5    5
    	4    4    4    4    4    4    4    4    4
    	4    4    4    4    4    4    4    4    5


JRuby 1.6.4-1.9
----------------

	Testing ruby with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
    	6    7    8    8    9   10   11   11   60
    	6    6    7    7    7    7    7    7   36
    	6    6    6    6    7    7    7    7   46
    	6    6    6    6    6    6    7    8   31
    	6    6    6    6    6    7    7    8   27


Go 60.1 9497
----------------

	Testing go with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
	   11   12   12   12   12   12   13   15   18
	   11   12   12   12   12   12   13   13   14
	   11   12   12   12   12   13   16   17   18
	   12   12   12   13   16   17   18   18   18
	   11   12   12   12   12   12   13   13   18


Node.js 0.4.12
------------------

	Testing node with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
    	8   10   11   12   13   14   21   24   29
    	8   10   12   12   14   14   22   24   30
    	8   10   12   12   14   14   22   25   31
    	8   10   12   12   14   14   21   24   30
    	8   10   11   12   13   14   20   23   27

Clojure 1.2.1 with Aleph
----------------

	Testing clj-aleph with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
	   12   12   12   12   13   14   19   37   52
	   11   12   12   12   12   13   14   36   44
	   10   10   11   12   13   14   14   14   75
	   10   10   11   11   12   12   13   40   82
	   10   10   11   11   12   12   13   36   55


Clojure 1.2.1 with Jetty + Ring
--------------------------------

	Testing clj-jetty with -n 10000 -c 50
  	  50%  66%  75%  80%  90%  95%  98%  99% 100%
	   14   14   14   14   14   14   15   15   40
	   14   14   14   14   14   14   14   15   15
	   13   14   14   14   14   14   14   14   41
	   14   14   14   14   14   14   15   15   41
	   13   14   14   14   14   14   14   15   38
