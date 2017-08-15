# Escalonador de Processos - PP 2017-2
Primeiro trabalho da disciplina de práticas em programação da UNIPAMPA, consiste na implementação de 3 políticas de escalonamento de processos: FCFS, SJF e RR.
### Executando o programa

Para executar o programa, basta em um terminal digar o comando ./escalonador seguido dos parâmetros desejados. Os parâmetros existentes são:
* **-e** "arquivo_de_entrada", instrui o programa a ler os processos do arquivo de entrada entre aspas (remover aspas durante a execução).
* **-p** Política de escalonamento desejada, valores válidos: fcfs, sjf e rr.
* **-q** Para a política rr, pode ser especificado o quantum utilizado, caso não informado o valor padrão utilizado é = 2

Exemplo de execução

```
$ ./escalonador -e entrada.txt -p rr -q 4
```

Exemplo de execução

```
$ ./escalonador -e entrada.txt -p fcfs
```
### Visualizando a saída do programa

Para visualizar a saída do programa, o mesmo conta com dois logs, um arquivo de texto comum com os processos executados, e uma página HTML onde a execução do processo é exibida com maiores detalhes.
Os arquivos de saída ficam na pasta logs do projeto. Ao abrir um log no formato html, a saída esperada é semelhante a da imagem abaixo:
![alt text](https://github.com/wolganens/pp_etapa1/blob/master/arquivos_web/loghtml.jpg)

## Autores

* **Amanda Oliveira**
* **Fernando de Oliveira**
* **Paloma Ribeiro**
* **Willian Soares**
* **Wolgan Ens**
