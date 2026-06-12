# Pecera Inteligente  

## Informe de avance

A continuación se detalla el estado de avance de los requisitos del sistema:

#### Referencia

| Estado | Significado |
|:---:|---|
| 🔴 | No se implementará |
| 🟡 | Implementación en proceso |
| 🟢 | Ya implementado |

#### Requisitos

| Grupo | ID | Descripción | Estado |
|---|---|---|---|
| Sensores ambientales | 1.1 | El sistema contará con un termómetro sumergible para supervisar la temperatura del agua de la pecera. | 🔴 |
|  | 1.2 | El sistema realizará lecturas en tiempo real de la temperatura y mostrará los valores en un display LED. | 🟡 |
|  | 1.3 | El sistema enviará alertas visuales o notificaciones si la temperatura supera los umbrales configurados. | 🟢 |
| Actuadores — Alimentación | 2.1 | El sistema contará con un servomotor encargado de accionar el mecanismo de alimentación automática de los peces. | 🔴 |
|  | 2.2 | La alimentación automática se realizará en horarios configurables definidos por el usuario. | 🔴 |
|  | 2.3 | El usuario podrá activar manualmente la alimentación desde la aplicación. | 🔴 |
| Actuadores — Iluminación | 2.4 | El sistema contará con una lámpara LED para simular ciclos de día y noche en la pecera. | 🔴 |
|  | 2.5 | Los horarios de encendido/apagado serán configurables para definir ciclos automáticos. | 🔴 |
| Actuadores — Filtrado | 2.6 | El sistema controlará un filtro de agua mediante un relay para activar o desactivar el sistema de filtrado. | 🔴 |
|  | 2.7 | El filtro operará en estado continuo, a excepción de los períodos de alimentación, durante los cuales se apagará. | 🔴 |
|  | 2.8 | El sistema verificará el estado del relay y notificará posibles fallos de activación del filtro. | 🔴 |
| Visualización | 3.1 | El sistema contará con un display LED para visualizar la temperatura actual del agua y estados básicos del sistema. | 🔴 |
|  | 3.2 | El display mostrará mensajes de alerta ante condiciones críticas o errores de sensores. | 🔴 |
| Almacenamiento | 4.1 | La configuración del sistema (horarios de alimentación, ciclos de iluminación y parámetros de temperatura) se persistirá en la memoria interna del microcontrolador. | 🔴 |
|  | 4.2 | El sistema recuperará automáticamente la configuración guardada al iniciar y validará su integridad. | 🔴 |
| Interfaz/App | 5.1 | Toda la interacción de usuario, notificaciones y alarmas podrá realizarse mediante una aplicación móvil conectada por BLE. | 🔴 |
|  | 5.2 | La aplicación permitirá configurar horarios de alimentación, ciclos de iluminación y umbrales de temperatura. | 🔴 |
|  | 5.3 | La aplicación móvil permitirá alternar entre el modo manual y el modo automático de operación. En el modo manual, la misma aplicación podrá activar o desactivar los actuadores. | 🔴 |
|  | 5.4 | El sistema enviará a la aplicación notificaciones de eventos normales y críticos (ej. ciclo de alimentación completado, sobretemperatura, fallo del sensor o error del relay). | 🔴 |
