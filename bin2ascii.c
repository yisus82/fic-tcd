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

char *filein,*fileout,*aux,a,b,c='\n',e=' ',t='\t';
int id1,id2,resta=0,i,cont1=0,cont2=1,numbyte=10,esp=0,tab=0;

if ((argc>5) || (argc<2)) {
				printf("bin2ascii: ERROR: Número de argumentos inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
				exit(0);
			}
			
if (argc==2) {
		filein=(char *) malloc((strlen(argv[1])+3)*sizeof(char));
		if (!((argv[1][0]=='.') || (argv[1][0]=='/'))){
								strcpy(filein,"."); 
								strcat(filein,"/");
								strcat(filein,argv[1]);
							}
			else strcpy(filein,argv[1]);
		if ((id1=open(filein,O_RDONLY,0777))==-1) {
								printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[1]);
								exit(0);
							}
		printf("\n");
		while(1) {
				if (read(id1,&a,1)==0) break;
				for (i=0;i<8;i++){
								b=(a&128)/128;
								printf("%c",b+48);
								a=a<<1;
						}
			}
		printf("\n\n");
		exit(0);
	}
	
if (argc==5) {
		if (!(strncmp(argv[1],"-w",2))) {
							if (strlen(argv[1])>2) {
										aux=(char *) malloc ((strlen(argv[1])-2)*sizeof(char));
										for(i=2;i<strlen(argv[1]);i++) aux[i-2]=argv[1][i];
										if (((numbyte=atoi(aux))<0)||((numbyte=atoi(aux))>255)) {
																	printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
																	exit(0);
																}
										if ((numbyte==0) && (strcmp(argv[1],"-w0"))) {
																printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
																exit(0);
															}
										}
								else {
									printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
									exit(0);
								}
						}
			else {
				printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
				exit(0);
			}
		if (!(strcmp(argv[2],"-b"))) esp=1;
			else if (!(strcmp(argv[2],"-t"))) tab=1;
				else {
					printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
					exit(0);
				}  
		filein=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
		if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
								strcpy(filein,"."); 
								strcat(filein,"/");
								strcat(filein,argv[3]);
							}
			else strcpy(filein,argv[3]);
		if ((id1=open(filein,O_RDONLY,0777))==-1) {
								printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[3]);
								exit(0);
							}
		fileout=(char *) malloc((strlen(argv[4])+3)*sizeof(char));
		if (!((argv[4][0]=='.') || (argv[4][0]=='/'))){
								strcpy(fileout,"."); 
								strcat(fileout,"/");
								strcat(fileout,argv[4]);
							}
			else strcpy(fileout,argv[4]);
		if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
										printf("bin2ascii: ERROR: No tiene permiso para crear un fichero en este directorio\n");
										close(id1);
										exit(0);
									}
		while(1) {
				if (read(id1,&a,1)==0) break;
				for (i=0;i<8;i++){
							b=(a&128)/128;
							b=b+48;
							if (cont1==8) {
									if (numbyte>0) {
											if (cont2==numbyte) {	
														write(id2,&c,1);
														cont2=0;
													}
											}
									if (cont2!=0) { 
											if (esp==1) write(id2,&e,1);
											if (tab==1) write(id2,&t,1);
										}
									cont1=0;
									if (numbyte>0) cont2++;					
								}
							write(id2,&b,1);
							cont1++;
							a=a<<1;
						}
			}
		exit(0);
	}
if (argc==3) {
		if (!(strncmp(argv[1],"-w",2))) {
							if (strlen(argv[1])>2) {
										aux=(char *) malloc ((strlen(argv[1])-2)*sizeof(char));
										for(i=2;i<strlen(argv[1]);i++) aux[i-2]=argv[1][i];
										if (((numbyte=atoi(aux))<0)||((numbyte=atoi(aux))>255)) {
																	printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
																	exit(0);
																}
										if ((numbyte==0) && (strcmp(argv[1],"-w0"))) {
																printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
																exit(0);
															}
										}
								else {
									printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
									exit(0);
								}
						}
			else if (!(strcmp(argv[1],"-b"))) esp=1;
				else if (!(strcmp(argv[1],"-t"))) tab=1;
					else {
						filein=(char *) malloc((strlen(argv[1])+3)*sizeof(char));
						if (!((argv[1][0]=='.') || (argv[1][0]=='/'))){
												strcpy(filein,"."); 
												strcat(filein,"/");
												strcat(filein,argv[1]);
												}
							else strcpy(filein,argv[1]);
						if ((id1=open(filein,O_RDONLY,0777))==-1) {
												printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[1]);
												exit(0);
											}
						fileout=(char *) malloc((strlen(argv[2])+3)*sizeof(char));
						if (!((argv[2][0]=='.') || (argv[2][0]=='/'))){
												strcpy(fileout,"."); 
												strcat(fileout,"/");
												strcat(fileout,argv[2]);
												}
							else strcpy(fileout,argv[2]);
						if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
														printf("bin2ascii: ERROR: No tiene permiso para crear un fichero en este directorio\n");
														close(id1);
														exit(0);
													}
						while(1) {
								if (read(id1,&a,1)==0) break;
								for (i=0;i<8;i++){
											b=(a&128)/128;
											b=b+48;
											write(id2,&b,1);	
											a=a<<1;
										}
							}
						exit(0);
					}
		filein=(char *) malloc((strlen(argv[2])+3)*sizeof(char));
		if (!((argv[2][0]=='.') || (argv[2][0]=='/'))){
								strcpy(filein,"."); 
								strcat(filein,"/");
								strcat(filein,argv[2]);
								}
			else strcpy(filein,argv[2]);
		if ((id1=open(filein,O_RDONLY,0777))==-1) {
								printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[2]);
								exit(0);
							}
		while(1) {
				if (read(id1,&a,1)==0) break;
				for (i=0;i<8;i++){
b=(a&128)/128;
							b=b+48;
							if (cont1==8) {
									if (numbyte>0) {
											if (cont2==numbyte) {	
														printf("\n");
														cont2=0;
													}
											}
									if (cont2!=0) { 
											if (esp==1) printf(" ");
											if (tab==1) printf("\t");
										}
									cont1=0;
									if (numbyte>0) cont2++;					
								}
							printf("%c",b);
							cont1++;
							a=a<<1;
						}
				}
		printf("\n");
		exit(0);	
	}
if (!(strncmp(argv[1],"-w",2))) {
					if (strlen(argv[1])>2) {
								aux=(char *) malloc ((strlen(argv[1])-2)*sizeof(char));
								for(i=2;i<strlen(argv[1]);i++) aux[i-2]=argv[1][i];
								if (((numbyte=atoi(aux))<0)||((numbyte=atoi(aux))>255)) {
															printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
															exit(0);
														}
								if ((numbyte==0) && (strcmp(argv[1],"-w0"))) {
														printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
														exit(0);
													}
								}
						else {
							printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
							exit(0);
						}
					if (!(strcmp(argv[2],"-b"))) esp=1;
						else if (!(strcmp(argv[2],"-t"))) tab=1;
							else {
								filein=(char *) malloc((strlen(argv[2])+3)*sizeof(char));
								if (!((argv[2][0]=='.') || (argv[2][0]=='/'))){
														strcpy(filein,"."); 
														strcat(filein,"/");
														strcat(filein,argv[2]);
														}
									else strcpy(filein,argv[2]);
								if ((id1=open(filein,O_RDONLY,0777))==-1) {
														printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[1]);
														exit(0);
													}
								fileout=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
								if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
														strcpy(fileout,"."); 
														strcat(fileout,"/");
														strcat(fileout,argv[3]);
														}
									else strcpy(fileout,argv[3]);
								if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
																printf("bin2ascii: ERROR: No tiene permiso para crear un fichero en este directorio\n");
																close(id1);
																exit(0);
															}
								while(1) {
										if (read(id1,&a,1)==0) break;
										for (i=0;i<8;i++){
													b=(a&128)/128;
													b=b+48;
													if (cont1==8) {
															if (numbyte>0) {
																	if (cont2==numbyte) {	
																				write(id2,&c,1);
																				cont2=0;
																			}
																	}
															cont1=0;
															if (numbyte>0) cont2++;					
															}
													write(id2,&b,1);
													cont1++;
													a=a<<1;
												}
									}
								exit(0);
							}
					filein=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
					if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
											strcpy(filein,"."); 
											strcat(filein,"/");
											strcat(filein,argv[3]);
											}
						else strcpy(filein,argv[3]);
					if ((id1=open(filein,O_RDONLY,0777))==-1) {
											printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[3]);
											exit(0);
										}
					while(1) {
							if (read(id1,&a,1)==0) break;
							for (i=0;i<8;i++){
										b=(a&128)/128;
										b=b+48;
										if (cont1==8) {
												if (numbyte>0) {
														if (cont2==numbyte) {	
																	printf("\n");
																	cont2=0;
																}
														}
												if (cont2!=0) { 
														if (esp==1) printf(" ");
														if (tab==1) printf("\t");
													}
												cont1=0;
												if (numbyte>0) cont2++;					
											}
										printf("%c",b);
										cont1++;
										a=a<<1;
									}
						}
					printf("\n");
				}
	else {
		if (!(strcmp(argv[1],"-b"))) esp=1;
			else if (!(strcmp(argv[1],"-t"))) tab=1;
					else {
						printf("bin2ascii: ERROR: Argumento inválido. Ejemplo: bin2ascii [-w<xxx>] [ |-b |-t] <filein> [<fileout>]\n");
						exit(0);
					}
		filein=(char *) malloc((strlen(argv[2])+3)*sizeof(char));
		if (!((argv[2][0]=='.') || (argv[2][0]=='/'))){
								strcpy(filein,"."); 
								strcat(filein,"/");
								strcat(filein,argv[2]);
								}
			else strcpy(filein,argv[2]);
		if ((id1=open(filein,O_RDONLY,0777))==-1) {
								printf("bin2ascii: ERROR: No existe el archivo %s\n",argv[2]);
								exit(0);
							}
		fileout=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
		if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
								strcpy(fileout,"."); 
								strcat(fileout,"/");
								strcat(fileout,argv[3]);
								}
			else strcpy(fileout,argv[3]);
		if ((id2=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
										printf("bin2ascii: ERROR: No tiene permiso para crear un fichero en este directorio\n");
										close(id1);
										exit(0);
									}
		while(1) {
				if (read(id1,&a,1)==0) break;
				for (i=0;i<8;i++){
							b=(a&128)/128;
							b=b+48;
							if (cont1==8) {
									if (esp==1) write(id2,&e,1);
									if (tab==1) write(id2,&t,1);
									cont1=0;
								}
							write(id2,&b,1);
							cont1++;
							a=a<<1;
						}
			}
		}
}
