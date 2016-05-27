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
 int fesclusao, fcolaoeste, testigo, pidbarco;

 signal(10,R10);
 fesclusao=open("esclusao",O_RDWR);
 fcolaoeste=open("colaoeste",O_RDWR);

 while(1)
 {
	read(fesclusao,&testigo,sizeof(testigo));
	read(fcolaoeste,&pidbarco,sizeof(pidbarco));
	kill(pidbarco,16);
 }


}
