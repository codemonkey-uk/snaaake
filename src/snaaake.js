
mergeInto(LibraryManager.library, {
	// extern "C" int GetLocalHighScore();
	GetLocalHighScore: function() {
		var result = 0;
		if (f = Module.getCookie("local_highscore")) result = f;
		return result;
	},

	// extern "C" void SetLocalHighScore(int d);
	SetLocalHighScore: function(d) {
		Module.setCookie("local_highscore", d, 30);
	}
});


