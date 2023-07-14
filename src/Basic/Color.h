/*Implementa uma classe para cor*/

#ifndef _COLOR_
#define _COLOR_

#include "../gl_canvas2d.h"

class Color
{
public:
    float r, g, b;

    /*contrutor (r,g,b)*/
    Color(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    /*construtor (r,g,b) preto*/
    Color(){
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }

    /*retorna uma cópia do objeto color*/
    Color *copy()
    {
        return new Color(r, g, b);
    }

    /*aplica a cor para o canvas*/
    void apply_color()
    {
        CV::color(r, g, b);
    }

    /*verifica se uma cor é igual a outra*/
    bool equals(Color &c)
    {
        if (c.r == r && c.g == g && c.b == b)
            return true;

        return false;
    }

    /*print para debug*/
    void print()
    {
        printf("\n%f %f %f\n", r, g, b);
    }
};

#endif
