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
 int flago, fcolalago, testigo, pidbarco;

 signal(10,R10);
 flago=open("lago",O_RDWR);
 fcolalago=open("colalago",O_RDWR);

 while(!llega10)
 {
	read(flago,&testigo,sizeof(testigo));
	read(fcolalago,&pidbarco,sizeof(pidbarco));
	kill(pidbarco,16);
 }

}
