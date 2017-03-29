#include "operacao_mult.h"
#include "dialog_matriz.h"

//pointeiro de função para voltar a tela principal.
static void (* _App_opm_app_main_voltar)(void);

GtkBuilder * _App_opm_builder;
GtkSpinner * _App_opm_progresso;
GtkWidget  * _App_opm_dash_matriz;
GtkWidget  * _App_opm_box_win;

Matriz * _App_opm_m_A;
Matriz * _App_opm_m_B;

GtkWidget * get_frame_oper_mult()
{
    _App_opm_builder        = gtk_builder_new();

    gtk_builder_add_from_file (_App_opm_builder, "glade/mult_oper.glade", NULL);

    _App_opm_box_win        = GTK_WIDGET    (gtk_builder_get_object(_App_opm_builder, "mult_oper"));
    _App_opm_progresso      = GTK_SPINNER   (gtk_builder_get_object(_App_opm_builder, "spinner_calc_mult"));
    _App_opm_dash_matriz    = GTK_WIDGET    (gtk_builder_get_object(_App_opm_builder, "grid_matriz_mult"));

    gtk_builder_connect_signals(_App_opm_builder, NULL);

    _App_opm_m_B = NULL;
    _App_opm_m_A = NULL;

    return _App_opm_box_win;
}

void arrow_voltar_mult_button_release()
{
    _App_opm_app_main_voltar();
    opm_dim_limpar_dash_matriz();
}

void oper_mult_app_principal(void (* app_voltar)(void))
{
    _App_opm_app_main_voltar = app_voltar;
}

void opm_arrow_voltar_button_release()
{
    opm_dim_limpar_dash_matriz();

    gtk_spinner_stop(_App_opm_progresso);
    _App_opm_app_main_voltar();
}

void opm_set_matriz_B(Matriz * m_B)
{
    _App_opm_m_B = m_B;
    opm_exibir_matriz(2, 0, _App_opm_m_B);

    if(_App_opm_m_A != NULL)
    {
        GtkWidget * label;
        GtkStyleContext *context;

        label = gtk_label_new("x");

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"font_b");

        gtk_widget_show(label);
        gtk_grid_attach((GtkGrid *)_App_opm_dash_matriz, label, 1, 0, 1, 1);

        opm_exibir_resultado();
    }
}

void opm_set_matriz_A(Matriz * m_A)
{
    _App_opm_m_A = m_A;

    opm_exibir_matriz(0, 0, _App_opm_m_A);

    if(_App_opm_m_B != NULL)
    {
        GtkWidget * label;
        GtkStyleContext *context;

        label = gtk_label_new("x");

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"font_b");

        gtk_widget_show(label);
        gtk_grid_attach((GtkGrid *)_App_opm_dash_matriz, label, 1, 0, 1, 1);

        opm_exibir_resultado();
    }
}

void opm_btn_limpar_button_release_event()
{
    desalocarMemoriaMatriz(_App_opm_m_B);
    desalocarMemoriaMatriz(_App_opm_m_A);

    _App_opm_m_B = NULL;
    _App_opm_m_A = NULL;

    opm_dim_limpar_dash_matriz();
}


void opm_btn_matriz_B_button_release_even()
{
    GtkWindow * win;

    win = get_dialog_matriz(&opm_set_matriz_B);
    gtk_window_set_modal(win, TRUE);

    gtk_widget_show_all((GtkWidget *)win);
}


void opm_btn_matriz_A_button_release_even()
{
    GtkWindow * win;

    win = get_dialog_matriz(&opm_set_matriz_A);
    gtk_window_set_modal(win, TRUE);

    gtk_widget_show_all((GtkWidget *)win);
}

void unref_oper_mult_frm()
{
    g_object_unref(_App_opm_builder);
}

void opm_dim_limpar_dash_matriz()
{
    GList * children, * iter;

    children = gtk_container_get_children(GTK_CONTAINER(_App_opm_dash_matriz));

    for(iter = children; iter != NULL; iter = g_list_next(iter))
    {
        gtk_widget_destroy(GTK_WIDGET(iter->data));

    }

    g_list_free(children);
}

void opm_exibir_resultado()
{
    gtk_widget_show((GtkWidget *)_App_opm_progresso);

    Matriz * res;
    res = multMatriz(_App_opm_m_A, _App_opm_m_B);

    if(res != NULL)
    {
        GtkWidget * label;
        GtkStyleContext *context;

        label = gtk_label_new("=");

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"font_b");

        gtk_widget_show(label);

        gtk_grid_attach((GtkGrid *)_App_opm_dash_matriz, label, 3, 0, 1, 1);

        opm_exibir_matriz(4, 0, res);
        desalocarMemoriaMatriz(res);

    } else{

        GtkWidget * label;
        GtkStyleContext *context;

        label = gtk_label_new("Operação inválida!");

        context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context,"oper_invalida");

        gtk_grid_attach((GtkGrid *)_App_opm_dash_matriz, label, 4, 0, 1, 1);
        gtk_widget_show(label);
    }

    gtk_widget_hide((GtkWidget *)_App_opm_progresso);
}

void opm_exibir_matriz(int dash_col, int dash_row, Matriz * m)
{
    GtkWidget       * grid;
    GtkWidget       * label;
    GtkStyleContext * context;
    GtkWidget       * event_box;

    grid = gtk_grid_new ();

    gtk_grid_set_column_homogeneous ((GtkGrid *)grid, TRUE);
	gtk_grid_set_row_homogeneous    ((GtkGrid *)grid, TRUE);
    gtk_grid_set_column_spacing     ((GtkGrid *)grid, 15);

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

    gtk_grid_attach((GtkGrid *)_App_opm_dash_matriz, grid, dash_col, dash_row, 1, 1);
    gtk_widget_show(grid);
}
