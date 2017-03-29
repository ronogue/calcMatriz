#include "operacao_det.h"
#include "dialog_matriz.h"

//pointeiro de função para voltar a tela principal.
static void (* _App_det_app_main_voltar)(void);

GtkBuilder * _App_det_builder;
GtkSpinner * _App_det_progresso;
GtkWidget  * _App_det_dash_matriz;
GtkWidget  * _App_det_box_win;
GtkWidget  * _App_det_label_;
GtkWidget  * _App_det_label_A_det;

Matriz * _App_det_m_A;

GtkWidget * get_frame_oper_determinante()
{
    _App_det_builder        = gtk_builder_new();

    gtk_builder_add_from_file (_App_det_builder, "glade/det_oper.glade", NULL);

    _App_det_box_win        = GTK_WIDGET    (gtk_builder_get_object(_App_det_builder, "det_oper"));
    _App_det_progresso      = GTK_SPINNER   (gtk_builder_get_object(_App_det_builder, "spinner_calc_det"));
    _App_det_dash_matriz    = GTK_WIDGET    (gtk_builder_get_object(_App_det_builder, "grid_matriz_det"));
    _App_det_label_         = GTK_WIDGET    (gtk_builder_get_object(_App_det_builder, "lbl_A_"));
    _App_det_label_A_det    = GTK_WIDGET    (gtk_builder_get_object(_App_det_builder, "lbl_A_det"));

    gtk_builder_connect_signals(_App_det_builder, NULL);

    _App_det_m_A = NULL;

    return _App_det_box_win;
}

void arrow_voltar_det_button_release()
{
    det_dim_limpar_dash_matriz();
    _App_det_app_main_voltar();
}

void det_dim_limpar_dash_matriz()
{
    GtkWidget * el = gtk_grid_get_child_at((GtkGrid *)_App_det_dash_matriz, 1, 0);

    if(el != NULL)
    {
        gtk_widget_destroy(el);
    }

    el = gtk_grid_get_child_at((GtkGrid *)_App_det_dash_matriz, 3, 0);

    if(el != NULL)
    {
        gtk_widget_destroy(el);
    }

    gtk_widget_set_visible(_App_det_label_, FALSE);
    gtk_widget_set_visible(_App_det_label_A_det,FALSE);
}

void det_exibir_resultado()
{
    GtkWidget       * label;
    GtkStyleContext * context;
    Fracao          * res;
    gchar           * v;

    gtk_widget_set_visible((GtkWidget *)_App_det_progresso, TRUE);

    gtk_widget_set_visible(_App_det_label_, TRUE);
    gtk_widget_set_visible(_App_det_label_A_det,TRUE);

    res = detProcessoTriangulacao(_App_det_m_A);

    if(res == NULL)
    {
        label = gtk_label_new("Matriz inválida!");

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"oper_invalida");

    } else {

        if(res->denominador != 1)
        {
            v = g_strdup_printf("%d/%d", res->numerador, res->denominador);

        } else{

            v = g_strdup_printf("%d", res->numerador);
        }
        desalocarMemoriaMemoriaFracao(1, res);

        label = gtk_label_new(v);

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"font");
    }

    gtk_widget_show(label);

    gtk_grid_attach((GtkGrid *)_App_det_dash_matriz, label, 3, 0, 1, 1);
    gtk_widget_set_visible((GtkWidget *)_App_det_progresso, FALSE);
}

void det_exibir_matriz(int dash_col, int dash_row, Matriz * m)
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

            if(fr->denominador != 1)
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

    gtk_grid_attach((GtkGrid *)_App_det_dash_matriz, grid, dash_col, dash_row, 1, 1);
    gtk_widget_show(grid);
}

void det_btn_matriz_A_button_release_even()
{
    GtkWindow * win;

    win = get_dialog_matriz(&det_set_matriz_A);
    gtk_window_set_modal(win, TRUE);

    gtk_widget_show_all((GtkWidget *)win);
}

void unref_oper_det_frm()
{
    g_object_unref(_App_det_builder);
}

void det_btn_limpar_button_release_event()
{
    desalocarMemoriaMatriz(_App_det_m_A);
    _App_det_m_A = NULL;

    det_dim_limpar_dash_matriz();
}

void oper_det_app_principal(void (* app_voltar)(void))
{
    _App_det_app_main_voltar = app_voltar;
}

void det_set_matriz_A(Matriz * m_A)
{
    _App_det_m_A = m_A;

    det_exibir_matriz(1, 0, _App_det_m_A);
    det_exibir_resultado();
}
