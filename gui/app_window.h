#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <gtk-3.0/gtk/gtk.h>
#include "../util/fracao.h"

/**
 *Função para voltar a tela principal da
 *aplicação.
 */
void app_main();

/**
 *Callback executado quando a ApplicationWindow
 *é fechada.
 */
void on_app_window_destroy();

/**
 *Função para inicializar a aplicação.
 *
 *@param argc - usado pelo gtk
 *@param argv[] - usado pelo gtk
 */
void app_init(int argc, char *argv[]);

/**
 *Função para limpar o dash da aplicação
 *principal.
 */
void limparDash();

/**
 *Função para inicializar as variáveis dos
 *forms para executar as operações.
 */
void init_vars_oper();

/**
 *Função para inserir um formulário no dash.
 *
 *@param form - formulário a ser inserido.
 */
void inserir_form_dash(GtkWidget * form);

//### EVENTS ###//

void btn_soma_clicked();

void btn_transposta_clicked();

void btn_mult_clicked();

void btn_determinante_clicked();

void btn_inversa_clicked();

#endif
