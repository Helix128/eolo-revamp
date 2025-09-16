#ifndef ISCENE_H
#define ISCENE_H

// Forward declaration of AppContext to avoid circular dependencies
struct AppContext;

// Interface for defining a scene in the interface
class IScene
{
public: 
    // Called when entering the scene (for one-time initialization)
    virtual void enter(AppContext& context) {}
    
    // Called every frame for logic and drawing
    virtual void update(AppContext& context) = 0;
    
    // Virtual destructor for proper cleanup
    virtual ~IScene() {}
};
#endif