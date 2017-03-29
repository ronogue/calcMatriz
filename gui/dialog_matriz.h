#ifndef DIALOG_MATRIZ_H
#define DIALOG_MATRIZ_H

#include <gtk-3.0/gtk/gtk.h>
#include "../util/matriz.h"

GtkWindow * get_dialog_matriz(void (* set_grid)(Matriz *));

//#### EVENTOS ###///

void btn_ok1_button_release_event();

void btn_cancelar_button_release_event();

void btn_add_button_release_event();

void btn_remover_button_release_event();

//## FUNÇÕES AUXILIARES ##/

/*
 *Função para pegar a matriz gerada no formulário.
 *
 *@return pointeiro para uma matriz.
 */
Matriz * get_matriz();

/**
 *Função para criar uma matriz nula no formulário.
 *
 */
void criarMatriz();

#endif
