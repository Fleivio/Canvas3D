/*Implementa a classe para uma figura colorida, é usado por Clickable e Figure*/

#ifndef _COLORED_SHAPE_
#define _COLORED_SHAPE_

#include "Color.h"

class ColoredShape
{
private:
    static Color defaultColor;
    static Color defaultBorderColor;

public:
    Color *color;
    bool isFilled;

    bool hasBorder;
    Color *borderColor;

    /*contrutores (r,g,b,filled)*/
    ColoredShape(float r, float g, float b, bool isFilled);
    ColoredShape(float r, float g, float b);
    ColoredShape(Color *c, bool isFilled);
    ColoredShape(Color *c);
    ColoredShape(bool isFilled);
    ColoredShape();
    ~ColoredShape();

    /*seta o preenchimento da forma true -> com preenchimento*/
    void set_filled(bool isFilled);

    /*set a borda da forma true -> com borda*/
    void set_border(bool hasBorder);

    /*seta a cor da borda da forma*/
    void set_border_color(float r, float g, float b);
    /*seta a cor da borda da forma*/
    void set_border_color(Color *c);

    /*seta a cor da forma*/
    void set_color(Color *c);
    /*seta a cor da forma*/
    void set_color(float r, float g, float b);
};

#endif