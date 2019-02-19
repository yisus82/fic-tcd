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


int main(int argc,char *argv[]){

char *file,*aux,a,car;
int id,i,num,resta=0,cont=0,total=0;

if ((argc>4) || (argc<3)) {
				printf("numbit: ERROR: Número de argumentos inválido. Ejemplo: numbit [ | -a | -b] [0 | 1] <file>\n");
				exit(0);
			}

if (!(strcmp(argv[1],"-a"))) {
				if (argc<4) {
						printf("numbit: ERROR: Número de argumentos inválido. Ejemplo: numbit [ | -a | -b] [0 | 1] <file>\n");
						exit(0);
				}
				file=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
				if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
										strcpy(file,"."); 
										strcat(file,"/");
										strcat(file,argv[3]);
									}
					else strcpy(file,argv[3]);
				if ((id=open(file,O_RDONLY,0777))==-1) {
									printf("numbit: ERROR: No existe el archivo %s\n",argv[3]);
									exit(0);
									}
				if ((num=atoi(argv[2]))!=1) {
								if (strcmp("0",argv[2])) {
												printf("numbit: ERROR: Argumento inválido. Ejemplo: numbit [ | -a | -b] [0 | 1] <file>\n");
												close(id);												
												exit(0);
											}
							}
				car=num+48;
				while(1){
						if (read(id,&a,1)==0) break;
						if ((a=='0') || (a=='1')) {
										total++;
										if  (a==car) cont++;
									}
							else if ((a!=32) && (a!=9) && (a!=10)) {
												printf("numbit: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[3],a);
												close(id);
												exit(0);
												} 	
					}
				printf("%d de %d (%.4f %%)\n\n",cont,total,((float)cont/(float)total)*100);
}

	else if ((argc==4) && (strcmp(argv[1],"-b"))) {
							printf("numbit: ERROR: Argumento inválido. Ejemplo: numbit [ | -a | -b] [0 | 1] <file>\n");
							exit(0);
						}
 		else {
 			resta=(argc==3);
			file=(char *) malloc((strlen(argv[3-resta])+3)*sizeof(char));
			if (!((argv[3-resta][0]=='.') || (argv[3-resta][0]=='/'))){
											strcpy(file,"."); 
											strcat(file,"/");
											strcat(file,argv[3-resta]);
										}
				else strcpy(file,argv[3-resta]);
			if ((id=open(file,O_RDONLY,0777))==-1) {
								printf("sumabi: ERROR: No existe el archivo %s\n",argv[3-resta]);														
								exit(0);
								}
			if ((num=atoi(argv[2-resta]))!=1) {
								if (strcmp("0",argv[2-resta])) {
												printf("numbit: ERROR: Argumento inválido. Ejemplo: numbit [ | -a | -b] [0 | 1] <file>\n");
												close(id);			
												exit(0);
												}
							}
			while(1){
				if (read(id,&a,1)==0) break;
				for (i=0;i<8;i++) {
							if ((a&1)==num) cont++;
							total++;
							a=a>>1;
						}
				}
                        printf("%d de %d (%2.4f %%)\n\n",cont,total,((float)cont/(float)total)*100);
		}
}
