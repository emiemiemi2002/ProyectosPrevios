.def r=r16
.def aleat=r17
.def numero=r18
.def intentos=r19
.def bytenumero=r23
.def rcar=r24

;EQUIPO (Sistemas Programables 2024)-----------------------
;Emiliano Espinoza Perales
;Beria Solange Colwell Saucedo
;Oscar Omar García González

;Definir pines de puertos como salidas o entradas
ldi r,0b11111111;Puerto D, usado para pines de datos de pantalla LCD | PD0-PD7 => OUT
out ddrd,r
ldi r,0b11100000;Puerto B, usado para botones y KEYPAD | PB0-PB4 => IN, PB5-PB7 => OUT
out ddrb,r
ldi r,0b00111111;Puerto C, usado para pines E y RS de pantalla LCD y LED 7-SEG | PC4-PC5 => OUT
out ddrc,r;

INICIO:;----------------------------------------------------------------------------------------------------------------------
;Enviamos voltaje por PB5 (Columna del KEYPAD en la que está el botón INICIO)
ldi r,0b00100000 
out portb,r 

;Valor inicial de registro que guarda el valor del número aleatorio
ldi aleat,0

;Iniciar pantalla y mandar mensaje inicial--------------------------------------------------------
ldi r,0b00000000
out portc,r ;PC4(E), PC5(RS) => 0 (RS en GND para comandos de configuración)

ldi r,0b00110000
out portd,r ;PD4, PD5 => 1 (Comando: Configurar con 8 bits (Default)) 

ldi r,0b00010000
out portc,r ;PC4(E) => 1 (Se manda voltaje a E (Enable))

rcall delay2 ;Retardo de 100uS

ldi r,0b00000000
out portc,r ;PC4(E) => 0 (Se manda GND a E)

rcall delay2 ;Retardo de 100uS

ldi r,0b00001110
out portd,r ;(Comando: Encender cursor en LCD)

ldi r,0b00010000
out portc,r ;PC4(E) => 1 (Se manda voltaje a E)

rcall delay2 ;Retardo de 100uS

ldi r,0b00000000
out portc,r ;PC4(E) => 0 (Se manda GND a E)

;Enviar caracteres de mensaje inicial
ldi r,0b00100000
out portc,r ;PC4(E) => 0, PC5(RS) => 1 (RS en voltaje para envio de datos)

rcall msjinicio ;Llamada a rutina para enviar caracteres de msj de bienvenida

;Ciclo inicial para esperar el pulsado de botón de INICIO--------------------------------------------------------
eti0:
   rcall aleatorio
   sbic pinb,3
   rjmp eti1
   rjmp eti0

;Aquí se mostrará en la pantalla el mensaje de teclear número--------------------------------------------------------
eti1:
   rcall limpiar ;Llamada a rutina para limpiar contenido de pantalla

   ldi r,0b00100000
   out portc,r ;PC5(RS) => 1 (RS en voltaje para envio de datos)

   rcall msjespera ;Llamada a rutina para enviar caracteres de msj de espera de número

   ldi intentos,0 ;Cargar registro que almacena el número de intentos con 0

repite:;Zona de detección de botones------------------------------------------------------------------------------------------
   ;Enviar voltaje por PB5
   rcall delay ;Retardo de 50mS
   ldi r,0b00100000 
   out portb,r
   ;Detectar entrada en pines de entrada de puerto B (Botones 1, 4, 7, INICIO y E1)
   sbic pinb,0	
   rjmp bot1
   sbic pinb,1
   rjmp bot4
   sbic pinb,2	
   rjmp bot7
   sbic pinb,3	
   rjmp botINICIO
   sbic pinb,4	
   rjmp botE1
   ;Quitamos voltaje de PB5 y enviamos voltaje por PB6
   rcall delay ;Retardo de 50mS
   ldi r,0b01000000
   out portb,r
   ;Detectar entrada en pines de entrada de puerto B (Botones 2, 5, 8, 0 y E2)
   sbic pinb,0	
   rjmp bot2
   sbic pinb,1
   rjmp bot5
   sbic pinb,2	
   rjmp bot8
   sbic pinb,3	
   rjmp bot0
   sbic pinb,4	
   rjmp botE2
   ;Quitamos voltaje de PB6 y enviamos voltaje por PB7
   rcall delay ;Retardo de 50mS
   ldi r,0b10000000
   out portb,r
   ;Detectar entrada en pines de entrada de puerto B (Botones 3, 6, 9, RESET y E3)
   sbic pinb,0	
   rjmp bot3
   sbic pinb,1
   rjmp bot6
   sbic pinb,2	
   rjmp bot9
   sbic pinb,3	
   rjmp botRESET
   sbic pinb,4	
   rjmp botE3
;
rjmp repite

;Acciones de botones-------------------------------------------------------------------------------------------
bot1:
   sbic pinb,0 ;Si se está pulsando el botón (PB0 = 1) brinca a 'bot1', si se suelta el botón (PB0 = 0), brinca una instrucción.
   rjmp bot1
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq repite ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos ;Incrementamos el número de intentos en uno.
   rcall desplegarnumerointentos ;Llamada a subrutina 'desplegarnumerointentos', que muestra en el display de 7-Seg el núm. actual de intentos.

   ldi bytenumero,0b00110001 ;Cargamos en 'bytenumero' la combinación de bits del número del botón pulsado (para desplegarlo en pantalla LCD). 
   ldi numero,1 ;Cargamos en 'numero' el número elegido.
   rcall compara ;Llamada a subrutina 'compara'.
   rjmp repite ;Regreso a la zona de detección de botones.

bot4:
   sbic pinb,1
   rjmp bot4
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq repite ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110100
   ldi numero,4
   rcall compara
   rjmp repite

bot7:
   sbic pinb,2
   rjmp bot7
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq repite ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110111
   ldi numero,7
   rcall compara
   rjmp repite

botINICIO:
   rjmp repite

botE1: ;Botón para CONTINUAR después de haber perdido o ganado.
   sbic pinb,4
   rjmp botE1
   ;
   cpi intentos,3 ;Verificar si el número de intentos es igual a 3...
   breq botE1A ;Si sí, limpiar pantalla y regresar a inicio del programa
   brlo botE1B ;Si no, saltar a zona de detección de botones

botE1A:
   rcall limpiar
   rjmp INICIO

botE1B:
   rjmp repite

bot2:
   sbic pinb,0
   rjmp bot2 
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE1B ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110010
   ldi numero,2
   rcall compara
   rjmp repite

bot5:
   sbic pinb,1
   rjmp bot5
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE1B ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110101
   ldi numero,5
   rcall compara
   rjmp repite

bot8:
   sbic pinb,2 
   rjmp bot8
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE2 ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00111000
   ldi numero,8
   rcall compara
   rjmp repite

bot0:
   sbic pinb,3
   rjmp bot0
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE2 ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110000
   ldi numero,0
   rcall compara
   rjmp repite

botE2:
   rjmp repite

bot3:
   sbic pinb,0
   rjmp bot3
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE2 ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110011
   ldi numero,3
   rcall compara
   rjmp repite

bot6:
   sbic pinb,1
   rjmp bot6
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE2 ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00110110
   ldi numero,6
   rcall compara
   rjmp repite

bot9:
   sbic pinb,2
   rjmp bot9
   ;
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq botE3 ;Si son iguales, regresa a la zona de detección de botones.

   inc intentos
   rcall desplegarnumerointentos
   
   ldi bytenumero,0b00111001
   ldi numero,9
   rcall compara
   rjmp repite

botRESET:
   ;Limpiar pantalla y regresar a la parte inicial del programa (en cualquier momento que se pulse)
   rcall limpiar
   rjmp INICIO

botE3:
   rjmp repite

;Zona de subrutinas-------------------------------------------------------------------------------------------
;Acciones juego
aleatorio: ;Inicio de la subrutina 'aleatorio'
   inc aleat
   cpi aleat,10
   breq eti2
   ret
eti2:
   ldi aleat,0
ret ;Retorna el control

compara: ;Inicio de la subrutina 'compara'
   rcall limpiar ;Llamada a rutina para limpiar contenido de pantalla

   in r,pinc ;Leer pines de puerto C en 'r'
   ori r,0b00100000
   out portc,r ;PC5(RS) => 1 (RS en voltaje para envio de datos)

   cp aleat,numero
   breq ganador ;'aleat' es IGUAL que 'numero'
   brlo compmenor ;'aleat' es menor que 'numero'
   rcall compmayor ;'aleat' es mayor que 'numero'
ret ;Retorna el control

ganador: ;Inicio de la subrutina 'ganador'
   ldi intentos,3 ;Se carga inmediatamente 3 al registro que cuenta los intentos para que funcione el botón CONTINUA aunque se haya ganado.
   ;
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01110101
   rcall enviar ;u
   ldi rcar,0b01101101
   rcall enviar ;m
   ldi rcar,0b00111010
   rcall enviar ;:
   mov rcar,bytenumero
   rcall enviar ;Numero elegido
   ldi rcar,0b01111100
   rcall enviar ;|
   ldi rcar,0b01000111
   rcall enviar ;G
   ldi rcar,0b01000001
   rcall enviar ;A
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01000001
   rcall enviar ;A
   ldi rcar,0b01010011
   rcall enviar ;S
   ldi rcar,0b01010100
   rcall enviar ;T
   ldi rcar,0b01000101
   rcall enviar ;E
   ldi rcar,0b00100001
   rcall enviar ;!
ret ;Retorna el control

compmenor: ;Inicio de la subrutina 'compmenor'
   cpi intentos,3 ;Comparar número de intentos con 3 (límite)
   breq perdedor ;Si el número de intentos es 3, salta a 'perdedor'
   brlo menor ;Si el número de intentos es menor a tres, salta a 'menor'
ret ;Retorna el control

compmayor: ;Inicio de la subrutina 'compmayor'
   cpi intentos,3 ;Comparar número de intentos con 3 (límite)
   breq perdedor ;Si el número de intentos es 3, salta a 'perdedor'
   brlo mayor ;Si el número de intentos es menor a tres, salta a 'mayor'
ret ;Retorna el control

perdedor: ;Inicio de la subrutina 'perdedor'
   ldi rcar,0b01010000
   rcall enviar ;P
   ldi rcar,0b01010000
   rcall enviar ;P
   ldi rcar,0b01000101
   rcall enviar ;E
   ldi rcar,0b01010010
   rcall enviar ;R
   ldi rcar,0b01000100
   rcall enviar ;D
   ldi rcar,0b01001001
   rcall enviar ;I
   ldi rcar,0b01010011
   rcall enviar ;S
   ldi rcar,0b01010100
   rcall enviar ;T
   ldi rcar,0b01000101
   rcall enviar ;E
   ldi rcar,0b00100001
   rcall enviar ;!
   ldi rcar,0b00100000
   rcall enviar ;' '
   ldi rcar,0b00111010
   rcall enviar ;:
   ldi rcar,0b00101000
   rcall enviar ;(
ret ;Retorna el control

menor: ;Inicio de la subrutina 'menor'
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01110101
   rcall enviar ;u
   ldi rcar,0b01101101
   rcall enviar ;m
   ldi rcar,0b00111010
   rcall enviar ;:
   mov rcar,bytenumero
   rcall enviar ;Numero elegido
   ldi rcar,0b01111100
   rcall enviar ;|
   ldi rcar,0b01001101
   rcall enviar ;M
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b01110011
   rcall enviar ;s 
   ldi rcar,0b00100000
   rcall enviar ;' '
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b01100010
   rcall enviar ;b
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b01101010
   rcall enviar ;j
   ldi rcar,0b01101111
   rcall enviar ;o
ret ;Retorna el control

mayor: ;Inicio de la subrutina 'mayor'
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01001110
   rcall enviar ;N
   ldi rcar,0b01110101
   rcall enviar ;u
   ldi rcar,0b01101101
   rcall enviar ;m
   ldi rcar,0b00111010
   rcall enviar ;:
   mov rcar,bytenumero
   rcall enviar ;Numero elegido
   ldi rcar,0b01111100
   rcall enviar ;|
   ldi rcar,0b01001101
   rcall enviar ;M
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b01110011
   rcall enviar ;s 
   ldi rcar,0b00100000
   rcall enviar ;' '
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b01110010
   rcall enviar ;r
   ldi rcar,0b01110010
   rcall enviar ;r
   ldi rcar,0b01101001
   rcall enviar ;i
   ldi rcar,0b01100010
   rcall enviar ;b
   ldi rcar,0b01100001
   rcall enviar ;a
ret ;Retorna el control

;Delays---------------------------------------------------------------
delay: ;Inicio de la subrutina 'delay'
; 50ms at 1 MHz
    ldi  r20, 65
    ldi  r21, 239
L1: dec  r21
    brne L1
    dec  r20
    brne L1
ret ;Retorna el control

delay2: ;Inicio de la subrutina 'delay2'
    ; 100us
    ldi  r22, 33
L2: dec  r22
    brne L2
    nop
ret ;Retorna el control

;Acciones pantalla---------------------------------------------------------------
enviar: ;Inicio de la subrutina 'enviar'
   out portd,rcar ;Enviar caracter almacenado en 'rcar' por el puerto D

   in r,pinc ;Leer pines de puerto C en 'r'
   ori r,0b00110000
   out portc,r ;PC4(E), PC5(RS) => 1

   rcall delay2 ;Retardo de 100us

   in r,pinc ;Leer pines de puerto C en 'r'
   andi r,0b11101111
   out portc,r ;PC4(E) => 0

   rcall delay2 ;Retardo de 100us
ret ;Retorna el control

limpiar: ;Inicio de la subrutina 'limpiar'
   in r,pinc ;Leer pines de puerto C en 'r'
   andi r,0b11001111
   out portc,r ;PC4(E), PC5(RS) => 0

   ldi r,0b00000001
   out portd,r ;Borrar contenido de LCD

   in r,pinc ;Leer pines de puerto C en 'r'
   ori r,0b00010000
   out portc,r ;PC4(E) => 1

   rcall delay2 ;Retardo de 100us

   in r,pinc ;Leer pines de puerto C en 'r'
   andi r,0b11101111
   out portc,r ;PC4(E) => 0

   rcall delay2 ;Retardo de 100us
ret ;Retorna el control

;Mensajes---------------------------------------------------------------
msjespera: ;Inicio de la subrutina 'msjespera'
   ldi rcar,0b01010000
   rcall enviar ;P
   ldi rcar,0b01010000
   rcall enviar ;P
   ldi rcar,0b01110101
   rcall enviar ;u
   ldi rcar,0b01101100
   rcall enviar ;l
   ldi rcar,0b01110011
   rcall enviar ;s
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b00100000
   rcall enviar ;' '
   ldi rcar,0b01101110
   rcall enviar ;n
   ldi rcar,0b01110101
   rcall enviar ;u
   ldi rcar,0b01101101
   rcall enviar ;m
   ldi rcar,0b00101000
   rcall enviar ;(
   ldi rcar,0b00110001
   rcall enviar ;1
   ldi rcar,0b00101101
   rcall enviar ;-
   ldi rcar,0b00111001
   rcall enviar ;9
   ldi rcar,0b00101001
   rcall enviar ;)
   ldi rcar,0b00101110
   rcall enviar ;.
ret ;Retorna el control

msjinicio: ;Inicio de la subrutina 'msjinicio'
   ldi rcar,0b01000010
   rcall enviar ;B
   ldi rcar,0b01101001
   rcall enviar ;i
   ldi rcar,0b01100101
   rcall enviar ;e
   ldi rcar,0b01101110
   rcall enviar ;n
   ldi rcar,0b01110110
   rcall enviar ;v
   ldi rcar,0b01100101
   rcall enviar ;e
   ldi rcar,0b01101110
   rcall enviar ;n
   ldi rcar,0b01101001
   rcall enviar ;i
   ldi rcar,0b01100100
   rcall enviar ;d
   ldi rcar,0b01101111
   rcall enviar ;o
   ldi rcar,0b00101111
   rcall enviar ;/
   ldi rcar,0b01100001
   rcall enviar ;a
   ldi rcar,0b00100001
   rcall enviar ;!
   ldi rcar,0b00101110
   rcall enviar ;.
   ldi rcar,0b00101110
   rcall enviar ;.
   ldi rcar,0b00101110
   rcall enviar ;.
ret ;Retorna el control

;Otros---------------------------------------------------------------
desplegarnumerointentos: ;Inicio de la subrutina 'desplegarnumerointentos'
   cpi intentos,1 ;Compara el número en registro de intentos con 1.
   breq uno ;Si son iguales, brinca a 'uno'.
   cpi intentos,2 ;Compara el número en registro de intentos con 2.
   breq dos ;Si son iguales, brinca a 'dos'.
   cpi intentos,3 ;Compara el número en registro de intentos con 3.
   breq tres ;Si son iguales, brinca a 'tres'.
ret ;Retorna el control

uno: ;Manda por los pines menos significativos del puerto C, la combinación binaria del número 1.
   ;0001
   in r,pinc ;Leer pines de puerto C en 'r'
   ori r,0b00000001
   out portc,r ;PC0 => 1
   ;
   in r,pinc ;Leer pines de puerto C en 'r'
   andi r,0b11110001
   out portc,r ;PC1,PC2,PC3 => 0
ret

dos: ;Manda por los pines menos significativos del puerto C, la combinación binaria del número 2.
   ;0010
   in r,pinc ;Leer pines de puerto C en 'r'
   ori r,0b00000010
   out portc,r ;PC1 => 1

   in r,pinc ;Leer pines de puerto C en 'r' 
   andi r,0b11110010
   out portc,r ;PC0,PC2,PC3 => 0
ret

tres: ;Manda por los pines menos significativos del puerto C, la combinación binaria del número 3.
   ;0011
   in r,pinc ;Leer pines de puerto C en 'r'
   ori r,0b00000011
   out portc,r ;PC0,PC1 => 1

   in r,pinc ;Leer pines de puerto C en 'r'
   andi r,0b11110011
   out portc,r ;PC2,PC3 => 0
ret