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

int main(int argc,char *argv[]){

char *filein,*fileout,*aux,a,b=0;
int id1,id2,id_aux,i=0,j,fin=0,max=0;
DIR *dir;
struct dirent *fichero;

if ((argc>3) || (argc<2)) {
				printf("ascii2bin: ERROR: Número de argumentos inválido. Ejemplo: ascii2bin [<filein>] <fileout>\n");
				exit(0);
			}
			
if (argc==3) {
		filein=(char *) malloc((strlen(argv[1])+3)*sizeof(char));
		if (!((argv[1][0]=='.') || (argv[1][0]=='/'))){
								strcpy(filein,"."); 
								strcat(filein,"/");
								strcat(filein,argv[1]);
							}
			else strcpy(filein,argv[1]);
		if ((id1=open(filein,O_RDONLY,0777))==-1) {
								printf("ascii2bin: ERROR: No existe el archivo %s\n",argv[1]);
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
										printf("ascii2bin: ERROR: No tiene permiso para crear un fichero en este directorio\n");
										close(id1);
										exit(0);
									}
		dir=opendir(".");
		while ((fichero=readdir(dir))!=NULL) if ((i=strlen(fichero->d_name))>max) max=i;
		aux=(char *) malloc((4+max)*sizeof(char));
		strcpy(aux,"./a");
		for (i=0;i<max;i++) strcat(aux,"a");
		if ((id_aux=open(aux,O_WRONLY|O_CREAT|O_EXCL,0777))==-1) {
										printf("ascii2bin: ERROR: Renombre el archivo %s y vuelva a ejecutar el programa\n",aux);
										close(id1);
										close(id2);
										exit(0);
									}
		while(1){
			if (read(id1,&b,1)==0) break; 
			if  ((b!='0') && (b!='1')) { if ((b==32) || (b==9) || (b==10)) continue;
							else {
								printf("ascii2bin: ERROR: Carácter no admitido en el archivo ASCII %s: %c\n",argv[1],b);
								close(id1);
								close(id2);
								close(id_aux);
								unlink(aux);
								exit(0);
							} 
						}
			write(id_aux,&b,1);
			}
		close(id1);
		id1=open(aux,O_RDONLY,0777);
		b=0;
		i=0;
		while(1){		
			if ((fin=(read(id1,&a,1)==0)) && (i==0)) break;
				else {
					if (fin==0) b=b+a-48;
					if (i<7) {
							i++;
							b=b<<1;
						}
						else {
							write(id2,&b,1);
							b=0;
							i=0;
						}
				}
		}
		unlink(aux);
}					
	else {
		printf("Para acabar de introducir los bits presione la tecla ENTER dos veces seguidas\n\n");
		fileout=(char *) malloc((strlen(argv[1])+3)*sizeof(char));
		if (!((argv[1][0]=='.') || (argv[1][0]=='/'))){
								strcpy(fileout,"."); 
								strcat(fileout,"/");
								strcat(fileout,argv[1]);
							}
			else strcpy(fileout,argv[1]);
		if ((id1=open(fileout,O_WRONLY|O_CREAT|O_TRUNC,0777))==-1) {
										printf("ascii2bin: ERROR: No tiene permiso para crear un fichero en este directorio\n");
										exit(0);
									}
		while (1) {
				fin=((a=getchar())==10);
				if (fin==1) fin=((a=getchar())==10);
				if (fin==1) { 
						if (i!=0) {
								for (j=i;j<7;j++) b=b<<1;
								write(id1,&b,1);
							}
						break;
					}
				if  ((a!=48) && (a!=49)) { if (!((a==32) || (a==9) || (a==10))) {
													printf("\nascii2bin: ERROR: Carácter no admitido: %c\n",a);
													exit(0);
												} 
							}
					else {
						if (fin==0) b=b+a-48;
						if (i<7) {
								b=b<<1;
								i++;
							} 
							else {
								write(id1,&b,1);
								i=0;
							}
					}
			}
	}
}
