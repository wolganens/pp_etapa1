var processos = $("#processos").text().split(" ");
processos = processos.filter(v=>v!='');

var escalonador = {	
	ciclos:[],
	proc:[],
	colors: [],
	ciclo_atual: 0,
	setColors: function(){
		var i;		
		for (i = 0 ; i < escalonador.proc.length ; i++){
			escalonador.colors.push(randomColor({luminosity: 'light'}));
		}		
	},
	setProcessos: function(){
		var i;
		for (i = 0 ; i < processos.length; i++){
			var regex_processo = /[A-Z]/;
			var regex_ciclo = /\d/;
			escalonador.ciclos.push(
				processos[i]
			);
			var label = processos[i].match(regex_processo)[0];
			if (escalonador.proc.indexOf(label) == -1) {
				escalonador.proc.push(label);
			}
		}
	},
	divs:[],
	setDivs: function(){
		var i;
		var regex_processo = /[A-Z]/;
		for(i = 0 ; i < escalonador.ciclos.length; i++){
			escalonador.divs.push(
				'<div class="ciclo hidden col-xs-2 col-lg-1" style="font-weight:bold;font-size:22px;border:1px solid black;background:' + escalonador.colors[escalonador.proc.indexOf(escalonador.ciclos[i].match(regex_processo)[0])] + '">'+ escalonador.ciclos[i] +'</div>'
			);
		}		
		for(i = 0 ; i < escalonador.divs.length; i++) {
			$(".row").append(escalonador.divs[i]);
		}
	},
	exibe_ciclo_atual(){
		
		$(".ciclo").hide();
		$(".ciclo").addClass('hidden');
		if (escalonador.ciclo_atual == 0) {
			$($('.ciclo')[0]).removeClass('hidden').show('fast');
		} else {
			for (i = 0; i <= escalonador.ciclo_atual ; i++){
				console.log($($('.ciclo')[i]));
				$($('.ciclo')[i]).removeClass('hidden').show('fast');
			}
		}		
	},
	eventos(){
		$("#avanca").click(function(event) {
			escalonador.ciclo_atual++;
		});
		$("#volta").click(function(event) {
			if(escalonador.ciclo_atual>0){
				escalonador.ciclo_atual--;
			}
		});
		$("#reseta").click(function(event) {
			escalonador.ciclo_atual = 0;
		});
		$("#final").click(function(event) {
			escalonador.ciclo_atual = escalonador.ciclos.length -1;
		});
		$(".btn-default").click(function(event) {
			if($(this).is('#avanca')){
				if(escalonador.ciclo_atual == escalonador.ciclos.length) {
					alert("Execução finalizada!");
					return;
				}
			}
			escalonador.exibe_ciclo_atual();
		});
	}
}
escalonador.setProcessos();
escalonador.setColors();
escalonador.setDivs();
escalonador.eventos();
escalonador.exibe_ciclo_atual();