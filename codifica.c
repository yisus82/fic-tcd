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

int main(int argc,char *argv[]) {

char *filein,*fileout,*codigo,*aux,a,b,c='\n';
int **matriz,*pfuente,*pcodigo,*aux2,id1,id2,id3,resta=(argc==4),i,j,l,n,k,d,fin=0,cont1=0,cont2=0;
DIR *dir;
struct dirent *fichero;
struct stat propiedad;

if ((argc>5) || (argc<4)) {
				printf("codifica: ERROR: Número de argumentos inválido. Ejemplo: codifica [ | -a | -b] <codigo> <filein> <fileout>\n");
				exit(0);
			}

filein=(char *) malloc((strlen(argv[3-resta])+3)*sizeof(char));
if (!((argv[3-resta][0]=='.') || (argv[3-resta][0]=='/'))){
								strcpy(filein,"."); 
								strcat(filein,"/");
								strcat(filein,argv[3-resta]);
							}
	else strcpy(filein,argv[3-resta]);
if ((id1=open(filein,O_RDONLY,0777))==-1) {
						printf("codifica: ERROR: No se encuentra el archivo a codificar %s\n",argv[3-resta]);
						exit(0);
					}	


codigo=(char *) malloc((strlen(argv[2-resta])+3)*sizeof(char));
if (!((argv[2-resta][0]=='.') || (argv[2-resta][0]=='/'))){
								strcpy(codigo,"."); 
								strcat(codigo,"/");
								strcat(codigo,argv[2-resta]);
							}
	else strcpy(codigo,argv[2-resta]);
if ((id3=open(codigo,O_RDONLY,0777))==-1) {
						printf("codifica: ERROR: codigo incorrecto\n");
						close(id1);
						close(id2);
						exit(0);
					}
					
aux=(char *) malloc(5*sizeof(char));
for (i=0;i<4;i++) {
			read(id3,&aux[i],1);
			if (aux[i]=='\n') {
						if (i==0) {
								printf("codifica: ERROR: codigo incorrecto\n");
								close(id1);
								close(id2);
								close(id3);
								exit(0);
							}
							else break;
					}
				else {
					if ((aux[i]<'0') || (aux[i]>'9') || (i==3) || (aux[0]=='0')) {
													printf("codifica: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													close(id3);
													exit(0);
												}
				}
		}
n=atoi(aux);

for (i=0;i<4;i++) {
			read(id3,&aux[i],1);
			if (aux[i]=='\n') {
						if (i==0) {
								printf("codifica: ERROR: codigo incorrecto\n");
								close(id1);
								close(id2);
								close(id3);
								exit(0);
							}
							else break;
					}
				else {
					if ((aux[i]<'0') || (aux[i]>'9') || (i==3) || (aux[0]=='0')) {
													printf("codifica: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													close(id3);
													exit(0);
												}
				}
		}
k=atoi(aux);

for (i=0;i<4;i++) {
			read(id3,&aux[i],1);
			if (aux[i]=='\n') {
						if (i==0) {
								printf("codifica: ERROR: codigo incorrecto\n");
								close(id1);
								close(id2);
								close(id3);
								exit(0);
							}
							else break;
					}
				else {
					if ((aux[i]<'0') || (aux[i]>'9') || (i==3) || (aux[0]=='0')) {
													printf("codifica: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													close(id3);
													exit(0);
												}
				}
		}
d=atoi(aux);

matriz=(int **) malloc(k*sizeof(int));
for (i=0;i<k;i++) matriz[i]=(int *) malloc(n*sizeof(int));

for (i=0;i<k;i++) {
			for (j=0;j<n+1;j++){
						read(id3,&a,1);
						if (a=='\n') {
								if (j==0) {
										printf("codifica: ERROR: codigo incorrecto\n");
										close(id1);
										close(id2);
										close(id3);
										exit(0);
									}
									else break;
							}
							else {
								if (((a!='0') && (a!='1')) || (j==n)) {
													printf("codifica: ERROR: codigo incorrecto\n");
													close(id1);
													close(id2);
													close(id3);
													exit(0);
												}
									else matriz[i][j]=a-48;
							}
					}
		}

fileout=(char *) malloc((strlen(argv[4-resta])+3)*sizeof(char));
if (!((argv[4-resta][0]=='.') || (argv[4-resta][0]=='/'))){
								strcpy(fileout,"."); 
								strcat(fileout,"/");
								strcat(fileout,argv[4-resta]);
							}
	else strcpy(fileout,argv[4-resta]);
if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
								printf("codifica: ERROR: No tiene permiso para crear un fichero en este directorio\n");
								close(id1);
								exit(0);
							}
							
							
pfuente=(int *) malloc(k*sizeof(int));
pcodigo=(int *) malloc(n*sizeof(int));
			
dir=opendir(".");
while ((fichero=readdir(dir))!=NULL) if ((!strcmp((fichero->d_name),argv[3-resta])) && (lstat(filein,&propiedad)!=(-1))) i=propiedad.st_size;


	
if (!(strcmp(argv[1],"-a")) && (argc==5)) {
						aux=(char *) malloc(11*sizeof(char));
						sprintf(aux,"%d",i);
						for (i=0;i<11;i++) write(id2,&aux[i],1);
						write(id2,&c,1);
						while(1){
								for (i=0;i<k;i++) pfuente[i]=0;
								for (i=0;i<k;i++) {
											if (read(id1,&a,1)==0) fin=1;
											if (fin==1) exit(0);
											if  ((a!='0') && (a!='1')) { 
															if ((a!=32) && (a!=9) && (a!=10)) {
																				printf("codifica: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[3],a);
																				close(id1);
																				close(id2);
																				exit(0);
																			}
																else {
																	i--;
																	continue; 
																}
														}
												else if (fin==0) pfuente[i]=a-48;
										}
								if (cont1==1) {
										cont1=0;
										write(id2,&c,1);
									}
								for (i=0;i<n;i++) pcodigo[i]=0;
								for (j=0;j<n;j++) for (i=0;i<k;i++) pcodigo[j]=pcodigo[j]^(pfuente[i]&matriz[i][j]);
								for (i=0;i<n;i++) {
											pcodigo[i]+=48;
											write(id2,&pcodigo[i],1);
										}
								cont1++;
							}
}
	else {
		if ((strcmp(argv[1],"-b")) && (argc==5)) {
								printf("codifica: ERROR: Argumento inválido. Ejemplo: codifica [ | -a | -b] <codigo> <filein> <fileout>\n");
								close(id1);
								close(id2);
								close(id3);
								exit(0);
							}
		aux=(char *) malloc((4+1)*sizeof(char));
		for (j=3;j>=0;j--) {
       			aux[j]=i%256;
       			i=i/256;
    		}
		for (j=0;j<4;j++) write(id2,&aux[j],1);
		a=0;
    		l=0;
    		b=0;
    		cont1=0;
    		aux2=(int *) malloc(k*sizeof(int));

    		while (1) {
	  	  	for (i=0;i<k;i++) {
	      			if (l==0) {
		 				l=128;
		 				if (read(id1,&a,1)==0) fin=1;
	     				}
	      			if (fin) a=0;
	      	      		aux2[i]=(a/l)&1;
	      			l=l>>1;
	  		}
	  
	  		for (j=0;j<n;j++) {
	      			cont2=(aux2[0]&matriz[0][j]);
	      			for (i=1;i<k;i++) cont2=cont2^(aux2[i] & matriz[i][j]);
	      			cont1++;
	      			b=b*2;
	      			if (cont2) b++;
	      			if (cont1%8==0) write(id2,&b,1);
	      		}
	      		if (fin) break;
  		}
	    	
	    	if (cont1%8!=0) {
       				while (cont1%8!=0) {
	     				cont1++;
	     				b=b*2;
       				}
       				write(id2,&b,1);
     			}
	}
}
									