# Detección Híbrida de Anomalías en Grafos Dinámicos (MIDAS + Link-Cut Trees)

Este proyecto es desarrollado como parte del trabajo final del curso **CS3014 - Estructura de Datos Avanzados (2026-1)** bajo la dirección del profesor Luciano A. Romero Calla.

## Integrantes
* **Tu Nombre y Apellidos** - Correo Institucional

## Breve Descripción del Proyecto
El proyecto implementa un sistema en tiempo real para la detección de comportamientos sospechosos (anomalías) en flujos de datos estructurados como grafos dinámicos (ej. redes de computadoras o transacciones bancarias). 

Utilizamos un enfoque híbrido innovador:
1. **Frecuencia (Baseline):** Algoritmo MIDAS en C++ para detectar ráfagas de tráfico inusual usando Count-Min Sketches.
2. **Estructura (Aporte Original):** Un **Link-Cut Tree** aumentado con tamaños de subárbol implementado desde cero en C++ que identifica, en tiempo $O(\log n)$, si una nueva conexión une componentes masivas previamente aisladas (detección de puentes críticos/fraude estructural).

---

## 📅 Estado de Avance (Draft - Entrega 26 de Junio)

De acuerdo con los requerimientos de la entrega parcial del 26 de junio, el proyecto cuenta con el siguiente estado:

- [x] Definición del problema real y justificación del uso de estructuras avanzadas (Syllabus 5.9).
- [x] Descarga, compilación y validación del baseline oficial de MIDAS en C++ sobre el dataset DARPA.
- [x] Diseño arquitectónico de las carpetas del proyecto y esqueleto del Link-Cut Tree aumentado.
- [ ] Implementación completa de las operaciones `link`, `cut`, y `connected` del LCT con Splay Trees (En desarrollo).
- [ ] Pipeline de integración y cálculo del score híbrido (Pendiente).
- [ ] Interfaz visual interactiva web animada vía WebAssembly/Emscripten (Pendiente).

## Cómo Compilar el Estado Actual
*(Provisional para el baseline)*
```bash
mkdir build && cd build
cmake ..
make
