#ifndef OPERACAO_TRANSPOSTA_H
#define OPERACAO_TRANSPOSTA_H

#include <gtk-3.0/gtk/gtk.h>

#include "../util/matriz.h"
#include "../util/operacoes_matriz.h"

/**
 * função para pegar o frame que contém o formulário
 * para realizar a transposição de uma matriz.
 *
 * @return GtkWidget
 */
GtkWidget * get_frame_oper_transposicao();

/**
 * Função para setar uma função para voltar à aplicaçao/tela
 * principal.
 *
 * @param app_voltar - pointeiro para uma função.
 */
void oper_transposicao_app_principal(void (*app_voltar)(void));

/**
 * Desaloca memória usada para criar o formulário.
 */
void unref_oper_transposicao_frm();


//#### EVENTOS ###//

void opt_btn_matriz_A_button_release_even();

void opt_btn_limpar_button_release_event();

void arrow_voltar_trans_button_release();

//### FUNÇÕES AUXILIARES ###

void opt_set_matriz_A(Matriz * m);

void opt_exibir_matriz(int dash_col, int dash_row, Matriz * m);

void opt_exibir_resultado();

void opt_limpar_dash_matriz();

#endif
