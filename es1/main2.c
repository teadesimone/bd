#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct canzone{
    char titolo[50];
    char autore[30];
}
 
typedef canzone;

void cerca_canzoni( FILE* fp);
void inserisci_canzone(FILE *fp);
void modifica_artista(FILE* fp, FILE* fp2);
void cancella_canzoni(FILE *fp, FILE* fp2);
void stringa(char* str);
void * xmalloc(size_t nbytes);
char * leggistringa(size_t n);
int leggi(char Stringa [],size_t n);

int main (){

FILE* fp,*fp2;
int opzione,op=1;

do{

printf("\ncosa desideri fare?\n");
printf(" 1 cercare le canzoni di un determinato artista\n 2 inserire una nuova canzone\n 3 modificare il nome di un artista\n 4 cancellare un artista con tutte le sue canzoni\n\n");

scanf("%d",&opzione);
getchar();

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

    char *autor;
    canzone temp;
    int count=0;

    fp=fopen("canzoni.txt","r");

    if(!fp){
    fprintf(stderr, "Errore nell'apertura del file");
    }

    printf("\nle canzoni di che artista cercare?\n");
    
    autor=leggistringa(50);
    stringa(autor);

    printf("le canzoni dell'artista %s presenti nel database sono:\n\n",autor);

    while(!feof(fp)){
        
        fscanf(fp,"%s %s",temp.titolo,temp.autore);
        
        if(strcmp(autor,temp.autore)== 0){

            printf("%s\n",temp.titolo);
            count++;
         }
    }

    if(count==0){
        printf("\nnon sono presenti canzoni di quell'artista\n\n");
    }
     fclose(fp);
     free(autor);
}

void inserisci_canzone (FILE* fp){

    char* titolo;
    char* autore;
    canzone temp;
    int n=0;


    fp=fopen("canzoni.txt","a+");

    if(!fp){
    fprintf(stderr, "Errore nell'apertura del file");
    }

    printf("\nche canzone desidere aggiungere?\n");
    
    titolo=leggistringa(50);
    stringa(titolo);
    printf("\ninserisci l'autore\n");
    autore=leggistringa(50);
    stringa(autore);

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
    free(autore);
    free(titolo);
}

void modifica_artista( FILE *fp, FILE *fp2){

    char *autore,*nuovo;
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
    
    autore=leggistringa(50);
    stringa(autore);

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
        nuovo=leggistringa(50);
        stringa(nuovo);

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
    

    remove("canzoni.txt");
    rename("temp.txt","canzoni.txt");
    free(autore);
    free(nuovo);
    }
    fclose(fp);
    fclose(fp2);
}

void cancella_canzoni( FILE *fp, FILE * fp2){

    char *autore;
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
    
    autore=leggistringa(50);
    stringa(autore);

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
    

    remove("canzoni.txt");
    rename("temp.txt","canzoni.txt");
    free(autore);
    }
    fclose(fp);
    fclose(fp2);
}

void stringa(char* str){

    int i;

    for(i=0;str[i]!='\0';i++){

        if(str[i]==' '){

            str[i]='_';
        }
        else continue;
    }
}

void * xmalloc(size_t nbytes)
{
  void *p =malloc(nbytes);

  if(!p)
  {
    fprintf(stderr,"Errore allocazione di memoria");
    exit(-1);
  }
  return p;
}


char * leggistringa(size_t tagliamax)
{
	char *S = xmalloc((tagliamax+1)*sizeof(char));
    char *S1;
	int lun;

	lun =leggi(S,tagliamax);
	S1=xmalloc((lun+1)*sizeof(char));
	strcpy(S1,S);
	free(S);
	return S1;
}

int leggi(char Stringa [],size_t n)
{
   int lunghezza;

   fgets(Stringa,n+1,stdin);

   lunghezza = strlen(Stringa);

   if(Stringa[lunghezza-1]=='\n')
   {
     Stringa[lunghezza-1]='\0';
   }

   return strlen(Stringa);
}
