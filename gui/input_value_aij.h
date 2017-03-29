#ifndef INPUT_VALUE_AIJ_H
#define INPUT_VALUE_AIJ_H

#include <gtk-3.0/gtk/gtk.h>

GtkWindow * get_win_input_value_a_ij(void (* set_val)(GtkWidget * label, const gchar * valor),GtkWidget * label_);

//## EVENTOS ##/

void btn_ok_input_value_button_release_event();

/**
 *Evento executado quando o usuário pressionar
 *o enter.
 */
void key_pressed_entry(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

void btn_cancelar_input_value_button_release_event();


#endif
