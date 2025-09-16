#ifndef ISCENE_H
#define ISCENE_H

// Declaración adelantada de AppContext para evitar dependencias circulares
struct AppContext;

// Interfaz para definir una escena en la interfaz
class IScene
{
public: 
    // Llamado al entrar en la escena (para inicialización única)
    virtual void enter(AppContext& context) {}
    
    // Llamado en cada ciclo de actualización 
    virtual void update(AppContext& context) = 0;
    
    // Destructor virtual para limpieza adecuada
    virtual ~IScene() {}
};
#endif