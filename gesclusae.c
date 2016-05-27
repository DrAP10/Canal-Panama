#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int llega10=0;
void R10() {exit(0);}

main()
{
 int fesclusae, fcolaeste, testigo, pidbarco;

 signal(10,R10);
 fesclusae=open("esclusae",O_RDWR);
 fcolaeste=open("colaeste",O_RDWR);

 while(1)
 {
	read(fesclusae,&testigo,sizeof(testigo));
	read(fcolaeste,&pidbarco,sizeof(pidbarco));
	kill(pidbarco,16);
 }

}
