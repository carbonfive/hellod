var http = require('http');
http.createServer(function (req, res) {
  //console.log( JSON.stringify( req.headers ) );
  var content = '<html><body><h1>Hello World</h1></body></html>';
  res.writeHead(200, {'Content-Type': 'text/html', 'Content-Length' : content.length.toString() });
  res.end(content);
}).listen(8081);
