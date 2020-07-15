//Archivos cabecera del sistema
#include <stdlib.h> // Requerido para atoi
#include <stdio.h> // Requerido para printf
#include <errno.h>
#include <pthread.h>
#include "fumadores.h"

void test_fumadores(){
  // Hilo fumapa, referente al fumador con papel
  pthread_t *fumaPa;

  // Hilo fumaTa, referente al fumador con tabaco
  pthread_t *fumaTa;

  // Hilo fumaFo, referente al fumador con fosforo
  pthread_t *fumaFo;
  //Hilo pro, referente al proveedor
  pthread_t *pro;

  int ret;
  void* dummy;

  fumaPa = malloc(sizeof(pthread_t));
  fumaFo = malloc(sizeof(pthread_t));
  fumaTa = malloc(sizeof(pthread_t));
  pro = malloc(sizeof(pthread_t));
  int tries = 0;

//Se lanzan los Hilos de Fumadores y el proveedor

  ret = pthread_create(&fumaPa, NULL, fumaPapel, NULL);
  if (ret) {
    errno=ret;
    fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
    exit(-1);
  }

  ret = pthread_create(&fumaTa, NULL, fumaTabaco, NULL);
  if (ret) {
    errno=ret;
    fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
    exit(-1);
  }
  ret = pthread_create(&fumaFo, NULL, fumaFosfo, NULL);
  if (ret) {
    errno=ret;
    fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
    exit(-1);
  }

  ret = pthread_create(&pro, NULL, proveedor, NULL);
  if (ret) {
    errno=ret;
    fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
    exit(-1);
    }
//Se hacen los Join de los hilos 
  ret=pthread_join(fumaPa,&dummy);
    if (ret) {
    errno=ret;
    fprintf(stderr,"Error %d en el join del hilo fumaPa %d: %s\n",errno,strerror(errno));
    exit(-1);
    }
  ret=pthread_join(fumaFo,&dummy);
    if (ret) {
    errno=ret;
    fprintf(stderr,"Error %d en el join del hilo fumaFo %d: %s\n",errno,strerror(errno));
    exit(-1);
    }
  ret=pthread_join(fumaTa,&dummy);
    if (ret) {
    errno=ret;
    fprintf(stderr,"Error %d en el join del hilo fumaTa %d: %s\n",errno,strerror(errno));
    exit(-1);
      }
  ret=pthread_join(pro,&dummy);
    if (ret) {
    errno=ret;
    fprintf(stderr,"Error %d en el join del hilo proveedor %d: %s\n",errno,strerror(errno));
    exit(-1);
  }
}
//Funcion main:
//Ejecuta las pruebas de Fumadores
void main(){

  printf("////Comienza la prueba de Fumadores...\n");

  test_fumadores();

  printf("////Termina la prueba de Fumadores...\n");
}