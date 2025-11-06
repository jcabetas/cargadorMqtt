# Cargador STM32 Modbus

## Características:
  El cargador gestiona dos relés (uno para fase A y neutro, y otro para fases adicionales B y C)
  Se comunica por mqtt a home-assistant mediante un XiaoC6, y un interfaz modbus para el medidor
  
## Modos de funcionamiento:
  Xiao funciona de manera transparente entre Mqtt y STM32. La configuración inicial del STM32 es 16A monofásico.
  La comunicación del cargador (definido por su nombre, p.e. "Kona") se hace:
  - La configuración se hace enviando al topic "Kona/config" un JSON con los siguientes valores:
    * imax, imin, numfases, numcontactores, paroconcontactores, modelomedidor, idmodbus, baudmodbus
    Si no recibe ajustes, se queda en imax y corta con contactores
  - Cuando arranca el STM32, le pide a Xiao que se configure en home assistant pasandole el numero de fases. Es un
    json tipo "{"orden":"conecta","numfases":"3"}
    Si cambia el numero de fases por configuración recibida, le puede volver a enviar petición de reenganche  
    Cuando esté configurado, Xiao enviará a STM32 "{"orden":"estado","conectado":"1", "numfases":"3"}
  - En cualquier momento STM32 puede preguntar estado a Xiao con json "{"orden":"diestado"} . STM32 contestara con 
    "{"orden":"estado", "numfases":"1·,...}
  - Ajuste, puede ser por:
    * Isp (enviando al topic "Kona/isp/set" un json {"isp":"13.2"}
    * Psp (idem con "psp")
    Si no recibe instrucciones durante 30s, se queda ajustado a Imax
  - Envio de estados a homeassistant enviando al topic "Kona/state" un json con valores isp, coche (estado del cargador) y potencia
    A futuro añadir Preal, kWh cargados, Ia (Ib e Ic si es trifásico)
  

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






