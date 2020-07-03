#include "myheader.h"
int main(int argc,char *argv[])
{
        struct sockaddr_in addr_con; 
        int addrlen = sizeof(addr_con); 
        //recivo de la terminal la ip ola pagina a la cual se hara el ping
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),
        ttl=64,pac=4,ciclo;
		char *mensaje=(char *)malloc(100*sizeof(char));
		char *inter=(char *)malloc(32*sizeof(char));
		char *destino=(char *)malloc(32*sizeof(char));
           if (argc<2)return 0; 
        else strcpy(destino,argv[1]);
        if(paquete==-1)
        {
        	perror("error al abrir el socket");
        	return 1;
        }else{
//socket abierto
                printf("Iserte la interfaz de red: ");
        		scanf("%s",inter);
        		printf("URL o IP a realizar ping: %s ",destino);
                //scanf("%s",destino); lee de la consola el destino al cual se hara el ping
        		printf("\n\033[0;31m***Conexión con los siguientes datos***\n");
                parametros(destino,&ttl,&pac,tuip,mensaje); // recivo los parametros para el ping traduce
                //traduce la pagina y la traduce en una direccíon ip
                cabr=datosred(inter,paquete); // datos de la red 
                int tiempopac[pac];
                printf("\n\nping con direccion> ");putip(tuip);
                if(compruebared(cabr,tuip)) // compruebo si el destino es una direccion de internet 
                {
                        printf("\n\nEl destino esta dentro de la red\n");
                        estructuraarp(cabr,tuip,tumac);
                }
                else //Se ejecuta este codigo con la red esta fuera la red domestica 
                         puts("\nDestino fuera de la red");                     
                ip_addr = dns_lookup(destino, &addr_con);
                reverse_hostname = reverse_dns_lookup(ip_addr); 
                printf("\nConectando a '%s' con IP: %s\n", destino, ip_addr); 
                //printf("\nDominio: %s", destino); 
                sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
                if(sockfd<0) 
                { 
                    printf("\nSocket no recibido\n"); 
                    return 0; 
                } 
                else
                    printf("\nSocket %d recibido\n", sockfd); 
            //signal para el control+c terminar programa
                printf("\033[0m");
               // signal(SIGINT, intHandler); // agrega una funcion al momento de ejecutar la interrupcion ctlr+c se ejecuta intHandler
                mandar_ping(sockfd, &addr_con, reverse_hostname, ip_addr, destino);

        }   
        return 0;
}
void parametros(char *dest,int *ttl,int *pac,unsigned char *tuip,char *mensaje)
{
    //printf("LLegue\n");
    //printf("PR1=%s\n",dest);
    int flag=0;
    if(dest[0]=='w'&& dest[1]=='w' && dest[2]=='w')
    {
        char *hostip;
        hostip=hostname_to_ip(dest);
        printf("Destino:%s->IP:%s\n", dest,hostip);
        sscanf(hostip," %d.%d.%d.%d",(int*)&tuip[0],(int*)&tuip[1],(int*)&tuip[2],(int*)&tuip[3]);
        flag=1;
    }else{
        //printf("Destino:%s\n", dest);
        sscanf(dest,"%d.%d.%d.%d",(int*)&tuip[0],(int*)&tuip[1],(int*)&tuip[2],(int*)&tuip[3]);
        flag=1;
    }
    if (flag==0)
    {
        printf("Destino no válido\n");
    }
}
char* hostname_to_ip(char * hostname)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    char* ip;
    ip=(char*)malloc(15*sizeof(char));     
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        // get the host info
        herror("gethostbyname");
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
    }
     
    return ip;
}
int ipValida(char *ip)
{
    struct sockaddr_in adr_inet;
    int flag=1;
    if (!inet_pton(AF_INET,ip,&adr_inet.sin_addr))//devuelve 1 en caso de éxito (dirección de red se convirtió con éxito). Se devuelve 0 si src no contiene una cadena de caracteres que representa una dirección de red válida
    {
        printf("\nIngrese una IP válida!!!");
        flag=0;
    }
    return flag;

}
void putip(unsigned char *ip)
{
	for(i=0;i<4;i++)
	{
		printf("%d",ip[i]);
		if(i==3)
			continue;
		printf(".");
	}
}
void putmac(unsigned char *mac)
{
	for(i=0;i<6;i++)
        {
                printf("%.2x",mac[i]);
                if(i==5)
                        continue;
                printf(":");
        }
}
/*optiene los datos de mi interfaz de conexion la cual  es la wlo1
tambien rellena parte del paquete con datos de la conexion y mi ip */
sred * datosred(char *interfaz,int paq)
{
        struct ifreq infointerfaz;
        struct ifreq nic;
	sred *nvor;
        strcpy(infointerfaz.ifr_name,interfaz);
	nvor=(sred *)malloc(sizeof(sred));
	nvor->paquete=paq;
        if(ioctl(paq,SIOCGIFINDEX,&infointerfaz)==-1)
                {perror("\nerror al obtener indice");exit(-1);}
        nvor->indice=infointerfaz.ifr_ifindex;
        //---------------------------------------
        if(ioctl(paq,SIOCGIFHWADDR,&infointerfaz)==-1)
                {perror("\nerror al obtener la mac");}
        else{
            //memcpy(MACorigen,nic.ifr_hwaddr.sa_data+0,6);
	    /*memcpy(MACorigen,red.ifr_hwaddr.sa_data,6);
		imprimeMAC (MACorigen,0);
		printf("\n");
            printf("\n La MAC es: "); */                          //MACorigen
            for(i=0;i<6;i++)
            {
               // printf("%.2x:", MACorigen[i]);
            }
            memcpy(nvor->mac+0,infointerfaz.ifr_hwaddr.sa_data,6);}
        //---------------------------------------    
        if(ioctl(paq,SIOCGIFADDR,&infointerfaz)==-1)
                {perror("\nerror al obener la ip");}
        else
            {
            /*memcpy(IPorigen,nic.ifr_addr.sa_data+2,4);
	//memcpy(IPOrigen,ip.ifr_addr.sa_data+2,4); 
		printf ("Direccion IP: ");
		imprimeIP(IPorigen,0);
		printf("\n");
            printf("\n La IP es: "); */                           //IPorigen
            for(i=0;i<4;i++)
                //printf("%d:", IPorigen[i]);
                //printf("\n");
                memcpy(nvor->ip+0,infointerfaz.ifr_addr.sa_data+2,4);
            }
        //-----------------------------------------        
        if(ioctl(paq,SIOCGIFNETMASK,&infointerfaz)==-1)
                {perror("\nerror al obtener la mascara de subrred");}
        else
                {memcpy(nvor->mascara,infointerfaz.ifr_netmask.sa_data+2,4);}
        system("ip r|grep default > MACdoor.txt");
        if((puerta=fopen("MACdoor.txt","r"))!=NULL)
        {
                fscanf(puerta,"? (%d.%d.%d.%d) at %x:%x:%x:%x:%x:%x",(int*)&nvor->ipenlace[0],(int*)&nvor->ipenlace[1],(int*)&nvor->ipenlace[2],(int*)&nvor->ipenlace[3],(unsigned int *)&nvor->macenlace[0],(unsigned int *)&nvor->macenlace[1],(unsigned int *)&nvor->macenlace[2],(unsigned int *)&nvor->macenlace[3],(unsigned int *)&nvor->macenlace[4],(unsigned int *)&nvor->macenlace[5]);
        }
        else
                {printf("\nError al abrir el archivo");exit(-1);}
        fclose(puerta);
        return nvor;
}
int resivearp(sred *cabr,unsigned char *tuip,unsigned char *tumac)
{
        struct timeval start, end;
        double time;
	gettimeofday(&start, NULL);
        while(time<2000)
        {
                int tam;
                tam=recvfrom(cabr->paquete,tramaarprec,48,0,NULL,0);
                if(tam==-1)
                        {perror("\nError al recibir trama");}
                else
                {
                        if(!memcmp(tramaarprec+20,codrespuesta,2)&&!memcmp(tramaarprec+0,cabr->mac,6)&&!memcmp(tramaarprec+28,tuip,4))
                        {
                                memcpy(tumac+0,tramaarprec+6,6);
				printf("\nObteniendo mac de ");putip(tuip);printf(" ...");
                                printf("su mac es: ");putmac(tumac);printf("\n");
                                return 0;
                        }
                }
                gettimeofday(&end, NULL);
                time =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
        }
	return 1;
}
void enviaarp(sred *cabr,unsigned char *tuip,unsigned char *tumac)
{
        int tam;
        struct sockaddr_ll nic;
        memset(&nic, 0x00, sizeof(nic));
        nic.sll_family = AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex = cabr->indice;
        tam = sendto(cabr->paquete, tramaarpenv,48, 0, (struct sockaddr *)&nic, sizeof(nic));
        if(tam == -1)
                perror("\nError al enviar\n\n");
        else
        {
                if(resivearp(cabr,tuip,tumac))
			{printf("\nrespuesta fallida\n"); exit(-1);}
        }
}
void estructuraarp(sred *cabr,unsigned char *tuip,unsigned char *tumac)
{
    memset(tumac,0xff,6);
    memcpy(tramaarpenv+0,tumac,6);
    memcpy(tramaarpenv+6,cabr->mac,6);
    memcpy(tramaarpenv+12,etertype,2);
	tramaarpenv[14]=0x00;//harware
	tramaarpenv[15]=0x01;//harware
	tramaarpenv[16]=0x08;//protocolo
	tramaarpenv[17]=0x00;//protocolo
    tramaarpenv[18]=0x06;//ldh
    tramaarpenv[19]=0x04;//ldp
    memcpy(tramaarpenv+20,codenvio,2);
    memcpy(tramaarpenv+22,cabr->mac,6);
    memcpy(tramaarpenv+28,cabr->ip,4);
    memcpy(tramaarpenv+32,tumac,6);
    memcpy(tramaarpenv+38,tuip,4);
	enviaarp(cabr,tuip,tumac);
}
void estadisticas(int *tiempopac,unsigned char *tuip,int pac)
{
	int min,max,med=0;
	min=tiempopac[0];
	max=tiempopac[0];
	for(i=0;i<ctapac[1];i++)
	{
		//printf("%d  ",tiempopac[i]);
		if(tiempopac[i]<min)
			min=tiempopac[i];
		if(tiempopac[i]>max)
			max=tiempopac[i];
		med=med+tiempopac[i];
	}
	med=med/ctapac[1];
	printf("Paquetes enviados=%d, Recibidos=%d, Perdidos=%d\n",ctapac[0],ctapac[1],ctapac[2]);
}
int compruebared(sred *cabr,unsigned char *tuip) // comprovar si es una direccion ip dentro de la red 
{
        unsigned char miipmas[4];
        unsigned char tuipmas[4];
        for(i=0;i<4;i++)
        {
                miipmas[i]=cabr->ip[i]&cabr->mascara[i];
                tuipmas[i]=tuip[i]&cabr->mascara[i];
        }
        if(!memcmp(miipmas,tuipmas,4))
                return 1;
      	return 0;
}
void checksum(int limi, int lims, unsigned char *check0, unsigned char *check1, unsigned char *mtrama)
{
	unsigned int suma=0;
	unsigned short aux;
	for(i=limi;i<lims;i+=2)
	{
		aux=mtrama[i];
		aux=(aux<<8)+mtrama[i+1];
		suma=suma+aux;
	}
	suma=(suma&0x0000FFFF)+(suma>>16);
	*check0=(unsigned char)~(suma);
        *check1=(unsigned char)~(suma>>8);
}
int reciveping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra)
{
        int tamano;
        struct timeval start, end;
        long int ptime=0;
		gettimeofday(&start, NULL);
        while( ptime < 100)//ciclo que recibira tramas
        {
                tamano = recvfrom(cabr->paquete,tramapingrec,74,0,NULL,0);
                if(tamano == -1)
                        printf("Error al recibir ping");
                else
                {
                        if(!memcmp(tramapingrec,cabr->mac,6)&&!memcmp(tramapingrec+12,ethertypeping,2)&&!memcmp(tramapingrec+26,tuip,4)&&!memcmp(tramapingrec+30,cabr->ip,4))
                        {
                               	gettimeofday(&end, NULL);
                                ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
                                ctapac[1]++;
				tiempopac[intime]=ptime;intime++;
                                //printf("\nRespuesta desde: ");putip(tuip);
//                       printf(": bytes=74 tiempo=%ldms ttl=%d",ptime,tramapingenv[22]);
				return(1);
                        }
                }
                gettimeofday(&end, NULL);
                ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        }
        printf("\nRespuesta desde ");putip(tuip);
        printf(": fallida time=%ldms ttl=%d",ptime,tramapingenv[22]);
	ctapac[2]++;
	return(0);
}
void enviaping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra)
{
        struct sockaddr_ll nic;
        int tamano;
        memset(&nic, 0, sizeof(struct sockaddr_ll));
        nic.sll_family= AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex=cabr->indice;
        tamano =sendto(cabr->paquete,tramapingenv,tamtra,0,(struct sockaddr *)&nic, sizeof(struct sockaddr_ll));
        if(tamano == -1)               
                perror("\nError al enviar ping");
	else
		{ctapac[0]++;reciveping(cabr,tuip,tiempopac,sec,tamtra);}
		
}
void estructuraping(sred*cabr,unsigned char *tumac,unsigned char *tuip,int secuencia,int ttl,int red,int *tiempopac,char *mensaje)
{
    
	memset(tramapingenv+0,0x00,74);
	if(red)
		memcpy(tramapingenv+0,tumac,6);
	else
		memcpy(tramapingenv+0,cabr->macenlace,6);
        memcpy(tramapingenv + 6,cabr->mac,6);
	tramapingenv[12]=0x08;//ethertipe ping
	tramapingenv[13]=0x00;//ethertipe ping
    ///sigue todo lo del encabezado ip
	tramapingenv[14]=0x45;//version ip
	tramapingenv[15]=0x00;//tiposervicio
	tramapingenv[16]=0x00;//longitud ip
	tramapingenv[17]=28+strlen(mensaje);//0x3c;//longitud ip
	tramapingenv[18]=rand();
	tramapingenv[19]=0x00;
	tramapingenv[20]=0x00;
	tramapingenv[21]=0x00;	
    memcpy(tramapingenv +22,&ttl,1);
	tramapingenv[23]=0x01;//protocolo ping
	tramapingenv[24]=0x00;//checsum
	tramapingenv[25]=0x00;//checsum
	memcpy(tramapingenv +26,cabr->ip,4);
    memcpy(tramapingenv +30,tuip,4);
	checksum(14,33,&tramapingenv[25],&tramapingenv[24],tramapingenv);
    //ahora se llena el encabezado udp
	tramapingenv[34]=0x08;
	tramapingenv[35]=0x00;
	tramapingenv[36]=0x00;
	tramapingenv[37]=0x00;
	tramapingenv[38]=0x00;
	tramapingenv[39]=0x01;     
	tramapingenv[40]=0x00;
    memcpy(tramapingenv +41,&secuencia,1);
	memcpy(tramapingenv +42,mensaje,strlen(mensaje));
	checksum(34,74,&tramapingenv[37],&tramapingenv[36],tramapingenv);
//	checksum(34,(41+strlen(mensaje)),&tramapingenv[37],&tramapingenv[36],tramapingenv);
	enviaping(cabr,tuip,tiempopac,secuencia,(42+strlen(mensaje)));
}
char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con) 
{ 
    //printf("\nBuscando DNS..\n"); 
    struct hostent *host_entity; 
    char *ip=(char*)malloc(NI_MAXHOST*sizeof(char)); 
    int i; 

    if ((host_entity = gethostbyname(addr_host)) == NULL) 
    { 
         
        return NULL; 
    } 
    
     
    strcpy(ip, inet_ntoa(*(struct in_addr *) 
                        host_entity->h_addr)); 

    (*addr_con).sin_family = host_entity->h_addrtype; 
    (*addr_con).sin_port = htons (PORT_NO); 
    (*addr_con).sin_addr.s_addr = *(long*)host_entity->h_addr; 

    return ip; 
    
} 
char* reverse_dns_lookup(char *ip_addr) 
{ 
    struct sockaddr_in temp_addr;    
    socklen_t len; 
    char buf[NI_MAXHOST], *ret_buf; 

    temp_addr.sin_family = AF_INET; 
    temp_addr.sin_addr.s_addr = inet_addr(ip_addr); 
    len = sizeof(struct sockaddr_in); 

    if (getnameinfo((struct sockaddr *) &temp_addr, len, buf, 
                    sizeof(buf), NULL, 0, NI_NAMEREQD)) 
    { 
       //    printf("No se pudo encontrar el host\n"); 
        return NULL; 
    } 
    ret_buf = (char*)malloc((strlen(buf) +1)*sizeof(char) ); 
    strcpy(ret_buf, buf); 
    return ret_buf; 
} 
/*
void intHandler(int dummy) 
{ 
    pingloop=0; 
} 
/*/
void mandar_ping(int ping_sockfd, struct sockaddr_in *ping_addr, char *ping_dom, char *ping_ip, char *rev_host) 
{ 
    int ttl_val=64, msg_count=0, i, addr_len, flag=1, 
            msg_received_count=0; 
    
    struct ping_pkt pckt; 
    struct sockaddr_in r_addr; 
    struct timespec time_start, time_end, tfs, tfe; 
    long double rtt_msec=0, total_msec=0; 
    struct timeval tv_out; 
    tv_out.tv_sec = RECV_TIMEOUT; 
    tv_out.tv_usec = 0; 

    clock_gettime(CLOCK_MONOTONIC, &tfs); 

    
    // set socket options at ip to TTL and value to 64, 
    // change to what you want by setting ttl_val 
    if (setsockopt(ping_sockfd, SOL_IP, IP_TTL, 
            &ttl_val, sizeof(ttl_val)) != 0) 
    { 
        printf("\nSocket fallo\n"); 
        return; 
    } 

    else
    { 
        printf("\n"); 
    } 

    // setting timeout of recv setting 
    setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof tv_out); 

    // send icmp packet in an infinite loop 
    int contador =4;
    //while(pingloop)
    while (contador--) 
    { 
        // flag is whether packet was sent or not 
        flag=1; 
    
        //filling packet 
        bzero(&pckt, sizeof(pckt)); 
        
        pckt.hdr.type = ICMP_ECHO; 
        pckt.hdr.un.echo.id = getpid(); 
       	char *mensaje="Hello world my name is Bryan XD";
	int contmensajeTrama=0;
        for ( i = 0; i < sizeof(pckt.msg)-1; i++ ) {
           pckt.msg[i]=mensaje[contmensajeTrama++];
	 }
        
        pckt.msg[i] = 0; 
        pckt.hdr.un.echo.sequence = msg_count++; 
        pckt.hdr.checksum = chksm(&pckt, sizeof(pckt)); 


        usleep(PING_SLEEP_RATE); 

        //send packet 
        clock_gettime(CLOCK_MONOTONIC, &time_start); 
        if ( sendto(ping_sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*) ping_addr, 
            sizeof(*ping_addr)) <= 0) 
        { 
            printf("\nFallo envio de paquete\n"); 
            flag=0; 
        } 

        //receive packet 
        addr_len=sizeof(r_addr); 

        if ( recvfrom(ping_sockfd, &pckt, sizeof(pckt), 0, 
            (struct sockaddr*)&r_addr, &addr_len) <= 0 
            && msg_count>1) 
        { 
            printf("\nFallo recibo de paquete\n"); 
        } 

        else
        { 
            clock_gettime(CLOCK_MONOTONIC, &time_end); 
            
            double timeElapsed = ((double)(time_end.tv_nsec - time_start.tv_nsec))/1000000.0;
            rtt_msec = (time_end.tv_sec-time_start.tv_sec) * 1000.0 + timeElapsed; 
            
            // si el paque no fue enviado, pues no recive nada   <<<<<   if packet was not sent, don't receive 
            if(flag) 
            { 
                if(!(pckt.hdr.type ==69 && pckt.hdr.code==0)) 
                { 
                    printf("Error..Paquete recibido con tipo %d codigo %d\n",pckt.hdr.type, pckt.hdr.code); 
                } 
                else
                { 
                    printf("%d bytes   icmp-seq=%d ttl=%d rtt = %Lf ms.\n", PING_PKT_S,  msg_count,ttl_val, rtt_msec); 
                    msg_received_count++; 
                } 
            } 
        }    
    } 
    // se ejecuta despues del ctrl+c ya que es una  interrupcion de tipo usuario    
    clock_gettime(CLOCK_MONOTONIC, &tfe); 
    double timeElapsed = ((double)(tfe.tv_nsec - 
                        tfs.tv_nsec))/1000000.0; 
    
    total_msec = (tfe.tv_sec-tfs.tv_sec)*1000.0+timeElapsed;
                    
    printf("\n%d pkg env, %d pkg rec, %.2f porcentaje. Tiempo total: %Lf ms.\n\n", msg_count, msg_received_count, (((double)msg_received_count)/(double)msg_count) * 100.0, total_msec); 
} 

void imprimeIP (unsigned char *ip,int index){
	int i;
	//printf ("Direccion IP: ");
		for(i=index;i<index+4;i++)
		printf("%d.",ip[i]);
		//printf ("\n");
}

void imprimeMAC(unsigned char *mac,int index){
	int i;
	for(i=index;i<index+6;i++)
		printf("%.2X:",mac[i]);
		//printf ("\n");
}
