<img width="522" height="162" alt="image" src="https://github.com/user-attachments/assets/1a63da53-a31b-4383-afba-4dbaffcf9bfb" />

**UNIVERSIDAD DE BUENOS AIRES**  
**Facultad de Ingeniería**  
**TA134 - Taller de Sistemas Embebidos**

Memoria del Trabajo Final:

***Nombre del proyecto se propondrá una vez este esté más avanzado.***

**Autores:**

**Lautaro Gaston Fritz** **\- 102320**

**Mauro Alex Tedesco** **\- 102958**

**José Francisco López García** **\- n20240046**

*Este trabajo fue realizado en las Ciudad Autónoma de Buenos Aires,*   
*entre marzo y agosto del 2026\.*

# RESUMEN

El objetivo del presente proyecto es diseñar e implementar un sistema embebido de automatización y monitoreo para peceras domésticas. El sistema busca automatizar determinadas tareas de cuidado, atención y operación de la pecera, como el control del sistema de filtrado y la coordinación de ciclos de alimentación, permitiendo además la configuración manual de parámetros de funcionamiento. 

# Índice General

[Registro de versiones](#registro-de-versiones)

[Introducción general](#introducción-general)

- [Presentación del proyecto](#presentación-del-proyecto)

[Introducción Específica](#introducción-específica)

- [Requisitos](#requisitos)

- [Casos de uso](#casos-de-uso)

- [Hardware utilizado](#hardware-utilizado)

  - [Placa NUCLEO-F103RB](#2.3.1-placa-nucleo-f103rb)

  - [Servomotor SG90](#2.3.2-servomotor-sg90)

  - [Relé](#2.3.3-relé)

  - [Pantalla LCD 16×2](#2.3.4-pantalla-lcd-16×2)

  - [Sensor Digital Temperatura Ds18b20](#2.3.5-sensor-digital-temperatura-ds18b20)

  - [Aro De Luz Led](#2.3.6-aro-de-luz-led)

  - [Foco de Corriente Alterna](#2.3.7-foco-de-corriente-alterna)

  - [Módulo Bluetooth HM-10](#2.3.8-módulo-bluetooth-hm-10)

  - [Buzzer TMB12A05](#2.3.7-buzzer-tmb12a05)

  - [LED Rojo](#2.3.8-led-rojo)

- [Software Utilizado](#2.4-software-utilizado)

  - [Entorno de desarrollo placa NUCLEO](#2.4.1-entorno-de-desarrollo-placa-nucleo)

  - [Entorno de desarrollo módulo BLT HM-10](#2.4.2-entorno-de-desarrollo-módulo-blt-hm-10)

[Diseño e implementación](#diseño-e-implementación)

- [Hardware del sistema](#3.1-hardware-del-sistema)

  - [Dispensador de alimento](#3.1.1-dispensador-de-alimento)

  - [Luces LED para el ciclo día y noche](#3.1.2-luces-led-para-el-ciclo-día-y-noche)

  - [Filtrado de agua](#3.1.3-filtrado-de-agua)

- [Firmware del sistema](#3.2-firmware-del-sistema)

  - [Lógica y estructura](#3.2.1-lógica-y-estructura)

  - [Módulo de generación de señales PWM](#3.2.x-módulo-de-generación-de-señales-pwm)

  - [Módulo de medición de temperatura](#3.2.x-módulo-de-medición-de-temperatura)

  - [Módulo de comunicación Bluetooth](#3.2.x-módulo-de-comunicación-bluetooth)

  - [Módulo de visualización mediante display LCD](#3.2.x-módulo-de-visualización-mediante-display-lcd)

  - [Módulo de actuadores y alarmas](#3.2.x-módulo-de-actuadores-y-alarmas)

[Ensayos y resultados](#ensayos-y-resultados)

- [Pruebas funcionales del hardware](#4.1-pruebas-funcionales-del-hardware)

- [Pruebas de sensor con interfaz del usuario](#4.1.1-pruebas-de-sensor-con-interfaz-del-usuario)

- [Capturas de control temperatura](#capturas-de-control-temperatura)

- [Pruebas funcionales del firmware](#4.2-pruebas-funcionales-del-firmware)

- [Pruebas de integración](#4.3-pruebas-de-integración)

- [Cumplimiento de requisitos](#4.4-cumplimiento-de-requisitos)

[Conclusiones](#conclusiones)

- [Resultados obtenidos](#5.1-resultados-obtenidos)

[Próximos pasos](#5.2-próximos-pasos)

[Bibliografía](#bibliografía)

# Registro de versiones

| Revisión | Cambios realizados | Fecha |
| :---- | :---- | :---- |
| **1.0** | Creación del documento | 10/7/2026 |
| **1.1** | Cambio a formato markdown | 11/7/2026 |
| **1.2** |  |  |

# CAPÍTULO 1 

# Introducción general

## Presentación del proyecto

**Figura 1.1:** Diagrama bloques general del sistema.

# CAPÍTULO 2

# Introducción Específica

## 2.1 Requisitos

| Grupo | ID | Descripción |
| :---- | :---- | :---- |
| **Sensores ambientales** | **1.1** | El sistema contará con un sensor de temperatura sumergible para monitorear la temperatura del agua del tanque. |
|  | **1.2** | El sistema realizará mediciones periódicas de la temperatura del agua. |
|  | **1.3** | El sistema generará una alarma cuando la temperatura se encuentre fuera de los límites configurados. |
| **Actuadores – Alimentación** | **2.1** | El sistema contará con un servomotor encargado de accionar el mecanismo de alimentación automática. |
|  | **2.2** | El sistema dispensará alimento automáticamente en los horarios configurados por el usuario. |
|  | **2.3** | El usuario podrá iniciar manualmente un ciclo de alimentación desde la aplicación móvil. |
| **Actuadores – Iluminación** | **2.4** | El sistema contará con luces LED para simular los ciclos de día y noche del tanque. |
|  | **2.5** | El sistema permitirá configurar los horarios de encendido y apagado de la iluminación para establecer ciclos automáticos. |
| **Actuadores – Carga de CA** | **2.6** | El sistema controlará una carga de corriente alterna que simulará el funcionamiento del filtro de agua; en el prototipo se utilizará un foco de CA como carga. |
|  | **2.7** | La carga de corriente alterna permanecerá activada durante el funcionamiento normal y se desactivará temporalmente durante el ciclo de alimentación. |
|  | **2.8** | El sistema verificará el estado del relé y notificará posibles fallos en su accionamiento. |
| **Sistema de alarmas** | **3.1** | El sistema contará con un buzzer para emitir una alarma auditiva cuando se detecte una condición crítica. |
|  | **3.2** | El sistema contará con un LED rojo para indicar visualmente el estado de alarma. |
| **Visualización** | **4.1** | El sistema contará con un display LED para visualizar la temperatura actual del agua del tanque. |
| **Almacenamiento** | **5.1** | El sistema almacenará en la memoria no volátil del microcontrolador la configuración de horarios de alimentación, ciclos de iluminación y límites de temperatura. |
|  | **5.2** | El sistema recuperará automáticamente la configuración almacenada al iniciar su funcionamiento y verificará su integridad. |
| **Interfaz móvil** | **6.1** | El sistema permitirá la interacción del usuario mediante una aplicación móvil conectada a través de Bluetooth Low Energy (BLE). |
|  | **6.2** | La aplicación permitirá configurar los horarios de alimentación, los ciclos de iluminación y los límites de temperatura. |
|  | **6.3** | La aplicación permitirá seleccionar entre el modo manual y el modo automático de funcionamiento. En el modo manual será posible controlar directamente los actuadores. |
|  | **6.4** | El sistema enviará notificaciones a la aplicación sobre eventos de funcionamiento y condiciones de alarma. |
| **Alimentación eléctrica** | **7.1** | El sistema utilizará una fuente de alimentación de corriente continua independiente para suministrar energía a los actuadores, reduciendo la demanda de corriente sobre el microcontrolador. |
|  | **7.2** | El microcontrolador y los actuadores compartirán una referencia común de tierra (GND) para garantizar el correcto funcionamiento del sistema. |

**Tabla 2.1:** requerimientos iniciales del proyecto

## 2.2 Casos de uso

| Elemento | Definición |
| :---- | :---- |
| **Disparador** | El sistema detecta que se ha alcanzado el horario de alimentación configurado o recibe una orden de alimentación manual desde la aplicación móvil. |
| **Precondiciones** | El sistema está encendido. El servomotor de alimentación funciona correctamente y los horarios de alimentación se encuentran configurados y almacenados. |
| **Flujo principal** | El sistema inicia el ciclo de alimentación. Desactiva temporalmente el filtro de agua para evitar la dispersión del alimento, espera el tiempo establecido y acciona el servomotor para dispensar la cantidad programada. Finalizado el ciclo, reactiva el filtro de agua y notifica la ejecución de la alimentación a la aplicación móvil. |
| **Flujos alternativos** | a. Si el sistema presenta un estado de error, el ciclo de alimentación no se ejecuta y se notifica la condición a la aplicación. |

**Tabla 2.2:** Caso de uso 1: alimentación automática

| Elemento | Definición |
| :---- | :---- |
| **Disparador** | El sistema detecta un cambio de horario correspondiente al ciclo de iluminación programado. |
| **Precondiciones** | El sistema está encendido. La iluminación LED funciona correctamente y los horarios de encendido y apagado están configurados. |
| **Flujo principal** | El sistema enciende o apaga la iluminación según el horario establecido y mantiene dicho estado hasta el siguiente cambio programado. El nuevo estado se informa a la aplicación móvil. |
| **Flujos alternativos** | a. Si ocurre un fallo en la iluminación, el sistema desactiva la salida correspondiente y notifica la condición a la aplicación. |

**Tabla 2.3:** Caso de uso 2: control de iluminación día/noche

| Elemento | Definición |
| :---- | :---- |
| **Disparador** | El sistema ejecuta el funcionamiento normal o recibe una orden desde la aplicación para activar o desactivar el sistema de filtrado. |
| **Precondiciones** | El sistema está encendido. El relé encargado del filtro de agua funciona correctamente y el estado del filtrado está definido en la configuración. |
| **Flujo principal** | El sistema mantiene el filtro de agua en funcionamiento durante la operación normal. Cuando se inicia un ciclo de alimentación, el sistema desactiva temporalmente el filtro para evitar la dispersión del alimento y lo reactiva automáticamente al finalizar la alimentación. El estado del filtro se informa a la aplicación móvil. |
| **Flujos alternativos** | a. Si se detecta un fallo en el accionamiento del relé, el sistema deshabilita el control automático del filtro y notifica la falla a la aplicación. |

**Tabla 2.4:** Caso de uso 3: control del sistema de filtrado

| Elemento | Definición |
| :---- | :---- |
| **Disparador** | El sensor detecta una temperatura fuera de los límites configurados por el usuario. |
| **Precondiciones** | El sistema está encendido. El sensor de temperatura funciona correctamente y los límites de temperatura se encuentran configurados. |
| **Flujo principal** | El sistema monitorea continuamente la temperatura del agua. Cuando la temperatura supera el límite máximo o desciende por debajo del mínimo permitido, activa una alarma sonora mediante un buzzer y una alarma visual mediante un LED rojo, además de enviar una notificación a la aplicación móvil. Cuando la temperatura vuelve al rango permitido, las alarmas se desactivan automáticamente. |
| **Flujos alternativos** | a. Si ocurre un fallo en el sensor de temperatura, el sistema informa la condición a la aplicación móvil y suspende el monitoreo automático hasta que el sensor vuelva a estar disponible. |

**Tabla 2.5:** Caso de uso 4: Monitoreo de temperatura y alarma

| Elemento | Definición |
| :---- | :---- |
| **Disparador** | El usuario selecciona un actuador desde la aplicación móvil. |
| **Precondiciones** | El sistema está encendido, conectado mediante BLE y los actuadores funcionan correctamente. |
| **Flujo principal** | El usuario controla manualmente el alimentador automático, la iluminación o el filtro de agua desde la aplicación móvil. El sistema ejecuta la acción solicitada y actualiza el estado correspondiente en la aplicación. |
| **Flujos alternativos** | a. Si ocurre un fallo en la comunicación BLE, la orden no se ejecuta y el sistema informa el error al usuario. |
|  | b. Si el actuador seleccionado ya se encuentra en el estado solicitado, el sistema no realiza ninguna acción. |

**Tabla 2.6:** Caso de uso 5: configuración de parámetros

| Elemento | Definición |
| :---- | :---- |
| **Disparador** | El usuario selecciona un actuador desde la aplicación móvil. |
| **Precondiciones** | El sistema está encendido, conectado mediante BLE y los actuadores funcionan correctamente. |
| **Flujo principal** | El usuario controla manualmente el alimentador automático, la iluminación o el filtro de agua desde la aplicación móvil. El sistema ejecuta la acción solicitada y actualiza el estado correspondiente en la aplicación. |
| **Flujos alternativos** | a. Si ocurre un fallo en la comunicación BLE, la orden no se ejecuta y el sistema informa el error al usuario. |
|  | b. Si el actuador seleccionado ya se encuentra en el estado solicitado, el sistema no realiza ninguna acción. |

**Tabla 2.7:** Caso de uso 6: control manual de actuadores

## 2.3 Hardware utilizado

En esta sección se presenta una descripción de los diferentes componentes de hardware empleados en el desarrollo del proyecto.

### 2.3.1 Placa NUCLEO-F103RB

Esta placa integra un microcontrolador **STM32F103RB,** basado en la arquitectura ARM Cortex-M3, el cual fue utilizado para ejecutar la lógica de control del sistema, gestionar la adquisición de datos de los sensores y controlar los actuadores implementados en el prototipo. La elección de esta plataforma se debe a que fue la utilizada durante el curso de Sistemas Embebidos, contexto en el que se desarrolló este proyecto, lo que permitió aprovechar la experiencia previa adquirida y reducir el tiempo de implementación.

Además, la NUCLEO-F103RB dispone de diversos periféricos, entre ellos entradas y salidas digitales, temporizadores, convertidores analógico-digitales e interfaces de comunicación como UART, SPI e I²C, los cuales facilitaron la integración de los diferentes módulos del sistema. Para el desarrollo del software se empleó el lenguaje **C**, haciendo uso de las herramientas proporcionadas para la familia de microcontroladores STM32.

<img width="420" height="457" alt="image" src="https://github.com/user-attachments/assets/a5abb9af-09ba-4cf9-8bc8-1775c76e1b82" />

**Figura 2.1:** Placa de desarrollo NUCLEO-F103RB.

https://www.st.com/resource/en/datasheet/stm32f103cb.pdf

### 2.3.2 Servomotor SG90

El servomotor SG90 fue seleccionado como el actuador encargado de accionar el mecanismo de alimentación automática del prototipo. Su función consiste en generar el movimiento necesario para abrir el dispensador de alimento, permitiendo la caída de una cantidad controlada de comida hacia la pecera. Una vez finalizada la alimentación, el servomotor retorna a su posición inicial, cerrando nuevamente el mecanismo y evitando la liberación involuntaria de alimento.

La elección de este servomotor se debe a que ofrece un control preciso de la posición angular, característica indispensable para garantizar una dosificación repetible y confiable en cada ciclo de alimentación. Además, presenta un tamaño compacto, bajo costo y un consumo reducido, lo que facilita su integración al sistema desarrollado.

El servomotor recibe la señal de control generada por la placa NUCLEO-F103RB mediante una modulación por ancho de pulso (PWM), mientras que su alimentación eléctrica se realiza de forma independiente mediante una fuente lineal externa. Esta configuración evita sobrecargar la alimentación de la placa de desarrollo y garantiza el funcionamiento estable del actuador durante la operación del sistema.

<img width="482" height="342" alt="image" src="https://github.com/user-attachments/assets/13dceca0-43aa-4ca3-9a49-91fc9fa42c79" />

**Figura 2.2:** Servomotor SG90

https://www.todomicro.com.ar/servomotores/279-servomotor-tower-pro-sg90-9g.html

### 2.3.3 Relé

El relé fue incorporado al sistema para controlar la alimentación de una carga de 220V en corriente alterna (CA), representada en el prototipo mediante un foco que simula el funcionamiento del filtro de agua de la pecera. Debido a que este tipo de carga no puede ser accionada directamente por la placa NUCLEO-F103RB, el relé actúa como una interfaz de potencia que permite conmutar su alimentación a partir de una señal de control proveniente del microcontrolador.

El relé recibe la señal de activación desde una salida digital de la placa NUCLEO-F103RB, mientras que su circuito de accionamiento se alimenta mediante una fuente lineal externa y el circuito de potencia se conecta directamente a la línea de 220V CA. De esta manera, es posible encender o apagar el foco, el cual representa el funcionamiento del filtro de agua, manteniendo el aislamiento entre el circuito de control de baja tensión y la carga de corriente alterna.

La utilización de este componente permite validar el funcionamiento de la etapa de control y potencia del sistema sin necesidad de conectar el filtro real, mejorando la seguridad durante las pruebas y la confiabilidad del prototipo.

<img width="366" height="276" alt="image" src="https://github.com/user-attachments/assets/e50c0258-41f9-4b3f-92dc-924bd32f7c3e" />

**Figura 2.3:** Relé

https://www.todomicro.com.ar/reles/342-modulo-relay-rele-de-1-canal-con-entrada-ttl.html

### 2.3.4 Pantalla LCD 16×2

El display LCD 16×2 con módulo I²C utilizado en el proyecto desempeña un papel fundamental al proporcionar una interfaz visual para la presentación de datos. Con una capacidad de mostrar 16 caracteres distribuidos en 2 líneas, este módulo se emplea para presentar de forma clara y legible la información relevante para el usuario. 

En particular, el display LCD 16×2 en este proyecto se utiliza para mostrar la temperatura medida por el sistema, permitiendo al usuario monitorear de manera sencilla esta variable durante el funcionamiento del prototipo. La información visualizada es enviada por la placa NUCLEO-F103RB, mientras que el módulo es alimentado con una tensión de 5V.

El mismo se presenta en la **Figura 2.4**.

<img width="320" height="352" alt="image" src="https://github.com/user-attachments/assets/58f369ea-98c3-47ec-995b-4876bc4256ad" />

**Figura 2.4:** Pantalla LCD 16×2

(link)

### **2.3.5 Sensor Digital Temperatura Ds18b20**

El sensor digital de temperatura DS18B20 sumergible fue incorporado al sistema para realizar la medición de la temperatura del agua de la pecera. Este sensor permite obtener lecturas precisas de la temperatura y transmitir dicha información al sistema para su procesamiento. 

En este proyecto, el sensor DS18B20 mide continuamente la temperatura del agua y envía la información a la placa NUCLEO-F103RB, donde los datos son procesados para posteriormente ser visualizados en el display LCD. De esta manera, el usuario puede monitorear la temperatura del agua en tiempo real y verificar el correcto funcionamiento del sistema.

<img width="521" height="335" alt="image" src="https://github.com/user-attachments/assets/6e0bbcd8-8ffd-4c85-9db8-04fb605f3474" />

**Figura 2.5:** Sensor Digital Temperatura Ds18b20

https://www.alldatasheet.com/datasheet-pdf/view/58557/DALLAS/DS18B20.html

### 2.3.6 Aro De Luz Led

El aro de luz LED fue incorporado al sistema para simular el ciclo de iluminación de la pecera, representando los periodos de día y noche durante el funcionamiento del prototipo. 

El aro de luz LED recibe la señal de activación desde la placa NUCLEO-F103RB, mientras que su alimentación se realiza mediante una fuente de corriente continua (CC) externa. De esta manera, es posible controlar su encendido y apagado de forma automática de acuerdo con la lógica implementada en el sistema, simulando el ciclo diario de iluminación de la pecera.

**Figura 2.6:** Aro De Luz Led

### 2.3.7 Foco de Corriente Alterna

El foco de corriente alterna fue incorporado al prototipo como una carga representativa del filtro de agua de la pecera. Su función es simular el funcionamiento del filtro durante las pruebas, permitiendo verificar el correcto accionamiento del relé y de la etapa de potencia implementada en el sistema. 

<img width="300" height="237" alt="image" src="https://github.com/user-attachments/assets/384b219c-a3de-4f04-9e6a-aba5f017217d" />

**Figura 2.7:** Foco de corriente alterna 

### 2.3.8 Módulo Bluetooth HM-10

En el trabajo realizado se empleó el módulo Bluetooth HM-10, el cual se muestra en la **Figura 2.7**. Este módulo permite establecer una comunicación inalámbrica entre la placa NUCLEO-F103RB y un dispositivo móvil, posibilitando el monitoreo del sistema y el envío de comandos de control.

Mediante esta comunicación es posible visualizar si la temperatura medida salió de los valores normales, conocer el estado de funcionamiento del prototipo y controlar el encendido y apagado del filtro y del alimentador. Asimismo, permite seleccionar el modo de operación manual o automático. 

<img width="301" height="237" alt="image" src="https://github.com/user-attachments/assets/b71bef09-e8ea-4f14-800c-016f424d4391" />

**Figura 2.8:** Módulo Bluetooth HM-10

https://www.alldatasheet.com/html-pdf/1179058/ETC1/HM-10/341/3/HM-10.html 

### 2.3.7 Buzzer TMB12A05

El buzzer fue incorporado al sistema como un dispositivo de alerta audible, cuya función es emitir una señal sonora cuando el sistema detecta una condición de alarma. De esta manera, proporciona una indicación inmediata al usuario sobre la presencia de un evento que requiere atención.

En este proyecto, el buzzer es accionado por la placa NUCLEO-F103RB y se activa cuando la temperatura del agua supera los límites establecidos o cuando el sistema entra en estado de alarma.

<img width="270" height="221" alt="image" src="https://github.com/user-attachments/assets/bbe50405-10ba-49e1-8acd-7a5f0181c984" />

**Figura 2.8:** Buzzer TMB12A05 

https://www.quick-teck.co.uk/Management/EEUploadFile/1420788438.pdf

### 2.3.8 LED Rojo

El LED rojo fue incorporado al sistema como un dispositivo de alerta visual, cuya función es indicar de manera inmediata cuando el sistema detecta una condición de alarma. De esta forma, proporciona al usuario una señal luminosa que permite identificar rápidamente la presencia de una condición anómala.

<img width="167" height="212" alt="image" src="https://github.com/user-attachments/assets/3cc99bba-c770-4307-bfd0-c964b754023a" />

**Figura 2.8:** Led rojo 

## 2.4 Software Utilizado

En esta sección se describen los diferentes componentes de software empleados para el desarrollo del proyecto.

### 2.4.1 Entorno de desarrollo placa NUCLEO

La plataforma de desarrollo NUCLEO-F103RB, basada en el microcontrolador STM32F103RB, se integra con el entorno de desarrollo STM32CubeIDE. Este entorno proporciona un conjunto de herramientas específicamente diseñadas para el desarrollo de aplicaciones embebidas sobre microcontroladores ARM Cortex-M, ofreciendo una plataforma eficiente para el diseño, compilación, depuración y programación de aplicaciones.

El desarrollo del software se realizó utilizando este entorno de desarrollo, el cual incorpora un editor de código, un compilador y herramientas de depuración que facilitan el proceso de programación y verificación de las aplicaciones. Una vez compilado, el código fuente es traducido a lenguaje máquina y programado en la memoria del microcontrolador, permitiendo que las instrucciones desarrolladas se ejecuten y se conviertan en acciones sobre los periféricos y dispositivos conectados al sistema. Para este proyecto, el desarrollo se realizó empleando el lenguaje de programación C

### 2.4.2 Entorno de desarrollo módulo BLT HM-10

El HM-10 incorpora un microcontrolador interno con un firmware encargado de implementar el stack Bluetooth Low Energy (BLE). Cuando recibe datos mediante la interfaz UART, el firmware los procesa, los encapsula en paquetes BLE y los transmite de forma inalámbrica. En sentido inverso, al recibir paquetes BLE, el módulo los interpreta, extrae la información útil y la envía a través de la interfaz UART hacia el microcontrolador principal. De esta manera, el HM-10 funciona como un puente entre la comunicación serie UART y Bluetooth Low Energy, permitiendo la comunicación inalámbrica sin que el microcontrolador tenga que gestionar directamente la complejidad del protocolo Bluetooth. 

# CAPÍTULO 3

# Diseño e implementación

## 3.1 Hardware del sistema

En esta sección se describen las principales características del hardware empleado en el desarrollo del sistema. Asimismo, en la **Figura 3.1** se presenta un diagrama en bloques que muestra la arquitectura general y la interconexión de los diferentes componentes que conforman el prototipo.

<img width="747" height="472" alt="image" src="https://github.com/user-attachments/assets/73a96c61-2fb7-44b4-a691-9fe6f7796cd3" />

**Figura 3.1:** Diagrama en bloques de los componentes de hardware del sistema.

**Figura 3.2:** Diagrama de conexiones de los componentes hardware

| Módulo Bluetooth HM-10 | Conexión |
| :---- | :---- |
| TXD | RX NUCLEO Board pin (D0) |
| RXD | TX NUCLEO Board pin (D1) |
| VCC | Fuente externa de 5V |
| GND | GND común |

Se utiliza una resistencia *pull-up* para garantizar el correcto funcionamiento de la comunicación del módulo Bluetooth HM-10. 

**Tabla 3.1:** Resumen de conexiones del módulo Bluetooth HM-10. 

| Buzzer y LED de alarma | Conexión |
| :---- | :---- |
| Entrada de control | NUCLEO Board pin (D8) |
| VCC | Fuente externa de 5V |
| GND | GND común |

La etapa de control utiliza un transistor (2n2222 NPN) y una resistencia de base para el correcto accionamiento del dispositivo. 

**Tabla 3.2:** Resumen de conexiones del buzzer y LED de alarma. 

| Servomotor SG90 | Conexión |
| :---- | :---- |
| Señal PWM | NUCLEO Board pin (D4) |
| VCC | Fuente externa de 5V |
| GND | GND común |

La línea de control incorpora una resistencia *pull-up* para garantizar el correcto funcionamiento de la señal PWM del servomotor, mientras que la alimentación se realiza mediante una fuente externa de 5V para evitar incrementar la demanda de corriente sobre la placa NUCLEO-F103RB. 

**Tabla 3.3:** Resumen de conexiones del servomotor SG90. 

| Módulo relé | Conexión |
| :---- | :---- |
| Entrada de control (IN) | NUCLEO Board pin (D5) |
| VCC | Fuente externa de 5V |
| GND | GND común |
| COM | Línea de alimentación de 220V CA |
| NO | Foco de corriente alterna (simulación del filtro de agua) |

La etapa de control utiliza un transistor (2n2222 NPN) y una resistencia de base para el correcto accionamiento del dispositivo. 

**Tabla 3.4:** Resumen de conexiones del módulo relé. 

| Aro LED | Conexión |
| :---- | :---- |
| Entrada de control | NUCLEO Board pin (D10)  |
| VCC | Fuente externa de 5V |
| GND | GND común |

La etapa de control incorpora un transistor 2N2222 y una resistencia de base para el correcto accionamiento del aro LED. Además, su alimentación se realiza mediante una fuente externa de 5V para evitar incrementar la demanda de corriente sobre la placa NUCLEO-F103RB.

**Tabla 3.5:** Resumen de conexiones de luces LEDs.  

| Termómetro DS1820 | Conexión |
| :---- | :---- |
| Entrada de control | NUCLEO Board pin (D7)  |
| VCC | Fuente externa de 5V |
| GND | GND común |

Se utiliza una resistencia *pull-up* para garantizar el correcto funcionamiento de la comunicación del termómetro DS1820.

**Tabla 3.6:** Resumen de conexiones del termómetro DS1820.

| Display LCD I2C | Conexión |
| :---- | :---- |
| SCL | NUCLEO Board pin (D14)  \- Línea de reloj de comunicación I2C |
| SDA | NUCLEO Board pin (D15)  \- Línea de datos de comunicación I2C |
| VCC | Fuente de 5V |
| GND | GND común |

El display LCD utiliza la interfaz de comunicación I2C mediante las líneas SDA y SCL, permitiendo la transmisión de datos y sincronización con la NUCLEO-F103RB utilizando únicamente dos señales de comunicación. La alimentación del módulo se realiza mediante una fuente de 5V con referencia común de GND.

**Tabla 3.7:** Resumen de conexiones del display LCD mediante interfaz I2C. 

**Figura 3.3:** del prototipo

**Tabla 3.8:** Resumen de los costos de cada componente y el total

### 3.1.1 Dispensador de alimento

En esta subsección se describe el dispensador de alimento implementado en el sistema. La **Figura 3.X** presenta una vista del mecanismo desarrollado para el prototipo. El dispensador está constituido por una tolva destinada al almacenamiento del alimento y una compuerta ubicada en su parte inferior, la cual regula la salida del alimento hacia la pecera.

El funcionamiento del mecanismo se basa en el accionamiento de un servomotor SG90, encargado de abrir y cerrar la compuerta de la tolva. La cantidad de alimento dispensada puede regularse modificando el tiempo durante el cual la compuerta permanece abierta o el ángulo de apertura alcanzado por el servomotor, permitiendo obtener una dosificación más precisa y adaptada a las necesidades del sistema.

El servomotor recibe la señal de control PWM generada por la placa NUCLEO-F103RB, mientras que su alimentación se realiza mediante una fuente externa de corriente continua (CC), evitando sobrecargar la alimentación de la placa de desarrollo y garantizando un funcionamiento estable del actuador.

Asimismo, el sistema supervisa el estado de operación del mecanismo de alimentación. En caso de detectarse una condición de falla del actuador o una situación de error definida por la lógica de control, el proceso de alimentación es suspendido y el sistema pasa al estado de alarma correspondiente, notificando la condición al usuario.

Figura 3.X: Se muestra el apartado de dispensador de alimento. 

### 3.1.2 Luces LED para el ciclo día y noche

En esta subsección se describe el sistema de iluminación implementado en el prototipo. La Figura 3.X presenta el aro de luz LED utilizado para simular el ciclo de día y noche de la pecera. Este dispositivo permite proporcionar una iluminación artificial en aquellos casos en que el acuario se encuentre en ambientes con escasa o nula iluminación natural.

El aro LED es controlado por la placa NUCLEO-F103RB, la cual genera señales PWM de encendido y apagado de acuerdo con la lógica implementada en el sistema. Además, estas pueden operarse mediante órdenes enviadas por el usuario desde la aplicación móvil vía Bluetooth. De esta manera, es posible operar tanto en modo automático, respetando los horarios programados, como en modo manual. 

La alimentación del aro LED se realiza mediante una fuente externa de corriente continua (CC), evitando incrementar la demanda de corriente sobre la placa de desarrollo. Asimismo, la señal proveniente del microcontrolador acciona un transistor de conmutación, el cual actúa como interfaz de potencia para controlar el encendido y apagado del aro LED de forma segura y confiable.

### 3.1.3 Filtrado de agua

En esta subsección se describe el sistema de filtrado implementado en el prototipo. Debido a que la mayoría de los filtros comerciales para acuarios operan con corriente alterna (CA), se decidió representar su funcionamiento mediante un foco de corriente alterna, el cual actúa como una carga equivalente durante las pruebas. De esta manera, es posible validar el funcionamiento de la etapa de control y potencia sin necesidad de utilizar un filtro real.

El encendido y apagado de la carga se realiza mediante un módulo relé, el cual recibe la señal de control generada por la placa NUCLEO-F103RB. La etapa de accionamiento del relé incorpora un transistor y los elementos de protección necesarios para permitir el control seguro de la carga de corriente alterna desde una salida digital del microcontrolador.

Durante el funcionamiento normal, el sistema mantiene activo el filtrado del agua. Sin embargo, cuando se inicia un ciclo de alimentación, el microcontrolador desactiva temporalmente el relé para apagar el filtro, evitando que el movimiento del agua disperse el alimento antes de que los peces puedan consumirlo. Finalizada la alimentación, el sistema reactiva automáticamente el filtrado, restableciendo las condiciones normales de operación.

## 3.2 Firmware del sistema

En esta sección se describen las principales características del firmware implementado en el sistema. Asimismo, se presenta la estructura lógica del software, basada en una arquitectura modular que divide el funcionamiento del sistema en diferentes módulos encargados de la gestión de los sensores, actuadores, comunicaciones y demás funciones implementadas en el prototipo. 

### 3.2.1 Lógica y estructura

### 3.2.2 Módulo de generación de señales PWM

El módulo de generación de señales PWM fue implementado mediante una máquina de estados desarrollada en el archivo `task_pwm.c` y definida en `task_pwm_attribute.h`. Este módulo permite controlar la potencia aplicada a los actuadores del sistema, como el servomotor y la iluminación de los LEDs, mediante la variación del ciclo de trabajo de una señal PWM generada por los temporizadores del microcontrolador.

La estructura del módulo permite establecer un valor mínimo, un valor máximo, el valor actual de la señal PWM (`current_value`) y el valor objetivo (`target_value`) al cual debe llegar el actuador. De esta manera, el sistema puede realizar transiciones progresivas entre diferentes niveles de funcionamiento, evitando cambios bruscos en la señal aplicada.

La máquina de estados está compuesta por tres estados principales: `ST_PWM_OFF`, `ST_PWM_ON` y `ST_PWM_MOVING`. En el estado `ST_PWM_OFF`, el actuador permanece desactivado hasta recibir el evento correspondiente de activación. Cuando se genera el evento `EV_PWM_ON`, el módulo establece el nuevo valor objetivo mediante `target_value` y cambia al estado `ST_PWM_MOVING` para iniciar la transición progresiva.

Durante el estado `ST_PWM_MOVING`, el valor actual de PWM (`current_value`) se incrementa o disminuye gradualmente hasta alcanzar el valor objetivo establecido. Este proceso permite realizar un arranque o una parada suave del actuador. Una vez alcanzado el valor deseado, el módulo cambia al estado correspondiente, `ST_PWM_ON` o `ST_PWM_OFF`.

En el estado `ST_PWM_ON`, el actuador mantiene el valor máximo configurado hasta recibir el evento de apagado `EV_PWM_OFF`. Al producirse dicho evento, se establece nuevamente el valor mínimo como objetivo y el módulo retorna al estado `ST_PWM_MOVING` para realizar una disminución progresiva de la señal PWM.

La actualización de la señal hacia el hardware se realiza mediante la configuración del registro de comparación del temporizador del microcontrolador, utilizando la función `pwm_update()` para actualizar el canal PWM correspondiente. Según el identificador del módulo (`id`), la señal generada es enviada al servomotor o al sistema de iluminación LED, permitiendo controlar su funcionamiento mediante la variación del ciclo de trabajo.

### 3.2.3 Módulo de medición de temperatura

El módulo de medición de temperatura fue implementado mediante una máquina de estados no bloqueante desarrollada en el archivo `task_thermometer.c` y definida en `task_thermometer_attribute.h`. Esta arquitectura permite gestionar el sensor `DS18B20` mediante el protocolo `OneWire` sin detener la ejecución del resto del sistema, debido al tiempo de conversión requerido por el sensor, que puede alcanzar los 750 ms.

La máquina de estados está compuesta por tres estados principales: `ST_THERM_IDLE`, `ST_THERM_WAITING_CONVERSION` y `ST_THERM_WAITING_READ`. En el estado inicial `ST_THERM_IDLE`, el módulo permanece en espera del evento `EV_THERM_START_READ`, encargado de iniciar un nuevo ciclo de medición mediante la función `ds18b20_cnv()`, la cual envía al sensor el comando `DS18B20_CMD_CONV` (`0x44`) para comenzar la conversión de temperatura.

Posteriormente, el módulo utiliza las funciones `ds18b20_is_busy()` y `ds18b20_is_cnv_done()` para verificar la finalización de la comunicación `OneWire` y el tiempo necesario de conversión del sensor. Una vez completado este proceso, la función `ds18b20_req_read()` envía el comando `DS18B20_CMD_READ` (`0xBE`) para solicitar la lectura de los datos almacenados en el sensor.

La comunicación con el `DS18B20` es gestionada mediante el archivo `ow.c`, encargado de implementar el protocolo `OneWire` utilizando interrupciones del Timer 1 para controlar los tiempos de transmisión y recepción de datos sin bloquear la ejecución principal del microcontrolador.

Finalmente, la función `ds18b20_read_c()` realiza la lectura de la información recibida, verifica la integridad de los datos mediante `CRC8` y convierte el valor obtenido al formato utilizado por el sistema, almacenándolo como un valor entero expresado en centésimas de grado Celsius.

La temperatura medida es comparada con los valores límites configurados mediante las variables `temp_limit_max` y `temp_limit_min`. En caso de superar los valores establecidos, el módulo genera el evento `EV_BUZZER_BLINK`, permitiendo activar la alarma sonora del sistema. Cuando la temperatura vuelve al rango permitido, se genera el evento `EV_BUZZER_OFF` para desactivar la alarma.

Una vez finalizada la adquisición y procesamiento de la temperatura, el módulo retorna al estado inicial, quedando preparado para realizar una nueva medición.

### 3.2.4 Módulo de comunicación Bluetooth

El módulo de comunicación Bluetooth fue implementado mediante una arquitectura basada en eventos asíncronos utilizando comunicación UART con DMA, desarrollada en el archivo `task_bluetooth.c`. Esta implementación permite recibir comandos enviados desde la aplicación móvil sin requerir una supervisión constante por parte del microcontrolador, ya que la recepción de datos es gestionada directamente por el periférico DMA y las interrupciones del sistema.

Durante la inicialización del módulo, la función `HAL_UART_Receive_DMA()` configura la recepción de datos mediante el puerto serie USART3, almacenando los bytes recibidos en un buffer hasta completar la cantidad de datos definida. Una vez recibido el comando completo, el hardware genera una interrupción que ejecuta la función `HAL_UART_RxCpltCallback()`, encargada de procesar la información obtenida.

Dentro de esta función, los datos recibidos son convertidos a una cadena de caracteres para realizar su interpretación mediante la función `strcmp()`. Esta comparación permite identificar los diferentes comandos enviados desde la aplicación, como activación del modo manual o control de los actuadores del sistema.

Una vez identificado el comando recibido, el módulo genera los eventos correspondientes mediante la función `put_event_task_system()`, enviando la orden hacia la tarea principal del sistema. De esta manera, el módulo Bluetooth funciona como una interfaz de comunicación entre la aplicación móvil y el controlador, permitiendo modificar estados del sistema como el encendido del filtro u otras funciones de control.

Finalmente, luego del procesamiento del comando recibido, la comunicación UART mediante DMA vuelve a configurarse para quedar disponible para una nueva recepción de datos, permitiendo mantener una comunicación continua con el módulo Bluetooth.

### 3.2.5 Módulo de visualización mediante display LCD

El módulo de visualización fue implementado mediante una arquitectura dividida en dos capas principales: la capa lógica desarrollada en `task_lcd.c`, encargada de gestionar la actualización de la información mostrada, y la capa de hardware implementada en `i2c_lcd.c`, responsable de la comunicación con el display mediante el protocolo I2C.

La máquina de estados del módulo está compuesta por dos estados principales: `ST_LCD_IDLE` y `ST_LCD_UPDATE`. En el estado inicial `ST_LCD_IDLE`, el módulo permanece en espera hasta que se cumple el tiempo establecido para realizar una nueva actualización del display. Este control se realiza mediante la función `HAL_GetTick()`, permitiendo ejecutar la actualización de forma periódica sin bloquear la ejecución del sistema.

Cuando se alcanza el tiempo de actualización, el módulo pasa al estado `ST_LCD_UPDATE`, donde obtiene la información necesaria para mostrar en pantalla. Por ejemplo, un valor de temperatura sensado, esta es tomada desde la variable global `task_thermometer_dta_list[ID_THERM_A].temperature` para luego ser formateada mediante la función `sprintf()`, generando la cadena de caracteres que será enviada al display.

La comunicación con el display LCD es gestionada por el archivo `i2c_lcd.c`, donde la función `lcd_send_string()` realiza la conversión de los datos al formato requerido por el controlador del display y prepara el buffer de transmisión. Luego, mediante la función `HAL_I2C_Master_Transmit_DMA()`, los datos son enviados utilizando `DMA`, permitiendo que la transferencia por I2C se realice sin bloquear al procesador.

Una vez finalizada la actualización de la información mostrada, la máquina de estados retorna al estado `ST_LCD_IDLE`, quedando preparada para realizar una nueva actualización. De esta manera, el módulo permite visualizar periódicamente los datos del sistema manteniendo la ejecución simultánea de otras tareas, como la lectura de sensores, comunicación Bluetooth y control de actuadores.

### 3.2.6 Módulo de actuadores y alarmas

El módulo de actuadores y alarmas fue implementado mediante una máquina de estados desarrollada en el archivo `task_actuator.c` y definida en `task_actuator_attribute.h`. Esta implementación permite controlar los diferentes actuadores del sistema, como el relé del filtro, el buzzer y el LED de alarma, utilizando una única máquina de estados genérica para todos los dispositivos.

La configuración de cada actuador se encuentra definida mediante la estructura `task_actuator_cfg_t`, la cual almacena los parámetros asociados al hardware, como el puerto `GPIO`, el pin de conexión, el tiempo de parpadeo (`tick_max`) y los niveles de activación y desactivación (`act_on` y `act_off`). Por otra parte, la estructura `task_actuator_dta_t` contiene la información dinámica de cada actuador, incluyendo su estado actual, el último evento recibido y el temporizador utilizado durante su funcionamiento.

La máquina de estados está compuesta por tres estados principales: `ST_ACT_OFF`, `ST_ACT_ON` y `ST_ACT_BLINKING`. En el estado `ST_ACT_OFF`, el actuador permanece desactivado hasta recibir un evento mediante la función `put_event_task_actuator()`. Cuando recibe un evento de activación, pasa al estado `ST_ACT_ON`, mientras que la recepción del evento `EV_BUZZER_BLINK` provoca la transición al estado `ST_ACT_BLINKING`, encargado de generar una señal intermitente.

Durante el estado `ST_ACT_ON`, el actuador permanece activado hasta recibir el evento correspondiente de apagado, retornando nuevamente al estado `ST_ACT_OFF`. En el estado `ST_ACT_BLINKING`, el módulo utiliza la función `HAL_GetTick()` para controlar el tiempo de conmutación definido para cada actuador y la función `HAL_GPIO_TogglePin()` para alternar el estado del pin de salida de forma periódica, permitiendo generar el parpadeo sin bloquear la ejecución del sistema.

En el caso del relé del filtro (`ID_RELAY_FILTER`), la máquina de estados controla su activación y desactivación mediante los eventos generados por el sistema, tanto en modo automático como manual, manteniendo el actuador en los estados `ST_ACT_OFF` o `ST_ACT_ON` según corresponda. Por su parte, el buzzer (`ID_BUZZER`) permanece normalmente en el estado `ST_ACT_OFF` y, cuando el módulo de temperatura detecta una condición de alarma, recibe el evento `EV_BUZZER_BLINK`, ingresando al estado `ST_ACT_BLINKING` para emitir una señal sonora intermitente. Una vez que la temperatura retorna al rango establecido, el sistema genera el evento `EV_BUZZER_OFF`, desactivando la alarma y retornando el buzzer al estado `ST_ACT_OFF`.

De esta manera, el módulo centraliza el control de los actuadores y las alarmas del sistema mediante una única máquina de estados, permitiendo responder a los eventos generados por las demás tareas sin bloquear la ejecución del firmware.

# CAPÍTULO 4

# Ensayos y resultados

## 4.1 Pruebas funcionales del hardware

**Lo de servo,luces, filtro,**

### 4.1.1 Pruebas de sensor con interfaz del usuario

### Capturas de control temperatura

## 4.2 Pruebas funcionales del firmware

## 4.3 Pruebas de integración

Las pruebas de integración permitieron verificar el funcionamiento conjunto de los diferentes módulos del sistema, comprobando la correcta interacción entre sensores, actuadores, comunicación Bluetooth y aplicación móvil.

Durante los ensayos se verificó la adquisición de datos de temperatura, el control de los actuadores (alimentación, iluminación y filtrado), la generación de alarmas y la comunicación bidireccional mediante BLE. Además, se comprobó que la arquitectura implementada permite la ejecución simultánea de las tareas sin generar bloqueos en el funcionamiento del sistema.

La evidencia del funcionamiento general del prototipo se encuentra documentada en el video de presentación incluido en el Anexo B.

En la Tabla 4.1 se presenta el cumplimiento de los casos de uso definidos en la Sección 2.2.

| Caso de Uso | Título | ¿Se cumplió? |
| :---- | :---- | :---- |
| **\#1** | Alimentación automática y manual | **✔ Cumplido** |
| **\#2** | Control de iluminación día/noche | **✔ Cumplido** |
| **\#3** | Control del sistema de filtrado | **✔ Cumplido** |
| **\#4** | Monitoreo de temperatura y alarmas | **✔ Cumplido** |
| **\#5** | Configuración mediante aplicación móvil | **✔ Cumplido** |
| **\#6** | Control manual de actuadores mediante BLE | **✔ Cumplido** |

**Tabla 4.1** Cumplimiento de los casos de uso planteados.

## 4.4 Cumplimiento de requisitos

| Grupo | ID | Descripción | ¿Se cumplió? |
| :---- | :---- | :---- | :---- |
| **Sensores ambientales** | **1.1** | **El sistema contará con un sensor de temperatura sumergible para monitorear la temperatura del agua del tanque.** | **✔ Cumplido** |
|  | **1.2** | **El sistema realizará mediciones periódicas de la temperatura del agua.** | **✔ Cumplido** |
|  | **1.3** | **El sistema generará una alarma cuando la temperatura se encuentre fuera de los límites configurados.** | **✔ Cumplido** |
| **Actuadores – Alimentación** | **2.1** | **El sistema contará con un servomotor encargado de accionar el mecanismo de alimentación automática.** | **✔ Cumplido** |
|  | **2.2** | **El sistema dispensará alimento automáticamente en los horarios configurados por el usuario.** | **❌ No cumplido** |
|  | **2.3** | **El usuario podrá iniciar manualmente un ciclo de alimentación desde la aplicación móvil.** | **✔ Cumplido** |
| **Actuadores – Iluminación** | **2.4** | **El sistema contará con luces LED para simular los ciclos de día y noche del tanque.** | **✔ Cumplido** |
|  | **2.5** | **El sistema permitirá configurar los horarios de encendido y apagado de la iluminación para establecer ciclos automáticos.** | **✔ Cumplido** |
| **Actuadores – Carga de CA** | **2.6** | **El sistema controlará una carga de corriente alterna que simulará el funcionamiento del filtro de agua; en el prototipo se utilizará un foco de CA como carga.** | **✔ Cumplido** |
|  | **2.7** | **La carga de corriente alterna permanecerá activada durante el funcionamiento normal y se desactivará temporalmente durante el ciclo de alimentación.** | **✔ Cumplido** |
|  | **2.8** | **El sistema verificará el estado del relé y notificará posibles fallos en su accionamiento.** | **❌ No cumplido** |

**Tabla 4.2** Cumplimiento de los requerimientos planteados.

# CAPÍTULO 5

# Conclusiones

## 5.1 Resultados obtenidos

**\-La integración pudo ser realizada si el** 

**\-comunicación BLE**

**\-manejo de sensor** 

**\-interfaz de usuario** 

## 5.2 Próximos pasos

# Bibliografía
