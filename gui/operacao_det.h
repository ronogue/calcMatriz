#ifndef OPERACAO_DETERMINANTE_H
#define OPERACAO_DETERMINANTE_H

#include <gtk-3.0/gtk/gtk.h>

#include "../util/matriz.h"
#include "../util/operacoes_matriz.h"

/**
 * função para pegar o frame que contém o formulário
 * para realizar a transposição de uma matriz.
 *
 * @return GtkWidget
 */
GtkWidget * get_frame_oper_determinante();

/**
 * Função para setar uma função para voltar à aplicaçao/tela
 * principal.
 *
 * @param app_voltar - pointeiro para uma função.
 */
void oper_det_app_principal(void (*app_voltar)(void));

/**
 * Desaloca memória usada para criar o formulário.
 */
void unref_oper_det_frm();


//#### EVENTOS ###//

void det_btn_matriz_A_button_release_even();

void det_btn_limpar_button_release_event();

void arrow_voltar_det_button_release();

//### FUNÇÕES AUXILIARES ###

void det_set_matriz_A(Matriz * m);

void det_exibir_matriz(int dash_col, int dash_row, Matriz * m);

void det_exibir_resultado();

void det_dim_limpar_dash_matriz();

#endif
