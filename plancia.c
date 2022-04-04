

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