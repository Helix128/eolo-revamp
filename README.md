# EOLO - Documentación

## Resumen
EOLO utiliza un AppContext central como fuente única de datos y proporciona acceso unificado a módulos de hardware.

## Principios clave
- Fuente única de verdad: todo el estado compartido vive en AppContext.
- Inyección de dependencias: AppContext se pasa a las funciones/escenas que lo necesitan.
- Gestión centralizada del ciclo de vida: AppContext::begin() inicializa hardware en setup().

## Archivos principales
- AppContext.h — estado central y contenedores de servicios
- SceneManager.h — gestión de escenas
- Scenes/IScene.h — interfaz base de escenas
- Input.h, Motor.h, Plantower.h, Battery.h, Logger.h — módulos de hardware
- GUI.h y escenas en Scenes/ (LogoScene, HomeScene, FlujoScene)

## Uso mínimo
- Leer/Modificar estado desde cualquier escena vía `context`.
- Inicializar AppContext en el .ino y pasar al SceneManager en el loop.

Ejemplo breve:
```cpp
// leer
float flujo = context.flujoObjetivo;
// modificar
context.flujoObjetivo = 7.5f;
```
