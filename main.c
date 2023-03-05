#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ArchivoB "C:\\Users\\Mi PC\\Documents\\EDA I\\examen\\alcobendas.b__"
#define camino "C:\\Users\\Mi PC\\Documents\\EDA I\\examen\\"

struct comuna
{
	char periodo[10];
	char descripcion[30];
	char mujeres[10];
	char hombres[10];
	char total[10];
};
void imprimir(struct comuna **,short);
void AnioMayNat(long*,short);

int main (void)
{
    FILE*archivo=NULL;
    FILE*archivoTxt=NULL;
    FILE*archivoCsv=NULL;
    char AnioBuscado[6];
    char DescB[16];
    char anioComp1[6];
    char anioComp2[6];
    short cant=0;
    short anios=cant/21;
    short aux=0;
    short aux2=0;
    long TotalAnio1=0;
    long TotalAnio2=0;
    char NomArchCsv[200]="";
    char ArchUs[30]="";
    short indice=0;


    struct comuna *VComuna=NULL;


    archivo=fopen(ArchivoB,"rb");

    if(archivo==NULL)
    {
        printf("no deberias leer esto");                             //en este primer if comprobamos que el arichivo no contenga null
    }                                                                //caso contrario, prosedemos a crear un vector de estructuras mientras recorremos el archivo y vamos pasando la informacion
    else                                                             //al vector de estructuras,aumento la variable de cant para saber cuantas structuras hay y poder usarlas mas adelante
    {

            VComuna=(struct comuna*)realloc(VComuna,(indice+1)*sizeof(struct comuna));
            fread(&VComuna[indice],sizeof(struct comuna),1,archivo);
            if(VComuna!=NULL)
            {
                while(!feof(archivo))
                {
                    indice++;
                    cant++;
                    VComuna=(struct comuna*)realloc(VComuna,(indice+1)*sizeof(struct comuna));
                    fread(&VComuna[indice],sizeof(struct comuna),1,archivo);

                }
            }


        fclose(archivo);
}
    long VectorTotales[cant];
                                                                    //iniciamos un ciclo while para poder repetir el switch case que nos sirve como menu para guiar al usuario por la aplicacion
    short opcion;
    short salida=0;


    while(salida==0)

    {

            printf("\n\n\t\tBIENVENIDO A EL PROGRAMA DE ORGANIZADOR DE ALCOBENDAS(POA)\n\n\t\tPara iniciar debera ingresar una de las opcion\n\n\n");
            printf("opcion 1: mostrar en pantalla todos los datos del archivo del anio que usted elija(1998-2017)\n\nopcion 2:convertir en archivo .txt todos los datos que tenemos del rango hetario que indique\n\nopcion 3:mostrar en pantalla la diferencia de natalidad de dos anios que elija\n\nopcion 4:convertir en formato .csv todos los datos\n\nopcion 5:limpiar la pantalla\n\nopcion 6:exit\n");
            printf("opcion: ");
            fflush(stdin);
            scanf("%hd[^\n]",&opcion);
            switch(opcion)
            {

            case 1:

                        printf("\nPOR FAVOR INGRESAR ANIO DESEADO: ");
                        fflush(stdin);
                        scanf("%s[0-9][^-\n]",&AnioBuscado);
                        printf("%s\n",AnioBuscado);
                        indice=0;

                        while(strcmp(AnioBuscado,VComuna[indice].periodo)!=0 && indice<cant)       //este while lo uso para saber si es que existe el a�o ingresado por el usuario
                        {                                                                          //utilizo la variable cant para asegurarme que el ciclo recorra todo el vector de estructuras
                            indice++;
                            aux++;
                        }
                        printf("%hd",aux);                                                         //con este if lo que compruebo es que el anio ingresado y el a�o que se encuentra en el indice, si
                        printf("\tperiodo - descripcion - hombres - mujeres - total\n");           //no es asi entonces sale del case con un mensaje de error
                            if(strcmp(AnioBuscado,VComuna[indice].periodo)==0 && indice<cant)
                            {
                                imprimir(&VComuna,aux);                                            //una vez se comprueba que los anios coinciden entonces pasamos a imprimir en pantalla con esta funcion

                            }else{
                                printf("valor no encontrado\nComprobar que el a�o no este mal escrito o contenga un menos\n\n");
                            }
                        break;
            case 2:
                        printf("POR FAVOR INGRESAR DESCRIPCION BUSCADA: ");                         // segundo case donde buscamos una descripcion,
                        scanf("%s[^\n]",&DescB);
                        printf("DescB=%s\n\n",DescB);


                        indice=0;
                        aux=0;
                        short rest=0;
                        short anios=cant/21;


                            for(indice=0; strcmp(DescB,VComuna[aux].descripcion)!=0 && indice<cant; indice++)       //utilizo el lazo for para buscar por todo el vector de estructuras el dato pedido
                            {                                                                                       //amplifico la variable aux para saber a en que parte del vector se encuentra el dato
                                aux++;

                            }
                            printf("%hd\n\n",aux);

                            if(strcmp(VComuna[aux].descripcion,DescB)==0)                           //pasamos a crear el archivo txt,utilizo strcat para crear el camino hasta el archivo
                            {
                                char NomArch[200]="";

                                strcat(NomArch,camino);

                                strcat(NomArch,DescB);
                                strcat(NomArch,".txt");
                                printf("%s\n\n",NomArch);

                                archivoTxt=fopen(NomArch,"wt");

                            if(archivoTxt==NULL){
                                printf("Hubo un problema con el archivo, NULL");
                            }else{

                            for(indice=0;indice<=anios && aux<=cant;indice++)                       //pasamos con fprintf los datos del vector que se encuentran en aux
                                {

                                    fprintf(archivoTxt,"\t periodo=>%s\n\tdescripcion=>%s\n",VComuna[aux].periodo,VComuna[aux].descripcion);
                                    fprintf(archivoTxt,"\t hombres=>%s\n",VComuna[aux].hombres);
                                    fprintf(archivoTxt,"\t mujeres=>%s\n",VComuna[aux].mujeres);
                                    fprintf(archivoTxt,"\t total=>%s\n",VComuna[aux].total);
                                    aux=aux+21;

                                }


                                fclose(archivoTxt);

                            }
                            }


                                break;
            case 3:
                            printf("POR FAVOR INGRESAR 1 ANIO A COMPARAR: ");               // 3 case comparamos natalidad de distintos anios,reestrinjo que el usuario pueda ingresar letras y guiones
                            scanf("%s[0-9][^-\n]",&anioComp1);
                            printf("\nPOR FAVOR INGRESAR 2 ANIO A COMPARAR: ");
                            scanf("%s[0-9][^-\n]",&anioComp2);
                            printf("\n%s\n%s\n",anioComp1,anioComp2);
                            indice=0;
                            aux=0;
                            aux2=0;
                            short DiferenciaNat=0;

                            if( strcmp(anioComp1,VComuna[aux].periodo)==0){                 //comparo que los anios coincidan y convierto en numero el total del 1 a�o
                            sscanf(VComuna[aux].total,"%ld",&TotalAnio1);
                            }else{
                            for(indice=0; strcmp(anioComp1,VComuna[aux].periodo)!=0 && indice<cant; indice++)
                            {
                                printf("\n\t%s\n",VComuna[aux].periodo);
                                printf("%ld\n",anioComp1);
                                aux=aux+21;                                                 //aca hago recorrer el vector pero que el la variable aux la voy sumano de a 21 porq los datos estan separados por 21 datos
                                sscanf(VComuna[aux].total,"%ld",&TotalAnio1);

                            }
                                }

                            if( strcmp(anioComp2,VComuna[aux2].periodo)==0){
                                sscanf(VComuna[aux2].total,"%ld",&TotalAnio2);
                            }else{
                            for(indice=0; strcmp(anioComp2,VComuna[aux2].periodo)!=0 && indice<cant; indice++)
                            {
                                printf("%s\n",VComuna[aux2].total);
                                printf("%ld\n",anioComp2);
                                aux2=aux2+21;
                                sscanf(VComuna[aux2].total,"%ld",&TotalAnio2);

                            }
                                }
                            printf("total anio 1 %ld\n",TotalAnio1);
                            printf("total anio 2 %ld",TotalAnio2);

                            DiferenciaNat=TotalAnio1-TotalAnio2;                            //una vez encontramos los datos y los convertimos en numeros, pasamos a compararlos y mostrar en pantalla
                            printf("\n\n\n La diferencia entre los a�os es de = %hd",DiferenciaNat);


                break;
            case 4:
                            printf("escriba el nombre del archivo: ");
                            scanf("%s[^\n]",&ArchUs);
                            printf("conviertiendo a archivo .csv-----\n");

                            strcat(NomArchCsv,camino);
//                            printf("%s\n",NomArchCsv);
                            strcat(NomArchCsv,ArchUs);
//                            printf("%s\n",NomArchCsv);
                            strcat(NomArchCsv,".csv");
//                            printf("%s\n",NomArchCsv);

                            archivoCsv=fopen(NomArchCsv,"wt");

                            if(archivoCsv==NULL){
                                printf("hubo un error archivo con NULL");
                            }else{

                            for(indice=0;indice<cant;indice++)
                            {
                                fprintf(archivoCsv," ""%s"",""%s"",""%s"",""%s"",""%s""\n",VComuna[indice].periodo,VComuna[indice].descripcion,VComuna[indice].hombres,VComuna[indice].mujeres,VComuna[indice].total);

                            }

                            fclose(archivoCsv);}


                break;

            case 5:
                system("cls");
                break;
            case 6:
                printf("\nmuchas gracias, hasta luego (^-^)/\n\n");
                salida=1;
                break;
            default:printf("\n\n\t\tnumero ingresado incorrecto, pruebe devuelta\n\n");

            }

    }

    return 0;
    }



void imprimir(struct comuna **V,short aux)                          //una vez se comprueba que los anios coinciden entonces pasamos a imprimir en pantalla con esta funcion
{

    for(short indice=0;indice<21;indice++)
                {
                    printf("\t%s  ",((*V)+aux)->periodo);
                    printf("\t    %s",((*V)+aux)->descripcion);
                    printf("\t  %s",((*V)+aux)->hombres);
                    printf("\t  %s",((*V)+aux)->mujeres);
                    printf("\t  %s",((*V)+aux)->total);
                    aux++;
                }
}


