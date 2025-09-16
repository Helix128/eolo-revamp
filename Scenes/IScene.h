#ifndef ISCENE_H
#define ISCENE_H

#include "../Config.h"
#include <U8g2lib.h>
#include "../Input.h"

// Interfaz para definir una escena en la interfaz
class IScene
{
    public: 
    virtual void draw(DisplayModel &u8g2, Input &input) = 0;
};
#endif