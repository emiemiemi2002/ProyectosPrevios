#----------PROYECTO M�TODOS NUM�RICOS----------#


########## 1.- Descripci�n del problema ##########
#Se realiz� una encuesta de manera independiente con el objetivo de recolectar 
#informaci�n actual referente al estado/caracter�sticas f�sicas de un total de 
#75 personas seleccionadas de manera aleatoria. Informaci�n en forma de variables
#que tiene como objetivo obtener la correlaci�n entre las mismas y m�s espec�ficamente
#de la mayor�a de estas variables con una variable espec�fica como lo podr�a ser 
#el peso.
#Cada registro representa una persona encuestada. A continuaci�n se describen
#las variables de estudio...


########## 2.- Descripci�n de las variables de estudio ##########
#_PESO: Variable num�rica de los kg que pesa.
#VARIABLE DEPENDIENTE
#_ALTURA: Variable num�rica de los cm que mide.
#VARIABLE INDEPENDIENTE
#_EDAD: Variable num�rica de los a�os de edad.
#VARIABLE INDEPENDIENTE
#_COMPLEXI�N: Variable num�rica (Rango 1:3) que representa el tipo de cuerpo.
#VARIABLE INDEPENDIENTE
#_NACIONALIDAD: Variable num�rica (Rango 1:3) que representa la nacionalidad.
#VARIABLE INDEPENDIENTE
#_SEXO: Variable Cualitativa (1 = si la persona es hombre, 2 = si la persona es mujer).
#VARIABLE INDEPENDIENTE


########## 3.- An�lisis exploratorio de los datos ##########
#Leer/cargar archivo .csv (valores separados por comas)
archivoleido <- read.csv("BDD-METODOSNUMERICOS-OFF.csv")
#Imprimir una vista de los primeros 6 registros
head(archivoleido)
#    PESO(Kg) ALTURA(Cm) EDAD COMPLEXI�N_F�SICA NACIONALIDAD SEXO
# 1    62	      175	     20	          1	             1	      1
# 2    79	      172	     19	          2	             1	      1
# 3   102	      179	     23	          3	             2	      2
# 4    67	      165	     42	          1	             3  	    2
# 5    80	      185	     27	          2	             2	      1
# 6   110	      165	     50	          3	             1	      2
#Se hace posible la vinculaci�n con las variables/columnas de nuestra base de datos...
#Simplificando a la expresi�n "archivoleido$nombre_variable"
attach(archivoleido)
#Se desvinculan las variables/columnas de la base de datos que 'attach()' hizo...
#posible referenciar de manera individual
detach(archivoleido)

#Gr�ficas de Dispersi�n
#Diagrama de dispersi�n de ALTURA en relaci�n al n�mero de registro
plot(ALTURA..Cm., xlab="No. de Registro", main = "Diagrama de Dispersi�n (Altura)")
#EXPLICACI�N.- En el diagrama de dispersi�n de los valores de la Altura en funci�n
#al n�mero de registro se puede visualizar una gran dispersi�n entre la mayor�a de 
#los valores en la tabla. Podemos observar que del registro 1 al 25 hay valores de
#estatura variados, la mayor�a por encima de los de menor valor, al igual que existe 
#el valor mayor (190). Los registros de entre 25 y 40 muestran valores de estatura 
#medios. Finalmente, los valores de estatura de los registros de 40 a 75 presentan 
#el comportamiento m�s variado, conteniendo el menor valor (155), valores medios y
#algunos de los mayores.

#Diagrama de dispersi�n de EDAD en relaci�n al n�mero de registro
plot(EDAD, xlab="No. de Registro", main = "Diagrama de Dispersi�n (Edad)")
#EXPLICACI�N.- Podemos visualizar que del registro 1 al 35 existen los valores de 
#edad mayores, al igual que valores de edad menores y medios que van creciendo.Se
#observa la mayor dispersi�n en este rango. Del registro 35 al 75 se siguen mostrando
#los valores de edad menores y medios que contin�an incrementando.

#Diagrama de dispersi�n de COMPLEXI�N F�SICA en relaci�n al n�mero de registro
plot(COMPLEXION.FISICA, xlab="No. de Registro", main = "Diagrama de Dispersi�n (Complexi�n F�sica)")
#EXPLICACI�N.- Al ser una variable de tres valores posibles, el an�lisis se hace de 
#manera que visualicemos la cantidad de cada tipo de complexi�n en cierto rango del
#n�mero de registros. Con esto, vemos que:
#En los registros del 0 al 20: Predominan ectomorfos y hay menos mesomorfos.
#En los registros del 20 al 40: Predominan mesomorfos sobre ectomorfos y endomorfos.
#En los registros del 40 al 60: Predominan ectomorfos y mesomorfos sobre endomorfos.
#En los registros del 60 al 75: Predominan mesomorfos y endomorfos sobre ectomorfos.

#Diagrama de dispersi�n de NACIONALIDAD en relaci�n al n�mero de registro
plot(NACIONALIDAD, xlab="No. de Registro", main = "Diagrama de Dispersi�n (Nacionalidad)")
#EXPLICACI�N.-
#En los registros del 0 al 20: No existe diferencia significativa, pero hay mas europeos.
#En los registros del 20 al 40: Sin diferencia significativa, hay m�s americanos y menos europeos.
#En los registros del 40 al 60: Hay m�s europeos y menos personas americanas.
#En los registros del 60 al 75: Hay mas personas asi�ticas y europeas que americanas.

#Diagrama de dispersi�n de SEXO en relaci�n al n�mero de registro
plot(SEXO, xlab="No. de Registro", main = "Diagrama de Dispersi�n (Sexo)")
#EXPLICACI�N.-
#En los registros del 0 al 20: Sin diferencia significativa, hay mas hombres que mujeres.
#En los registros del 20 al 40: Sin diferencia significativa, hay mas mujeres que hombres.
#En los registros del 40 al 60: Sin diferencia significativa, hay mas mujeres que hombres.
#En los registros del 60 al 75: Sin diferencia significativa, hay mas hombres que mujeres.


########## 4.- An�lisis de correlaciones ##########
#Llamar a la librer�a 'corrplot'
library(corrplot)
#Usar comando 'corrplot' para generar gr�fica visual de la correlaci�n entre nuestras
#variables independientes, considerando un rango de valores de -1 a 1 (valor de correlaci�n)
#que se representa con un gradiente de colores: azul, blanco y rojo. La figura escogida
#fue la elipse.
corrplot(cor(archivoleido), method = "ellipse")
#EXPLICACI�N.- Podemos observar que, la mayor�a de las variables no tienen un nivel 
#significativo de correlaci�n entre s�. Al igual que existen valores positivos y negativos 
#de correlaci�n. La mayor correlaci�n positiva es entre la COMPLEXI�N F�SICA y el PESO,
#lo que indica que ambas variables (sus valores) incrementan una con la otra. La mayor
#correlaci�n negativa  es entre la EDAD y la ALTURA (QUE ES M�NIMA), lo que indica que si 
#la variable de EDAD incrementa, la variable ALTURA disminuye.


########## 5.- Ajuste del modelo y c�lculo de los coeficientes o par�metros ##########
#Ajuste de modelo-
#Variable Dependiente ~ Variable(s) Independiente(s)
#lm(formula = �..PESO..Kg. ~ ALTURA..Cm. + EDAD + COMPLEXION.FISICA + NACIONALIDAD + SEXO)
modeloarchivoleido <- lm(�..PESO..Kg.~ALTURA..Cm.+EDAD+COMPLEXION.FISICA+NACIONALIDAD+SEXO)
#Determinar coeficientes-
#Con 'summary()' calculamos los coeficientes y determinamos cuales de nuestras variables
#independientes tienen mayor influencia en la variable dependiente de acuerdo a el n�mero
#de asteriscos presentes en cada una. Tenemos tambi�n valores como #el estimado(Estimate) 
#y el error(Std. Error).
summary(modeloarchivoleido)
#AN�LISIS.-
#Coefficients:
#                  Estimate Std. Error t value Pr(>|t|)    
#(Intercept)       50.25600   42.67590   1.178 0.242994    
#ALTURA..Cm.        0.09059    0.22294   0.406 0.685731 (NO influye en 'PESO')    
#EDAD               0.23950    0.22528   1.063 0.291432 (NO influye en 'PESO')
#COMPLEXION.FISICA  8.64831    2.31385   3.738 0.000379 *** (S� influye en 'PESO')
#NACIONALIDAD      -2.42596    2.28934  -1.060 0.292986 (NO influye en 'PESO') 
#SEXO              -3.04380    3.63245  -0.838 0.404954 (NO influye en 'PESO')  
#Multiple R-squared:  0.2281,	Adjusted R-squared:  0.1722 

#Coeficientes del modelo
# 50.25600

# 0.09059
# 0.23950
# 8.64831 (Estad�sticamente significativo)
# -2.42596 
# -3.04380 (No es estad�sicamente significativo)

#0.2281, coeficiente de determinaci�n m�ltiple, determina que tan cerca est�n los
#datos de la l�nea de regresi�n ajustada.


########## 6.- Predicciones ##########
#Despu�s de recabar 75 registros de manera aleatoria de las caracter�sticas f�sicas
#de personas de 3 nacionalidades, el encuestador desea predecir el nivel de peso en kg
#para la pr�xima persona de cierta nacionalidad a encuestar, y as� poder saber si
#existe un patr�n en el rango de peso de acuerdo a las dem�s caracter�sticas f�sicas.
#DATOS.- Altura:180, Edad:29, Complexi�n: 1, Nacionalidad: 3, Sexo:1
predict(object = modeloarchivoleido, newdata = data.frame(ALTURA..Cm.=180,EDAD=29,
        COMPLEXION.FISICA=1, NACIONALIDAD=3, SEXO=1), interval="predict", level=0.95)
#RESULTADO.- El resultado de la predicci�n del PESO de una persona de altura 180
#, de 29 a�os, de complexi�n f�sica delgada (ectomorfo), de nacionalidad asi�tica 
#y de sexo 'hombre'... ha sido de 71 kgs.
#Conclusi�n.- Este valor de peso ha sido mayormente determinado por la COMPLEXI�N F�SICA.
#Y se da a entender que, de acuerdo a los datos que tenemos, las personas asi�ticas
#tienden a tener valores de peso m�s regulados/normales.


########## 7.- Conclusiones del modelo de regresi�n lineal ##########
#Despu�s de ajustar el modelo de regresi�n lineal, sabemos que nuestras variables
#(independientes) que tuvieron una repercusi�n sobre la variable dependiente o de 
#de respuesta (PESO) fueron: COMPLEXI�N F�SICA solamente. En cuanto a las variables
#NACIONALIDAD y SEXO podemos decir que fue el caso contrario, ya que, al existir una
#correlaci�n negativa, el efecto de relaci�n fue inverso, (aunque m�nimo). 


########## 8.- Ajuste del modelo de regresi�n log�stica ##########
#ASIGNAR VARIABLE DEPENDIENTE E INDEPENDIENTE.- 
#Variable dependiente: SEXO
#Variable independiente: COMPLEXI�N F�SICA
#Para continuar con la investigaci�n acerca de los patrones de caracter�sticas f�sicas
#espec�ficas de acuerdo a alguna otra caracter�stica en especial, el encuestador est�
#interesado en conocer la probabilidad de que una persona sea hombre o mujer dependiendo 
#de su complexi�n f�sica.

#Convertir nuestra variable categ�rica en factor con 'as.factor()'
SEXO <- as.factor(SEXO)
modelo_logistico <- glm(formula = SEXO~COMPLEXION.FISICA, 
                        family = binomial(link = "logit"))
#Con 'summary.gml()' se muestra qu� variables influyen
#en la variable dependiente, dependiendo del numero de asteriscos.
summary.glm(modelo_logistico)

#Call:
#glm(formula = SEXO ~ COMPLEXION.FISICA, family = binomial(link = "logit"))

#Coefficients:
#                    Estimate Std. Error z value Pr(>|z|)
#(Intercept)       -2.667e-02  6.219e-01  -0.043    0.966
#COMPLEXION.FISICA  2.564e-16  2.887e-01   0.000    1.000

#CONCLUSI�N.- La variable COMPLEXION.FISICA no influye en el correspondiente SEXO
#de los encuestados, lo que quiere decir que hay variedad/no se sigue un patr�n de
#que cierto sexo tenga mayormente una cierta complexi�n. Dado esto, la probabilidad
#es casi nula.


########## 9.- Predicciones del modelo log�stico y conclusiones ##########
#Predecir dado un valor de complexi�n f�sica de 3 (Endomorfo)
predict(modelo_logistico, 
        newdata = data.frame(COMPLEXION.FISICA = 3))
#RESULTADO= -0.02666825

#Conclusiones del modelo de regresi�n log�stica.-
#La variable independiente COMPLEXI�N F�SICA no influye en la variable 
#dependiente SEXO por tanto no es posible calcular una probabilidad 
#coherente


########## 10. Coherencia entre an�lisis ##########
#A partir de todas las operaciones previamente realizadas y del an�lisis de la informaci�n
#recabada en la encuesta/base de datos, podemos decir que el hecho de que no exista la suficiente
#correlaci�n entre todas y cada una de las variables es el hecho de que la informaci�n presenta
#datos muy variados entre los 75 registros, en otras palabras, no existe un 'sesgo' entre la
#informaci�n que se presenta en los registros y c�mo esta se va relacionando a lo largo de la
#tabla, por lo que se puede decir que hay gran variedad de casos a pesar de ser solamente 75
#filas.
#Los modelos de regresi�n nos ayudaron a enfocar el an�lisis de esta correlaci�n entre una
#variable dependiente o de respuesta y varias variables independientes o 'de regresi�n', 
#haci�ndonos concluir que hubo un m�nimo valor de correlaciones, solo una variable tuvo relevancia. 
#La otra utilidad de contar con estos modelos fue que pudimos aplicar predicciones a partir de los
#datos con los que ya cont�bamos.



