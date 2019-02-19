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

char *filein,*fileout,a,b;
int id1,id2,resta=0,i,n,escribe=1,cont,numcar,fin=0,principio=1;

if ((argc>5) || (argc<3)) {
				printf("transmit: ERROR: Número de argumentos inválido. Ejemplo: transmit [ | -a | -b] <n> <filein> <fileout>\n");
				exit(0);
			}

if (!(strncmp(argv[1],"-a",2))) {
					if (((n=atoi(argv[2]))<0) || ((n=atoi(argv[2]))>10000)) {
													printf("transmit: ERROR: Argumento inválido. Ejemplo: transmit [ | -a | -b] <n> <filein> <fileout>\n");
													exit(0);
												}
					if ((n==0) && (strcmp("0",argv[2]))) {
										printf("transmit: ERROR: Argumento inválido. Ejemplo: transmit [ | -a | -b] <n> <filein> <fileout>\n");
										exit(0);
									}
					if (argc>3) {
							filein=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
							if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
													strcpy(filein,"."); 
													strcat(filein,"/");
													strcat(filein,argv[3]);
												}
								else strcpy(filein,argv[3]);
							if ((id1=open(filein,O_RDONLY,0777))==-1) {
													printf("transmit: ERROR: No existe el archivo %s\n",argv[3]);
													exit(0);
												}
							if (argc==5) {
									fileout=(char *) malloc((strlen(argv[4])+3)*sizeof(char));
									if (!((argv[4][0]=='.') || (argv[4][0]=='/'))){
															strcpy(fileout,"."); 
															strcat(fileout,"/");
															strcat(fileout,argv[4]);
														}
										else strcpy(fileout,argv[4]);
									if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
																	printf("transmit: ERROR: No tiene permiso para crear un fichero en este directorio\n");
																	close(id1);
																	exit(0);
																}
									while(1){
										if (read(id1,&a,1)==0) break; 
										if  ((a!='0') && (a!='1')) { if ((a==32) || (a==9)|| (a==10)) {if (a!=10) write(id2,&a,1);}
														else {
															printf("transmit: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[3],a);
															close(id1);
															close(id2);
															exit(0);
														} 
													}
										i=rand()%10000;
										if (i<n) {
												if (a=='0') a='1';
													else a='0';
											}
										write(id2,&a,1);
										}											
							}
								else {
									printf("Bits transmitidos:\n");
									while(1){
										if (read(id1,&a,1)==0) break; 
										if  ((a!='0') && (a!='1')) { if ((a==32) || (a==9) || (a==10)) continue;
														else {
															printf("transmit: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[3],a);
															close(id1);
															exit(0);
														} 
													}
										i=rand()%10000;
										if (i<n) {
												if (a=='0') a='1';
													else a='0';
											}
										if (numcar>0){
												if (cont==numcar) {
															printf("\n");
															cont=0;
														}
												printf("%c",a);
												cont++;
											}
											else printf("%c",a);
										}
									printf("\n\n");
								}
				}
					else {
						printf("Para acabar de introducir los bits presione la tecla ENTER y si no quiere \nseguir introduciendo bits presione la tecla ENTER sin introducir ningun bit\n\n");
						printf("\nBits transmitidos: ");
						while (1) {
								fin=((a=getchar())==10);
								if (principio&&fin) break;
									else principio=0;
								if (fin==1) {
										printf("\nBits transmitidos: ");
										fin=((a=getchar())==10);
										escribe=1;
									}
								if (fin==1) break;
								if  ((a!=48) && (a!=49)) { if (!((a==32) || (a==9))) {
															printf("\ntransmit: ERROR: Carácter no admitido: %c\n",a);
															exit(0);
														} 
											}
								i=rand()%10000;
								if (i<n) {
										if (a=='0') a='1';
											else a='0';
									}
								if (escribe==1) {
										printf("Bits recibidos: ");
										escribe=0;
										}
								printf("%c",a);
							}
					}
}
	else if ((argc==5) && (strcmp(argv[1],"-b"))) {
							printf("transmit: ERROR: Argumento inválido. Ejemplo: transmit [ | -a | -b] <n> <filein> <fileout>\n");
							exit(0);
						}
		else {
			resta=(argc==4);
			if (((n=atoi(argv[2-resta]))<0) || ((n=atoi(argv[2-resta]))>10000)) {
												printf("transmit: ERROR: Argumento inválido. Ejemplo: transmit [ | -a<xxx> | -b] <n> <filein> <fileout>\n");
												exit(0);
											}
			if ((n==0) && (strcmp("0",argv[2-resta]))) {
									printf("transmit: ERROR: Argumento inválido. Ejemplo: transmit [ | -a | -b] <n> <filein> <fileout>\n");
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
									printf("sumabi: ERROR: No existe el archivo %s\n",argv[3-resta]);
									exit(0);
								}
			fileout=(char *) malloc((strlen(argv[4-resta])+3)*sizeof(char));
			if (!((argv[4-resta][0]=='.') || (argv[4-resta][0]=='/'))){
											strcpy(fileout,"."); 
											strcat(fileout,"/");
											strcat(fileout,argv[4-resta]);
										}
				else strcpy(fileout,argv[4-resta]);
			if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
											printf("sumabi: ERROR: No tiene permiso para crear un fichero en este directorio\n");
											close(id1);
											exit(0);
										}
			while(1){
				if (read(id1,&a,1)==0) break;
				b=0;
				for (cont=0;cont<8;cont++){
								i=rand()%10000;
								numcar=(a&128)/128;
								if (i<n) {
										if (numcar==0) numcar=1;
										else numcar=0;
									}
								b=b+numcar;
								if (cont<7) b=b<<1;
								a=a<<1;
							}
				write(id2,&b,1);
				}
	}						 							
}
