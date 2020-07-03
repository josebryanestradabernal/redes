#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int  leerTrama(unsigned char *trama,FILE *in);
int analizarTrama(unsigned char *trama,int n);
int tramaInformacion(unsigned char * trama,int dsap,int ssap,int n);
int tramaNoNumerada(unsigned char *trama,int dsap,int ssap,int n);
int tramaSupervision(unsigned char *trama,int dsap,int ssap,int n);
int buffer=-1;
int main (int argc , char *argv[]){
FILE *in; 
if (argc<2){printf("Falta de archivo de entrada\n");return 1;}
in=fopen(argv[1],"r");
unsigned char tramaH[2500];
for (int i=0; i< 45;i++){
	printf("\n\x1B[32mTrama %d",i+1);
int lon=leerTrama(tramaH,in);
	analizarTrama(tramaH,lon);
	getchar();

}
fclose(in);
}

int leerTrama (unsigned char *trama ,FILE *in){
	int flag =0,c; 
	if (buffer!=-1){
	trama[0]=(unsigned char)buffer;
	flag=1;
	}
	while (flag<14){
		fscanf(in,"%02x",&c);
		trama[flag]=(unsigned char)c;
		flag++;
	}
	int longi=trama[13];
	
	while (flag<longi+14){
	fscanf(in,"%02x",&c);
	trama[flag++]=(unsigned char )c;
	}
	fscanf(in,"%02x",&buffer);
	while(buffer==0x20){trama[flag++]=(unsigned char)buffer;
	if (!feof(in))fscanf(in,"%02x",&buffer);
	else {buffer=-1;flag--;break;}
	} 
	for (int i=0;i<flag;i++){
			if (i%16==0)printf ("\n");
		printf("%02X ",trama[i]);
	
	} 
	return longi;
} 

int analizarTrama(unsigned char *trama ,int n){
	printf("\n\x1B[34mMac Destino:%02x %02x %02x %02x %02x %02x",trama[0]
	,trama[1],trama[2],trama[3],trama[4],trama[5]);

	printf("\nMac Origen:%02x %02x %02x %02x %02x %02x",trama[6]
	,trama[7],trama[8],trama[9],trama[10],trama[11]);
	printf("\nLongitud: %d",n);
	char bitDSAP= trama[14]&1;
	char bitSSAP =trama[15]&1;
	printf("\nDSAP: %02x %s",trama[14],(trama[14]&1?"grupo":"individual"));
	printf("\nSSAP: %02x %s",trama[15],(bitSSAP?"respuesta":"comando"));
	printf("\nSAP: ");
	for (int i=14;i<=15;i++){
		int sap=trama[i]&0xfe; 
		switch (sap){
			case 0x00:printf("SAP: Null LSAP");break;
			case 0x02 : printf("Individual LLC Sublayer Management Function");break;
			case 0x03:printf( "Group LLC Sublayer Management Function");break;
			case 0x04:printf("IBM SNA Path Control (individual)");break;
			case 0x05: printf("IBM SNA Path Control (group)");break;
			case 0x06 :printf("ARPANET Internet Protocol (IP)");break;
			case 0x08: printf("SNA");break;
			case 0x0C: printf("SNA"); break;
			case 0x0E :printf("PROWAY (IEC955) Network Management & Initialization");
			case 0x18 :printf("Texas Instruments");break;
			case 0x42 :printf("IEEE 802.1 Bridge Spanning Tree Protocol");break;
			case 0x4E :printf("EIA RS-511 Manufacturing Message Service"); break;
			case 0x7E :printf("ISO 8208 (X.25 over IEEE 802.2 Type 2 LLC)"); break;
			case 0x80 :printf("Xerox Network Systems (XNS)"); break;
			case 0x86 :printf("Nestar"); break;
			case 0x8E :printf("PROWAY (IEC 955) Active Station List Maintenance"); break;
			case 0x98 :printf("ARPANET Address Resolution Protocol (ARP)"); break;
			case 0xBC :printf("Banyan VINES"); break;
			case 0xAA :printf("SubNetwork Access Protocol (SNAP)"); break;
			case 0xE0 :printf("Novell NetWare"); break;
			case 0xF0 :printf("IBM NetBIOS"); break;
			case 0xF4 :printf("IBM LAN Management (individual)"); break;
			case 0xF5 :printf("IBM LAN Management (group)"); break;
			case 0xF8 :printf("IBM Remote Program Load (RPL)"); break;
			case 0xFA :printf("Ungermann-Bass"); break;
			case 0xFE :printf("ISO Network Layer Protocol"); break;
			case 0xFF :printf("Global LSAP"); break;
		}
		printf("  ");
	} 
	unsigned char control[2]={trama[16],trama[17]};
	int bitControl=trama[16]&3;
	switch (bitControl){
		// EN EL CASO DE la trama de informacion el and da 00 o 10 (0,2)
		case 0:tramaInformacion(control,bitDSAP,bitSSAP,2); break;
		case 3:tramaNoNumerada(control,bitDSAP,bitSSAP,2); break;
		case 2:tramaInformacion(control,bitDSAP,bitSSAP,2); break;
		case 1:tramaSupervision(control,bitDSAP,bitSSAP,2); break;
	}

}
int tramaInformacion(unsigned char *trama, int dsap, int ssap,int n){
	printf ("\nTrama de información");
	printf ("\nN(S): %d , N(R): %d",trama[0]>>1,trama[1]>>1);
	printf("\nP/F=%d%s",trama[1]&1,(trama[1]&1?", Requiere Respuesta inmediata":""));
	if (trama[1]&1){
		printf(" ,  %s", (ssap?"final":"poll"));
	}
}

int tramaNoNumerada(unsigned char *trama,int dsap,int ssap,int n){
	printf ("\nTrama No Numerada");
	int mm=(trama[0]>>2)&3;
	int mmm=trama[0]>>5;
	if (mm==0 && mmm==4){printf("\nSNRM Set Normal Response");}
	else if (mm==3 && mmm==6)	{printf("\nSNRME Set normal response extended mode");}
	else if (mm==3 && mmm==0 && ssap==0){printf("\nSARM Set Asynchronous Response mode");}
	else if (mm==3 && mmm==1){printf("\nSABM Set Asynchronous balance mode");}
	else if (mm==3 && mmm==3){printf("\nSABME Set Asynchronous balance mode extend");}
	else if (mm==3 && mmm==2){printf("\nSARME Set Asynchronous Response mode extend");}
	else if (mm==1 && mmm==0 && ssap==0){printf("\nSIM");}
	else if (mm==0 && mmm==2 && ssap==0){printf("\nDISC");}
	else if (mm==0 && mmm==3){printf("\nUA");}
	else if (mm==3 && mmm==0 ){printf("\nDM");}
	else if (mm==0 && mmm==2){printf("\nRD");}
	else if (mm==1 && mmm==0){printf("\nRIM");}
	else if (mm==0 && mmm==0){printf("\nUI");}
	else if (mm==0 && mmm==1){printf("\nPoll UP");}
	else if (mm==3 && mmm==4){printf("\nRSET");}
	else if (mm==0 && mmm==7){printf("\nTEST");}
	printf("\nP/F=%d%s",(trama[0]>>4)&1,((trama[0]>>4)&1?", Requiere Respuesta inmediata":""));
	if ((trama[0]>>4)&1){
		printf(" ,  %s", (ssap?"final":"poll"));
	}
}
int tramaSupervision(unsigned char *trama,int dsap,int ssap,int n){
	printf ("\nTrama de Supervision");
		printf ("\nN(R): %d",trama[1]>>1);
	int bitSS=(trama[0]>>2)&3;
	printf("\nSS=%d , ",bitSS);
	switch ( bitSS)
	{
		case 0x00:printf("RR");break; 
		case 0x10:printf("REJ");break;
		case 0x01:printf("RNR");break;
		case 0x11:printf("SREJ");break;
	}
		printf("\nP/F=%d%s",trama[1]&1,(trama[1]&1?", Requiere Respuesta inmediata":""));
	if (trama[1]&1){
		printf(" ,  %s", (ssap?"final":"poll"));
	}

}
