#include "operacao_transposta.h"
#include "dialog_matriz.h"

//pointeiro de função para voltar a tela principal.
static void (* _App_opt_app_main_voltar)(void);

GtkBuilder * _App_opt_builder;
GtkSpinner * _App_opt_progresso;
GtkWidget  * _App_opt_dash_matriz;
GtkWidget  * _App_opt_box_win;
GtkWidget  * _App_opt_label_A;
GtkWidget  * _App_opt_label_At;

Matriz * _App_opt_m_A;

GtkWidget * get_frame_oper_transposicao()
{
    _App_opt_builder        = gtk_builder_new();

    gtk_builder_add_from_file (_App_opt_builder, "glade/trans_oper.glade", NULL);

    _App_opt_box_win        = GTK_WIDGET    (gtk_builder_get_object(_App_opt_builder, "trans_oper"));
    _App_opt_progresso      = GTK_SPINNER   (gtk_builder_get_object(_App_opt_builder, "spinner_calc_trans"));
    _App_opt_dash_matriz    = GTK_WIDGET    (gtk_builder_get_object(_App_opt_builder, "grid_matriz_trans"));
    _App_opt_label_A        = GTK_WIDGET    (gtk_builder_get_object(_App_opt_builder, "lbl_A"));
    _App_opt_label_At       = GTK_WIDGET    (gtk_builder_get_object(_App_opt_builder, "lbl_At"));

    gtk_builder_connect_signals(_App_opt_builder, NULL);

    _App_opt_m_A = NULL;

    return _App_opt_box_win;
}

void arrow_voltar_trans_button_release()
{
    opt_limpar_dash_matriz();
    _App_opt_app_main_voltar();
}

void opt_limpar_dash_matriz()
{
    GtkWidget * el = NULL;

    el = gtk_grid_get_child_at((GtkGrid *)_App_opt_dash_matriz, 1, 0);

    if(el != NULL)
    {
        gtk_widget_destroy(el);
    }

    el = gtk_grid_get_child_at((GtkGrid *)_App_opt_dash_matriz, 3, 0);

    if(el != NULL)
    {
        gtk_widget_destroy(el);
    }

    gtk_widget_set_visible(_App_opt_label_A, FALSE);
    gtk_widget_set_visible(_App_opt_label_At,FALSE);
}

void opt_exibir_resultado()
{
    gtk_widget_set_visible((GtkWidget *)_App_opt_progresso, TRUE);

    gtk_widget_set_visible(_App_opt_label_A, TRUE);
    gtk_widget_set_visible(_App_opt_label_At,TRUE);

    Matriz * res = NULL;
    res = transporMatriz(_App_opt_m_A);

    opt_exibir_matriz(3, 0, res);
    desalocarMemoriaMatriz(res);
    res = NULL;

    gtk_widget_set_visible((GtkWidget *)_App_opt_progresso, FALSE);
}

void opt_exibir_matriz(int dash_col, int dash_row, Matriz * m)
{

    GtkWidget       * grid          = NULL;
    GtkWidget       * label         = NULL;
    GtkStyleContext * context       = NULL;
    GtkWidget       * event_box     = NULL;

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

    gtk_grid_attach((GtkGrid *)_App_opt_dash_matriz, grid, dash_col, dash_row, 1, 1);
    gtk_widget_show(grid);
}

void opt_btn_matriz_A_button_release_even()
{
    GtkWindow * win;

    win = get_dialog_matriz(&opt_set_matriz_A);
    gtk_window_set_modal(win, TRUE);

    gtk_widget_show_all((GtkWidget *)win);
}

void unref_oper_transposicao_frm()
{
    g_object_unref(_App_opt_builder);
}

void opt_btn_limpar_button_release_event()
{
    opt_limpar_dash_matriz();

    desalocarMemoriaMatriz(_App_opt_m_A);
    _App_opt_m_A = NULL;
}

void oper_transposicao_app_principal(void (* app_voltar)(void))
{
    _App_opt_app_main_voltar = app_voltar;
}

void opt_set_matriz_A(Matriz * m_A)
{
    _App_opt_m_A = m_A;

    opt_exibir_matriz(1, 0, _App_opt_m_A);
    opt_exibir_resultado();
}
