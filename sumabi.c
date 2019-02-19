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

char *filein_1,*filein_2,*fileout,*aux,a,b,c='\n';
int id1,id2,id3,resta=0,cont=0,numcar=80,i;

if ((argc>5) || (argc<4)) {
				printf("sumabi: ERROR: Número de argumentos inválido. Ejemplo: sumabi [ | -a<xxx> | -b] <filein_1>  <filein_2>  <fileout>\n");
				exit(0);
			}

if (!(strncmp(argv[1],"-a",2))) {
					if (strlen(argv[1])>2) {
								aux=(char *) malloc ((strlen(argv[1])-2)*sizeof(char));
								for(i=2;i<strlen(argv[1]);i++) aux[i-2]=argv[1][i];
								if (((numcar=atoi(aux))<0)||((numcar=atoi(aux))>255)) {
															printf("sumabi: ERROR: Argumento inválido. Ejemplo: sumabi [ | -a<xxx> | -b] <filein_1>  <filein_2>  <fileout>\n");
															exit(0);
														}
								if ((numcar==0) && (strcmp(argv[1],"-a0"))) {
														printf("sumabi: ERROR: Argumento inválido. Ejemplo: sumabi [ | -a<xxx> | -b] <filein_1>  <filein_2>  <fileout>\n");
														exit(0);
													}
								}
					if (!(strcmp(argv[1],"-a"))) numcar=80;
					filein_1=(char *) malloc((strlen(argv[2])+3)*sizeof(char));
					if (!((argv[2][0]=='.') || (argv[2][0]=='/'))){
											strcpy(filein_1,"."); 
											strcat(filein_1,"/");
											strcat(filein_1,argv[2]);
										}
						else strcpy(filein_1,argv[2]);
					if ((id1=open(filein_1,O_RDONLY,0777))==-1) {
											printf("sumabi: ERROR: No existe el archivo %s\n",argv[2]);
											exit(0);
										}
					filein_2=(char *) malloc((strlen(argv[3])+3)*sizeof(char));
					if (!((argv[3][0]=='.') || (argv[3][0]=='/'))){
											strcpy(filein_2,"."); 
											strcat(filein_2,"/");
											strcat(filein_2,argv[3]);
										}
						else strcpy(filein_2,argv[3]);
					if ((id2=open(filein_2,O_RDONLY,0777))==-1) {
											printf("sumabi: ERROR: No existe el archivo %s\n",argv[3]);
											close(id1);
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
							if ((id3=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
															printf("sumabi: ERROR: No tiene permiso para crear un fichero en este directorio\n");
															close(id1);
															close(id2);
															exit(0);
														}
							while(1){
								if (read(id1,&a,1)==0) break; 
								if  ((a!='0') && (a!='1')) { if ((a==32) || (a==9) || (a==10)) continue;
												else {
													printf("sumabi: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[2],a);
													close(id1);
													close(id2);
													close(id3);
													exit(0);
												} 
											}
								while ((read(id2,&b,1)!=0) && (b!='0') && (b!='1')) {
															if ((b!=32) && (b!=9) && (b!=10)) {
																				printf("sumabi: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[3],b);
																				close(id1);
																				close(id2);
																				close(id3);
																				exit(0);
																			} 	
															}
								if  (b=='1') {
										if (a=='0') a='1';
											else a='0';
									}
								if (numcar>0){
										if (cont==numcar) {
													write(id3,&c,1);
													cont=0;
												}
										write(id3,&a,1);
										cont++;
									}
									else write(id3,&a,1);
							}
					}
					else {
						printf("\nEl resultado de la suma es:\n");
						while(1){
							if (read(id1,&a,1)==0) break; 
							if  ((a!='0') && (a!='1')) { if ((a==32) || (a==9) || (a==10)) continue;
											else {
												printf("sumabi: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[2],a);
												close(id1);
												close(id2);
												exit(0);
											} 
										}
							while ((read(id2,&b,1)!=0) && (b!='0') && (b!='1')) {
														if ((b!=32) && (b!=9) && (b!=10)) {
																			printf("sumabi: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[3],b);
																			close(id1);
																			close(id2);
																			exit(0);
																		} 	
													}
							if  (b=='1') {
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

	else if ((argc==5) && (strcmp(argv[1],"-b"))) {
							printf("sumabi: ERROR: Argumento inválido. Ejemplo: sumabi [ | -a<xxx> | -b] <filein_1>  <filein_2>  <fileout>\n");
							exit(0);
						}
 			else {
 				resta=(argc==4);
				filein_1=(char *) malloc((strlen(argv[2-resta])+3)*sizeof(char));
				if (!((argv[2-resta][0]=='.') || (argv[2-resta][0]=='/'))){
												strcpy(filein_1,"."); 
												strcat(filein_1,"/");
												strcat(filein_1,argv[2-resta]);
											}
					else strcpy(filein_1,argv[2-resta]);
				if ((id1=open(filein_1,O_RDONLY,0777))==-1) {
										printf("sumabi: ERROR: No existe el archivo %s\n",argv[2-resta]);
										exit(0);
									}
				filein_2=(char *) malloc((strlen(argv[3-resta])+3)*sizeof(char));
				if (!((argv[3-resta][0]=='.') || (argv[3-resta][0]=='/'))){
												strcpy(filein_2,"."); 
												strcat(filein_2,"/");
												strcat(filein_2,argv[3-resta]);
											}
					else strcpy(filein_2,argv[3-resta]);
				if ((id2=open(filein_2,O_RDONLY,0777))==-1) {
										printf("sumabi: ERROR: No existe el archivo %s\n",argv[3-resta]);
										close(id1);
										exit(0);
									}
				fileout=(char *) malloc((strlen(argv[4-resta])+3)*sizeof(char));
				if (!((argv[4-resta][0]=='.') || (argv[4-resta][0]=='/'))){
												strcpy(fileout,"."); 
												strcat(fileout,"/");
												strcat(fileout,argv[4-resta]);
											}
					else strcpy(fileout,argv[4-resta]);
				if ((id3=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
												printf("sumabi: ERROR: No tiene permiso para crear un fichero en este directorio\n");
												close(id1);
												close(id2);
												exit(0);
											}
				while(1){
					if (read(id1,&a,1)==0) break;
					read(id2,&b,1);
					a=a^b;
					write(id3,&a,1);
				}
	}
		
}
