#include "input_value_aij.h"

void (* _App_inva_set_value)(GtkWidget * label, const gchar * valor);

GtkBuilder  *   _App_inva_builder;
GtkEntry    *   _App_inva_entry_valor;
GtkWindow   *   _App_inva_input_value_aij_win;
GtkWidget   *   _App_inva_label_a_ij;

GtkWindow * get_win_input_value_a_ij(void (* set_val)(GtkWidget * label, const gchar * valor), GtkWidget * label_)
{
    _App_inva_builder = gtk_builder_new();

    gtk_builder_add_from_file (_App_inva_builder, "glade/input_value_aij.glade", NULL);

    _App_inva_input_value_aij_win = GTK_WINDOW(gtk_builder_get_object(_App_inva_builder, "input_value_aij"));
    gtk_builder_connect_signals(_App_inva_builder, NULL);

    _App_inva_entry_valor   = GTK_ENTRY(gtk_builder_get_object(_App_inva_builder, "entry_valor"));
    _App_inva_set_value     = set_val;
    _App_inva_label_a_ij    = label_;

    return _App_inva_input_value_aij_win;
}

void btn_ok_input_value_button_release_event()
{
    _App_inva_set_value(_App_inva_label_a_ij, gtk_entry_get_text(_App_inva_entry_valor));

    gtk_window_close(_App_inva_input_value_aij_win);
    g_object_unref(_App_inva_builder);
}

void btn_cancelar_input_value_button_release_event()
{
    gtk_window_close(_App_inva_input_value_aij_win);
    g_object_unref(_App_inva_builder);
}

void key_pressed_entry(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if(event->keyval == GDK_KEY_KP_Enter || event->keyval == GDK_KEY_Return)
    {
        btn_ok_input_value_button_release_event();
    }
}
