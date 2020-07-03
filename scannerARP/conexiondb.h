#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <unistd.h> 

int insertarTrama (unsigned char *ip,unsigned char *mac,int i){
   sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("redes", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    char p[60];
    sprintf(p,"%i,'%i.%i.%i.%i','%.2X %.2X %.2X %.2X %.2X %.2X');",i,ip[0],ip[1],ip[2],ip[3],
    mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    char sql[1500] = "insert into tramas(pid,ip,mac) values (";
   //concatenar
   strcat (sql,p);
   //printf ("%s",sql);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
}
