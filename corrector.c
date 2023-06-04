/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Daniel Alejandro Romero
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/

#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <stdlib.h>
//#include <ctype.h>
#define LONGITUD 32
#define TAMTOKEN 50// creo que este esta un poco de más
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#define MAX_WORDS 800
#define TAMTOKEN 50

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{

	//Sustituya estas lineas por su c�digo
	iNumElementos=1;
	strcpy(szPalabras[0],"AquiVaElDiccionario");
	iEstadisticas[0] = 1; // la primer palabra aparece solo una vez.

    // Abre el archivo en modo de lectura
    FILE* file = fopen("szNombre", "r");

    // Verifica si se pudo abrir el archivo correctamente
    if (file == NULL) {
        printf("Error al abrir el archivo, verifique el archivo mencionado este en la carpeta, o que no este corrupto\n");
        return 1;
    }
    else
    {
        // Obtiene el tamaño del archivo
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        rewind(file);

        // Define el array en base al tamaño del archivo
        char textoEnBruto[size];

        // Lee el contenido del archivo y lo guarda en el array
        fread(textoEnBruto, 1, size, file);

        // Cierra el archivo
        fclose(file);

        char szPalabras[MAX_WORDS][TAMTOKEN];

         // Separa cada palabra en el array "szPalabrasSinOrden"
        char token =strtok(textoEnBruto, ". , ? ¿ ! ¡ ");
        int inumPalabras = 0;
        while (token != NULL) 
        {
            strcpy(szPalabras[inumPalabras], token);
            token = strtok(NULL, ". , ? ¿ ! ¡ ");
            inumPalabras++;
        }
        /*
         la función strtok() para separar cada palabra en el array szPalabrasSinOrden evitando los caracteres especificados.
        */
        //ordenar las palabras alfabeticamente
        int count1, count2;
        char palabra_actual[TAMTOKEN];

        // Usa un doble bucle para ordenar las palabras alfabeticamente y contar las palabras repetidas
        for (count1 = 0; count1 < inumPalabras - 1; count1++) 
        {
          for (count2 = 0; count2 < inumPalabras - count1 - 1; count2++) 
          {
            if (strcmp(szPalabras[count2], szPalabras[count2 + 1]) > 0) 
            {
                // cambio szPalabras[count2] a szPalabras[count2 + 1]
                strcpy(palabra_actual, szPalabras[count2]);
                strcpy(szPalabras[count2], szPalabras[count2 + 1]);
                strcpy(szPalabras[count2 + 1], palabra_actual);
            }
          }
        }
        //contar el numero de palabras que se repiten
        strcpy(palabra_actual, szPalabras[0]);  // empieza con la primera palabra
        int iEstadisticas[inumPalabras];
        iEstadisticas[0] = 1;  // inicializar el contador con 1
        for (i = 1; i < inumPalabras; i++) 
        {
            if (strcmp(szPalabras[i], palabra_actual) == 0) 
            {
              // La palabra es la misma que palabra actual
              iEstadisticas[i] = iEstadisticas[i - 1] + 1;  // incremeta el contador
            } 
            else 
            {
              // La palabra es diferente a palabra actual
              strcpy(palabra_actual, szPalabras[i]);  // actualiza la palabra
              iEstadisticas[i] = 1;  // reinicia el contador
            }
        }
    }
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c�digo
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}



/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*
int _tmain(int argc, char * argv[])
{
	char	szNombre[50];
	char	szPalabras[NUMPALABRAS][TAMTOKEN];
	int		iEstadisticas[NUMPALABRAS];
	int		i;
	int		iNumElementos;
	int		iNumSugeridas;
	char	szPalabraLeida[TAMTOKEN];
	char	szPalabrasSugeridas[3300][TAMTOKEN];
	char	szListaFinal[3300][TAMTOKEN];
	int		iPeso[3300]; //son 66 combinaciones por letra, mas o menos 3300 para 50 letras
	int		iNumLista;

	//Inicia el arreglo de estadisticas
	for (i = 0; i < NUMPALABRAS; i++)
		iEstadisticas[i] = 0;

	strcpy_s(szNombre, "anita.txt");
	//printf("Archivo para el diccionario: ");
	//scanf_s("%s", szNombre, 50);

	Diccionario(szNombre, szPalabras, iEstadisticas, iNumElementos);

	for (int j = 0; j < iNumElementos; j++)
		printf("%-12s %i\n", szPalabras[j], iEstadisticas[j]);

	printf("Numero de elementos en la lista: %i\n", iNumElementos);
	strcpy_s(szPalabraLeida, "");
	while (strcmp(szPalabraLeida, "fin"))
	{
		printf("\nDigite una palabra o 'fin' para terminar: ");
		scanf_s("%s", szPalabraLeida, TAMTOKEN);
		_strlwr_s(szPalabraLeida);
		ClonaPalabras(szPalabraLeida, szPalabrasSugeridas, iNumSugeridas);

		for (int j = 0; j < iNumSugeridas - 1; j++)
			printf("%s\n", szPalabrasSugeridas[j]);
		printf("Numero de elementos en la lista de clonacion: %i\n", iNumSugeridas);

		ListaCandidatas(szPalabrasSugeridas, iNumSugeridas, szPalabras, iEstadisticas, iNumElementos,
			szListaFinal, iPeso, iNumLista);
		printf("\n\nTal vez ud quiso decir:\npalabra\t frecuencia\n");
		printf("=======\t ==========\n");
		if (iNumLista > 0)
		{

			for (int j = 0; j < iNumLista; j++)
				printf("%s\t%i\n", szListaFinal[j], iPeso[j]);
			printf("Numero de elementos en la lista de opciones: %i\n", iNumLista);
		}
		else
			printf("\n\nSin opciones que mostrar\n");
	}

	return 0;
}
*/
