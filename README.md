# EOLO Prototype - Refactored Architecture

## Overview

This project has been refactored to use a centralized AppContext architecture that serves as the single source of truth for application state and provides unified access to all hardware modules and services.

## Architecture Principles

### 1. Single Source of Truth
- All shared variables and state live within `AppContext`
- No scene maintains its own copy of shared data
- Direct access to context for reading/modifying data

### 2. Dependency Injection
- `AppContext` is passed as a parameter to functions that need it
- No more global variables or complex static singletons
- Each component receives its "toolbox" with everything needed

### 3. Centralized Lifecycle Management
- `AppContext` is created once in the .ino file
- `begin()` method initializes all hardware modules in setup()
- Context is passed to SceneManager in the main loop

## Key Files

### Core Architecture
- **`AppContext.h`** - Central state and service container
- **`SceneManager.h/.cpp`** - Scene management system
- **`Scenes/IScene.h`** - Base interface for all scenes

### Hardware Modules
- **`Input.h`** - Encoder/button input management
- **`Motor.h`** - Motor control
- **`Plantower.h`** - Air quality sensor
- **`Battery.h`** - Battery level monitoring
- **`Logger.h`** - SD card data logging

### User Interface
- **`GUI.h`** - Common UI elements
- **`Scenes/LogoScene.h`** - Splash screen
- **`Scenes/HomeScene.h`** - Main menu
- **`Scenes/SetFlowScene.h`** - Flow rate configuration

## Usage Examples

### Creating a New Scene

```cpp
#include "IScene.h"
#include "../AppContext.h"

class MyScene : public IScene {
public:
    void enter(AppContext& context) override {
        // One-time initialization when entering scene
        context.input.resetCounter();
    }

    void update(AppContext& context) override {
        // Called every frame
        
        // 1. Handle input/logic
        if (context.input.buttonPressed) {
            context.input.resetButton();
            // Do something
        }
        
        // 2. Draw to screen
        context.u8g2.clearBuffer();
        context.u8g2.drawStr(0, 20, "Hello World");
        context.u8g2.sendBuffer();
    }
};
```

### Accessing Shared State

```cpp
// Reading state
float currentFlow = context.flujoObjetivo;
bool isCapturing = context.capturaActiva;

// Modifying state
context.flujoObjetivo = 7.5f;
context.startCapture();
```

### Logging Data

```cpp
// Log current state to SD card
context.logger.logSnapshot(context);
```

## Hardware Configuration

Make sure to verify/adjust these pin definitions in `AppContext.h`:

```cpp
#define PIN_MOTOR_A 14
#define PIN_MOTOR_B 12
```

## Compilation

The project should compile as a standard Arduino sketch. The main files are:

1. `EOLOPrototype.ino` - Main Arduino sketch
2. All `.h` files in the root directory
3. All scene files in the `Scenes/` subdirectory
4. `SceneManager.cpp` - Contains static member definitions

## Benefits of This Architecture

1. **Maintainability** - Clear separation of concerns
2. **Testability** - Dependencies are explicit and injectable
3. **Scalability** - Easy to add new scenes and features
4. **Reliability** - Single source of truth prevents state inconsistencies
5. **Debugging** - Centralized state makes it easier to track issues

## Scene Lifecycle

1. **Registration** - Scenes are registered in `SceneRegistry.h`
2. **Activation** - `SceneManager::setScene()` switches scenes
3. **Entry** - New scene's `enter()` method is called once
4. **Update Loop** - Scene's `update()` method is called every frame
5. **Exit** - Switching scenes automatically handles cleanup

## Adding New Hardware Modules

1. Add the module to `AppContext.h` as a member variable
2. Initialize it in `AppContext::begin()`
3. Access it from scenes via `context.yourModule`

This architecture provides a solid foundation for expanding the EOLO prototype while maintaining clean, manageable code.