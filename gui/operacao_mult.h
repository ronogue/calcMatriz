#ifndef OPERACAO_MULT_H
#define OPERACAO_MULT_H

#include <gtk-3.0/gtk/gtk.h>

#include "../util/matriz.h"
#include "../util/operacoes_matriz.h"

/**
 * função para pegar o frame que contém o formulário
 * para realizar a multiplicação de duas matrizes.
 *
 * @return GtkWidget
 */
GtkWidget * get_frame_oper_mult();

/**
 * Função para setar uma função para voltar à aplicaçao/tela
 * principal.
 *
 * @param app_voltar - pointeiro para uma função.
 */
void oper_mult_app_principal(void (*app_voltar)(void));

/**
 * Desaloca memória usada para criar o formulário.
 */
void unref_oper_mult_frm();

//#### EVENTS ###//

/**
 * Evento do botão voltar.
 */
void opm_arrow_voltar_button_release();

void opm_btn_limpar_button_release_event();

void opm_btn_matriz_A_button_release_even();

void opm_btn_matriz_B_button_release_even();

void arrow_voltar_mult_button_release();

//### FUNÇÕES AUXILIARES ###//

void opm_set_matriz_A(Matriz * m);

void opm_set_matriz_B(Matriz * m);

void opm_exibir_matriz(int dash_col, int dash_row, Matriz * m);

void opm_exibir_resultado();

void opm_dim_limpar_dash_matriz();

#endif
