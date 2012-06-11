/*
//======================//
//  CAMPO MINADO  v1.5  //
//======================//
Por: Etiene Dalcol, Mat 1211996, T3WA
Para: Disciplina de Programação I ministrada por Simone Barbosa, PUC-RIO, Junho de 2012
//======================//
Log de Alterações:
v1.0: 06/06/2012 Jogo Pronto!
v1.1: 06/06/2012 Limpando a tela pra ficar bonitinho. (Acho que só funciona em windows)
v1.2: 06/06/2012 Corrigindo bug na contagem dos vizinhos. (Checagem das bordas)
v1.3: 06/06/2012 Corrigindo bug na geração do campo que não era aleatória de verdade. (Colocando seed no rand)
v1.4: 10/06/2012 Corrigindo bug na abertura de brancos. As fronteiras não estavam abrindo.
v1.5: 10/06/2012 Adicionando as linhas e colunas dos outros lados pra visualizar melhor o campo.
To-do:
-Modificar a lógica para gerar o campo com as minas após a escolha da primeira coordenada. Usuário perder de primeira é TENSO.
Morri assim algumas e resolvi ajeitar. Como a senhora também não previu isso pois pediu pra sortear as minas primeiro resolvi já entregar
e depois eu brinco com isso! =)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LINHAS 20
#define MAX_COLUNAS 20

void ler_dimensoes(int *x, int *y){
	printf("Digite as dimensoes do campo:\n");
	scanf("%d %d",x,y);
	if((*y > MAX_LINHAS) || (*x > MAX_COLUNAS)){
		printf("Nao exceda o numero maximo de linhas(%d) ou colunas(%d)!\n",MAX_LINHAS,MAX_COLUNAS);
		ler_dimensoes(x,y);
	}
	else if((*y < 0) || (*x < 0)){
		printf("O valor de linhas e colunas precisa ser positivo!\n");
		ler_dimensoes(x,y);
	}
}

void ler_minas(int *n, int x, int y){
	printf("Digite a quantidade de minas:\n");
	scanf("%d",n);
	if(*n > x*y/2){
		printf("Minas demais! Por gentileza, preencha no maximo ate a metade do campo de minas.\n");
		ler_minas(n,x,y);
	}
	else if(*n < 0){
		printf("A quantidade de minas precisa ser positiva.\n");
		ler_minas(n,x,y);
	}
}

void sortear_mina(char campo[][MAX_COLUNAS], int x, int y){
	int x_m = rand() % x, y_m = rand() % y;
	if(campo[x_m][y_m] == 'm')
		sortear_mina(campo,x,y);
	else
		campo[x_m][y_m] = 'm';
}	

void preencher_minas(char campo[][MAX_COLUNAS], int n, int x, int y){
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			campo[i][j] = ' ';

	for(i=0;i<n;i++)
		sortear_mina(campo,x,y);
}

void exibir_campo(char campo[][MAX_COLUNAS], int x, int y){
	int i,j;
	char lin = 'A',col = 'A';

	printf("Exibindo campo:\n ");
	for(i=0;i<y;i++,col++)
		printf(" %c",col);
	printf("\n");
	for(i=0;i<x;i++,lin++){
		printf("%c ",lin);
		for(j=0;j<y;j++)
			printf("%c ",campo[i][j]);
		printf("%c ",lin);
		printf("\n");
	}
	printf(" ");
	for(i=0,col='A';i<y;i++,col++)
		printf(" %c",col);
	printf("\n");
}

void contar_vizinhos(char campo[][MAX_COLUNAS], int x, int y){
	int i,j;
	char n;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++){
			n = '0';
			if(campo[i][j]!='m'){
				if(j-1>=0 && campo[i][j-1]=='m')
					n++;
				if(j+1<y && campo[i][j+1]=='m')
					n++;
				if(i+1<x && j-1>=0 &&campo[i+1][j-1]=='m')
					n++;
				if(i+1<x && j+1<y && campo[i+1][j+1]=='m')
					n++;
				if(i-1>=0 && j-1>=0 &&campo[i-1][j-1]=='m')
					n++;
				if(j+1<y && i-1>=0 && campo[i-1][j+1]=='m')
					n++;
				if(i+1<x && campo[i+1][j]=='m')
					n++;
				if(i-1>=0 && campo[i-1][j]=='m')
					n++;
				if(n!='0')
					campo[i][j]=n;
			}
		}
}

void preencher_jogo(char jogo[][MAX_COLUNAS], int x, int y){
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			jogo[i][j] = '_';
}

void escolher_coordenada(char * cx, char * cy, int x, int y){
	int xmax=(int)'A'+x-1, ymax=(int)'A'+y-1;
	printf("Escolha a coordenada (linha e coluna):\n");
	scanf(" %c %c",cx,cy);
	if((*cx<'A')||((int)*cx>xmax)||(*cy<'A')||((int)*cy>ymax)){
		printf("Coordenadas invalidas! Escolha de novo.\n");
		escolher_coordenada(cx,cy,x,y);
	}
}

void abrir_ou_marcar(char * c){
	printf("Abrir ou marcar mina? A = abrir, M = marcar.\n");
	scanf(" %c",c);
	if((*c!='A')&&(*c!='M')){
		printf("Escolha invalida!\n",*c);
		abrir_ou_marcar(c);
	}
}

void abrir_brancos(char jogo[][MAX_COLUNAS], char campo[][MAX_COLUNAS], int x, int y, int cx, int cy){
	/*coord*/
	jogo[cx][cy]=' ';
	/*esquerda*/
	if(cy-1>=0)
		if(campo[cx][cy-1]==' ' && jogo[cx][cy-1]=='_')
			abrir_brancos(jogo,campo,x,y,cx,cy-1);
		else
			jogo[cx][cy-1] = campo[cx][cy-1];
	/*direita*/
	if(cy+1<y) 
		if(campo[cx][cy+1]==' ' && jogo[cx][cy+1]=='_')
			abrir_brancos(jogo,campo,x,y,cx,cy+1);
		else
			jogo[cx][cy+1] = campo[cx][cy+1];
	/*embaixo*/
	if(cx+1<x)
		if(campo[cx+1][cy]==' ' && jogo[cx+1][cy]=='_')
			abrir_brancos(jogo,campo,x,y,cx+1,cy);
		else
			jogo[cx+1][cy] = campo[cx+1][cy];
	/*em cima*/
	if(cx-1>=0)
		if(campo[cx-1][cy]==' ' && jogo[cx-1][cy]=='_')
			abrir_brancos(jogo,campo,x,y,cx-1,cy);
		else
			jogo[cx-1][cy] = campo[cx-1][cy];
	/*sudoeste -> só abre se esquerda ou embaixo estiver aberto*/
	if(cx+1<x && cy-1>=0 && campo[cx+1][cy-1]==' ' && jogo[cx+1][cy-1]=='_' && (campo[cx+1][cy]==' ' || campo[cx][cy-1]==' '))
		abrir_brancos(jogo,campo,x,y,cx+1,cy-1);
	/*sudeste -> só abre se direita ou embaixo estiver aberto*/
	if(cy+1<y && cx+1<x && campo[cx+1][cy+1]==' ' && jogo[cx+1][cy+1]=='_' && (campo[cx+1][cy]==' ' || campo[cx][cy+1]==' '))
		abrir_brancos(jogo,campo,x,y,cx+1,cy+1);
	/*noroeste -> só abre se esquerda ou em cima estiver aberto*/
	if(cy-1>=0 && cx-1>=0 && campo[cx-1][cy-1]==' ' && jogo[cx-1][cy-1]=='_' && (campo[cx-1][cy]==' ' || campo[cx][cy-1]==' '))
		abrir_brancos(jogo,campo,x,y,cx-1,cy-1);
	/*nordeste -> só abre se direito ou emcima estiver aberto*/
	if(cy+1<y && cx-1>=0 && campo[cx-1][cy+1]==' ' && jogo[cx-1][cy+1]=='_' && (campo[cx-1][cy]==' ' || campo[cx][cy+1]==' '))
		abrir_brancos(jogo,campo,x,y,cx-1,cy+1);
}

void jogar(char campo[][MAX_COLUNAS], char jogo[][MAX_COLUNAS], int x, int y, int tinicio){
	char cx, cy, ca;
	int i,j,count=0,tfim;
	system("cls");
	exibir_campo(jogo,x,y);
	escolher_coordenada(&cx,&cy,x,y);
	abrir_ou_marcar(&ca);
	if(ca=='A'){
		if(campo[cx-65][cy-65]=='m'){
			system("cls");
			exibir_campo(campo,x,y);
			printf("Voce abriu uma mina! Game Over!\n");
			return;
		}
		else if(campo[cx-65][cy-65]!=' '){
			jogo[cx-65][cy-65]=campo[cx-65][cy-65];
		}
		else{
			abrir_brancos(jogo,campo,x,y,cx-65,cy-65);
		}
		/*verificar se há campos não abertos além das minas*/
		for(i=0;i<x;i++)
			for(j=0;j<y;j++)
				if((campo[i][j]!='m') && (jogo[i][j]=='_'))
					count++;
		if(count==0){
			system("cls");
			exibir_campo(campo,x,y);
			tfim=clock();
			printf("Todas os campos foram abertos. Voce ganhou o jogo em %d segundos! Parabens!\n",(tfim-tinicio)/1000);
			return;
		}
	}
	else{
		jogo[(int)cx-65][(int)cy-65]='?';
		/*verificar se há minhas não marcadas*/
		for(i=0;i<x;i++)
			for(j=0;j<y;j++)
				if((campo[i][j]=='m') && (jogo[i][j]=='_'))
					count++;
		if(count==0){
			system("cls");
			exibir_campo(campo,x,y);
			tfim=clock();
			printf("Todas as minas foram marcadas. Voce ganhou o jogo em %d segundos! Parabens!\n",(tfim-tinicio)/1000);
			return;
		}
	}
	jogar(campo,jogo,x,y,tinicio);

}

int main(void){
	int x,y,minas,tinicio;
	char campo[MAX_LINHAS][MAX_COLUNAS];
	char jogo[MAX_LINHAS][MAX_COLUNAS];
	char j;
	srand(time(NULL));
	while(1){
	ler_dimensoes(&x,&y);
	ler_minas(&minas,x,y);
	preencher_minas(campo,minas,x,y);
	contar_vizinhos(campo,x,y);

	/*Mostra a resposta!
	exibir_campo(campo,x,y);*/
	preencher_jogo(jogo,x,y);
	tinicio = clock();
	jogar(campo,jogo,x,y,tinicio);
	printf("Deseja jogar novamente? S=sim, N=nao.\n");
	scanf(" %c",&j);
	if(j=='S')
		system("cls");
	else
		break;
	}
	system("pause");
	return 0;
}
