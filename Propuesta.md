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

## **1\. Selección del proyecto a implementar**

### **1.1 Objetivo del proyecto y resultados esperados**

El objetivo del presente proyecto es diseñar e implementar un sistema embebido de automatización y monitoreo para peceras domésticas. El sistema busca automatizar determinadas tareas de cuidado, atención y operación de la pecera, como el control del sistema de filtrado y la coordinación de ciclos de alimentación, permitiendo además la configuración manual de parámetros de funcionamiento.

Como resultados esperados, se pretende obtener un prototipo funcional capaz de:

* controlar actuadores asociados a la pecera,
* ejecutar ciclos automáticos de funcionamiento,
* almacenar parámetros de configuración en memoria no volátil,
* operar mediante distintos modos de funcionamiento (inicialización, operación normal, configuración y control manual remoto),
* permitir el control y supervisión remota del sistema mediante un dispositivo móvil,
* y servir como base para futuras ampliaciones.

### **1.2 Motivación**

En la actualidad existen soluciones comerciales orientadas a la automatización y monitoreo de peceras domésticas, incluyendo sistemas de control de filtrado, iluminación, alimentación y supervisión ambiental. Sin embargo, gran parte de estas soluciones corresponden a productos importados, lo que implica elevados costos de adquisición, limitada disponibilidad en el mercado local y menor flexibilidad para su personalización o mantenimiento.

### **1.3 Proyectos similares**

En base a los objetivos planteados, se consideran distintas variantes posibles del sistema, las cuales implican diferentes niveles de complejidad en términos de hardware, sensores y actuadores requeridos.

**1. Sistema base:** Control y automatización de funciones esenciales del acuario:
* Encendido y apagado del sistema de filtrado mediante temporización.
* Encendido y apagado de iluminación, simulando ciclos de día y noche.
* Activación automática del alimentador en horarios preestablecidos.
* Configuración de parámetros de funcionamiento (horarios de alimentación, duración de ciclos de iluminación, entre otros), almacenados en memoria no volátil.
* Control remoto del sistema a través de un dispositivo móvil.
* Monitoreo de temperatura del agua y notificación ante valores fuera de los límites establecidos, permitiendo la intervención del usuario.  

**2. Sistema base con control de temperatura:** Incluye todas las funcionalidades del sistema base, incorporando además actuadores destinados a la regulación automática de la temperatura del agua. 

**3. Sistema avanzado con control químico:** Incluye las funcionalidades anteriores, agregando monitoreo y control de parámetros químicos del agua, tales como pH y salinidad, orientado a especies con mayores requerimientos ambientales.

Para comparar estas alternativas, se tienen en cuenta cinco aspectos característicos, los cuales se ponderan del 1 al 10:
1.  **Disponibilidad del hardware (9):** Se evalúa si el proyecto puede implementarse utilizando hardware que se consiga fácilmente en el mercado regional, sin necesidad de importación o tiempos de envío extensos.
2.  **Impacto en el proyecto (8):** Se pondera cuánto aporta a la funcionalidad y control de la pecera.
3.  **Costo (8):** Se evalúa el costo total del hardware requerido para cada opción.
4.  **Dificultad técnica / Viabilidad (10):** Se contempla el tiempo requerido y la complejidad de implementación, teniendo en cuenta los conocimientos disponibles.
5.  **Interés personal del equipo (7):** Se pondera la motivación e interés del equipo en implementar cada alternativa.

La siguiente tabla (Tabla 1) muestra los valores ponderados asignados a cada proyecto considerado

<table>
    <thead>
        <tr>
            <th rowspan="2">Criterio</th>
            <th colspan="2">Proyecto Base</th>
            <th colspan="2">Base + Control de temperatura</th>
            <th colspan="2">Base + Control químico</th>
        </tr>
        <tr>
            <th>Puntaje</th>
            <th>Puntaje Ponderado</th>
            <th>Puntaje</th>
            <th>Puntaje Ponderado</th>
            <th>Puntaje</th>
            <th>Puntaje Ponderado</th>
        </tr>
    </thead>
    <tbody>
        <tr class="header-row">
            <td align="center">Disponibilidad de Hardware <br>(peso: 9)</td>
            <td>10</td>
            <td>90</td>
            <td>10</td>
            <td>90</td>
            <td>4</td>
            <td>36</td>
        </tr>
        <tr>
            <td align="center">Impacto en el proyecto <br>(peso: 8)</td>
            <td>8</td>
            <td>64</td>
            <td>5</td>
            <td>40</td>
            <td>7</td>
            <td>56</td>
        </tr>
        <tr class="header-row">
            <td align="center">Costo (peso: 8)</td>
            <td>8</td>
            <td>64</td>
            <td>7</td>
            <td>56</td>
            <td>3</td>
            <td>24</td>
        </tr>
        <tr>
            <td align="center">Dificultad técnica / Viabilidad <br>(peso: 10)</td>
            <td>9</td>
            <td>90</td>
            <td>7</td>
            <td>70</td>
            <td>3</td>
            <td>30</td>
        </tr>
        <tr class="header-row">
            <td align="center">Interés personal <br>(peso: 7)</td>
            <td>8</td>
            <td>56</td>
            <td>8</td>
            <td>56</td>
            <td>9</td>
            <td>63</td>
        </tr>
        <tr class="highlight-green">
            <td><strong>Puntaje Total</strong></td>
            <td>-</td>
            <td><strong>364</strong></td>
            <td>-</td>
            <td>312</td>
            <td>-</td>
            <td class="highlight-red">209</td>
        </tr>
    </tbody>
</table>

<p align="center"><em>Tabla 1: Comparación de alternativas de proyecto</em></p>

### **1.4 Selección del proyecto**

Vistas las consideraciones tomadas en cuenta para discriminar cuál sería el proyecto óptimo para desarrollar, se decidió seguir adelante con la opción de sistema base para peceras domésticas. Esta alternativa, en comparación con las demás, cumple con las funcionalidades esenciales planteadas para el proyecto, manteniendo al mismo tiempo un nivel de complejidad y costo razonable respecto a las prestaciones ofrecidas.

Si bien las variantes que incorporan control automático de temperatura y monitoreo químico del agua agregan nuevas capacidades al sistema, estas implican un aumento considerable en la dificultad técnica, el costo de implementación y la necesidad de hardware más específico. Particularmente, la incorporación de sensores de pH y salinidad requiere componentes menos accesibles y procesos de calibración más complejos, lo que reduce la viabilidad del proyecto dentro del tiempo y recursos disponibles.

Los principales desafíos que se van a afrontar son la integración eficiente de los distintos módulos electrónicos, la sincronización y comunicación con la aplicación móvil y la implementación de una interfaz de configuración que permita un uso simple e intuitivo para el usuario.

#### **1.4.1 Diagrama en bloques**

<img width="1035" height="552" alt="image" src="https://github.com/user-attachments/assets/5f1d1514-e05c-4253-ab30-6ef90483146a" />

<p align="center"><em>Figura 1: Diagrama en bloques del sistema</em></p>

## **2\. Elicitación de requisitos y casos de uso**

### **2.1 Requisitos del proyecto**

| Grupo | ID | Descripción |
|---|---|---|
| Sensores ambientales | 1.1 | El sistema contará con un termómetro sumergible para supervisar la temperatura del agua de la pecera. |
|  | 1.2 | El sistema realizará lecturas en tiempo real de la temperatura y mostrará los valores en un display LED. |
|  | 1.3 | El sistema enviará alertas visuales o notificaciones si la temperatura supera los umbrales configurados. |
| Actuadores — Alimentación | 2.1 | El sistema contará con un servomotor encargado de accionar el mecanismo de alimentación automática de los peces. |
|  | 2.2 | La alimentación automática se realizará en horarios configurables definidos por el usuario. |
|  | 2.3 | El usuario podrá activar manualmente la alimentación desde la aplicación. |
| Actuadores — Iluminación | 2.4 | El sistema contará con una lámpara LED para simular ciclos de día y noche en la pecera. |
|  | 2.5 | Los horarios de encendido/apagado serán configurables para definir ciclos automáticos. |
| Actuadores — Filtrado | 2.6 | El sistema controlará un filtro de agua mediante un relay para activar o desactivar el sistema de filtrado. |
|  | 2.7 | El filtro operará en estado continuo, a excepción de los períodos de alimentación, durante los cuales se apagará. |
|  | 2.8 | El sistema verificará el estado del relay y notificará posibles fallos de activación del filtro. |
| Visualización | 3.1 | El sistema contará con un display LED para visualizar la temperatura actual del agua y estados básicos del sistema. |
|  | 3.2 | El display mostrará mensajes de alerta ante condiciones críticas o errores de sensores. |
| Almacenamiento | 4.1 | La configuración del sistema (horarios de alimentación, ciclos de iluminación y parámetros de temperatura) se persistirá en la memoria interna del microcontrolador. |
|  | 4.2 | El sistema recuperará automáticamente la configuración guardada al iniciar y validará su integridad. |
| Interfaz/App | 5.1 | Toda la interacción de usuario, notificaciones y alarmas podrá realizarse mediante una aplicación móvil conectada por BLE. |
|  | 5.2 | La aplicación permitirá configurar horarios de alimentación, ciclos de iluminación y umbrales de temperatura. |
|  | 5.3 | La aplicación móvil permitirá alternar entre el modo manual y el modo automático de operación. En el modo manual, la misma aplicación podrá activar o desactivar los actuadores. |
|  | 5.4 | El sistema enviará a la aplicación notificaciones de eventos normales y críticos (ej. ciclo de alimentación completado, sobretemperatura, fallo del sensor o error del relay). |

<p align="center"><em>Tabla 2.1: Requisitos del proyecto</em></p>

### **2.2 Casos de uso**

En las Tablas 2.2 a 2.7 se presentan 3 casos de uso para el sistema:

#### Caso de uso 1 — Alimentación automática

| Elemento | Definición |
|---|---|
| Disparador | El sistema detecta que se ha alcanzado el horario de alimentación configurado en la aplicación o recibe una orden de alimentación manual. |
| Precondiciones | El sistema está encendido. El servomotor de alimentación está conectado y funcional. El horario de alimentación está configurado y almacenado en memoria. |
| Flujo principal | El sistema entra en estado de alimentación. Desactiva temporalmente el filtro de agua para evitar dispersión del alimento. Espera un tiempo de estabilización del agua. Activa el servomotor para dispensar alimento durante un tiempo definido. Finalizada la acción, el sistema vuelve al estado normal y reactiva el filtro. Se notifica a la app la ejecución de la alimentación. |
| Flujos alternativos | a. El sistema está en estado de error: la alimentación no se ejecuta y se envía una notificación a la app. |

<p align="center"><em>Tabla 2.2: Control de alimentación</em></p>

---

#### Caso de uso 2 — Control de iluminación día/noche

| Elemento | Definición |
|---|---|
| Disparador | El sistema detecta un cambio de horario programado para el ciclo de iluminación. |
| Precondiciones | El sistema está encendido. La tira LED está conectada y funcional. Los horarios de encendido/apagado están configurados y almacenados en memoria. |
| Flujo principal | El sistema ajusta el estado de la iluminación según el ciclo configurado. Enciende o apaga la tira LED. Mantiene el estado hasta el próximo cambio programado. El estado de iluminación se actualiza en la app y en el display local. |
| Flujos alternativos | a. Falla en la tira LED: el sistema apaga la salida afectada y notifica error a la aplicación. |

<p align="center"><em>Tabla 2.3: Control de iluminación día/noche</em></p>

---

#### Caso de uso 3 — Control de filtrado de agua

| Elemento | Definición |
|---|---|
| Disparador | El sistema ejecuta el modo automático de mantenimiento o recibe una orden desde la aplicación para activar/desactivar el filtro. |
| Precondiciones | El sistema está encendido. El relay del filtro está conectado y funcional. El estado del filtro está definido en la configuración del sistema. |
| Flujo principal | El sistema activa el relay para encender el filtro de agua durante el funcionamiento normal. En caso de rutina de alimentación, el sistema desactiva temporalmente el filtro y lo reactiva una vez finalizado el ciclo. El estado del filtro se reporta a la aplicación y al display. |
| Flujos alternativos | a. Fallo del relay o ausencia de respuesta del filtro: el sistema desactiva el control automático del filtro y notifica la falla a la aplicación. |

<p align="center"><em>Tabla 2.4: Control de filtrado de agua</em></p>

---

#### Caso de uso 4 — Monitoreo de temperatura y alarma

| Elemento | Definición |
|---|---|
| Disparador | El sensor de temperatura detecta un valor fuera de los límites configurados por el usuario. |
| Precondiciones | El sistema está encendido. El sensor de temperatura está conectado y funcionando correctamente. Los umbrales de temperatura mínima y máxima están configurados en el sistema. |
| Flujo principal | El sistema monitorea continuamente la temperatura del agua. Cuando la temperatura supera el umbral máximo o desciende por debajo del mínimo permitido, el sistema activa una alarma sonora y visual, además de enviar una notificación a la aplicación móvil. La alarma permanece activa hasta que la temperatura vuelve a encontrarse dentro de los valores normales configurados. Una vez restablecida la temperatura, el sistema desactiva automáticamente la alarma y actualiza el estado en la aplicación y el display. |
| Flujos alternativos | a. Fallo del sensor de temperatura: el sistema informa la falla en el display y la aplicación móvil, deshabilitando el monitoreo automático hasta que el sensor vuelva a estar disponible. |

<p align="center"><em>Tabla 2.5:  Monitoreo de temperatura y alarma</em></p>

---

#### Caso de uso 5 — Configuración de parámetros desde la aplicación móvil

| Elemento | Definición |
|---|---|
| Disparador | El usuario accede a la aplicación móvil y modifica parámetros de configuración del sistema. |
| Precondiciones | El sistema está encendido y conectado a la aplicación móvil. El usuario tiene acceso autorizado a la configuración. |
| Flujo principal | El usuario modifica parámetros como horarios de alimentación, duración de ciclos de iluminación, límites de temperatura o tiempos de filtrado desde la aplicación móvil. El sistema almacena los nuevos parámetros en memoria no volátil y notifica al usuario que es necesario reiniciar el sistema para aplicar los cambios realizados. |
| Flujos alternativos | a. Error de comunicación entre la aplicación y el sistema: la configuración no se guarda y se informa el fallo al usuario. |

<p align="center"><em>Tabla 2.6: Configuración de parámetros</em></p>

---

#### Caso de uso 6 — Control manual de actuadores desde la aplicación móvil

| Elemento | Definición |
|---|---|
| Disparador | El usuario selecciona manualmente un actuador desde la aplicación móvil. |
| Precondiciones | El sistema está encendido y conectado a la aplicación móvil. Los actuadores están correctamente conectados y funcionales. |
| Flujo principal | El usuario activa o desactiva manualmente actuadores del sistema, tales como iluminación, filtro o alimentador, mediante la aplicación móvil. El sistema recibe la orden, ejecuta la acción correspondiente y actualiza el estado del actuador tanto en la aplicación como en el display local. |
| Flujos alternativos | a. Fallo de comunicación con la aplicación móvil: la orden no se ejecuta y el sistema informa el error al usuario.  
| | b. El actuador solicitado ya se encuentra en el estado pedido y no se realiza ninguna acción.|

<p align="center"><em>Tabla 2.7: Control manual de actuadores</em></p>
