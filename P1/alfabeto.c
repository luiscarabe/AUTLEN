/* Óscar Pinto y Luis Cárabe. Pareja 2, grupo 1401*/

#include "alfabeto.h"

typedef struct _alfabeto{
  char* nombre;
  int size;
  palabra* palabra; /*Almacena todos los símbolos del alfabeto*/
} alfabeto;

alfabeto* crear_alfabeto(char* nombre, int size){
  alfabeto* new_alfabeto = NULL;

  /*Reservamos memoria para el nuevo alfabeto*/
  new_alfabeto = (alfabeto*) malloc(sizeof(alfabeto));

  if(!new_alfabeto){
    return NULL;
  }
  /*Reservamos memoria para todos los símbolos (una palabra)*/
  new_alfabeto->palabra = crear_palabra();

  if(!new_alfabeto->palabra){
    free(new_alfabeto);
    return NULL;
  }

  new_alfabeto->size = size;

  /*Reservamos memoria para el nombre y lo copiamos*/
  new_alfabeto->nombre = (char*)malloc((strlen(nombre)+1)*sizeof(char));

  if(!new_alfabeto->nombre){
    eliminar_palabra(new_alfabeto->palabra);
    free(new_alfabeto);
    return NULL;
  }

  strcpy(new_alfabeto->nombre, nombre);

  return new_alfabeto;
}

void eliminar_alfabeto(alfabeto* alfabeto){

  /*Comprobamos el argumento que nos pasan*/
  if(!alfabeto){
    return;
  }

  if(!alfabeto->palabra){
    free(alfabeto);
    free(alfabeto->nombre);
    return;
  }
  /*Liberamos recursos*/
  eliminar_palabra(alfabeto->palabra);
  free(alfabeto->nombre);
  free(alfabeto);
}

int alfabeto_get_size(alfabeto* alfabeto){
  if(!alfabeto || !alfabeto->palabra){
    return -1;
  }
  /*El tamaño del alfabeto será el tamaño de la palabra en él*/
  return palabra_get_size(alfabeto->palabra);
}

char** alfabeto_get_simbolos(alfabeto* alfabeto){
  if(!alfabeto || !alfabeto->palabra){
    return NULL;
  }
  /*Los símbolos están almacenados en la palabra*/
  return palabra_get_simbolos(alfabeto->palabra);
}

char* alfabeto_insertar_simbolo(alfabeto* alfabeto, char* simbolo){
  int i = 0;
  char ** simbolos = NULL;

  if(!alfabeto || !alfabeto->palabra || !simbolo){
    return NULL;
  }


  /*Obtenemos la lista de simbolos*/
  simbolos = palabra_get_simbolos(alfabeto->palabra);

  /*Si hemos excedido el tamanio, no lo insertamos*/
  if(palabra_get_size(alfabeto->palabra) >= alfabeto->size){
    return NULL;
  }

  if(!simbolos){
    return NULL;
  }

  /*Comprobamos que no se repite el simbolo*/
  for(i=0; i<alfabeto_get_size(alfabeto); i++){
    if(strcmp(simbolos[i], simbolo) == 0){
      return NULL;
    }
  }

  /*Si no se repite lo insertamos */

  if(!palabra_insertar_simbolo(alfabeto->palabra, simbolo)){
    return NULL;
  }

  /*Devolvemos el simbolo insertado*/
  simbolos = palabra_get_simbolos(alfabeto->palabra);
  return simbolos[alfabeto_get_size(alfabeto) - 1];
}

void alfabeto_imprimir(FILE* fichero, alfabeto* alfabeto){
  char** simbolos = NULL;
  char* simbolo = NULL;
  int i;
  /*Comprobamos los argumentos*/
  if (!fichero || !alfabeto || !alfabeto->palabra || !alfabeto->nombre)
      return;

  simbolos = alfabeto_get_simbolos(alfabeto);

  fprintf(fichero, "%s={ ", alfabeto->nombre);

  for(i = 0 ; i < palabra_get_size(alfabeto->palabra) ; i++){
    simbolo = simbolos[i];
    fprintf(fichero, "%s ", simbolo);
  }

  fprintf(fichero, "}\n");

  return;
}