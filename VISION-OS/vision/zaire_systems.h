#ifndef ZAIRE_SYSTEMS_H
#define ZAIRE_SYSTEMS_H


#include "globalVar.h"



//Err Types
typedef enum{
	ZAIRE_OK = 0,
	ZAIRE_ERR = !ZAIRE_OK
}zaire_err_t;

//SYSTEM GPIO CONFIGS
#define LOW		0x00
#define HIGH		0x01


//Initialize ZAIRE SYSTEMS
zaire_err_t zaire_systems_init(void);


#endif //ZAIRE_SYSTEMS_H
