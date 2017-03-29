#ifndef OPERACAO_SOMA_H
#define OPERACAO_SOMA_H

#include <gtk-3.0/gtk/gtk.h>

#include "../util/matriz.h"
#include "../util/operacoes_matriz.h"

/**
 * função para pegar o frame que contém o formulário
 * para realizar a soma de duas matrizes.
 *
 * @return GtkWidget
 */
GtkWidget * get_frame_oper_somar();

/**
 * Função para setar uma função para voltar à aplicaçao/tela
 * principal.
 *
 * @param app_voltar - pointeiro para uma função.
 */
void oper_soma_app_principal(void (*app_voltar)(void));

/**
 * Desaloca memória usada para criar o formulário.
 */
void unref_oper_soma_frm();

//#### EVENTS ###//


/**
 * Evento do botão voltar.
 */
void arrow_voltar_button_release();

void btn_matriz_A_button_release_even();

void btn_matriz_B_button_release_even();

//### FUNÇÕES AUXILIARES ###//

void set_matriz_A(Matriz * m);

void set_matriz_B(Matriz * m);

void btn_limpar_button_release_event();

void exibir_matriz(int dash_col, int dash_row, Matriz * m);

void exibir_resultado();

void dim_limpar_dash_matriz();

#endif
