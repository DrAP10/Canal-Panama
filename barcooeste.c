#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "comun.h"
#include "comunbarcos.h"

extern int llega14;

int llega16=0;
void R16(){llega16=1;}

main()
{
 
 int colagrafica, lapipe;
 struct Parametros param;
 int fesclusao, fesclusae, flago, testigo=1, fcolaeste, fcolaoeste,fcolalago, mipid;

 srand(getpid());
 signal(10,R10); // me preparo para la senyal 10
 signal(16,R16); // me preparo para la senyal 1
 signal(12,R12); // me preparo para la senyal 12
 signal(14,R14); // me preparo para la señal de alarma

 // Creamos y abrimos la cola de mensajes
 colagrafica=crea_cola(ftok ("./fichcola.txt", 18));

 // Abrimos las fifos
 fesclusae=open("esclusae",O_WRONLY);
 fcolaeste=open("colaeste",O_WRONLY);
 fesclusao=open("esclusao",O_WRONLY);
 fcolaoeste=open("colaoeste",O_WRONLY);
 flago=open("lago",O_WRONLY);
 fcolalago=open("colalago",O_WRONLY);

 // Leemos de la pipe los parámetros
 read(2,&param,sizeof(param));
 
 //recuperamos la salida de errores 
 lapipe=dup(2);
 close(2);
 open("/dev/tty",O_RDWR);

 //nos pintamos en la llegada
 visualiza(colagrafica, VOESTEIN, PINTAR, TIPOOESTE); 
 alarm(rand()%(param.mevoymax-param.mevoymin+1)+param.mevoymin);

 mipid=getpid();
 // reservo sitio en el lago
 write(fcolalago,&mipid,sizeof(mipid));
 if(!llega16) pause();

 if(llega14) //me he aburrido de esperar
 {
	visualiza(colagrafica, VOESTEIN, BORRAR, TIPOOESTE);
	visualiza(colagrafica, VHORNOS, PINTAR, TIPOOESTE);
	// como estoy en la cola del lago, cuando me den el sitio lo devuelvo
	if(!llega16) pause();
	write(flago,&testigo,sizeof(testigo));
 }
 else 
 {
	llega16=0;
	alarm(0); //desactivo la alarma
	// reservo la esclusa oeste
	write(fcolaoeste,&mipid,sizeof(mipid));
	if(!llega16) pause();
	llega16=0;
	//entro en la esclusa
	visualiza(colagrafica, VOESTEIN, BORRAR, TIPOOESTE); 
	visualiza(colagrafica, VESCLUSAOESTE, PINTAR, TIPOOESTE); 
	sleep(param.tesclusa);
	//salgo y voy al lago
	visualiza(colagrafica, VESCLUSAOESTE, BORRAR, TIPOOESTE); 
	visualiza(colagrafica, VLAGOO, PINTAR, TIPOOESTE); 
	write(fesclusao,&testigo,sizeof(testigo));
	sleep((rand()%(param.lagomax-param.lagomin+1))+param.lagomin);
	// reservo la esclusa este
	write(fcolaeste,&mipid,sizeof(mipid));
	if(!llega16) pause();
	llega16=0;
	// salgo del lago y voy a la esclusa
	visualiza(colagrafica, VLAGOO, BORRAR, TIPOOESTE); 
	visualiza(colagrafica, VESCLUSAESTE, PINTAR, TIPOOESTE);
	write(flago,&testigo,sizeof(testigo));
	sleep(param.tesclusa);
	//salgo de la esclusa y me marcho
	visualiza(colagrafica, VESCLUSAESTE, BORRAR, TIPOOESTE);
	visualiza(colagrafica, VESTEOUT, PINTAR, TIPOOESTE); 
	write(fesclusae,&testigo,sizeof(testigo));
 }
 close(fesclusae);
 close(fesclusao);
 close(flago);
 close(fcolaeste);
 close(fcolaoeste);
 close(fcolalago);
}

