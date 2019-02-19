/****************************************************/
/****************************************************/
/************PRACTICA DE TEORIA DE CODIGOS***********/
/****************************************************/
/****************** REALIZADA POR: ******************/
/****************************************************/
/********* Jesus Angel Perez-Roca Fernandez *********/
/******************* (infjpf02) *********************/
/****************************************************/
/****************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

void cambiafilas(char **matriz,int fila1,int fila2,int longitud){
	char actual;
	int i;
	for (i=0;i<longitud;i++) {
	    actual=matriz[fila1][i];
	    matriz[fila1][i]=matriz[fila2][i];
	    matriz[fila2][i]=actual;
	}
}

void cambiacolumnas(char **matriz,int col1,int col2,int dimension){
	char actual;
	int i;
	for (i=0;i<dimension;i++) {
	    actual=matriz[i][col1];
	    matriz[i][col1]=matriz[i][col2];
	    matriz[i][col2]=actual;
	}
}

int buscapivote(char **matriz, int dimension, int orden) {
	int i;
	for (i=orden;i<dimension;i++) {
	   if (matriz[i][orden]=='1') return i;
	}
	return -1;
}

void hacerceros(char **matriz, int dimension, int longitud, int orden){
	int i,j;
	for (i=0;i<orden;i++) {
	   for (j=longitud-1;j>=orden;j--) {
	      if (matriz[i][orden]=='1') {
		 if (matriz[orden][j]=='1') {
		   if (matriz[i][j]=='1') matriz[i][j]='0';
		   else matriz[i][j]='1';
		 }
	      }
	   }
	}
	for (i=orden+1;i<dimension;i++) {
	    for (j=longitud-1;j>=orden;j--) {
	       if (matriz[i][orden]=='1') {
		  if (matriz[orden][j]=='1') {
		     if (matriz[i][j]=='1') matriz[i][j]='0';
		     else matriz[i][j]='1';
		  }
	       }
	    }
	}
}

int gauss(char **matriz,int dimension,int longitud,int *cambios) {
     int i=0,pivote,reserva,numero=0;

     reserva=dimension;
     while (i<dimension) {
     	pivote=buscapivote(matriz,dimension,i);
	if (pivote==-1) {
	    if (reserva>=longitud) {
	      printf("tblsind: ERROR: Imposible hacer gauss\n");
	      exit(0);
	    }
	    else {
	      cambiacolumnas(matriz, i, reserva, dimension);
	      cambios[numero]=i;
	      cambios[numero+1]=reserva;
	      numero=numero+2;
	      reserva++;
	      continue;
	    }
	}
	cambiafilas(matriz, i, pivote, longitud);
	hacerceros(matriz, dimension, longitud, i);
	i++;
     }
     return(numero-1);
}

void hprima(char **h,char **matriz,int dimension,int longitud) {
	int i,j,k;
	
	k=longitud-dimension;
	
	for (i=0;i<k;i++) for (j=0;j<dimension;j++) h[i][j]=matriz[j][dimension+i];
	   
	for (j=dimension;j<longitud;j++) for (i=0;i<k;i++) if (i==j-dimension) h[i][j]='1';
	     							else h[i][j]='0';
	     								
}

void deshacercambios(char **h,int dimension,int numcambios,int *cambios) {
	int i;

	for (i=numcambios;i>=0;i-=2)
	cambiacolumnas(h,cambios[i],cambios[i-1],dimension);
}

int comprobacion(char **g,char **h,int dimension,int longitud) {
	int i,j,cont,k,estasuma;
	
	k=longitud-dimension;
	for (i=0;i<dimension;i++) {
	   for (j=0;j<k;j++) {
		estasuma=0;
		for (cont=0;cont<longitud;cont++) if (g[i][cont] == 1 && h[j][cont] == 1) estasuma++;
		if ((estasuma % 2) != 0) return -1;
	   }
	}
	return 0;
}

void calculasindrome(char **h,char *vector,char *sindrome,int longitud,int dimension) {
	int i,j,cont;
	
	for (i=0;i<dimension;i++) {
		cont=0;
		for (j=0;j<longitud;j++) if ((vector[j]=='1') && (h[i][j]=='1')) cont++;
		if (cont%2==0) sindrome[i]='0';
			else sindrome[i]='1';
	}   
}

int factorial(int n) {
	int i, cont;

	cont=1;
	for (i=1;i<=n;i++) cont=cont*i;
	return cont;
}


int sobre(int m, int n) {
	return ((factorial(m))/(factorial(n) * factorial(m-n)));
}
	
int numentradas(int longitud,int l) {
	int i,cont;

	cont=1;
	for (i=1;i<=l;i++) cont=cont+sobre(longitud,i);
	return cont;
				
}

int numunos(char *vector,int longitud) {
	int i,cont;
	cont=0;
	for (i=0;i<longitud;i++) if (vector[i]=='1') cont++;
	return cont;
}

void anterior(char *vector,int longitud) {
	int i,j;

	if (numunos(vector,longitud)==0) for (j=0;j<longitud;j++) vector[j]='1';
		else {
	   		i=longitud-1;
	   		while (vector[i]!='1') i--;
	   	   	vector[i]='0';
	   		for (j=i+1;j<longitud;j++) if (vector[j]=='0') vector[j]='1';
		}
}


int main(int argc,char *argv[]){

char **matriz,**g,**h,*fileout,*codigo,*aux,*vector,*sindrome,a,b=',',c='\n';
int *cambios,id1,id2,i,j,n,k,d,l,numcambios,nivel=0;

if (argc!=3) {
		printf("tblsind: ERROR: Número de argumentos inválido. Ejemplo: tblsind <codigo> <fileout>\n");
		exit(0);
	}
			
codigo=(char *) malloc((strlen(argv[1])+3)*sizeof(char));
if (!((argv[1][0]=='.') || (argv[1][0]=='/'))){
						strcpy(codigo,"."); 
						strcat(codigo,"/");
						strcat(codigo,argv[1]);
					}
	else strcpy(codigo,argv[1]);
if ((id1=open(codigo,O_RDONLY,0777))==-1) {
						printf("tblsind: ERROR: codigo incorrecto\n");
						close(id2);
						exit(0);
					}
					
aux=(char *) malloc(5*sizeof(char));
for (i=0;i<4;i++) {
			read(id1,&aux[i],1);
			if (aux[i]=='\n') {
						if (i==0) {
								printf("tblsind: ERROR: codigo incorrecto\n");
								close(id1);
								close(id2);
								exit(0);
							}
							else break;
					}
				else {
					if ((aux[i]<'0') || (aux[i]>'9') || (i==3) || (aux[0]=='0')) {
													printf("tblsind: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													exit(0);
												}
				}
		}
n=atoi(aux);

for (i=0;i<4;i++) {
			read(id1,&aux[i],1);
			if (aux[i]=='\n') {
						if (i==0) {
								printf("tblsind: ERROR: codigo incorrecto\n");
								close(id1);
								close(id2);
								exit(0);
							}
							else break;
					}
				else {
					if ((aux[i]<'0') || (aux[i]>'9') || (i==3) || (aux[0]=='0')) {
													printf("tblsind: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													exit(0);
												}
				}
		}
k=atoi(aux);

for (i=0;i<4;i++) {
			read(id1,&aux[i],1);
			if (aux[i]=='\n') {
						if (i==0) {
								printf("tblsind: ERROR: codigo incorrecto\n");
								close(id1);
								close(id2);
								exit(0);
							}
							else break;
					}
				else {
					if ((aux[i]<'0') || (aux[i]>'9') || (i==3) || (aux[0]=='0')) {
													printf("tblsind: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													exit(0);
												}
				}
		}
d=atoi(aux);

matriz=(char **) malloc((k+1)*sizeof(char));
for (i=0;i<k;i++) matriz[i]=(char *) malloc((n+1)*sizeof(char));

for (i=0;i<k;i++) {
			for (j=0;j<n+1;j++){
						read(id1,&a,1);
						if (a=='\n') {
								if (j==0) {
										printf("tblsind: ERROR: codigo incorrecto\n");
										close(id1);
										close(id2);
										exit(0);
									}
									else break;
							}
							else {
								if (((a!='0') && (a!='1')) || (j==n)) {
													printf("tblsind: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													exit(0);
												}
									else matriz[i][j]=a;
							}
					}
		}

g=(char **) malloc((k+1)*sizeof(char));
for (i=0;i<k;i++) g[i]=(char *) malloc((n+1)*sizeof(char));

h=(char **) malloc((n+1)*sizeof(char));
for (i=0;i<n;i++) h[i]=(char *) malloc(((n-k)+1)*sizeof(char));

for (i=0;i<k;i++) for (j=0;j<n;j++) g[i][j]=matriz[i][j];

fileout=(char *) malloc((strlen(argv[2])+3)*sizeof(char));
if (!((argv[2][0]=='.') || (argv[2][0]=='/'))){
						strcpy(fileout,"."); 
						strcat(fileout,"/");
						strcat(fileout,argv[2]);
					}
	else strcpy(fileout,argv[2]);
if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
								printf("tblsind: ERROR: No tiene permiso para crear un fichero en este directorio\n");
								exit(0);
							}
							
cambios=(int *) malloc(2*(n-k)*sizeof(int));

numcambios=gauss(g,k,n,cambios);

hprima(h,g,k,n);

deshacercambios(h,(n-k),numcambios,cambios);

if (comprobacion(matriz,h,k,n)) {
				printf("tblsind: ERROR: [G]*[H]tr!=0\n");
				exit(0);
			}

l=(d-1-(d%2==0))/2;
if (l>(n-1)) {
		printf("tblsind: ERROR: distancia minima incorrecta\n");
		exit(0);
	}

vector=(char *) malloc((n+1)*sizeof(char));
for (i=0;i<n;i++) vector[i]='0';

sindrome=(char *) malloc((k+1)*sizeof(char));
for (i=0;i<k;i++) sindrome[i]='0';

j = 0;
do {
	if (numunos(vector,n)==nivel) {
			calculasindrome(h,vector,sindrome,n,k);
			for (i=0;i<n;i++) write(id2,&vector[i],1);
			write(id2,&b,1);
			for (i=0;i<k;i++) write(id2,&sindrome[i],1);
			write(id2,&c,1);
			j++;

		}
		anterior(vector,n);
		if (numunos(vector,n)==n) nivel++;
	} while (nivel<=l);
	
}
