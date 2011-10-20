var http = require('http');
http.createServer(function (req, res) {
  var content = '<html><body><h1>Hello World</h1></body></html>\r\n';
  res.writeHead(200, {'Connection' : 'close', 'Content-Type': 'text/html', 'Content-Length' : content.length.toString() });
  res.end(content);
}).listen(8081);
