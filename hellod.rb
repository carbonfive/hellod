require 'yaml'

class Hellod

  PORTS = { 'ruby' => 8080,
            'node' => 8081,
            'go' => 8082,
            'clj-aleph' => '8083',
            'clj-jetty' => '8084',
            'c' => '8085' }
  CMDS = { 'ruby' => 'ruby ruby/server.rb',
           'node' => 'node node/server.js',
           'go' => 'GOMAXPROCS=6; ./go/hellod',
           'clj-aleph' => 'cd clj-aleph; lein run',
           'clj-jetty' => 'cd clj-jetty; lein run',
           'c' => './c/hellod' }

  def initialize(opts = {})
    opts = { :requests => 10000, :concurrent => 50 }.merge(opts)
    @n = opts[:requests]
    @c = opts[:concurrent]
    @pids = {}
  end

  def start(flavor)
    read
    ports(flavor[0]).each do |f, p|
      print "Starting #{f} server on port #{p}..."
      if @pids[f]
        puts " already running with pid #{@pids[f]}"
      else
        begin
          pipe = IO.popen CMDS[f], 'r'
          puts " pid #{pipe.pid}"
          @pids[f] = pipe.pid
        rescue
          puts " failed"
        end
      end
    end
    write
  end

  def stop(flavor)
    read
    ports(flavor[0]).each do |f, p|
      pid = @pids[f]
      print "Stopping #{f} server with pid #{pid}..."
      if pid
        begin
          Process.kill 'HUP', pid
          Process.kill 'HUP', (pid + 2) if f =~ /^clj/  # crazy ass hack -mike
          puts " done"
        rescue
          puts " not running"
        end
        @pids.delete f
      else
        puts " not running"
      end
    end
    write
  end

  def test(flavor)
    read
    ports(flavor[0]).each do |f, p|
      puts "Testing #{f} with -n #{@n} -c #{@c}"
      if @pids[f]
        test_run p, true
        5.times { test_run p }
      else
        puts "Not started"
      end
      puts
    end
  end

  private

  def ports(flavor)
    if flavor == 'all'
      PORTS      
    else
      { flavor => PORTS[flavor] }
    end
  end

  def config_file
    "#{ENV['HOME']}/.hellod"
  end

  def write
    File.open config_file, 'w' do |f|
      f.write @pids.to_yaml    
    end
  end

  def read
    @pids = YAML.load( IO.read(config_file) ) if File.exists? config_file
    @pids = {} unless @pids
  end

  def test_run(port, header = false)
    h = header ? '1' : '2'
    IO.popen "ab -n #{@n} -c #{@c} http://localhost:#{port}/ 2>&1 | grep % | awk '{print $#{h}}' | xargs echo", 'r' do |io|
      io.readlines.each do |line|
        vals = line.split
        vals.each do |val|
          print sprintf("%5s", val)
        end
        puts
      end
    end
  end

end
