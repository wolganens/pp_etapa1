#include "logs.h"

FILE* log_texto;
FILE* log_html;
char _politica[50];

char* gera_nome_arquivo() {
	char buff[50], pasta_logs[80];
    struct tm *sTm;
    time_t now = time (0);    
    sTm = gmtime (&now);
	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
	strcpy(pasta_logs, "./logs/");
    return strcat(pasta_logs, buff);
}

void inicializa_logs(char *politica){
    char timestamp[150];
    strcpy(_politica,politica);
    strcpy(timestamp, gera_nome_arquivo());
    abre_log_texto(timestamp);
    abre_log_html(timestamp);
}
void abre_log_texto(char* timestamp){    
    char* arquivo = malloc(150*sizeof(char));
    strcpy(arquivo, timestamp);
    strcat(arquivo, ".log");
    log_texto = fopen(arquivo, "a+");
}
void abre_log_html(char* timestamp){    
    char* arquivo = malloc(1 + strlen(timestamp));    
    strcpy(arquivo, strcat(timestamp, ".html"));
    log_html = fopen(arquivo, "a+");
    fprintf(log_html, "<!DOCTYPE html>\n<html lang=\"\">\n   <head>\n        <meta charset=\"utf-8\">\n      <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n     <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n      <title>Escalonador de Processos - Relatório</title>\n\n\t<!-- Bootstrap CSS -->\n    <link rel=\"stylesheet\" href=\"../arquivos_web/bootstrap.min.css\">\n\n        <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->\n        <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n        <!--[if lt IE 9]>\n         <script src=\"https://oss.maxcdn.com/libs/html5shiv/3.7.2/html5shiv.min.js\"></script>\n            <script src=\"https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js\"></script>\n     <![endif]-->\n  </head>\n   <body><span style=\"display:none;\" id=\"politica\">%s</span><h1 class=\"page-header\">Escalonador de processos</h1><div id=\"processos\" style=\"display:none;\">", _politica);
}

void finaliza_logs(){
    fclose(log_texto);
    fprintf(log_html, "</div><div class=\"btn-group\">\n\t<button id=\"final\" class=\"btn btn-default\">Final</button><button id=\"reseta\" class=\"btn btn-default\">Reiniciar</button>\n\t<button id=\"avanca\" class=\"btn btn-default\">Avançar</button>\n\t<button id=\"volta\" class=\"btn btn-default\">Retroceder</button>\n</div><div id=\"execucao\" class=\"text-center\"></div><!-- jQuery -->\n        <script src=\"../arquivos_web/jquery.min.js\"></script>\n     <!-- Bootstrap JavaScript -->\n     <script src=\"../arquivos_web/bootstrap.min.js\"></script>\n     <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->\n <script src=\"../node_modules/randomcolor/randomColor.js\"></script><script src=\"../arquivos_web/script.js\"></script>\n </body>\n</html>");
    fclose(log_html);
}
void salva_log_execucao(proc* processo){
    if(processo->id == '-') {
        fprintf(log_texto, "%c ", processo->id);
        fprintf(log_html, "%c ", processo->id);
    } else {
        fprintf(log_texto, "%c%d ", processo->id, processo->ciclos);
        fprintf(log_html, "%c%d ", processo->id, processo->ciclos);
    }
}