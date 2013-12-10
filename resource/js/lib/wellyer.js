!function(w){
	
	var cache = {};
	var loadingModules = [];
	function Module(id){
		EventEmitter.call(this);
		this.id = id;
		this._ready = false;
	}
	Module.prototype.isDepend = function(id){
		return this.dependents.indexOf(id) !== -1;
	};
	Module.prototype.ready = function(){
		this._ready = true;
		console.log(this.id,'ready');
		this.emit('ready');
	}
	Module.prototype.undepend = function(id){
		var index = this.dependents.indexOf(id);
		if (index === -1) return;
		this.dependents.splice(index,1);
		if (this.dependents.length === 0) {
			this.emit('ready');
		};
	};
	for(var i in EventEmitter.prototype){
		if (typeof EventEmitter.prototype[i] === 'function') {
			Module.prototype[i] = EventEmitter.prototype[i];
		};
	};
	
	w.windinsky = {
		use: function(modules,fn){
			if (!modules) return;
			if (typeof modules === 'string') modules = [modules];
			if (modules.constructor !== Array) return ;
			windinsky.load(modules,fn);
		},
		define: function(id,dependents,fn){
			var _module = {
				exports:{}
			};
			if (cache[id]) {
				return ;
			};
			if (dependents.length === 0) {
				fn(windinsky.require,_module.exports,_module);
				cache[id] = _module.exports;
				windinsky.onload(id);
				return windinsky.onload(id);
			};
			var module = new Module(id);
			module.once('ready',function(){
				fn(windinsky.require,_module.exports,_module);
				cache[id] = _module.exports;
				windinsky.onload(id);
			});
			loadingModules.push([module,dependents]);
			windinsky.load(dependents);
		},
		_load: function(id,fn){
			var s = document.createElement('script'),
			head = document.head  || document.getElementsByTagName('head')[0] || document.documentElement;
			s.async = 'async';
			s.defer = 'defer';
			if (fn) {
				s.onerror = s.onload = s.onreadystatechange = function(){
					var state = s.readyState;
					if (!state || 'loaded' == state || 'complete' == state) {
						s.onerror = s.onload = s.onreadystatechange = null;
	                    head.removeChild(s);
	                }
				};
			};
			
			head.appendChild(s);
			s.src = windinsky.cfg.JS_PATH + id +'.js';
		},
		load: function(modules,fn){
			for (var i = 0; i < modules.length; i++) {
				var id = modules[i];
				if (cache[id]) {
					windinsky.onload(id);
					continue;
				}
				windinsky._load(id);
			};
		},
		require: function(id){
			return cache[id];
		},
		ready: function(id){
			windinsky.onReady(id);
		},
		onload: function(id){
			for (var i = 0; i < loadingModules.length; i++) {
				var module = loadingModules[i][0],
					dependents = loadingModules[i][1]
					index = dependents.indexOf(id);
				if(index === -1) continue;
				dependents.splice(index,1);
				if (dependents.length === 0) {
					loadingModules.splice(i,1);
					i--;
					module.emit('ready');
				};
			};
		}
	}
}(window);