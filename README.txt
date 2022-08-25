FAKENNACRY V 1.0

-Compilación: gcc -Wextra -Werror -Wall stockholm.c home/infection/stockholm

-Para su correcto funcionamiento, el programa stockholm debe ejecutarse dentro de la propia carpeta "infection" dentro del directorio "home".

-Una vez compilado, el programa stockholm funciona con las siguientes flags:
	-h / -help: muestra la ayuda
	-v / -version: muestra la versión actual
	-s / -silent: ejecuta el programa en modo silencioso (sin mostrar output)
	-r / -reverse seguido de la clave: revierte la infección

-Este programa encripta todos los archivos presentes en la carpeta /home/infection que tengan alguna de las extensiones a las que afectó el Wannacry y les añade la extensión .ft.

-Si el archivo tenía la extensión .ft previamente el programa no lo encripta (ni lo desencripta ni le quita su extensión primitiva después).

-El programa crea el archivo oculto .stockholm.txt, donde se almacena la clave de 16 caracteres generada aleatoriamente para revertir el proceso, que también se muestra por pantalla si se ejecuta en modo normal (no silencioso).