#include "app_window.h"

#include "operacao_soma.h"
#include "operacao_mult.h"
#include "operacao_transposta.h"
#include "operacao_det.h"
#include "operacao_inv.h"

GtkWidget * _App_apw_dash;
GtkWidget * _App_apw_app;
GtkBuilder* _App_apw_builder;

GtkWidget * _App_apw_oper_sum;
GtkWidget * _App_apw_oper_mult;
GtkWidget * _App_apw_oper_tran;
GtkWidget * _App_apw_oper_dete;
GtkWidget * _App_apw_oper_inve;

void app_init(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget       *window;


    _App_apw_builder = gtk_builder_new();
    gtk_builder_add_from_file (_App_apw_builder, "glade/app_window.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(_App_apw_builder, "app_window"));
    gtk_builder_connect_signals(_App_apw_builder, NULL);

    _App_apw_app  = GTK_WIDGET(gtk_builder_get_object(_App_apw_builder, "app"));
    _App_apw_dash = GTK_WIDGET(gtk_builder_get_object(_App_apw_builder, "dash"));

    GtkCssProvider *provider;

	provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(provider, "css.css", NULL);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    init_vars_oper();

    gtk_widget_show(window);
    gtk_main();
}

void init_vars_oper()
{
    _App_apw_oper_sum = get_frame_oper_somar();
    oper_soma_app_principal(&app_main);

    _App_apw_oper_mult = get_frame_oper_mult();
    oper_mult_app_principal(&app_main);

    _App_apw_oper_tran = get_frame_oper_transposicao();
    oper_transposicao_app_principal(&app_main);

    _App_apw_oper_dete = get_frame_oper_determinante();
    oper_det_app_principal(&app_main);

    _App_apw_oper_inve = get_frame_oper_inversa();
    oper_inv_app_principal(&app_main);
}

void app_main()
{
    inserir_form_dash(_App_apw_dash);
}

void btn_soma_clicked()
{
    inserir_form_dash(_App_apw_oper_sum);
}

void btn_transposta_clicked()
{
    inserir_form_dash(_App_apw_oper_tran);
}

void btn_mult_clicked()
{
    inserir_form_dash(_App_apw_oper_mult);
}

void btn_determinante_clicked()
{
    inserir_form_dash(_App_apw_oper_dete);
}

void btn_inversa_clicked()
{
    inserir_form_dash(_App_apw_oper_inve);
}

void limparDash()
{
    gtk_grid_remove_column ((GtkGrid *)_App_apw_app, 0);
    gtk_grid_insert_column ((GtkGrid *)_App_apw_app, 0);
}

void inserir_form_dash(GtkWidget * form)
{
    limparDash();
    gtk_grid_attach((GtkGrid *)_App_apw_app,  form, 0, 0, 1, 1);
}

void on_app_window_destroy()
{
    unref_oper_transposicao_frm();
    unref_oper_soma_frm();
    unref_oper_mult_frm();
    unref_oper_det_frm();
    unref_oper_inv_frm();

    g_object_unref(_App_apw_builder);
    gtk_main_quit();
}
