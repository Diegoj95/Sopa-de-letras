#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio(int n, int largo);
int ncaracteres(char cadena[30]);
void horizontal(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir);   //declaracion de funciones
void vertical(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir);
void diagonalp(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir);
void diagonals(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir,int n);
int revisar(char mpalabras[100][100], char palabras[30], int largo, int k,int *num);

main()
{
int n,k;                //Entradas: tamaño de la matriz, cantidad de palabras
int i,j,p,q,a,c;
int x,y;
int largo;
int repetir;
int cont=0;
int respuesta=0;
int direccion;
int num=0;
int ejex[100];
int ejey[100];
int casillas[100][100];
char sopa[100][100];
char mpalabras[100][100];
char palabras[30];
char b='a';

srand(time(NULL));
printf("*****BIENVENID@ AL JUEGO DE LA SOPA DE LETRAS*****\n\nPara comenzar es necesario ingresar algunos datos...\n\n");
printf("1-Introduzca el tamanho de la sopa(matriz simetrica): ");  //tamaño de la matriz
scanf("%d", &n);
while(n>=41)
{
	printf("\nPor motivos de espacio este juego no permite un tamanho mayor a 40\n");
	printf("\n1-Introduzca el tamanho de la sopa(matriz simetrica): ");  //tamaño de la matriz
    scanf("%d", &n);
}
printf("\n2-Introduzca el numero de palabras: ");              //cantidad de palabras
scanf("%d", &k);
while(k>n)
{
printf("\nEl numero de palabras debe ser menor o igual al tamanho de la sopa\n2-Introduzca el numero de palabras: ");            
scanf("%d", &k);	
}


for(i=0;i<k;i++)                                           //ingresar palabras
{
printf("\n-Escriba la palabra %d: ", i+1);
scanf("%s",palabras);	
largo=ncaracteres(palabras);

for(j=0;j<largo;j++)
{
mpalabras[i][j]=palabras[j];
}
repetir=0;
while(repetir==0)
{
ejex[i]=aleatorio(n,largo);                         //coordenadas aleatorias de inicio de la palabra
ejey[i]=aleatorio(n,largo);
x=ejex[i];
y=ejey[i];
direccion=rand()%4;                                 //condiciones para definir direccion de la palabra
if(direccion==0)  
{
horizontal(sopa,palabras,largo,x,y,&repetir);       //CASO 0
}
if(direccion==1)  
{
vertical(sopa,palabras,largo,x,y,&repetir);         //CASO 1
}
if(direccion==2)  
{
diagonalp(sopa,palabras,largo,x,y,&repetir);        //CASO 2
}
if(direccion==3)  
{
diagonals(sopa,palabras,largo,x,y,&repetir,n);      //CASO 3
}
}
}

for(p=0;p<n;p++)                                //for matriz auxiliar para guardar celdas ocupadas
{
for(q=0;q<n;q++)
{
if(sopa[p][q]!='\0')
{
casillas[p][q]=1;
}	
}
system("cls");
printf("\n");
}
for(i=0;i<n;i++)                                //for llenar matriz con letras aleatorias
{
for(j=0;j<n;j++)
{
if(casillas[i][j]!=1)                          //condicion para evitar sobrescribir sobre una palabra
{   
sopa[i][j]=b+rand()%26;
}
}
}
printf("       ");
for(p=0;p<n;p++)
{
if(p<=9)
{
printf("[%d] ",p);	
}
else
{
printf("[%d]",p);	
}
} 
printf("\n\n"); 
for(p=0;p<n;p++)                               //for imprimir matriz sopa
{
if(p<=9)
{
printf(" [%d] ",p);	
}
else
{
printf("[%d] ",p);	
}
for(q=0;q<n;q++)
{
printf(" | %c",sopa[p][q]);	
}
printf(" |\n");
}
//AQUI COMIENZA EL JUEGO//
time_t inicio, fin;
inicio=time(NULL);
printf("\n\n*****BUSQUE PALABRAS EN LA SOPA DE LETRAS E INGRESELAS, RECUERDE QUE SOLO PUEDE COMETER 3 ERRORES!*****\n");
i=3;
j=k;
while(i>0)
{
printf("\nIngrese una palabra: ");
scanf("%s",palabras);
largo=ncaracteres(palabras);
respuesta=revisar(mpalabras,palabras,largo,k,&num);
if(respuesta==1)
{
	printf("\nLa palabra '%s' SI se encuentra en la sopa y comienza en la coordenada (%d,%d)\n",palabras,ejex[num],ejey[num]);
	j=j-1;
	if(j==0)
	{
		i=0;
		printf("\nFELICIDADES HAS ADIVINADO TODAS LAS PALABRAS!!!");
		fin=time(NULL);	
		printf("\nTIEMPO UTILIZADO: %f", difftime(fin,inicio));
	}	
}
if(respuesta==0)
{
	printf("\nLa palabra '%s' NO se encuentra en la sopa\n",palabras);
	i=i-1;
	if(i==0)
	{
		printf("\nCOMETISTE 3 ERRORES, GAME OVER");
		fin=time(NULL);
		printf("\nTIEMPO UTILIZADO: %f", difftime(fin,inicio));	
	}
}	
}
}  //******************************FIN DEL MAIN**************************************//

//***********************************FUNCIONES****************************************//
int revisar(char mpalabras[100][100], char palabras[30], int largo, int k,int *num)
{
	int i,j,a,count;                         //verifica que las palabras se encuentren en la sopa
	int respuesta=0;
	
	for(i=0;i<k;i++)
	{
		a=0;
		count=largo;
		for(j=0;j<largo;j++)
		{
			if(mpalabras[i][j]==palabras[a])
			{
			count=count-1;
			a=a+1;
			if(count==0)
			{
				respuesta=1;
				*num=i;
			}
			}
		}
	}
	return(respuesta);
}
//************************************************************************************//
int aleatorio(int n, int largo)               //busca numeros aleatorios entre 0 y n-largo
{
int random;
random=rand()%(n-largo);
return(random);	
}
//************************************************************************************//
int ncaracteres(char palabra[30])                            //contador de caracteres
{
int count;
count=0;
while(palabra[count] != '\0')
	{
	count=count+1;
	}
return(count);
}
//*************************************CASO 0***********************************************// 

void horizontal(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir)
{
int a;

	for(a=0;a<largo;a++)
{   
    if(sopa[x][y]==palabras[a] || sopa[x][y]=='\0')
    {
    sopa[x][y]=palabras[a];
	y=y+1;
	if(a==largo-1)
	{
	*repetir=1;	
	}
	}
	else
	{
	*repetir=0;
	}
}
}
//****************************************CASO 1********************************************// 
void vertical(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir)
{
int a;
	for(a=0;a<largo;a++)
{   
    if(sopa[x][y]==palabras[a] || sopa[x][y]=='\0')
    {
    sopa[x][y]=palabras[a];
	x=x+1;
	if(a==largo-1)
	{
	*repetir=1;	
	}
	}
	else
	{
	*repetir=0;
	}
}
}
//****************************************CASO 2********************************************//
void diagonalp(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir)
{
int a;
	for(a=0;a<largo;a++)
{   
    if(x!=y)
    {
    break;
	}
    if(sopa[x][y]==palabras[a] || sopa[x][y]=='\0')
    {
    sopa[x][y]=palabras[a];
	x=x+1;
	y=y-1;
	if(a==largo-1)
	{
	*repetir=1;	
	}
	}
	else
	{
	*repetir=0;
	}
}
}
//******************************************CASO 3******************************************//
void diagonals(char sopa[100][100],char palabras[30],int largo,int x, int y,int *repetir,int n)
{
int a;
	for(a=0;a<largo;a++)
{   
    if(x+y!=n-1)
    {
    break;
	}
    if(sopa[x][y]==palabras[a] || sopa[x][y]=='\0')
    {
    sopa[x][y]=palabras[a];
	x=x+1;
	y=y+1;
	if(a==largo-1)
	{
	*repetir=1;	
	}
	}
	else
	{
	*repetir=0;
	}
}
}
