windinsky.define('index',['jquery','utils/render'],function(require,exports){
	var $ = require('jquery');
	var render = require('utils/render');
	$('body').append(render('test_render',{
		hengheng:'hengheng',
		h:false,
		a:'a',
		b:'b'
	}));
});