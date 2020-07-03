#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <sys/time.h>
#include "conexiondb.h"
#include <unistd.h>

unsigned char MACOrigen[6];
unsigned char MACDestino[6]= {0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char ipOrigen[4];
unsigned char ipDestino[4]= {0x00,0x00,0x00,0x00};
unsigned char tramaEnv[1514], tramaRec[1514];
unsigned char MACbro[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char ethertype[2]={0x0c,0x0c};
unsigned char arptype[2]={0x08,0x06};
struct ips{
   unsigned char ip[4];
   unsigned char mac[6]; 
   struct ips * sig;
};
struct timeval start, end;




int obtenerDatos(int ds){
	
	struct ifreq nic;
	int indice,i;
	char nombre[10];
	
	printf("\nInsertar el nombre de la interfaz:  ");
	scanf("%s", nombre);
	strcpy(nic.ifr_name,nombre);
	
	if(ioctl(ds,SIOCGIFINDEX,&nic)==-1){
		perror("\nError al obtener el indice");
		exit(1);
	}
	else{
		indice=nic.ifr_ifindex;
		printf("%d",indice);
	}
	
	if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
		perror("\Error al obtener la mac");
		exit(1);
	}
	else{
		memcpy(MACOrigen,nic.ifr_hwaddr.sa_data+0,6);
		printf("\nLa direccion mac es:");
		for(i=0;i<6;i++)
			printf(" %.2X:",MACOrigen[i]);
	}
	
	if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
		perror("\nError al obtener la ip");
		exit(1);
	}
	else{
		memcpy(ipOrigen,nic.ifr_addr.sa_data+2,4);
		printf("\nLa IP es: ");
		for(i=0;i<4;i++)
		printf("%d.",ipOrigen[i]);
	}
	
	return indice;
}


void enviarTrama(int ds, int indice, unsigned char *trama){
	
	int tam;
	struct sockaddr_ll interfaz;
	memset(&interfaz,0x00,sizeof(interfaz));
	interfaz.sll_family=AF_PACKET;
	interfaz.sll_protocol=htons(ETH_P_ALL);
	interfaz.sll_ifindex=indice;
	tam=sendto(ds,trama,60,0,(struct sockaddr *)&interfaz,sizeof(interfaz));
	
	if(tam==-1){
		perror("\nError al enviar");
		exit(1);
	}
	else{
		printf("\nExito al enviar"); 
	}
}

void imprimeTrama(unsigned char *trama, int tam){
	
	int i;
	printf("\n");
	
	for(i=0;i<tam;i++){
	 	if(i%16==0){
			printf("\n");
		}
		printf("%.2x",trama[i]);
	    printf(" ");
	}
	
	printf("\n \n");
}

void recibeTrama(int ds, unsigned char *trama){

	long mtime = 0, seconds, useconds; 
	int tam,bandera = 0;
	gettimeofday(&start, NULL);
    
	while(mtime<1000){
		tam=recvfrom(ds, trama, 1514, MSG_DONTWAIT,NULL,0);
		if(tam == 1){
			perror("\nError al recibir");
	   	}
		else{
			if(!memcmp(trama+0,MACOrigen,6)){
				imprimeTrama(trama, tam);
				bandera = 1;
			}
        }
		
        gettimeofday(&end, NULL);

        seconds  = end.tv_sec  - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
        
		if(bandera == 1){
            break;
        }
    }

    printf("Elapsed time: %ld milliseconds\n", mtime);
}



void insertar(struct ips ** myips){
    struct ips * aux = (struct ips *)malloc(sizeof(struct ips));
    memcpy(aux->ip,ipDestino,4);
    memcpy(aux->mac,MACDestino,6);
    aux->sig = *myips;
    *myips = aux;
}


void recibeARP2(int ds, unsigned char *trama, struct ips ** myips){
	struct timeval starte, ende;

	long mtime = 0, seconds = 0, useconds = 0; 

	unsigned char Opcode[2]={0x00,0x02};
	int tam,bandera = 0,i = 0;
	gettimeofday(&starte, NULL);
    while(mtime<100){
		tam=recvfrom(ds, trama, 1514, MSG_DONTWAIT,NULL,0);
		if(tam == 1){
			perror("\nError al recibir"); 	
		}
		else{
			if((!memcmp(trama+0,MACOrigen,6))&&(!memcmp(trama+12,arptype,2))&&(!memcmp(trama+20,Opcode,2))&&(!memcmp(trama+28,ipDestino,4))){
				memcpy(MACDestino,trama+22,6);                                                                                                                                 
				imprimeTrama(trama, tam);
                insertar(myips);
				printf("\nLa direccion mac es:");
				
				for(i=0;i<6;i++){
					printf(" %.2X:",MACDestino[i]);
				}
				
				printf("\n");
				bandera = 1;
			}
        }
        gettimeofday(&ende, NULL);

        seconds  = ende.tv_sec  - starte.tv_sec;
        useconds = ende.tv_usec - starte.tv_usec;
		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
        
		if(bandera == 1){
            break;
        }
    }

    printf("TIEMPO: %ld ms\n", mtime);
}



void scan(int ds, int indice, unsigned char *trama){
    unsigned char trama2[42];
    unsigned char IP[4] = {0x08,0x00,0x00,0x00};
    unsigned char MAC[6]= {0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};
    unsigned char hardware[2]={0x00,0x01};
    unsigned char protocolo[2]={0x08,0x00};
    unsigned char LHard[1]={0x06};
    unsigned char LProt[1]={0x04};
    unsigned char Opcode[2]={0x00,0x01};
    unsigned char host[1]={0x00};
    char nombre[16];
    int i = 0;
    struct ips * myips = NULL;
    for(host[0]=1;host[0]<255;host[0]++){
	    memcpy(ipDestino,ipOrigen,4);
	    memcpy(trama+0,MACbro,6);
	    memcpy(trama+6,MACOrigen,6);
	    memcpy(trama+12,arptype,2);
	    memcpy(trama+14,hardware,2);
	    memcpy(trama+16,protocolo,2);
	    memcpy(trama+18,LHard,1);
	    memcpy(trama+19,LProt,1);
	    memcpy(trama+20,Opcode,2);
	    memcpy(trama+22,MACOrigen,6);
	    memcpy(trama+28,ipOrigen,4);
	    memcpy(trama+32,MACDestino,6);
        memcpy(ipDestino+3,host,1);
        memcpy(trama+38,ipDestino,4);
       // imprimeTrama(trama, 42);
        enviarTrama(ds,indice,trama);
  	    recibeARP2(ds,trama,&myips);
    }
   memcpy(ipDestino,IP,4);
   memcpy(MACDestino,MAC,6);
   //insertar(&myips);
    struct ips * aux = myips;
	int pid=getpid();
	printf("El process id del la aplicacion es: %d\n ", pid);
    while(aux != NULL){
        printf("\nLa direccion mac de la ip : ");
        for(i=0;i<4;i++){
		       printf(" %d.",(aux->ip)[i]);
        }
        printf(" es: ");
        for(i=0;i<6;i++){
		        printf(" %.2X:",(aux->mac)[i]);
        }
		insertarTrama(aux->ip,aux->mac,pid);
        aux= aux->sig;
    }
    
}

int main(){
	int packet_socket,indice;
	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(packet_socket==-1){
		perror("\nError al abrir el socket");
		exit(1);
	}
	else{
		perror("\nExito al abrir el socket");
		indice=obtenerDatos(packet_socket);
		//enviarTrama(packet_socket,indice,tramaEnv);
		//recibeTrama(packet_socket,tramaRec);
        //doARP(packet_socket,indice,tramaEnv);
        scan(packet_socket,indice,tramaEnv);
	}
	close(packet_socket);		
	return(1);
}
