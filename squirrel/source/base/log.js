module.exports = function(){
	var arr = [];
	Array.prototype.push.apply(arr,arguments);
	arr.push(new Date());
	console.log(arr.join('  |  '));
}