#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct canzone{
    char titolo[50];
    char autore[20];
}
 
typedef canzone;

void cerca_canzoni( FILE* fp);
void inserisci_canzone(FILE *fp);
void modifica_artista(FILE* fp, FILE* fp2);
void cancella_canzoni(FILE *fp, FILE* fp2);

int main (){

FILE* fp,*fp2;
int opzione,op=1;

do{

printf("\ncosa desideri fare?\n");
printf(" 1 cercare le canzoni di un determinato artista\n 2 inserire una nuova canzone\n 3 modificare il nome di un artista\n 4 cancellare un artista con tutte le sue canzoni\n\n");

scanf("%d",&opzione);

    switch(opzione){
        case 1: cerca_canzoni(fp);break;
        case 2: inserisci_canzone(fp);break;
        case 3: modifica_artista(fp,fp2);break;
        case 4: cancella_canzoni(fp,fp2);break;
    }
    if (opzione<=0 || opzione >4){

        printf("\nopzione non esistente\n");
    }

    printf("\n\ndesideri continuare?\t 1=si\t altro=no\n");
    scanf("%d",&op);
}while(op==1);  

   return 0; 
}

void cerca_canzoni(FILE* fp){

    char autor[20];
    canzone temp;
    int count=0;

    fp=fopen("canzoni.txt","r");

    if(!fp){
    fprintf(stderr, "Errore nell'apertura del file");
    }

    printf("\nle canzoni di che artista cercare?(inserire l'underscore al posto dello spazio)\n");
    scanf("%s", autor);

    printf("le canzoni dell'artista %s presenti nel database sono:\n\n",autor);

    while(!feof(fp)){
        
        fscanf(fp,"%s %s",temp.titolo,temp.autore);
        
        if(strcmp(autor,temp.autore)== 0){

            printf("%s %s\n",temp.titolo,temp.autore);
            count++;
         }
    }

    if(count==0){
        printf("\nnon sono presenti canzoni di quell'artista\n\n");
    }
     fclose(fp);
}

void inserisci_canzone (FILE* fp){

    char titolo[50];
    char autore[20];
    canzone temp;
    int n=0;


    fp=fopen("canzoni.txt","a+");

    if(!fp){
    fprintf(stderr, "Errore nell'apertura del file");
    }

    printf("\nche canzone desidere aggiungere?\n");
    scanf("%s",titolo);
    printf("\ninserisci l'autore\n");
    scanf("%s",autore);

    while(!feof(fp)){

    fscanf(fp,"%s %s", temp.titolo, temp.autore);

        if (strcmp(autore,temp.autore)== 0 && strcmp(titolo,temp.titolo)==0){
             n=1; 
             break;
        } 
    }

    if(n!=1){

    fprintf(fp,"\n%s %s", titolo, autore);
        printf("\naggiunta andata a buon fine \n");

    }
    else if(n==1){

        printf("la canzone è già presente");
    }

    fclose(fp);
}

void modifica_artista( FILE *fp, FILE *fp2){

    char autore[20],nuovo[20];
    int n=0;
    canzone temp;

    fp=fopen("canzoni.txt","r");

    if(!fp){

        fprintf(stderr, "Errore nell'apertura del file");
    }

    fp2=fopen("temp.txt","w");

    if(!fp2){

        fprintf(stderr, "Errore nell'apertura del file");
    }

    printf("\nche artista vuoi modificare ?\n");
    scanf("%s", autore);

    while(!feof(fp)){    
        
        fscanf(fp,"%s %s", temp.titolo, temp.autore);

            if (strcmp(autore,temp.autore)== 0){
                n=1; 
                break;
            } 
    }
    rewind(fp);

    if(n!=1){

        printf("\nl'autore non è presente nel database\n");
    }
    
    else {

        printf("\ninserisci il nuovo nome dell'autore\n");
        scanf("%s",nuovo);

        while(!feof(fp)){    
        
        fscanf(fp,"%s %s", temp.titolo, temp.autore);

            if (strcmp(autore,temp.autore)== 0){
                
                fprintf(fp2,"\n%s %s", temp.titolo,nuovo);   
            }
            else{

                fprintf(fp2,"\n%s %s", temp.titolo, temp.autore);
            } 
        }

        printf("\nnome dell'autore cambiato correttamente\n");
    }

    remove("canzoni.txt");
    rename("temp.txt","canzoni.txt");
    fclose(fp);
    fclose(fp2);
}

void cancella_canzoni( FILE *fp, FILE * fp2){

    char autore[20];
    int n=0;
    canzone temp;

    fp=fopen("canzoni.txt","r");

    if(!fp){

        fprintf(stderr, "Errore nell'apertura del file");
    }

    fp2=fopen("temp.txt","w");

    if(!fp2){

        fprintf(stderr, "Errore nell'apertura del file");
    }

    printf("\nche artista vuoi cancellare ?\n");
    scanf("%s", autore);

    while(!feof(fp)){    
        
        fscanf(fp,"%s %s", temp.titolo, temp.autore);

            if (strcmp(autore,temp.autore)== 0){
                n=1; 
                break;
            } 
    }
    rewind(fp);

    if(n!=1){

        printf("\nl'autore non è presente nel database\n");
    }
    
    else {

        while(!feof(fp)){    
        
        fscanf(fp,"%s %s", temp.titolo, temp.autore);

            if (strcmp(autore,temp.autore)!= 0){
                
                fprintf(fp2,"\n%s %s", temp.titolo, temp.autore);
            } 
        }

        printf("\nautore cancellato correttamente\n");
    }

    remove("canzoni.txt");
    rename("temp.txt","canzoni.txt");
    fclose(fp);
    fclose(fp2);
}