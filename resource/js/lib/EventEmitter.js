function EventEmitter(){
	this.events = [];
};
EventEmitter.prototype = {
	once: function(id,fn){
		if (!this.events[id]) {
			this.events[id] = [];
		};
		this.events[id].push({
			remain:1,
			fn: fn
		});
	},
	on: function(id,fn){
		this.events[id].push({
			remain:Infinity,
			fn: fn
		});
	},
	emit: function(id,data){
		var fns = this.events[id];
		if (!fns) return;
		for (var i = 0; i < fns.length; i++) {
			var fn = fns[i];
			fn.fn(data);
			fn.remain--;
			if (fn.remain === 0) {
				this.events[id].splice(i,1);
				i--;
			};
		};
	}
};