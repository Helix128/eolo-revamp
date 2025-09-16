#ifndef ISCREEN_H
#define ISCREEN_H

// Interfaz para definir una escena en la interfaz
class IScene
{
    public: 
    virtual void draw(U8g2 &u8g2, Input &input) = 0;
};
#endif