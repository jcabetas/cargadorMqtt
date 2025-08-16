# Cargador STM32 Modbus

## Características:
  El cargador gestiona dos relés (uno para fase A y neutro, y otro para fases adicionales B y C)
  Tiene dos interfaces modbus, uno para conexion desde un ordenador, y otro para conexion opcional de medidor
  Se puede configurar también por terminal serie bluetooth.

## Modos de funcionamiento:
  El cargador puede funcionar de dos modos:
  - Manual: se usa setpoint manual de intensidad, y se activan los relés segun se ha configurado
  - Modbus intensidad: si se recibe setpoint intensidad, se fija PWM. La configuración de los relés se fijan por modbus
  Si no se recibe modbus durante un tiempo, pasamos a funcionar manual

## Gestion de Imin e Isp  
  - Si la Isp<Imin, se ajusta Isp=Imin sin dar error modbus
  - Si la Isp<Imin+0.2, se desconecta oscilador
  - Cuando la int. mínima es menor de 1A, si el setpoint es menor abre el contactor  

## Los estados del coche son:
  - Esperando coche: no se detecta a nadie conectado. Tensión a +12V 
  - Coche conectado, pero sin pedir (R:2k74) 
    => Oscilador conectado ajustado a potencia disponible
       Reseteamos contador kWh
  - Coche pide (R:882, o R:246 con ventilación)
    => Se cierra el contactor. 
       Se ajusta oscilador de acuerdo a la potencia deseada. 
       Si no hay potencia se elige entre intensidad de parada o abrir contactor
  - Coche deja de pedir: 
    => Se abre contactor, manteniendo oscilador.
  
## Interfaz de medidor
  Si tiene medidor, lo lee y lo pone en registros para poder ser adquiridos desde modbus por el ordenador

  
## Mapa Modbus:
### Holding registers

| Descripción | Registro | Comentario|
| -------- | ------- | ----|
| ID medidor | 0      |   |
| Baud medidor | 1      | 0:300, 1:600, 2:1200, 3:2400, 4:4800, 5:9600, 6:19200, 7:38400, 8:57600, 9:115200  
| Modelo medidor    | 2      | Si se supera este tiempo (s) sin recibir setpoint, fuerza conexión |
| Modo control | 3      | Fuerza conexion a esta hora |
| Timeout control | 4      | Desactiva conexion forzada a esta hora |
| ID ordenador | 5   | 0: apagado incondicional<p>1:encendido incondicional<p>2:setpoint (si no lo recibe, pasa a encendido)<p>3:similar al (2), pero fuerza conexion entre "Hora On" y "Hora off", siempre que se haya establecido fecha completa |
| Baud ordenador | 6    | Idem baud medidor |
| numFases | 7    |  |
| iMax       | 8    | |
| iMin (mA)  | 9    | 0 si se permite abrir contactor cuando no hay potencia |
| # contactores | 10   | |
| control contact | 11   | 1 solo monofasico, 2: gestiona mono-tri, 3: trifasico |
| i Setpoint | 12   | |
 

     
### Input registers

| Descripción | Registro | Comentario|
| -------- | ------- | ----|
| Número dimmers detectados | 0      |   |
| Dimmer 1 detectado | 1 ||
| Dimmer 2 detectado | 2 ||
| Dimmer 3 detectado | 3 ||
| Ancho pulso (us)   | 4 ||
| Período (us)       | 5 ||
| Potencia real (%)  | 6 ||





