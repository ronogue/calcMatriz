#include "dialog_matriz.h"
#include "input_value_aij.h"

#include "gui_util.h"

void (* _App_dim_set_grid_ptr)(Matriz *);

int _App_dim_mtr_row = 0;
int _App_dim_mtr_col = 0;

GtkBuilder  *   _App_dim_builder;
GtkWindow   *   _App_dim_dialog_app_matriz;
GtkWidget   *   _App_dim_grid;
GtkWidget   *   _App_dim_grid_matriz;

GtkEntry    *   _App_dim_entry_row;
GtkEntry    *   _App_dim_entry_col;

GtkWindow * get_dialog_matriz(void (* set_grid)(Matriz *))
{
    _App_dim_builder = gtk_builder_new();

    gtk_builder_add_from_file (_App_dim_builder, "glade/dialgo_matriz.glade", NULL);

    _App_dim_dialog_app_matriz  = GTK_WINDOW(gtk_builder_get_object(_App_dim_builder, "dialog_matriz"));
    gtk_builder_connect_signals(_App_dim_builder, NULL);

    _App_dim_entry_row          = GTK_ENTRY (gtk_builder_get_object(_App_dim_builder, "entry_row"));
	_App_dim_entry_col          = GTK_ENTRY (gtk_builder_get_object(_App_dim_builder, "entry_col"));

    _App_dim_grid_matriz        = GTK_WIDGET(gtk_builder_get_object(_App_dim_builder, "grid_matriz"));

    _App_dim_grid 	            = gtk_grid_new ();

	gtk_grid_set_column_homogeneous    ((GtkGrid *)_App_dim_grid, TRUE);
	gtk_grid_set_row_homogeneous       ((GtkGrid *)_App_dim_grid, TRUE);
    gtk_grid_set_column_spacing        ((GtkGrid *)_App_dim_grid, 20);

    _App_dim_set_grid_ptr = set_grid;

    return _App_dim_dialog_app_matriz;
}

void btn_ok1_button_release_event()
{
    Matriz * m;
    m = get_matriz();

    _App_dim_mtr_row = 0;
    _App_dim_mtr_col = 0;

    _App_dim_set_grid_ptr(m);

    gtk_window_close(_App_dim_dialog_app_matriz);
    g_object_unref(_App_dim_builder);
}

void btn_cancelar_button_release_event()
{
    gtk_window_close(_App_dim_dialog_app_matriz);
    g_object_unref(_App_dim_builder);
}

void btn_add_button_release_event()
{
    _App_dim_mtr_row = atoi(gtk_entry_get_text(_App_dim_entry_row));
	_App_dim_mtr_col = atoi(gtk_entry_get_text(_App_dim_entry_col));

    criarMatriz();

    gtk_grid_attach((GtkGrid *)_App_dim_grid_matriz, _App_dim_grid, 0, 0, 1, 1);
    gtk_widget_show(_App_dim_grid);
}

void set_value_a_ij(GtkWidget * label_a_ij, const gchar * valor)
{
    gtk_label_set_text((GtkLabel *)label_a_ij, valor);
}

void onclick_label_a_ij(GtkWidget * box)
{
    GtkWindow * win;
    win = get_win_input_value_a_ij(&set_value_a_ij, gtk_bin_get_child((GtkBin *)box));

    gtk_widget_show_all((GtkWidget *)win);
}

void criarMatriz()
{
    GtkWidget           * label;
    GtkStyleContext     * context;
    GtkWidget           * event_box;

	int i, j;

	for(i = 0; i < _App_dim_mtr_row; i++)
	{
        for(j = 0; j < _App_dim_mtr_col; j++)
		{
            event_box = gtk_event_box_new ();
			label = gtk_label_new("0");

            if(i == 0 && j == 0)
            {
                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"top");

            } else if( i == _App_dim_mtr_row -1 && j == 0){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"bottom");

            } else if(j == 0){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"left");

            } else {
                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"font");
            }

            if(i == 0 && j == _App_dim_mtr_col - 1){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"top-right");

            } else if( i == _App_dim_mtr_row -1 && j == _App_dim_mtr_col - 1){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"bottom-right");

            } else if(j == _App_dim_mtr_col - 1){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"right");
            } else{
                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"font");
            }

            gtk_container_add (GTK_CONTAINER (event_box), label);

            gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
            g_signal_connect(event_box, "button_press_event", (GCallback) &onclick_label_a_ij, NULL);

			gtk_grid_attach((GtkGrid *)_App_dim_grid, event_box, j, i, 1, 1);
			gtk_widget_show_all (event_box);
		}
	}
}

void btn_remover_button_release_event()
{
    gtk_widget_destroy(_App_dim_grid);

    _App_dim_grid 	= gtk_grid_new ();

    gtk_grid_set_column_homogeneous((GtkGrid *)_App_dim_grid, TRUE);
	gtk_grid_set_row_homogeneous((GtkGrid *)_App_dim_grid, TRUE);
    gtk_grid_set_column_spacing((GtkGrid *)_App_dim_grid, 20);
}

Matriz * get_matriz()
{
    GtkWidget * label;
    GtkWidget * event_box_;

    int i, j;

    Matriz * m = (Matriz *)malloc(sizeof(Matriz *));

    m->row = _App_dim_mtr_row;
    m->col = _App_dim_mtr_col;

    alocarMemoriaDadosMatriz(m);

    for(i = 0; i < _App_dim_mtr_row; i++)
	{
		for(j = 0; j < _App_dim_mtr_col; j++)
		{
            event_box_ = gtk_grid_get_child_at((GtkGrid *)_App_dim_grid, j, i);
            label = gtk_bin_get_child((GtkBin *)event_box_);

            m->dados[i][j] = g_char_to_fracao(gtk_label_get_text((GtkLabel *)label));
		}
	}

    return m;
}
