#include "operacao_inv.h"
#include "dialog_matriz.h"

//pointeiro de função para voltar a tela principal.
static void (* _App_inv_app_main_voltar)(void);

GtkBuilder * _App_inv_builder;
GtkSpinner * _App_inv_progresso;
GtkWidget  * _App_inv_dash_matriz;
GtkWidget  * _App_inv_box_win;
GtkWidget  * _App_inv_label_A_;
GtkWidget  * _App_inv_label_A_inv;

Matriz * _App_inv_m_A;

GtkWidget * get_frame_oper_inversa()
{
    _App_inv_builder        = gtk_builder_new();

    gtk_builder_add_from_file (_App_inv_builder, "glade/inv_oper.glade", NULL);

    _App_inv_box_win        = GTK_WIDGET    (gtk_builder_get_object(_App_inv_builder, "inv_oper"));
    _App_inv_progresso      = GTK_SPINNER   (gtk_builder_get_object(_App_inv_builder, "spinner_calc_inv"));
    _App_inv_dash_matriz    = GTK_WIDGET    (gtk_builder_get_object(_App_inv_builder, "grid_matriz_inv"));
    _App_inv_label_A_       = GTK_WIDGET    (gtk_builder_get_object(_App_inv_builder, "lbl_A_"));
    _App_inv_label_A_inv    = GTK_WIDGET    (gtk_builder_get_object(_App_inv_builder, "lbl_A_inv"));

    gtk_builder_connect_signals(_App_inv_builder, NULL);

    _App_inv_m_A = NULL;

    return _App_inv_box_win;
}

void arrow_voltar_inv_button_release()
{
    inv_dim_limpar_dash_matriz();
    _App_inv_app_main_voltar();
}


void inv_dim_limpar_dash_matriz()
{
    GtkWidget * el = gtk_grid_get_child_at((GtkGrid *)_App_inv_dash_matriz, 1, 0);

    if(el != NULL)
    {
        gtk_widget_destroy(el);
    }

    el = gtk_grid_get_child_at((GtkGrid *)_App_inv_dash_matriz, 3, 0);

    if(el != NULL)
    {
        gtk_widget_destroy(el);
    }

    gtk_widget_set_visible(_App_inv_label_A_, FALSE);
    gtk_widget_set_visible(_App_inv_label_A_inv,FALSE);
}

void inv_exibir_resultado()
{
    gtk_widget_set_visible((GtkWidget *)_App_inv_progresso, TRUE);

    gtk_widget_set_visible(_App_inv_label_A_, TRUE);

    Matriz * res;
    res = calcMatrizInversa(_App_inv_m_A);

    if(res != NULL)
    {
        gtk_widget_set_visible(_App_inv_label_A_inv,TRUE);

        inv_exibir_matriz(3, 0, res);
        desalocarMemoriaMatriz(res);

    } else{

        GtkWidget * label;
        GtkStyleContext *context;

        label = gtk_label_new("Matriz singular!");

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"oper_invalida");

        gtk_grid_attach((GtkGrid *)_App_inv_dash_matriz, label, 3, 0, 1, 1);
        gtk_widget_show(label);
    }

    gtk_widget_set_visible((GtkWidget *)_App_inv_progresso, FALSE);
}

void inv_exibir_matriz(int dash_col, int dash_row, Matriz * m)
{

    GtkWidget       * grid;
    GtkWidget       * label;
    GtkStyleContext * context;
    GtkWidget       * event_box;

    grid = gtk_grid_new ();

    gtk_grid_set_column_homogeneous    ((GtkGrid *)grid, TRUE);
	gtk_grid_set_row_homogeneous       ((GtkGrid *)grid, TRUE);
    gtk_grid_set_column_spacing        ((GtkGrid *)grid, 15);

	int i, j;

	for(i = 0; i < m->row; i++)
	{
		for(j = 0; j < m->col; j++)
		{
            Fracao  * fr = m->dados[i][j];
            gchar   * v;

            if(fr->denominador != 1 && fr->numerador != 0)
            {
                v = g_strdup_printf("%d/%d", fr->numerador, fr->denominador);

            } else{

                v = g_strdup_printf("%d", fr->numerador);
            }

            label = gtk_label_new(v);

            if(i == 0 && j == 0)
            {
                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"top");

            } else if( i == m->row -1 && j == 0){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"bottom");

            } else if(j == 0){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"left");

            } else {
                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"font");
            }

            if(i == 0 && j == m->col - 1){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"top-right");

            } else if( i == m->row -1 && j == m->col - 1){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"bottom-right");

            } else if(j == m->col - 1){

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"right");

            } else{

                context = gtk_widget_get_style_context(label);
            	gtk_style_context_add_class(context,"font");
            }

			gtk_grid_attach((GtkGrid *)grid, label, j, i, 1, 1);
            gtk_widget_show(label);
		}
	}

    gtk_grid_attach((GtkGrid *)_App_inv_dash_matriz, grid, dash_col, dash_row, 1, 1);
    gtk_widget_show(grid);
}

void inv_btn_matriz_A_button_release_even()
{
    GtkWindow * win;

    win = get_dialog_matriz(&inv_set_matriz_A);
    gtk_window_set_modal(win, TRUE);

    gtk_widget_show_all((GtkWidget *)win);
}

void unref_oper_inv_frm()
{
    g_object_unref(_App_inv_builder);
}

void inv_btn_limpar_button_release_event()
{
    desalocarMemoriaMatriz(_App_inv_m_A);
    _App_inv_m_A = NULL;

    inv_dim_limpar_dash_matriz();
}

void oper_inv_app_principal(void (* app_voltar)(void))
{
    _App_inv_app_main_voltar = app_voltar;
}

void inv_set_matriz_A(Matriz * m_A)
{
    _App_inv_m_A = m_A;

    inv_exibir_matriz(1, 0, _App_inv_m_A);
    inv_exibir_resultado();
}
