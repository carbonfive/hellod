require 'yaml'

class Hellod

  PORTS = { 'ruby' => 8080, 'node' => 8081, 'go' => 8082 }
  CMDS = { 'ruby' => 'ruby ruby/server.rb',
           'node' => 'node node/server.js',
           'go' => './go/hellod' }

  def initialize(opts = {})
    opts = { :n => 10000, :c => 100 }.merge(opts)
    @n = opts[:n]
    @c = opts[:c]
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
    @pids = YAML.load( IO.read(config_file) )
  end

end
