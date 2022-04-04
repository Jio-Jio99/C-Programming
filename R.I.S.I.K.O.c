#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <windows.h>
#include <unistd.h>

#define P 7
#define S 6		/*massimo 6 minimo 2 squadre (come risiko normale)- altrimenti andare a sviluppare i colori per le altre squadre in pių*/

typedef struct{
	char carta[10];
} TipoElemLista;

typedef struct strutturaLista{			
	TipoElemLista info;
	struct strutturaLista* next;
} TipoNodo;

typedef TipoNodo* TipoLista;

typedef struct{
	TipoLista carte;
	int quantiTerritori;
	char colore[6];		
} TipoSquadra;

typedef struct{
	int quantePedine;
	char colore[6];	
} TipoElemPlancia;

typedef struct{
	TipoElemPlancia territorio[P][P];	
} TipoPlancia;

/*-----------------------------------------------------------------------CONTROLLI-&-STAMPA*/

void textcolor(unsigned short color){										/*colori*/
    // HANDLE hconsole  = GetStdHandle(STD_OUTPUT_HANDLE);
    // if (hconsole == INVALID_HANDLE_VALUE) return;
    // SetConsoleTextAttribute(hconsole,color);
}

void colori(char *colore){

	if(strcmp(colore,"ROSSO")==0)
		textcolor(12);
	else if(strcmp(colore,"BLU")==0)
		textcolor(9);
	else if(strcmp(colore,"VERDE")==0)
		textcolor(10);
	else if(strcmp(colore,"BIANCO")==0)
		textcolor(15);
	else if(strcmp(colore,"VIOLA")==0)
		textcolor(13);
	else if(strcmp(colore,"GIALLO")==0)
		textcolor(14);
		
return;
}

void stampaElem(TipoElemLista dato){										/*lista carte*/
	printf("\t -%s\n",dato);
return;
}

void stampaLista(TipoLista plis){
	
	if(!plis)
		printf("\n\t\t\t-Non ha carte-\n");
	else
		printf("\n -Ecco le carte:\n");
	while(plis){
		stampaElem(plis->info);
		plis=plis->next;
	}

return;
}

int controlloIntervallo(int min, int max){									/*controllo da input*/
	int c=0, y;
	
	do{						
		scanf("%d", &y);
		
		if(((char)y)!=y){
			c++;
			if(c==1)
				printf("\tError! Inserire solo numeri: ");
			getchar();
		}
		else{
			if(y>max || y<min){
				printf("\tError! Reinserire: ");
				c=1;
				getchar();
			}
			else{
				c=0;
			}
		}
	
	}
	while(c>0);
	
return y;
}

int controlloAdiacenza(int r,int c,int x,int y){							/*controllo di adiacenza*/
	int p=1;
		
	if((x==r-1 || x==r+1 || x==r) && (y==c-1 || y==c+1 || y==c))
		p=0;
	else{
		printf("\n\t\t\t\t\t  -ATTENZIONE-\n\tLe regole del Risiko permettono di attaccare o spostare le pedine solo ai territori adiacenti ai propri\n");
		system("PAUSE");
	}
		
return p;
}

void eliminaCarte(TipoLista *plis,char *carta,int *totC){
	TipoNodo *corr,*pgen,*prec;
	int conta=0,f=0,c=0,cn=0;
	
	pgen=malloc(sizeof(TipoNodo));
		if(!pgen)
			printf("error");
	
	prec=pgen;
	corr=pgen->next=*plis;
	
	if(strcmp(carta,"misto")!=0){
		
		if(strcmp(carta,"fante"))
			totC[0]+=3;
		if(strcmp(carta,"cavallo"))
			totC[1]+=3;
		if(strcmp(carta,"cannone"))	
			totC[2]+=3;
	
		while(corr && conta!=3){
			if(strcmp(carta,corr->info.carta)==0){
				prec->next=corr->next;
				free(corr);
				corr=prec->next;
				conta++;	
			}
			else{
				corr=corr->next;
				prec=prec->next;	
			}
		}
	
	}
	else{
		
		totC[0]+=1;
		totC[1]+=1;
		totC[2]+=1;
		
		while(corr && conta!=3){
			if((strcmp("fante",corr->info.carta)==0) && f!=1){
				prec->next=corr->next;
				free(corr);
				corr=prec->next;
				conta++;
				f=1;	
			}
			else if((strcmp("cavallo",corr->info.carta)==0) && c!=1){
				prec->next=corr->next;
				free(corr);
				corr=prec->next;
				conta++;
				c=1;	
			}
			else if((strcmp("cannone",corr->info.carta)==0) && cn!=1){
				prec->next=corr->next;
				free(corr);
				corr=prec->next;
				conta++;
				cn=1;	
			}
			else{
				corr=corr->next;
				prec=prec->next;	
			}
		}
	}
		
	*plis=pgen->next;
	free(pgen);
	
return;	
}

/*--------------------------------------------------------------------------------PROTOTIPI*/

void inizializzazionePlancia(TipoSquadra *squad, TipoPlancia *mappa);
void stampaPlancia(TipoPlancia mappa,char *colore);

void schieraFunzione(TipoPlancia *mappa,TipoSquadra squadra,int *totPedine);
void spostaPedine(TipoPlancia *mappa,TipoSquadra sposta,int *contatoreSposta);
void attaccoFunzione(TipoPlancia *mappa, TipoSquadra *attacco, TipoSquadra *arrayDifesa,int *cartaPresa,int *numeroCarte,int *nSquadreAttacco);

/*per le carte*/
void aggiungiCarta(TipoLista *listaCarte,int *totCarte);
void trisFunzione(TipoLista *carte,int *totalePed,int *arrayCarte);

/*per il giro dei dadi*/
int giroDadi(TipoPlancia *arr,TipoSquadra *attacco,int totA,int x,int y,TipoSquadra *arr2,int *nSquadre);
void randomico(int *dado,int n);
void ordinamento(int *dado,int n);
void scambio(int *num1,int *num2);

/*-------------------------------------------------------------------------------------MAIN*/

int main(){
	TipoPlancia plancia;
	TipoSquadra squadra[S];
	int t,menu,pedine,sposta,carta,i,totCarte[3]={15,15,15}, nSquadreMain=S;

if(S>2){
	
	textcolor(15);
	for(i=0;i<S;i++){	/*inizializzazione dell'array squadre*/
		if(i==0)
			strcpy(squadra[i].colore,"BIANCO");		
		else if(i==1)
			strcpy(squadra[i].colore,"BLU");
		else if(i==2)
			strcpy(squadra[i].colore,"VERDE");
		else if(i==3)
			strcpy(squadra[i].colore,"ROSSO");
		else if(i==4)
			strcpy(squadra[i].colore,"GIALLO");
		else if(i==5)
			strcpy(squadra[i].colore,"VIOLA");
		
		squadra[i].carte=NULL;
		squadra[i].quantiTerritori=(P*P)/S;
	}
	
	inizializzazionePlancia(squadra, &plancia);
 	
 	i=0;
 	do{
 		if(squadra[i].quantiTerritori==0 && i!=S-1)
			i++; 		
		else if(squadra[i].quantiTerritori==0 && i==S-1)
			i=0;
 		
		pedine=squadra[i].quantiTerritori/3;
		stampaPlancia(plancia,squadra[i].colore);
		trisFunzione(&squadra[i].carte,&pedine, totCarte);
		
		sposta=0;		/*per lo spostamento*/
		carta=0;
		system("cls");	
			
			do{
				stampaPlancia(plancia,squadra[i].colore);
							
				schieraFunzione(&plancia,squadra[i],&pedine);
				
				printf("\n Menu:");
					printf("\n\t1- ATTACCA");			
				if(sposta==1){
					textcolor(12);
					printf("\n\t2- SPOSTA (usato)");
					textcolor(15);
				}
				else{
					printf("\n\t2- SPOSTA");
				}
				printf("\n\t3- MOSTRA CARTE\n\t4- PASSA");
				printf("\n\n\t-Scelta: ");
				menu=controlloIntervallo(1,4);
				
				if(menu==1)
					attaccoFunzione(&plancia,&squadra[i],squadra,&carta, totCarte, &nSquadreMain);
				else if(menu==2 && sposta!=1){
					spostaPedine(&plancia, squadra[i],&sposta);
				}
				else if(menu==2 && sposta==1)
					printf("\t\t-Hai a disposizione max 1 spostamenti-\n");
				else if(menu==3)
					stampaLista(squadra[i].carte);
					
				else if(menu==4)
					printf("\n\t\t\t\t -TURNO FINITO-\n");
				
				system("PAUSE");
				system("cls");

			}
			while(menu!=4);
	
		i++;
		if(i==S)
		i=0;
	}
	while(i>=0 && nSquadreMain>2);
	printf("\n\t\tIl gioco e' FINITO!! Complimenti!\n");

}
else if(S==2){
	printf("\t\t\n-Non potete giocare poichč siete solamente due giocatori! Cercate almeno un terzo compagno!\n");	
}
	
return 0;
}


/*---------------------------------------------------------------------------------FUNZIONI per la PLANCIA*/

void inizializzazionePlancia(TipoSquadra *squad,TipoPlancia *mappa){
	int s,p,r,c;
	
	srand(time(NULL));
	
	for(r=0;r<P;r++){
		for(c=0;c<P;c++){
			mappa->territorio[r][c].quantePedine=0;
		}
	}
		
	for(s=0;s<S;s++){
		p=0;

		while(p<((P*P)/S)){
			r=rand()%P;
			c=rand()%P;
			
			if(mappa->territorio[r][c].quantePedine==0){
				mappa->territorio[r][c].quantePedine=((P*P)/S)/3;
				strcpy(mappa->territorio[r][c].colore,squad[s].colore);
			}
			else{
				p--;
			}
			
			p++;				
		}
	
	}

return;
}

void stampaPlancia(TipoPlancia mappa,char *colore){			/*stampa della plancia*/
	int i,r,c;

	printf("\n\t\t\t\t\tPLANCIA");
	printf("\n\n\t\t\t ");
	
	for(i=0;i<P;i++)
		printf("-  %d  ",i+1);
	printf("-\n\n");
	
	for(r=0;r<P;r++){
		if(r>0){
			printf("\t\t\t ");
			for(i=0;i<P;i++)
				printf("+-----");
			printf("+\n");
		}
		
		for(c=0;c<=P;c++){
			if(c==0)
				printf("\t\t%d-\t",r+1);
			if(c!=P){
				printf(" | ");
				colori(mappa.territorio[r][c].colore);
				printf(" %d ", mappa.territorio[r][c].quantePedine);
				textcolor(15);
			}
			if(c==P)
				printf(" |     -%d",r+1);
		}
		printf("\n");
	}
	
	printf("\n\t\t\t ");
	for(i=0;i<P;i++)
		printf("-  %d  ",i+1);
	printf("-\n");
	
	printf("\n\t\t\t\t  TURNO del ");
	colori(colore);
	printf("%s\n", colore);
	textcolor(15);
	
return;
}

/*---------------------------------------------------------------------------------------------FUNZIONI del MENU*/

void schieraFunzione(TipoPlancia *mappa,TipoSquadra squadra, int *totPedine){			
	int r,c,pedine;
	
	while(*totPedine>0){
		printf("\t\t\t  -Puoi schierare %d pedine in tutto-\n",*totPedine);
		printf("\n -Quante pedine su %d vuoi schierare? Ricorda che dovrai comunque schierarle tutte: ", *totPedine);
		pedine=controlloIntervallo(1,*totPedine); 
		
		do{
			printf(" -Dove schierare le %d pedine? Inserie riga e poi colonna\n", pedine);
			printf("\t\tRiga: ");
			r=controlloIntervallo(1,P);
			printf("\t\tColonna: ");
			c=controlloIntervallo(1,P);
			
			r-=1;
			c-=1;
			
			if(strcmp(squadra.colore,mappa->territorio[r][c].colore)==0){
				mappa->territorio[r][c].quantePedine+=pedine;
				printf("\n\t\t-Difesa rafforzata!-\n");
				*totPedine-=pedine;
				pedine=0;
			}
			else{
				printf("\n\tError! Questo e' un territorio nemico... ricalibra posizione\n\n");
			}
	
		} while(pedine>0);
		
		system("cls");
		stampaPlancia(*mappa,squadra.colore);
	}
		
return;
}

void spostaPedine(TipoPlancia *mappa,TipoSquadra sposta, int *contatoreSposta){
	int r,c,r2,c2,adiacente=0,ped,i;
	
	printf(" -Da dove spostare? Inserire coordinate territorio: ");
	printf("\n\t\tRiga: ");
	r=controlloIntervallo(0,P);
	printf("\t\tColonna: ");
	c=controlloIntervallo(0,P);
	
	if(r==0 || c==0){
		printf("\n\t\t\t-Operazione annullata, truppe richiamate-\n");
		return;
	}
	
	r-=1; c-=1;
	
	if(strcmp(sposta.colore,mappa->territorio[r][c].colore)==0){
		if(mappa->territorio[r][c].quantePedine>2){
			printf("\n -Quante pedine prendere? [max %d] ", mappa->territorio[r][c].quantePedine-2);
			ped= controlloIntervallo(1,mappa->territorio[r][c].quantePedine-2);
			
			do{
				printf("\n -Dove trasferirle? Inserire coordinate territorio: ");
				printf("\n\t\tRiga: ");
				r2=controlloIntervallo(0,P);
				printf("\t\tColonna: ");
				c2=controlloIntervallo(0,P);
				
				if(r2==0 || c2==0){
					printf("\n\t\t\t-Operazione annullata, truppe richiamate-\n");
					return;
				}
				
				r2-=1; c2-=1;
				
				if(controlloAdiacenza(r,c,r2,c2)==0){
						if(strcmp(sposta.colore,mappa->territorio[r2][c2].colore)==0){
							printf("\n\t\t-Transferimento");
							mappa->territorio[r][c].quantePedine-=ped;
							mappa->territorio[r2][c2].quantePedine+=ped;
							for(i=0;i<3;i++){
								printf(".");
								sleep(1);
							}
							*contatoreSposta=1;	
							printf(" avvenuto-\n");
							return;
						}
						else{
							printf("\n\t-Hai scelta 'SPOSTA', quindi adesso non puoi attaccare! Questo e' territorio nemico!\n");
							printf("\n\t\t\t\t-Ricalibra una nuova posizione-\n");
							adiacente++;
						}		
				}
				else{
					printf("\n\t\t\t\t-Ricalibra una nuova posizione-\n");
					adiacente++;
				}			
			
			}
			while(adiacente>0);
			
		}
		else{
			printf("\n\tError! Non puoi lasciare un tuo territorio con nessuna o una sola pedina, cambia territorio!\n");
			spostaPedine(&(*mappa),sposta, &(*contatoreSposta));
		}
	}
	else{
		printf("\n\tError! Questo e' territorio nemico... ricalibra posizione\n\n");
		spostaPedine(&(*mappa),sposta,&(*contatoreSposta));
	}

return;
}


void attaccoFunzione(TipoPlancia *mappa, TipoSquadra *attacco, TipoSquadra *arrayDifesa,int *cartaPresa,int *numeroCarte,int *nSquadreAttacco){
	int r,c,r2,c2,adiacente=0,ped,i;
	
	printf(" -Da dove spostare? Inserire coordinate territorio: ");
	printf("\n\t\tRiga: ");
	r=controlloIntervallo(0,P);
	printf("\t\tColonna: ");
	c=controlloIntervallo(0,P);
	
	if(r==0 || c==0){
		printf("\n\t\t\t-Operazione annullata, truppe richiamate-\n");
		return;
	}
	
	r-=1; c-=1;
	
	if(strcmp(attacco->colore,mappa->territorio[r][c].colore)==0){
		if(mappa->territorio[r][c].quantePedine>2){
			printf("\n -Quante pedine prendere? [max %d] ", mappa->territorio[r][c].quantePedine-2);
			ped= controlloIntervallo(1,mappa->territorio[r][c].quantePedine-2);
			
			do{
				printf("\n -Dove attaccare? Inserire coordinate territorio: ");
				printf("\n\t\tRiga: ");
				r2=controlloIntervallo(0,P);
				printf("\t\tColonna: ");
				c2=controlloIntervallo(0,P);
				
				if(r2==0 || c2==0){
					printf("\n\t\t\t-Operazione annullata, truppe richiamate-\n");
					return;
				}
				
				r2-=1; c2-=1;
				
				if(controlloAdiacenza(r,c,r2,c2)==0){
						if(strcmp(attacco->colore,mappa->territorio[r2][c2].colore)!=0){
							if((giroDadi(&(*mappa),&(*attacco),ped,r2,c2,arrayDifesa,&(*nSquadreAttacco))==1) && *cartaPresa!=1){
								aggiungiCarta(&attacco->carte, numeroCarte);
								*cartaPresa=1;
							}
							
							mappa->territorio[r][c].quantePedine-=ped;
							return;
						}
						else{
							printf("\n\t-Hai scelta 'ATTACCO', quindi adesso non puoi spostare in un tuo territorio!\n");
							printf("\n\t\t\t\t-Ricalibra una nuova posizione-\n");
							adiacente++;
						}		
				}
				else{
					printf("\n\t\t\t\t-Ricalibra una nuova posizione-\n");
					adiacente++;
				}			
			
			}
			while(adiacente>0);
			
		}
		else{
			printf("\n\tError! Non puoi lasciare un tuo territorio con nessuna o una sola pedina, cambia territorio!\n");
			attaccoFunzione(&(*mappa),&(*attacco), arrayDifesa,&(*cartaPresa), numeroCarte, &(*nSquadreAttacco));
		}
	}
	else{
		printf("\n\tError! Questo e' territorio nemico... ricalibra posizione\n\n");
		attaccoFunzione(&(*mappa),&(*attacco), arrayDifesa, &*cartaPresa, numeroCarte,&(*nSquadreAttacco));
	}

return;
}


int giroDadi(TipoPlancia *arr,TipoSquadra *attacco,int totA,int x,int y,TipoSquadra *arr2,int *nSquadre){
	int *dadoA, *dadoD,
		 totD, 
		 puntiA=0, puntiD=0, 
		 A, D, C,
		 conta=0, i, d,
		 risultato=0;
	
	totD= arr->territorio[x][y].quantePedine;
	
	for(d=0;d<S;d++){
		if(strcmp(arr->territorio[x][y].colore,arr2[d].colore)==0)
			break;
	}
	
	srand(time(NULL));		
		printf("\n\t-Lancio dei dadi:\n");
		sleep(1);
	do{
		/*pedine per l'attacco*/
		if(totA>=3)
			A=3;
		else
			A=totA;
			
		/*pedine per la difesa*/
		if(totD>=3)
			D=3;
		else
			D=totD;
		
		/*per calcolare la vittoria*/	
		
			if(conta>0){
				printf(" -Rilancio dei dadi:\n");
				free(dadoA);
				free(dadoD);
				sleep(1);
			}
			
			dadoA=malloc(A*sizeof(int));
				if(!dadoA)
					printf("Errore di allocazione!\n");
	
			dadoD=malloc(D*sizeof(int));
				if(!dadoD)
					printf("Errore di allocazione!\n");
						
			randomico(dadoA,A);		
			randomico(dadoD,D);
		
			printf("\n ATTACCO:\n");					/*stampa dei valori dei dadi*/
				for(i=0;i<A;i++){
					printf("   %d\n",dadoA[i]);
				}
				sleep(1);
			printf(" DIFESA:\n");
				for(i=0;i<D;i++){
					printf("   %d\n",dadoD[i]);
				}
				
			ordinamento(dadoA,A);		/*funzione per mettere in ordine decrescente*/
			ordinamento(dadoD,D);
			
			/*-------------------------------CONDIZIONI DI VITTORIA*/
			if(A>D)		/*per ciclare con il numero pių piccolo tra i dadi*/
				C=D;
			else
				C=A;
			
			puntiA=0;
			puntiD=0;
			
			for(i=0;i<C;i++){
				if(dadoA[i]>dadoD[i])
					puntiA++;
				else
					puntiD++;
			}
			
			A= A-puntiD;
			D= D-puntiA;
			
			totA= totA-puntiD;
			totD= totD-puntiA;
			sleep(1);
			if(totA==0 && puntiD==C){
				printf("\n\t\t\tL'attacco");
				colori(attacco->colore);
				printf(" %s", attacco->colore); textcolor(15);
				printf(" ha perso tutte le pedine!\n\t\t\t\tLA DIFESA");
				colori(arr2[d].colore); 
				printf(" %s ",arr2[d].colore); textcolor(15);
				printf("HA VINTO!\n\t\t\t\tPedine rimanenti: %d\n", totD);
				
				arr->territorio[x][y].quantePedine=totD;
			}
			else if(totD==0 && puntiA==C){
				printf("\n\t\t\tLa difesa ");
				colori(arr2[d].colore);
				printf("%s",arr2[d].colore); textcolor(15);
				printf(" ha perso tutte le pedine!\n\t\t\t\tL'ATTACCO");
				colori(attacco->colore);
				printf(" %s",attacco->colore); textcolor(15);
				printf(" HA VINTO!\n\t\t\t\tPedine rimanenti: %d\n", totA);
				arr->territorio[x][y].quantePedine=totA;
				strcpy(arr->territorio[x][y].colore,attacco->colore);
				attacco->quantiTerritori++;
				arr2[d].quantiTerritori--;
					if(arr2[d].quantiTerritori==0){
						printf("\n\t\t\t-Il");
						colori(arr2[d].colore);
						printf(" %s ",arr2[d].colore); textcolor(15);
						printf("e'stato eliminato!-\n");
						*nSquadre--;
					}
					
				risultato=1;
				
			}
			else{
				printf("\n\t-Pedine attacco perse: %d\n\t-Pedine difesa perse: %d\n", puntiD,puntiA);
				sleep(1);
			}
	
		if(totA!=0 && totD!=0){	
			printf("\n\n\t----------------------------%d TURNAZIONE----------------------------",conta+2);
			printf("\n\n Pedine rimanenti");
			colori(attacco->colore);
			printf(" ATTACCO");
			textcolor(15);
			printf(": %d\n Pedine rimanenti",totA);
			colori(arr2[d].colore);
			printf(" DIFESA");
			textcolor(15);
			printf(": %d\n\n", totD);
			sleep(1);
		}
		
		conta++;
	}
	while(totA>0 && totD>0);	
	
return risultato;
}

void randomico(int *dado,int n){		/*------------------------------------------------rand*/			
	int i;

	for(i=0;i<n;i++){				
		dado[i]=1+rand()%6;
	}
	
return;
}


void ordinamento(int *dado,int n){		/*------------------------------------------------ordinamento*/					
	int i,j,max;
	
	for(i=0;i<n-1;i++){
		max=i;
		for(j=i+1;j<=n-1;j++){
			if(dado[j]>dado[i]){
				max=j;
				scambio(dado+i,dado+max);
			}
		}
	}

return;
}


void scambio(int *num1,int *num2){		/*------------------------------------------------scambio*/
	int aux;
	
	aux=*num1;
	*num1=*num2;
	*num2=aux;
	
return;
}

void aggiungiCarta(TipoLista *listaCarte,int *totCarte){				/*--------------------------------------------------carte*/
	TipoNodo *nuovo,*prec,*corr,*pgen;
	int i;
	char *nomiCarte[3]={"fante","cavallo","cannone"};

	do{
		
		i=rand()%3;
		if(totCarte[0]==0 && totCarte[1]==0 && totCarte[2]==0){
			printf("\n\t\t\t\t -Non ci sono piu' carte-\n");
			return;
		}
		
	}while(totCarte[i]==0);
		
	pgen= malloc(sizeof(TipoNodo));
	if(!pgen){
		printf("Error di allocazione");
	}
	
	pgen->next=*listaCarte;			
	prec=pgen;
	corr=*listaCarte;			
	
	while(corr && (strcmp(corr->info.carta,nomiCarte[i])<0)){	/*ciclo per l'inserimento ordinato in modo alfabetico*/
		prec=corr;
		corr=corr->next;
	}	
		
	nuovo=malloc(sizeof(TipoNodo));
	if(!nuovo){
		printf("Problemi di allocazione!\n");
	}
	else{
		
		strcpy(nuovo->info.carta,nomiCarte[i]);
		totCarte[i]-=1;

		prec->next=nuovo;
		nuovo->next=corr;
		
	}
	*listaCarte=pgen->next;
	free(pgen);
	
	printf("\n\t\t\t\t    -Carta presa-\n");
	
return;
}

void trisFunzione(TipoLista *carte, int *totalePed, int *arrayCarte){
	TipoLista aux;
	TipoNodo *pgen,*prec,*corr;
	int rp=0,cav=0,fan=0,can=0, tris[2][4],i,c,conta=0,risposta;   /*fanti,cavalli,connoni,misto e la seconda riga č se č fatto o meno*/
	char *nomeTris[4]={"fante","cavallo","cannone","misto"};
	
	if(*carte==NULL)
		return;
		
	for(i=0;i<2;i++){
		for(c=0;c<4;c++){
			tris[i][c]=0;
		}
	}
		
	tris[0][0]=8;
	tris[0][1]=10;
	tris[0][2]=12;
	tris[0][3]=15;
	
	aux=*carte;
	while(aux){
		if(strcmp(aux->info.carta,"cavallo")==0)
			cav++;
		else if(strcmp(aux->info.carta,"fante")==0)
			fan++;
		else if(strcmp(aux->info.carta,"cannone")==0)
			can++;
		
		aux=aux->next;
	}
	
	if(fan>=3){
		tris[1][0]=1;
	}
	if(cav>=3){
		tris[1][1]=1;
	}
	if(can>=3){
		tris[1][2]=1;
	}
	if(can>0 && fan>0 && cav>0){
		tris[1][3]=1;
	}
	
	for(i=0;i<4;i++){
		if(tris[1][i]==1){
			conta++;
		}	
	}
	
	if(conta==1)
		printf(" -Hai fatto tris!\n");
	else if(conta>1)
		printf(" -Hai fatto pių tris!\n");
	
	for(i=0;i<4;i++){
		if(tris[1][i]==1){
			printf("\t\n -Ha fatto il tris %s, codice %d, con %d pedine\n",nomeTris[i], i+1,tris[0][i]);
		}	
	}
	
	if(conta!=0){
		printf(" -Vuoi utilizzare il tris? [si=1 / no=0] ");
		risposta= controlloIntervallo(0,1);		
	}
	
	while(rp!=1 && conta>0 && risposta==1){
		
		if(conta>1)
			printf(" -Quale tris utilizzare? Inserire il codice del tris: ");
		else 
			printf(" -Inserisci codice tris: ");
			
		c=controlloIntervallo(1,4);
				
		if(tris[1][c-1]==1){
			printf(" -Hai scelto il tris %s con %d pedine\n", nomeTris[c-1],tris[0][c-1]);
			eliminaCarte(&(*carte),nomeTris[c-1], arrayCarte);
			*totalePed+=tris[0][c-1];
			rp=1;
		}			
		else{
			printf("\t-scelta errata-\n");
			rp=0;
		}
		
	}
		
return;
}