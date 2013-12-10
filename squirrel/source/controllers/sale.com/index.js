var http = require('http');

var fn = {
	'index': function(req,res){
		var interfaces = {
			'test': 'outlets::/test/'
		};
		// return res.render('index',{__title:'哈哈'});
		var date = new Date();
		this.send(interfaces);
		this.on('end',function(data){
			console.log(data.test.a);
			data.__title = 'Welly - index';
			data.__css = ['index'];
			date.setMinutes(date.getMinutes()+1);
			res.setHeader("Set-Cookie", ['a=000;domain=windinsky.com;path=/;Expires='+date.toGMTString(), 't=1111', 'w=2222']);
			res.render('index',data);
		});
	}
};

module.exports = Controller.create(fn);