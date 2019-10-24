Se desea diseñar e implementar un programa concurrente basado en
el paradigma de la memoria compartida que imprime n mensajes en
pantalla. Este programa debe diseñarse de tal manera que se asegure
que el hilo 𝑖 reciba del hilo mod(𝑖 + 𝑛 − 1, 𝑛) una cadena de
caracteres que imprimirá en pantalla, donde 𝑖 es el identificador del
𝑡ℎ𝑟𝑒𝑎𝑑𝑖 , 𝑛 es el número de mensajes a imprimir y 𝑚𝑜𝑑(𝑎, 𝑏) es una
función que devuelve el residuo de la división entera 𝑎 ÷ 𝑏. 
