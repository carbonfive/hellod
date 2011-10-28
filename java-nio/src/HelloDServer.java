import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.util.Iterator;
import java.util.Set;

public class HelloDServer {
    private static int port = 8086;
    private static final String BODY_TEXT  =  "<html><body><h1>Hello World</h1></body></html>\r\n";
    private static final String HEADER_TEXT = String.format("HTTP/1.1 200 OKContent-Type: text/html\r\nContent-Length: %1$d\r\n\r\n", BODY_TEXT.getBytes().length);


    public static void main(String args[]) throws Exception {
        Selector selector = Selector.open();

        ServerSocketChannel channel = ServerSocketChannel.open();
        channel.configureBlocking(false);

        InetSocketAddress isa = new InetSocketAddress(port);
        channel.socket().bind(isa);

        // Register interest in connections
        channel.register(selector, SelectionKey.OP_ACCEPT);

        // Wait for something to happen
        while (selector.select() > 0) {
            //Get set of ready objects
            Set<SelectionKey> readyKeys = selector.selectedKeys();
            Iterator<SelectionKey> readyIterator = readyKeys.iterator();

            // Walk through set
            while(readyIterator.hasNext()) {

                // Get key from set
                SelectionKey key = readyIterator.next();

                // Remove current entry
                readyIterator.remove();

                if (key.isAcceptable()) {
                    //Get channel
                    ServerSocketChannel keyChannel = (ServerSocketChannel) key.channel();

                    // Get server socket
                    ServerSocket serverSocket = keyChannel.socket();

                    // Accept request
                    Socket socket = serverSocket.accept();

                    // Return canned message
                    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    out.print(HEADER_TEXT);
                    out.print(BODY_TEXT);
                    out.close();
                } else {
                    System.err.println("Oops");
                }
            }
        }
    }


}
