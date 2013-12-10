#!/usr/bin/env node

//local
var http = require('http')
	,port = process.argv.slice(2)
	,fs = require('fs')
	,api = require('./config/api.json')
	,path = require('./config/path.json')
	,cluster = require('cluster')
	,numCPUs = require('os').cpus().length
	,windinsky = require('windinsky');
//global
Controller = require('controller');
debug = true;

windinsky.set('views', __dirname + '/views/');
windinsky.set('views options', path);
windinsky.set('controllers', __dirname + '/controllers/sale.com/');

windinsky.add('cookie');
windinsky.add('wants');

Controller.configure({
	api:api
	,global:path
});

fs.createWriteStream(__dirname+"/config/pids", {
	flags: "a+",
	encoding: "utf-8",
	mode: 0666
}).write(process.pid + "\n");

// if (cluster.isMaster) {
//   // Fork workers.
//   for (var i = 0; i < numCPUs; i++) {
//     cluster.fork();
//   }

//   cluster.on('exit', function(worker, code, signal) {
//     console.log('worker ' + worker.process.pid + ' died');
//   });
// } else {
//   // Workers can share any TCP connection
//   // In this case its a HTTP server
//   http.createServer(function(req, res) {
//     console.log(process.pid);
//     windinsky.process(req,res);
//   }).listen(port[0]);
// }
console.log(port[0]);
http.createServer(function(req, res) {
	console.log(process.pid);
	windinsky.process(req,res);
}).listen(port[0]);