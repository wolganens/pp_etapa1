var processos = $("#processos").text().split(" ");
processos = processos.filter(v=>v!='');
console.log(processos);

var escalonador = {
	ciclos: processos.length,
	processos: [],
	setProcessos: function(){
		var i;
		for (i = 0 ; i < processos.length; i++){
			var regex = /[A-Z]/;			
			console.log(arr.match(regex)[0]);			
		}
	}
}