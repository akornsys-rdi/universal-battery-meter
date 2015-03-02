# universal-battery-meter #

### Universal Battery Meter ###

     _   _ ___ __  __   
    | | | | _ )  \/  |  
    | |_| | _ \ |\/| |  
     \___/|___/_|  |_|  

Project developed by [kwendenarmo](http://kwendenarmo.es/ "kwendenarmo") (<devel@kwendenarmo.es>).  
This project is under GPLv3 licence. See COPYING file.  
See CHANGELOG file to check the history of dates, versions and changes.  
README.md file.  

## Version ##

Versión 2.0.0 "devel"

## Cambios ##

Reimplementación del branch `old-v1`, con funcionalidades añadidas:

- Hardware dividido en tres bloques:
    * Display
        + Muestra datos a través de cuatro display 7seg.
        + Cuatro LED de modo (*V*, *A*, *Ah*, *ºC*) para indicar qué tipo de dato se está mostrando en display.
        + Diez led para escala analógica (RGGGGYYYRR).
        + Un buzzer con soporte para tonos.
        + Tres pulsadores (unit, set, mode) que permite cambiar la unidad mostrada en display y modificar la configuración de control.
        + El display usa entrada de 9 pines: `DS_VCC`, `DS_MOSI`, `DS_SCK`, `DS_SS`, `DS_BUZ`, `DS_UNT`, `DS_MOD`, `DS_SET`, `DS_GND`. VCC de 5V
        + Todos los LED (7seg e individuales) van multiplexados a través de SPI (Primer byte ánodo, Segundo byte cátodos comunes).
        + El sistema incluye un power-on-reset para limpiar los registros del SPI.
        + La entrada del buzzer se ataca directamente a través de un fet.
        + Los tres pulsadores llevan un anti-rebotes por hardware.
    * Control
        + Basado en ATmega328 a 16MHz
        + Conexión directa al display, mediante zócalo.
        + Cabecera de ISP.
        + EEPROM SPI (bus compartido) para log.
        + Conector de salidas de drenador abierto para media potencia. Salidas: `STAT_FULL`, `STAT_FLOAT`, `STAT_FAIL`, `OUT_CHARGE`, `OUT_DISCHARGE`.
        + Conector de comunicaciones mediante RS485 con pull y terminador. Válido para programación.
        + Conector de sonda mediante RS485 con pull y terminador. Incorpora alimentación regulada.
        + Permite múltiples sondas en cascada.
        + Autodetección de la sonda
        + Alimentación de módulo a 12-36vdc
        + Monitorización de tensiones en entrada y VCC
    * Sonda
        + Módulos en rangos de tensión y corriente admitida.
        + Basado en ATmega 328 a 16MHz
        + Conexión RS485 con el módulo principal.
        + Selector de terminador.
        + Conector de sonda para sondas en cascada.
        + Medida de tensión.
        + Medida de corriente.
        + Conector para sonda de temperatura.
        + Sensor de temperatura incorporado en el cuerpo de la sonda.

Usos:
- Logger
- Charger
- Discharger
- Monitor
- Voltmeter
- Ammeter
- Capacity meter

Librerias:
- datelib
- modbus??

Formfactor:
- panel (http://img-asia.electrocomponents.com/largeimages/R6876140-01.jpg)
