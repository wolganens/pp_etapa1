#include "logs.h"

FILE* log_texto;
FILE* log_html;

char* gera_nome_arquivo() {
	char buff[50], pasta_logs[80];
    struct tm *sTm;
    time_t now = time (0);    
    sTm = gmtime (&now);
	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
	strcpy(pasta_logs, "./logs/");
    return strcat(pasta_logs, buff);
}

void inicializa_logs(){
    char timestamp[150];
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
    fprintf(log_html, "<!DOCTYPE html>\n<html lang=\"\">\n   <head>\n        <meta charset=\"utf-8\">\n      <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n     <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n      <title>Title Page</title>\n\n       <!-- Bootstrap CSS -->\n        <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\" integrity=\"sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7\" crossorigin=\"anonymous\">\n\n        <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->\n        <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n        <!--[if lt IE 9]>\n         <script src=\"https://oss.maxcdn.com/libs/html5shiv/3.7.2/html5shiv.min.js\"></script>\n            <script src=\"https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js\"></script>\n     <![endif]-->\n  </head>\n   <body><div id=\"processos\" style=\"display:none;\">");
}

void finaliza_logs(){
    fclose(log_texto);
    fprintf(log_html, "</div> <!-- jQuery -->\n        <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/2.2.4/jquery.min.js\"></script>\n     <!-- Bootstrap JavaScript -->\n     <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js\" integrity=\"sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS\" crossorigin=\"anonymous\"></script>\n     <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->\n         <script src=\"../script.js\"></script>\n </body>\n</html>");
    fclose(log_html);
}
void salva_log_execucao(proc* processo){
    fprintf(log_texto, "%c%d ", processo->id, processo->ciclos);
    fprintf(log_html, "%c%d ", processo->id, processo->ciclos);
}