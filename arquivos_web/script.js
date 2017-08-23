var escalonador = {
	processos: {'-': {
		cor: 'rgba(218, 223, 225)',
		duracao: 1
	}},
	execucao:[],
	divs:[],
	ciclo_atual: 0,
	setProcessos: function (){
		this.execucao = processos = document.getElementById('processos').textContent.split(" ").filter(v=>v!='');
		var i, n, digit = /\d/g, letter = /\d+/, proccesso, id, index;
		for (i = 0, n = processos.length ; i < n ; i++) {
			id = processos[i].match(letter);
			if (!this.processos.hasOwnProperty(id)){
				this.processos[id] = {duracao: 1, cor: randomColor({luminosity: 'light', seed: (i % new Date().getTime())})}
			} else {
				this.processos[id].duracao++;
			}
		}
	},
	setDivs(){
		var i,n, digit = /\d/g, letter = /\d+/, div, div_ciclo, div_exec;
		for ( i = 0, n = this.execucao.length ; i < n ; i++){
			div = document.createElement('div');			
			div.style.background = this.processos[this.execucao[i].match(letter)].cor;
			div.style.display = 'none';			
			div.classList.add('ciclo');
			div.classList.add('col-xs-2', 'col-lg-1');
			div_exec = document.createElement('div');
			div_exec.textContent = this.execucao[i];
			div.appendChild(div_exec);
			div_ciclo = document.createElement('div');
			div_ciclo.textContent = i;
			div_ciclo.style.fontSize = '10px';			
			div_ciclo.style.background = 'white';
			div.appendChild(div_ciclo);
			document.getElementById('execucao').appendChild(div);
			this.divs.push(div);
		}
	},
	exibe_ciclo_atual: function(){		
		if (this.ciclo_atual == 0) {
			this.processos[this.execucao[this.ciclo_atual].match(/\d|\-/g)[0]].duracao--;
		}
		for (i = 0, n = this.divs.length ; i < n ; i++) {
			if (i <= escalonador.ciclo_atual) {
				this.divs[i].style.display = 'block';
			} else {
				this.divs[i].style.display = 'none';
			}
		}
	},
	events: function() {
		var buttons = document.getElementsByClassName('btn-default'),i, _this = this;
		document.getElementById('avanca').addEventListener('click', function(){
			if (_this.ciclo_atual < _this.execucao.length - 1){
				_this.ciclo_atual++;
				_this.processos[_this.execucao[_this.ciclo_atual].match(/\d|\-/g)[0]].duracao--;
			}
		});
		document.getElementById('volta').addEventListener('click', function(){
			if(_this.ciclo_atual > 0) {
				_this.processos[_this.execucao[_this.ciclo_atual].match(/\d|\-/g)[0]].duracao++;
				_this.ciclo_atual--;
			}
		});
		document.getElementById('final').addEventListener('click', function(){
			_this.ciclo_atual = _this.execucao.length - 1;
		});
		document.getElementById('reseta').addEventListener('click', function(){
			_this.ciclo_atual = 0;
		});
		for ( i = 0 ; i < buttons.length ; i++) {
			buttons[i].addEventListener('click', function(){
				_this.exibe_ciclo_atual();
			})
		}
	},
	init: function(){
		this.setProcessos();
		this.setDivs();
		this.exibe_ciclo_atual();
		this.events();
	}
}
escalonador.init();
// var escalonador = {	
// 	ciclos:[],
// 	proc:[],
// 	colors: [],
// 	ciclo_atual: 0,
// 	setColors: function(){
// 		var i;		
// 		for (i = 0 ; i < escalonador.proc.length ; i++){
// 			escalonador.colors.push(randomColor({luminosity: 'light'}));
// 		}		
// 	},
// 	setProcessos: function(){
// 		var i;
// 		for (i = 0 ; i < processos.length; i++){
// 			var regex_processo = /[A-Z]|\-/;
// 			var regex_ciclo = /\d/;
// 			escalonador.ciclos.push(
// 				processos[i]
// 			);
// 			var label = processos[i].match(regex_processo)[0];
// 			if (escalonador.proc.indexOf(label) == -1) {
// 				escalonador.proc.push(label);
// 			}
// 		}
// 	},
// 	divs:[],
// 	setDivs: function(){
// 		var i;
// 		var regex_processo = /[A-Z]|\-/;
// 		for(i = 0 ; i < escalonador.ciclos.length; i++){
// 			escalonador.divs.push(
// 				'<div class="ciclo hidden col-xs-2 col-lg-1" style="background:' + escalonador.colors[escalonador.proc.indexOf(escalonador.ciclos[i].match(regex_processo)[0])] + '">'+ escalonador.ciclos[i] +'</div>'
// 			);
// 		}		
// 		for(i = 0 ; i < escalonador.divs.length; i++) {
// 			$(".row").append(escalonador.divs[i]);
// 		}
// 	},
// 	exibe_ciclo_atual(){		
// 		$(".ciclo").each(function(index, el) {
// 			console.log($(this));
// 			if(index > escalonador.ciclo_atual) {
// 				$(this).hide('fast');
// 			} else {
// 				$(this).removeClass('hidden').show('fast');
// 			}
// 		});
// 	},
// 	eventos(){
// 		$("#avanca").click(function(event) {
// 			escalonador.ciclo_atual++;
// 		});
// 		$("#volta").click(function(event) {
// 			if(escalonador.ciclo_atual>0){
// 				escalonador.ciclo_atual--;
// 			}
// 		});
// 		$("#reseta").click(function(event) {
// 			escalonador.ciclo_atual = 0;
// 		});
// 		$("#final").click(function(event) {
// 			escalonador.ciclo_atual = escalonador.ciclos.length -1;
// 		});
// 		$(".btn-default").click(function(event) {
// 			if($(this).is('#avanca')){
// 				if(escalonador.ciclo_atual == escalonador.ciclos.length) {
// 					alert("Execução finalizada!");
// 					return;
// 				}
// 			}
// 			escalonador.exibe_ciclo_atual();
// 		});
// 	}
// }
// escalonador.setProcessos();
// escalonador.setColors();
// escalonador.setDivs();
// escalonador.eventos();
// escalonador.exibe_ciclo_atual();