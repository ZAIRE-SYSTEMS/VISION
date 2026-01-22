//main.c -- ZAIRE SYSTEMS -- VISION OS

#include "globalVar.h"






int main(void){
	zaire_err_t ret = zaire_systems_init();

	if(ret != ZAIRE_OK){
		printf("FAILED TO INIT ZAIRE SYSTEMS\n");
		return ZAIRE_ERR;
	}

	return ZAIRE_OK;
}
