#ifndef GUI_UTIL_H
#define GUI_UTIL_H

#include <gtk-3.0/gtk/gtk.h>
#include "../util/fracao.h"

/**
 *Função para converter g_char em fração.
 */
Fracao * g_char_to_fracao(const gchar * val);

#endif
