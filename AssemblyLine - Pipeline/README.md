Se desea diseñar e implementar un programa concurrente basado en el paradigma de la memoria compartida que simula la línea de ensamble de un automóvil de 15 etapas. Este programa recibe por entrada un número 𝑛 mayor que 100 que indica el número de automóviles que se van a ensamblar. Su salida es un vector que almacena los autos que han sido ensamblados. El programa además imprime en la terminal estándar el tiempo de ejecución que conllevo ensamblar los 𝑛 autos. 

La línea de ensamble se compone de 15 etapas: 

bodywork_1, bodywork_2 y bodywork_3 
paint_1, paint_2 
motor_1, motor_2 y motor_3 
seating_1, seating_2 
accesories_1, accesories_2, accesories_3, accesories_4 y accesories_5 

Las tres primeras etapas se encargan de construir la carrocería del auto bajo el siguiente orden: puesta de la carrocería, ensamble y puesta de neumáticos. Las siguientes dos etapas se encargan de la pintura del auto (color del interior y del exterior, respectivamente). Después, se tienen tres etapas encargadas de montar, ensamblar y calibrar el motor. Las dos etapas que vienen a continuación se encargan del establecimiento de los asientos delanteros y traseros, respectivamente. Las últimas cinco etapas instalan en orden los accesorios del automóvil: cristales delanteros, cristales traseros, cristales laterales, espejos retrovisores y tablero.

