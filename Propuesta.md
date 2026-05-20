<div align="center">

<img width="487" height="202" alt="image" src="https://github.com/user-attachments/assets/61586179-e7d3-4133-b582-d48b70cdf67d" />

**Facultad de Ingeniería - Universidad de Buenos Aires**  

**TA134 – Sistemas Embebidos**  
Curso 2 – Grupo 3

# Pecera Inteligente  

## Autores
Lautaro Gastón Fritz - 102320  
Mauro Axel Tedesco - 102958  
Francisco López García - 

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
