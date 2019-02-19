
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int modo = 0;

//FUNCION QUE CUENTA EL NUMERO DE ENTRADAS DE LA TABLA DE SINDROMES
int cuentaentradas(char *nombrearch) {
    char actual;
    int leialgo = 0;
    int lineas = 0;
    FILE* entrada;

    entrada = fopen(nombrearch,"r");
    if (entrada == NULL) {
	printf("TBLSIND: ERROR: Imposible abrir fichero %s\n", nombrearch);
	exit(1);
    }
    while ((actual = fgetc(entrada)) != EOF) {
	if (actual == '0' || actual == '1' || actual == ',') leialgo = 1;
	if ((actual == '\n') && (leialgo != 0)) {
	   lineas++;
	   leialgo = 0;
        }
    }
    if (leialgo != 0) lineas++;
    fclose(entrada);
    return lineas;
}

//FUNCION QUE CARGA LA TABLA DE SINDROMES EN MEMORIA
void cargatabla(char **tabla, char *archivo, int numentradas, int longentrada) {
    FILE *entrada;
    int i, j;
    char actual;

    entrada = fopen(archivo, "rt");
    if (entrada == NULL) {
	printf("TBLSIND: ERROR: Imposible abrir fichero %s\n", archivo);
	exit(-1);
    }

    for (i = 0; i < numentradas; i++) {
	for (j = 0; j < longentrada; j++) {
	   actual = fgetc(entrada);
	   if (actual != '0' && actual != '1' && actual != ',') {
		printf("TBLSIND: ERROR: Imposible abrir fichero %s\n", archivo);
		exit(-1);
	   }
	   tabla[i][j] = actual;
	}
	actual = fgetc(entrada);
	while (actual != EOF && actual != '\n') actual = fgetc(entrada);
	if (actual == EOF) break;
    }

    fclose(entrada);
}

//CALCULO DEL FACTORIAL DE UN NUMERO
int factorial(int numero) {
	int i, contador;

	contador = 1;
	for (i = 1; i <= numero; i++) contador *= i;
	return contador;
}

//CALCULO DE UN NUMERO SOBRE OTRO
int sobre(int m, int n) {
	return ((factorial(m))/(factorial(n) * factorial(m-n)));
}

//CALCULO DE L A PARTIR DE LA DISTANCIA MINIMA
int calculal(int distancia) {
	if (distancia % 2 == 0) {
		//ES DE LA FORMA d = 2l+2
		return ((distancia - 2)/2);
	}
	else {
		//ES DE LA FORMA d = 2l+1
		return ((distancia - 1)/2);
	}
}

//CALCULO DEL NUMERO DE ENTRADAS DE LA TABLA DE SINDROMES
int calculaentradas (int longitud, int l) {
	int i, contador;

	//SE TIENE EN CUENTA EL ERROR DE ORDEN 0: LA PALABRA CODIGO
	contador = 1;
	for (i = 1; i <= l; i++) contador += sobre(longitud, i);
	return contador;
}

//FUNCION QUE HALLA EL SINDROME DE UN VECTOR
void calculasindrome(char **h, char *vector, char *sindrome, int longitud, int dimension) {
	int i, j, contador;
	
	for (i = 0; i < dimension; i++) {
		contador = 0;
		for (j = 0; j < longitud; j++) {
			if (vector[j] == '1' && h[i][j] == '1') contador++;
		}
		if (contador % 2 == 0) sindrome[i] = '0';
		else sindrome[i] = '1';
	}   
}

//FUNCION QUE CALCULA EL NUMERO DE UNOS DE UN VECTOR
int numunos(char* vector, int longitud) {
	int i, contador;
	contador = 0;
	for (i = 0; i < longitud; i++) if (vector[i] == '1') contador++;
	return contador;
}

//FUNCION QUE DADO UN VECTOR CALCULA EL SIGUIENTE EN ORDEN LEXICOGRAFICO
//Nota: el siguiente del vector todo unos es el vector todo ceros
void siguiente(char *vector, int longitud) {
	int i, j;

	if (numunos(vector, longitud) == longitud) {
	   for (j = 0; j < longitud; j++) vector[j] = '0';
	}
	else {
	   i = longitud - 1;
	   while (vector[i] != '0') {
		i--;
	   }
	   vector[i] = '1';
	   for (j = i + 1; j < longitud; j++)if (vector[j] == '1') vector[j] = '0';
	}
}

//FUNCION QUE ELABORA LA TABLA DE SINDROMES INCOMPLETA
void construyetabla(char *tabla, char **h, char *vector, char* sindrome,
		 int l, int longitud, int dimension) {
	FILE *salida;
	int i, j;

	salida = fopen(tabla, "w");
	if (salida == NULL) {
		printf("TBLSIND: ERROR: Imposible abrir fichero %s\n", tabla);
		exit(-1);
	}

	j = 0;
	do {
		if (numunos(vector, longitud) <= l) {
			calculasindrome(h, vector, sindrome, longitud, dimension);
			for (i = 0; i < longitud; i++) {
				fputc(vector[i], salida);
				if (modo != 0) printf("%c", vector[i]);
			}
			fputc(',', salida);
			if (modo != 0) printf(",");
			for (i = 0; i < dimension; i++) {
				fputc(sindrome[i], salida);
				if (modo != 0) printf("%c", sindrome[i]);
			}
			fputc('\n', salida);
			if (modo != 0) printf("\n");
			j++;

		}
		siguiente(vector, longitud);
	} while (numunos(vector, longitud) != 0);
        fclose(salida);
}

//LECTURA DE LA LONGITUD, LA DIMENSION Y LA DISTANCIA MINIMA
void lectura1(char *archivo, int *dimension, int *longitud, int *distancia) {

    FILE *entrada;
    char actual;
    int linea, columna, numero;

    entrada = fopen(archivo,"rt");
    if (entrada == NULL) {
	printf("TBLSIND: ERROR: Codigo incorrecto\n");
	exit(-1);
    }

    linea = 1;
    do {
      numero = 0;
      if (feof(entrada)) {
	  printf("TBLSIND: ERROR: Codigo incorrecto\n");
	  exit(-1);
      }
      do {
	actual = fgetc(entrada);
	if (feof(entrada)) {
	  printf("TBLSIND: ERROR: Codigo incorrecto\n");
	  exit(-1);
	}
	if ((actual < '0' || actual > '9') && (actual != '\n')) {
	  do {
	     if (feof(entrada) || ((actual != '\n') && (actual != ' ')
		 && (actual != '\t'))) {
		 printf("TBLSIND: ERROR: Codigo incorrecto\n");
		 exit(-1);
	     }
	     actual = fgetc(entrada);
	  } while (actual != '\n');
	}
	else {
	  if (actual != '\n') {
	     numero *= 10;
	     numero += actual - '0';
	  }
	}
      } while (actual != '\n');
      if ((numero == 0) || ((linea == 3) && (numero > 99))) {
	 printf("TBLSIND: ERROR: Codigo incorrecto\n");
	 exit(-1);
      }
      if (linea == 1) *longitud = numero;
      if (linea == 2) *dimension = numero;
      if (linea == 3) *distancia = numero;
      linea++;
    } while (linea < 4);
    fclose(entrada);
}

//LECTURA DE LA MATRIZ GENERADORA DEL CODIGO
char** lectura2(char *archivo, int dimension, int longitud) {

    FILE *entrada;
    char actual;
    int contador, linea, columna, numero;
    char **matriz;

    entrada = fopen(archivo,"r");
    if (entrada == NULL) {
	printf("TBLSIND: ERROR: Codigo incorrecto\n");
	exit(-1);
    }

    contador = 0;
    while (contador < 3) {
	actual = fgetc(entrada);
	if (actual == '\n') contador++;
    }

    columna = 0;
    matriz = (char**) malloc(dimension * sizeof(char*));
    if (matriz == NULL) {
	printf("TBLSIND: ERROR: Falta memoria\n");
	exit(-1);
    }
    for (linea = 0; linea < dimension; linea++) {
       matriz[linea] = (char*) malloc(longitud * sizeof(char));
       if (matriz[linea] == NULL) {
	  printf("TBLSIND: ERROR: Falta memoria\n");
	  exit(-1);
       }
    }

    for (linea = 0; linea < dimension; linea++) {
       for (columna = 0; columna < longitud; columna++) {
	  if (feof(entrada)) {
	     printf("TBLSIND: ERROR: Codigo incorrecto\n");
	     exit(-1);
	  }
	  actual = fgetc(entrada);
	  if (actual != '0' && actual != '1') {
	     printf("TBLSIND: ERROR: Codigo incorrecto\n");
	     exit(-1);
	  }
	  matriz[linea][columna] = actual;
       }
       if (linea < dimension - 1) {
	  while (actual != '\n') {
	       if (feof(entrada)) {
		  printf("TBLSIND: ERROR: Codigo incorrecto\n");
		  exit(-1);
	       }
	       actual = fgetc(entrada);
	       if (actual != '\n' && actual != ' ' && actual != '\t') {
		  printf("TBLSIND: ERROR: Codigo incorrecto\n");
		  exit(-1);
	       }
	  }
       }
       else {
	   while (!feof(entrada)) {
		actual = fgetc(entrada);
		if (!feof(entrada) && actual != '\n' && actual != ' '
		    && actual != '\t') {
		    printf("TBLSIND: ERROR: Codigo incorrecto\n");
		    exit(-1);
		}
	   }
       }
    }

    fclose(entrada);
    return matriz;
}

//FUNCION QUE DIBUJA UNA MATRIZ
void dibug(char **matriz, int dimension, int longitud) {
    int linea, columna;

    for (linea = 0; linea < dimension; linea++) {
       for (columna = 0; columna < longitud; columna++) {
	  printf("%c ", matriz[linea][columna]);
       }
       printf("\n");
    }
}

//FUNCION QUE CREA UNA MATRIZ COPIA DE OTRA RESERVANDOLE MEMORIA
char **copiag(char **matriz, int dimension, int longitud){
	char **copia;
	int i, j;
	copia = (char**) malloc(dimension * sizeof(char*));
	if (copia == NULL) {
	  printf("TBLSIND: ERROR: Falta memoria\n");
	  exit(-1);
	}
	for (i = 0; i < dimension; i++) {
	   copia[i] = (char*) malloc(longitud * sizeof(char));
	   if (copia[i] == NULL) {
              printf("TBLSIND: ERROR: Falta memoria\n");
	      exit(-1);
	   }
	}
	for (i = 0; i < dimension; i++) {
	   for (j = 0; j < longitud; j++) {
		copia[i][j] = matriz[i][j];
	   }
	}
	return copia;
}

//FUNCION QUE LE RESERVA MEMORIA A UNA MATRIZ DE CARACTERES
char** creamatriz(int dimension, int longitud){
	int i;
	char **h;
	
	h = (char**) malloc(dimension * sizeof(char*));
	if (h == NULL){
	   printf("TBLSIND: ERROR: Falta memoria\n");
	   exit(-1);
	}
	
	for (i = 0; i < dimension; i++) {
	    h[i] = (char*) malloc(longitud * sizeof(char));
	    if (h[i] == NULL) {
		printf("TBLSIND: ERROR: Falta memoria\n");
		exit(-1);
	    }
	}
	return h;
}

//FUNCION QUE INTERCAMBIA DOS FILAS
void cambiafilas(char **matriz, int fila1, int fila2, int longitud){
	char actual;
	int i;
	for (i = 0; i < longitud; i++) {
	    actual = matriz[fila1][i];
	    matriz[fila1][i] = matriz[fila2][i];
	    matriz[fila2][i] = actual;
	}
}

//FUNCION QUE INTERCAMBIA DOS COLUMNAS
void cambiacolumnas(char **matriz, int col1, int col2, int dimension){
	char actual;
	int i;
	for (i = 0; i < dimension; i++) {
	    actual = matriz[i][col1];
	    matriz[i][col1] = matriz[i][col2];
	    matriz[i][col2] = actual;
	}
}

//FUNCION QUE BUSCA LA FILA DONDE ESTARA EL PIVOTE
int buscapivote(char **matriz, int dimension, int orden) {
	int i;
	for (i = orden; i < dimension; i++) {
	   if (matriz[i][orden] == '1') return i;
	}
	return -1;
}

//FUNCION QUE HACE CEROS POR ENCIMA Y POR DEBAJO DEL PIVOTE
void hacerceros(char **matriz, int dimension, int longitud, int orden){
	int i, j;
	for (i = 0; i < orden; i++) {
	   for (j = longitud - 1; j >= orden; j--) {
	      if (matriz[i][orden] == '1') {
		 if (matriz[orden][j] == '1') {
		   if (matriz[i][j] == '1') matriz[i][j] = '0';
		   else matriz[i][j] = '1';
		 }
	      }
	   }
	}
	for (i = orden + 1; i < dimension; i++) {
	    for (j = longitud - 1; j >= orden; j--) {
	       if (matriz[i][orden] == '1') {
		  if (matriz[orden][j] == '1') {
		     if (matriz[i][j] == '1') matriz[i][j] = '0';
		     else matriz[i][j] = '1';
		  }
	       }
	    }
	}
}

//FUNCION QUE HACE GAUSS A UNA MATRIZ
int gausear(char **matriz, int dimension, int longitud, int *cambios) {
     int i, pivote, reserva, numero;

     reserva = dimension;
     numero = 0;
     i = 0;
     while (i < dimension) {
     	pivote = buscapivote(matriz, dimension, i);
	if (pivote == -1) {
	    if (reserva >= longitud) {
	      printf("TBLSIND: ERROR: Imposible gauss\n");
	      exit(-1);
	    }
	    else {
	      cambiacolumnas(matriz, i, reserva, dimension);
	      cambios[numero] = i;
	      cambios[numero + 1] = reserva;
	      numero += 2;
	      reserva++;
	      continue;
	    }
	}
	cambiafilas(matriz, i, pivote, longitud);
	hacerceros(matriz, dimension, longitud, i);
	i++;
     }
     return (numero - 1);
}

//FUNCION QUE CREA H' A PARTIR DE G'
void llenah(char **h, char **matriz, int dimension, int longitud) {
	int i, j, k;
	
	k = longitud - dimension;
	
	for (i = 0; i < k; i++) {
	   for (j = 0; j < dimension; j++) {
	      h[i][j] = matriz[j][dimension + i];
	   }
	}
	
	for (j = dimension; j < longitud; j++) {
	   for (i = 0; i < k; i++) {
	     if (i == j - dimension) h[i][j] = '1';
	     else h[i][j] = '0';
	   }
	}
}

//FUNCION QUE TRANSFORMA H' EN H DESHACIENDO CAMBIOS EN COLUMNAS
void reformah(char **h, int dimension, int numcambios, int *cambios) {
	int i;

	for (i = numcambios; i >= 0; i-=2)
	cambiacolumnas(h, cambios[i], cambios[i-1], dimension);
}

//FUNCION QUE COMPRUEBA SI [G] * [H]tr = 0
int comprobacion(char **g, char **h, int dimension, int longitud) {
	int i, j, cont, k, estasuma;
	
	k = longitud - dimension;
	for (i = 0; i < dimension; i++) {
	   for (j = 0; j < k; j++) {
		estasuma = 0;
		for (cont = 0; cont < longitud; cont++) {
		   if (g[i][cont] == 1 && h[j][cont] == 1) estasuma++;
		}
		if ((estasuma % 2) != 0) return -1;
	   }
	}
	return 0;
}

char** calcularH(char *entrada, int dimension, int longitud, int distancia) {
    int i, k, numcambios;
    char **matriz, **g, **h;
    int *cambios;

    //LEEMOS LOS DETALLES DEL CODIGO DEL PRIMER ARCHIVO
    matriz = lectura2(entrada, dimension, longitud);
    k = longitud - dimension;
    if (k <= 0) {
	printf("TBLSIND: ERROR: Imposible encontrar matriz de paridad\n");
	exit(-1);
    }

    //ESCRIBIMOS LOS DETALLES DEL CODIGO POR PANTALLA
    if (modo == 1 || modo == 2) {
	printf("Dimension del codigo: %d\n", dimension);
	printf("Longitud del codigo: %d\n", longitud);
	printf("Distancia minima del codigo: %d\n", distancia);
	printf("La matriz generadora G es:\n");
	dibug(matriz, dimension, longitud);
    }

    //RESERVAMOS MEMORIA PARA EL VECTOR DE CAMBIOS EN COLUMNAS
    cambios = (int*) malloc(2 * k * sizeof(int));
    if (cambios == NULL) {
       printf("TBLSIND: ERROR: FALTA MEMORIA\n");
       exit(-1);
    }

    //SE CREA UNA COPIA PARA OPERAR SOBRE ELLA
    g = copiag(matriz, dimension, longitud);
    numcambios = gausear(g, dimension, longitud, cambios);
    if (modo == 1) {
	printf("La matriz G' sistematica equivalente a G es:\n");
	dibug(g, dimension, longitud);
    }

    //SE PINTAN LOS CAMBIOS REALIZADOS EN COLUMNAS
    if (modo == 1) {
       printf("Cambios realizados en columnas:\n");
       if (numcambios == -1) printf("No hubo cambios en columnas\n");
       else {
	    for (i = 0; i <= numcambios; i+=2) {
	       printf("%d <-> %d; ", cambios[i], cambios[i+1]);
	    }
	    printf("\n");
       }
    }

    //SE RESERVA MEMORIA PARA LA MATRIZ H
    h = creamatriz(k, longitud);

    //SE CONSTRUYE LA MATRIZ H'
    llenah(h, g, dimension, longitud);
    if (modo == 1) {
       printf("Obtenemos asi la siguiente matriz H'\n");
       dibug(h, k, longitud);
    }

    //SE CONSTRUYE LA MATRIZ H
    reformah(h, k, numcambios, cambios);
    if (modo == 1)
       printf("Ahora deshacemos los cambios en columnas para obtener H\n");
    if (modo == 1 || modo == 2) {
       printf("\nLa matriz control de paridad H es:\n");
       dibug(h, k, longitud);
    }

    //COMPROBAMOS SI G*[H]tr = 0
    if (comprobacion(matriz, h, dimension, longitud) == 0) {
       if (modo == 1 || modo == 2) printf("[G] * [H]tr = 0\n");
    }
    else printf("TBLSIND: ERROR: [G] * [H]tr <> 0\n");

    //SE LIBERA LA MEMORIA Y SE SALE
    free(matriz);
    free(g);
    free(cambios);
    return h;
}

void calcularT(char *entrada, char *salida){

    int i, j, k, l, dimension, longitud, distancia, numentradas, longtabla;
    char **h, **tabla;
    char *vector, *sindrome;

    //LEEMOS LOS DETALLES FUNDAMENTALES DEL CODIGO
    lectura1(entrada, &dimension, &longitud, &distancia);
    k = longitud - dimension;

    //CALCULAMOS LA MATRIZ DE PARIDAD H
    h = calcularH(entrada, dimension, longitud, distancia);

    //SE CALCULA EL VALOR DE l
    l = calculal(distancia);

    //SE PREPARA EL VECTOR QUE CALCULARA LOS SINDROMES
    vector = (char*)malloc(longitud * sizeof(char));
    if (vector == NULL) {
	printf("TBLSIND: ERROR: Falta memoria\n");
	exit(-1);
    }
    for (i = 0; i < longitud; i++) vector[i] = '0';

    //SE PREPARA EL ARRAY DONDE SE GUARDARA EL SINDROME
    sindrome = (char*)malloc(k * sizeof(char));
    if (sindrome == NULL) {
	printf("TBLSIND: ERROR: Falta memoria\n");
	exit(-1);
    }
    for (i = 0; i < k; i++) sindrome[i] = '0';    

    //SE CONSTRUYE LA TABLA DE SINDROMES
    construyetabla(salida, h, vector, sindrome, l, longitud, k);

    /* ACTIVAR ESTE CODIGO SI SE QUIERE CARGAR LA TABLA EN MEMORIA

    //SE CALCULA EL NUMERO DE ENTRADAS QUE TENDRA LA TABLA
    numentradas = cuentaentradas(salida);
    if (modo == 1 || modo == 2)
	printf("\nNumero de entradas en la tabla de sindromes: %d\n", numentradas);

    //SE RESERVA MEMORIA PARA LA TABLA Y SE LLENA
    longtabla = longitud + k + 1;
    tabla = creamatriz(numentradas, longtabla);
    cargatabla(tabla, salida, numentradas, longtabla);

    //SE IMPRIME LA TABLA COMO COMPROBACION
    if (modo == 2) {
	printf("\n");
	for (i = 0; i < numentradas; i++) {
	    for (j = 0; j < longtabla; j++) printf("%c", tabla[i][j]);
	    printf("\n");
	}
	printf("\nNumero de entradas en la tabla de sindromes: %d\n", numentradas);
    }

    FIN DE CODIGO DE CARGA DE TABLA EN MEMORIA*/

    //SE LIBERA LA MEMORIA Y SE SALE
    free(h);
    free(tabla);
}

int main (int argc, char * argv []) {
    if (argc != 3) {
       printf("TBLSIND: ERROR: Numero de argumentos incorrecto\n");
       exit(-1);
    }
    if (!strcmp(argv[1],argv[2])) {
       printf("TBLSIND: ERROR: Intento de modificacion de archivo de entrada %s\n", argv[2]);
       exit(-1);
    }
    calcularT(argv[1], argv[2]);
    return 0;
}

