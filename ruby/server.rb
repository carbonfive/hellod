require 'eventmachine'
require 'http/parser'

#GC.disable
class Server < EM::Connection

  def post_init
    @parser = Http::Parser.new
#    @parser.on_headers_complete = proc do
#    end
    @parser.on_message_complete = method(:get_slash)
  end

  def get_slash
    body = "<html><body><h1>Hello World</h1></body></html>\r\n"
    send_data "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\nContent-Length: #{body.size}\r\n\r\n"
    send_data body
    close_connection_after_writing
  end

  def unbind
  end

  def receive_data(data)
    @parser << data
  end
end

EM.run do
  Signal.trap("INT")  { EM.stop }
  Signal.trap("TERM") { EM.stop }

  EM.start_server("0.0.0.0", 8080, Server)
end
