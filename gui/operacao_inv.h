#ifndef OPERACAO_INVERSA_H
#define OPERACAO_INVERSA_H

#include <gtk-3.0/gtk/gtk.h>

#include "../util/matriz.h"
#include "../util/operacoes_matriz.h"

/**
 * função para pegar o frame que contém o formulário
 * para realizar a inversa de uma matriz.
 *
 * @return GtkWidget
 */
GtkWidget * get_frame_oper_inversa();

/**
 * Função para setar uma função para voltar à aplicaçao/tela
 * principal.
 *
 * @param app_voltar - pointeiro para uma função.
 */
void oper_inv_app_principal(void (*app_voltar)(void));

/**
 * Desaloca memória usada para criar o formulário.
 */
void unref_oper_inv_frm();

//### EVENTS ###//

void inv_btn_matriz_A_button_release_even();

void inv_btn_limpar_button_release_event();

void arrow_voltar_inv_button_release();

//### FUNÇÕES AUXILIARES ###

void inv_set_matriz_A(Matriz * m);

void inv_exibir_matriz(int dash_col, int dash_row, Matriz * m);

void inv_exibir_resultado();

void inv_dim_limpar_dash_matriz();

#endif
