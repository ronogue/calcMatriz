#include "gui_util.h"
#include <stdlib.h>

Fracao * g_char_to_fracao(const gchar * val_util_)
{
    Fracao * fr     = (Fracao *)malloc(sizeof(Fracao *));
    gchar  * barra  = g_strrstr(val_util_,"/");

    if( barra != NULL)
    {
        gchar ** str_util_  = g_strsplit (val_util_,"/", -1);

        fr->numerador =  atoi(str_util_[0]);
        fr->denominador = atoi(str_util_[1]);

        g_strfreev(str_util_);

    } else{

        fr->numerador =  atoi(val_util_);
        fr->denominador = 1;
    }

    return fr;
}
