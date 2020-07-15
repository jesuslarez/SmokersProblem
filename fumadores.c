
#include <stdlib.h> // Requerido para atoi
#include <stdio.h> // Requerido para printf
#include <errno.h>
#include <pthread.h>
#include "fumadores.h"
// Se incluye fichero cabecera en el que se declara los tipos y funciones de manejo del buffer circular

int mesa[] = {1,1,0};
pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t taken = PTHREAD_COND_INITIALIZER;
pthread_cond_t given = PTHREAD_COND_INITIALIZER;
int state = 1;

void fumaPapel(){
	while(1){
	        pthread_mutex_lock(&locker);
	    while(state == 0 || mesa[1]+mesa[2] != 2){
	        pthread_cond_wait(&given, &locker);
	    }
	//pthread_cond_wait(&given, &locker);
		printf("Fumador con Papel empieza de fumar\n");
		mesa[1] = 0;
		mesa[2] = 0;
		state = 0;
		printf("Fumador con Papel termino de fumar\n");
		pthread_cond_signal(&taken);
		pthread_mutex_unlock(&locker);
	}
}

void fumaTabaco(){
	while(1){
	    pthread_mutex_lock(&locker);
	    while(state == 0 || mesa[0]+mesa[2] != 2){
	        pthread_cond_wait(&given, &locker);
	    }
		//pthread_cond_wait(&given, &locker);
		printf("Fumador con Tabaco empieza de fumar\n");
		mesa[0] = 0;
		mesa[2] = 0;
		state = 0;
		printf("Fumador con Tabaco termino de fumar\n");
		pthread_cond_signal(&taken);
		pthread_mutex_unlock(&locker);
	}
}

void fumaFosfo(){
	while(1){
	    pthread_mutex_lock(&locker);
	    while(state == 0 || mesa[0]+mesa[1] != 2){
	        pthread_cond_wait(&given, &locker);
	    }
		//pthread_cond_wait(&given, &locker);
		printf("Fumador con Fosforos empieza de fumar\n");
		mesa[0] = 0;
		mesa[1] = 0;
		state = 0;
		printf("Fumador con Fosforos termino de fumar\n");
		pthread_cond_signal(&taken);
		pthread_mutex_unlock(&locker);
	}
}

void proveedor(){
    while(1){
		pthread_mutex_lock(&locker);
		while(state == 1){
		    pthread_cond_wait(&taken, &locker);
		}
		printf("Proveedor empieza a colocar ingredientes en la mesa\n");
		int first = rand() % 3;
		mesa[first] = 1;
		int second = rand() % 3;
		while(first == second){
			second = rand() % 3;
		}
		mesa[second] = 1;
		printf("Proveedor termino de colocar ingredientes\n");
		state = 1;
		pthread_cond_broadcast(&given);
		pthread_mutex_unlock(&locker);
	}
}