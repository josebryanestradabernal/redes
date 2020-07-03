
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/types.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <asm/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h> 
#include <netdb.h> // para usar el gethostbyname (char *page)
#include <signal.h> 
#include <time.h>
#include <netinet/ip_icmp.h> // header que contiene la estructura de la trama de icmp
#define PING_PKT_S 64 
#define PORT_NO 0 
#define PING_SLEEP_RATE 1000000 
#define RECV_TIMEOUT 1
unsigned char MACorigen[6],IPorigen[4];

typedef struct sred
{
	int indice,paquete;
	unsigned char ip[4];
	unsigned char mac[6];
	unsigned char mascara[4];
	unsigned char ipenlace[4];
	unsigned char macenlace[6];
	unsigned char ippu[4];
}sred;
struct ping_pkt 
{ 
    struct icmphdr hdr; 
    char msg[32]; 
}; 
unsigned char tuip[4],tumac[6];
char *ip_addr, *reverse_hostname; 
sred *cabr=NULL;
FILE *puerta;
int sockfd; 
int pingloop=1;
int i,ctapac[3]={0,0,0},intime=0;
unsigned char ethertypeping[2]={0x08,0x00}; // trama ipv4 se usa para acciones de revicion como píng y tracerroute
unsigned char tramapingenv[1514];
unsigned char tramapingrec[1514];
//Varibales ARP//
unsigned char etertype[2]={0x08,0x06}; //ethertype para una trama ARP
unsigned char tramaarpenv[48];
unsigned char tramaarprec[48];
unsigned char codenvio[2]={0x00,0x01};
unsigned char codrespuesta[2]={0x00,0x02};
////Declaración de funciones///
void parametros(char *dest,int *ttl,int *pac,unsigned char *tuip,char *mensaje);
void putip(unsigned char *ip);
void putmac(unsigned char *mac);
sred * datosred(char *interfaz,int paq);
char* hostname_to_ip(char * hostname);
void estadisticas(int *tiempopac,unsigned char *tuip,int pac);
int compruebared(sred *cabr,unsigned char *tuip);
void checksum(int limi, int lims, unsigned char *check0, unsigned char *check1, unsigned char *mtrama);
int reciveping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra);
void enviaping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra);
void estructuraping(sred*cabr,unsigned char *tumac,unsigned char *tuip,int secuencia,int ttl,int red,int *tiempopac,char *mensaje);
int resivearp(sred *cabr,unsigned char *tuip,unsigned char *tumac);
void enviaarp(sred *cabr,unsigned char *tuip,unsigned char *tumac);
void estructuraarp(sred *cabr,unsigned char *tuip,unsigned char *tumac);
char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con);
char* reverse_dns_lookup(char *ip_addr);
void intHandler(int dummy);
void mandar_ping(int ping_sockfd, struct sockaddr_in *ping_addr, char *ping_dom, char *ping_ip, char *rev_host) ;

void imprimeIP (unsigned char *ip,int index);
void imprimeMAC(unsigned char *mac,int index);

//checksum
unsigned short chksm(void *b, int len) 
{ unsigned short *buf = b; 
    unsigned int sum=0; 
    unsigned short result; 

    for ( sum = 0; len > 1; len -= 2 ) 
        sum += *buf++; 
    if ( len == 1 ) 
        sum += *(unsigned char*)buf; 
    sum = (sum >> 16) + (sum & 0xFFFF); 
    sum += (sum >> 16); 
    result = ~sum; 
    return result; 
} 
