<div align="center">

<img width="487" height="202" alt="image" src="https://github.com/user-attachments/assets/61586179-e7d3-4133-b582-d48b70cdf67d" />

**Facultad de Ingeniería - Universidad de Buenos Aires**  

**TA134 – Sistemas Embebidos**  
Curso 2 – Grupo 3

# Pecera Inteligente  

## Autores
Lautaro Gastón Fritz - 102320  
Mauro Axel Tedesco - 102958  
Francisco López García - n20240046

**Cuatrimestre de cursada:** 1er cuatrimestre 2026  

*Trabajo realizado entre mayo y julio de 2026.*
</div>

### **1\. Selección del proyecto a implementar**

#### **1.1 Objetivo del proyecto y resultados esperados**

El objetivo del presente proyecto es diseñar e implementar un sistema embebido de automatización y monitoreo para acuarios. El sistema busca automatizar determinadas tareas de mantenimiento y operación del acuario, como el control del sistema de filtrado y la coordinación de ciclos de alimentación, permitiendo además la configuración manual de parámetros de funcionamiento.

Como resultados esperados, se pretende obtener un prototipo funcional capaz de:

* controlar actuadores asociados al acuario,
* ejecutar ciclos automáticos de funcionamiento,
* almacenar parámetros de configuración en memoria no volátil,
* operar mediante distintos modos de funcionamiento (inicialización, operación normal, configuración y control manual),
* y servir como base para futuras ampliaciones orientadas al monitoreo ambiental y conectividad IoT.

El proyecto también tiene como finalidad aplicar conceptos de sistemas embebidos tales como manejo de periféricos, máquinas de estados, temporización, control de dispositivos externos y administración de configuraciones persistentes.

#### **1.2 Motivación**

En la actualidad existen soluciones comerciales orientadas a la automatización y monitoreo de acuarios, incluyendo sistemas de control de filtrado, iluminación, alimentación y supervisión ambiental. Sin embargo, gran parte de estas soluciones corresponden a productos importados, lo que implica elevados costos de adquisición, limitada disponibilidad en el mercado local y menor flexibilidad para su personalización o mantenimiento.

#### **1.3 Proyectos similares**

En base a los objetivos planteados, se consideran distintas variantes posibles del sistema, las cuales implican diferentes niveles de complejidad en términos de hardware, sensores y actuadores requeridos.

**1. Sistema base:** Control y automatización de funciones esenciales del acuario:
* Encendido y apagado del sistema de filtrado mediante temporización.
* Encendido y apagado de iluminación, simulando ciclos de día y noche.
* Activación automática del alimentador en horarios preestablecidos.
* Configuración de parámetros de funcionamiento (horarios de alimentación, duración de ciclos de iluminación, entre otros), almacenados en memoria no volátil.
* Monitoreo de temperatura del agua y notificación ante valores fuera de los límites establecidos, permitiendo la intervención del usuario.  

**2. Sistema base con control de temperatura:** Incluye todas las funcionalidades del sistema base, incorporando además actuadores destinados a la regulación automática de la temperatura del agua. 

**3. Sistema avanzado con control químico:** Incluye las funcionalidades anteriores, agregando monitoreo y control de parámetros químicos del agua, tales como pH y salinidad, orientado a especies con mayores requerimientos ambientales.

Para comparar estas alternativas, se tienen en cuenta seis aspectos característicos, los cuales se ponderan del 1 al 10:
1.  **Disponibilidad del hardware (9):** Se evalúa si el proyecto puede implementarse utilizando hardware que se consiga fácilmente en el mercado regional, sin necesidad de importación o tiempos de envío extensos.
2.  **Impacto en el proyecto (8):** Se pondera cuánto aporta a la funcionalidad y control del crecimiento del cultivo.
3.  **Costo (8):** Se evalúa el costo total del hardware requerido para cada opción.
4.  **Dificultad técnica / Viabilidad (10):** Se contempla el tiempo requerido y la complejidad de implementación, teniendo en cuenta los conocimientos disponibles.
5.  **Interés personal del equipo (7):** Se pondera la motivación e interés del equipo en implementar cada alternativa.

La siguiente tabla (Tabla 1.2.1) muestra los valores ponderados asignados a cada proyecto considerado

INSERTAR TABLA

<p align="center"><em>Tabla 1: Comparación de alternativas de proyecto</em></p>

<img width="877" height="495" alt="image" src="https://github.com/user-attachments/assets/19fef76c-687e-4594-8d79-d77ae98347cb" />

<p align="center"><em>Figura 1: Diagrama en bloques del sistema</em></p>

### **2\. Elicitación de requisitos y casos de uso**

#### **2.1 Requisitos del proyecto**

| Grupo | ID | Descripción |
|---|---|---|
| Sensores ambientales | 1.1 | El sistema contará con un termómetro sumergible para supervisar la temperatura del agua de la pecera. |
|  | 1.2 | El sistema realizará lecturas periódicas de la temperatura a una frecuencia configurable y mostrará los valores en un display LED. |
|  | 1.3 | El sistema enviará alertas visuales o notificaciones si la temperatura supera los umbrales configurados. |
| Actuadores — Alimentación | 2.1 | El sistema contará con un servomotor encargado de accionar el mecanismo de alimentación automática de los peces. |
|  | 2.2 | La alimentación automática se realizará en horarios configurables definidos por el usuario. |
|  | 2.3 | El usuario podrá activar manualmente la alimentación desde la aplicación o mediante un botón físico de prueba. |
| Actuadores — Iluminación | 2.4 | El sistema contará con luces LED para simular ciclos de día y noche dentro de la pecera. |
|  | 2.5 | La intensidad lumínica y los horarios de encendido/apagado serán configurables para definir ciclos automáticos. |
|  | 2.6 | El sistema podrá realizar transiciones graduales de iluminación para simular amanecer y atardecer. |
| Actuadores — Filtrado | 2.7 | El sistema controlará un filtro de agua mediante un relay para activar o desactivar el sistema de filtrado. |
|  | 2.8 | El filtro operará en estado continuo, a excepción de los períodos de alimentación, durante los cuales se apagará. |
|  | 2.9 | El sistema verificará el estado del relay y notificará posibles fallos de activación del filtro. |
| Visualización | 3.1 | El sistema contará con un display LED para visualizar la temperatura actual del agua y estados básicos del sistema. |
|  | 3.2 | El display mostrará mensajes de alerta ante condiciones críticas o errores de sensores. |
| Almacenamiento | 4.1 | La configuración del sistema (horarios de alimentación, ciclos de iluminación y parámetros de temperatura) se persistirá en la memoria interna del microcontrolador. |
|  | 4.2 | El sistema recuperará automáticamente la configuración guardada al iniciar y validará su integridad. |
| Interfaz/App | 5.1 | Toda la interacción de usuario, notificaciones y alarmas podrá realizarse mediante una aplicación móvil conectada por BLE o Wi-Fi. |
|  | 5.2 | La aplicación permitirá configurar horarios de alimentación, ciclos de iluminación y umbrales de temperatura. |
|  | 5.3 | El sistema enviará a la aplicación lecturas periódicas de temperatura y eventos críticos (ej. sobretemperatura, fallo del sensor o error del relay). |

<p align="center"><em>Tabla 2.1: Requisitos del proyecto</em></p>

En las Tablas 2.2 a 2.4 se presentan 3 casos de uso para el sistema:

## Caso de uso 1 — Alimentación automática

| Elemento | Definición |
|---|---|
| Disparador | El sistema detecta que se ha alcanzado el horario de alimentación configurado en la aplicación o recibe una orden de alimentación manual. |
| Precondiciones | El sistema está encendido. El servomotor de alimentación está conectado y funcional. El horario de alimentación está configurado y almacenado en memoria. El sistema no se encuentra en estado de mantenimiento. |
| Flujo principal | El sistema entra en estado de alimentación. Desactiva temporalmente el filtro de agua para evitar dispersión del alimento. Espera un tiempo de estabilización del agua. Activa el servomotor para dispensar alimento durante un tiempo definido. Finalizada la acción, el sistema vuelve al estado normal y reactiva el filtro. Se notifica a la app la ejecución de la alimentación. |
| Flujos alternativos | a. El sistema está en estado de error o mantenimiento: la alimentación no se ejecuta y se envía una notificación a la app. |

<p align="center"><em>Tabla 2.2: Control de alimentación</em></p>

---

## Caso de uso 2 — Control de iluminación día/noche

| Elemento | Definición |
|---|---|
| Disparador | El sistema detecta un cambio de horario programado para el ciclo de iluminación o recibe una modificación de parámetros desde la aplicación. |
| Precondiciones | El sistema está encendido. La tira LED está conectada y funcional. Los horarios de encendido/apagado o nivel de brillo están configurados y almacenados en memoria. |
| Flujo principal | El sistema ajusta el estado de la iluminación según el ciclo configurado. Enciende o apaga la tira LED o modifica su intensidad mediante PWM. Mantiene el estado hasta el próximo cambio programado. El estado de iluminación se actualiza en la app y en el display local. |
| Flujos alternativos | a. Falla en la tira LED o en el canal PWM: el sistema apaga la salida afectada y notifica error a la aplicación. |

<p align="center"><em>Tabla 2.3: Control de iluminación día/noche</em></p>

---

## Caso de uso 3 — Control de filtrado de agua

| Elemento | Definición |
|---|---|
| Disparador | El sistema ejecuta el modo automático de mantenimiento o recibe una orden desde la aplicación para activar/desactivar el filtro. |
| Precondiciones | El sistema está encendido. El relay del filtro está conectado y funcional. El estado del filtro está definido en la configuración del sistema. |
| Flujo principal | El sistema activa el relay para encender el filtro de agua durante el funcionamiento normal. En caso de rutina de alimentación, el sistema desactiva temporalmente el filtro y lo reactiva una vez finalizado el ciclo. El estado del filtro se reporta a la aplicación y al display. |
| Flujos alternativos | a. Fallo del relay o ausencia de respuesta del filtro: el sistema desactiva el control automático del filtro y notifica la falla a la aplicación. |

<p align="center"><em>Tabla 2.4: Control de filtrado de agua</em></p>
