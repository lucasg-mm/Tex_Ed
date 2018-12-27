#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento{
	struct elemento* prox;
	struct elemento* ant;
	char string[30];
}PALAVRA;

void inicializa_lista(PALAVRA** cursor){
	*cursor = NULL;
	
	return;
}

void insere_lista_final(PALAVRA** cursor, char dado[30]){
	PALAVRA* novo;  //Variável auxiliar que guarda novos nós
	PALAVRA* aux;
	
	//Cria nó e insere no final da lista ("normal"):
		novo = (PALAVRA*)malloc(sizeof(PALAVRA));
		
		if(novo == NULL){  //Erro na alocação de memória.
			exit(1);
		}
		
		novo->prox = NULL;
		strcpy(novo->string, dado);
		
		if(*cursor == NULL){  //Caso em que a lista está vazia, e, portanto, insere-se o dado no início.
			novo->ant = NULL;
			*cursor = novo;  //O ponteiro para o primeiro nó quase nunca muda, pois o primeiro quase nunca muda (estamos inserindo nó no final).
		}
		else{  //Caso em que a lista não está vazia e, portanto, insere-se o dado no fim.
			aux = *cursor;
			
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = novo;
			novo->ant = aux;
		}
	return;
}

void le_arquivo(PALAVRA** cursor, char* nome){
	char nume[5];  //Especifica o nome do arquivo a ser lido. (como são apenas 6 casos de teste, pode ser um char).
	char ext[5];  //Especifica a extensão do arquivo.  ###############Pode haver erro na numeração!
	FILE* arquivo;
	char normal[30];  //Variável auxiliar que guarda caracteres comuns.
	char especial[30];  //Variável auxiliar que guarda caracteres especiais.
	int flag;
	int flag2;
	int i;
	int j;
	int k;
	char c;  //Apenas para auxiliar a verificação de fim de arquivo.
	char normal_com_espaco[30];  //EDIÇÃO!!! É apenas a versão de "normal" com espaço no começo.
	char normal_ultimate[30];
	int checkpoint;
	
	strcpy(ext, ".ext");
	flag = 0;
	checkpoint = -1;
	k = 0;
	
	//Abertura de um arquivo especificado:
	scanf("%s", nume);
	
	strcat(nome, &nume[0]);  //Compondo o nome completo do arquivo.
	strcat(nome, ext);
			
	arquivo = fopen(nome, "r");
	
	if(arquivo == NULL){ //Erro na abertura do arquivo.
		exit(1);
	}
	
	for(i = 0; i < 30; i++){ //Preenchendo as strings com '\0'.
		normal[i] = '\0';
		especial[i] = '\0';
		normal_com_espaco[i] = '\0';
		normal_ultimate[i] = '\0';
	}
	
	//Leitura do tal arquivo:
	while((c = getc(arquivo)) != EOF){ //Enquanto o final do arquivo não tiver sido alcançado, continua no loop.
		flag2 = 0;
		
		fseek(arquivo, -sizeof(char), SEEK_CUR);
		
		fscanf(arquivo, "%s", normal);
		
		strcat(normal_com_espaco, normal);
		
		//Edit:
		for(i = 0; i < 30; i++){
			if(normal_com_espaco[i] == '\0'){
				break;
			}			
			if(((normal_com_espaco[i] < 'A') || (normal_com_espaco[i] > 'Z')) && ((normal_com_espaco[i] < 'a') || (normal_com_espaco[i] > 'z')) && ((normal_com_espaco[i] < '0') || (normal_com_espaco[i] > '9')) && (normal_com_espaco[i] != ' ')){
				especial[0] = normal_com_espaco[i];
				for(j = (checkpoint + 1); j < i; j++){
					normal_ultimate[k] = normal_com_espaco[j];
					flag = 1;
					flag2 = 1; //Diz se existe caracter especial numa sequencia.
					k++;
				}
				if(flag == 1){
					insere_lista_final(cursor, normal_ultimate);  //Insere lista final ultimate.
					insere_lista_final(cursor, especial);  //Insere lista final especial.
					flag = 0;//Zera a flag.
					checkpoint = i;  //Para saber a localização do último caracter especial.
					for(j = 0; j < 30; j++){ 
		                normal_ultimate[j] = '\0';
	                }
					k=0;  //Isso parece errado...
				}
			}
			if((flag2 == 1) && (normal_com_espaco[i+1] == '\0') && (((normal_com_espaco[i] >= 'A') && (normal_com_espaco[i] <= 'Z')) || ((normal_com_espaco[i] >= 'a') && (normal_com_espaco[i] <= 'z')) || ((normal_com_espaco[i] >= '0') && (normal_com_espaco[i] <= '9')))){
				for(j = (checkpoint + 1); j < (i+1); j++){
					normal_ultimate[k] = normal_com_espaco[j];
					k++;
				}
				insere_lista_final(cursor, normal_ultimate);  //Insere lista final ultimate.
				k = 0;
				break;
			} 
		}
		checkpoint = -1;
		
        for(j = 0; j < 30; j++){ 
            normal_ultimate[j] = '\0';
	    }		
		
		//Cria nó e insere no final da lista ("normal_com_espaco"):
		if(flag2 != 1){  //Se não tiver nenhum caracter especial na sequencia.
		    insere_lista_final(cursor, normal_com_espaco);
		}
		
		for(i = 0; i < 30; i++){ //Preenchendo de novo as strings com '\0'.
			normal[i] = '\0';
			especial[i] = '\0';
		}
		strcpy(normal_com_espaco, " ");  //EDIÇÃO!!!!!!!
	}
	fclose(arquivo);	
	
	return;
}

void insere_antes(PALAVRA** cursor, char string[30]){
	PALAVRA* novo;
	int i;
	
	//Cria nó:
	novo = (PALAVRA*)malloc(sizeof(PALAVRA));
		
	if(novo == NULL){  //Erro na alocação de memória.
		exit(1);
	}
	
	for(i = 0; i < 30; i++){  //Elimina o lixo de memória
		novo->string[i] = '\0';
	}
	
	strcpy(novo->string, string);
	//break point aqui
	if(*cursor == NULL){  //Caso em que a lista está vazia, e, portanto, insere-se o dado no início.
		novo->ant = NULL;
		*cursor = novo;  //O ponteiro para o primeiro nó quase nunca muda, pois o primeiro quase nunca muda (estamos inserindo nó no final).
	}
	else{  //Caso em que a lista não está vazia.
		if((*cursor)->ant == NULL){  //O cursor está no começo (posição 0).
		    novo->ant = NULL;
			novo->prox = *cursor;
			(*cursor)->ant = novo;
		}
		else{  //O cursor está no meio.
		    novo->ant = (*cursor)->ant;
			novo->ant->prox = novo;
		    (*cursor)->ant = novo;
		    novo->prox = *cursor;	
		}		
	}
	return;
}

void insere_depois(PALAVRA** cursor, char string[30]){
	PALAVRA* novo;
	int i;
	
	//Cria nó:
	novo = (PALAVRA*)malloc(sizeof(PALAVRA));
		
	if(novo == NULL){  //Erro na alocação de memória.
		exit(1);
	}
	
	for(i = 0; i < 30; i++){  //Elimina o lixo de memória
		novo->string[i] = '\0';
	}	
	
	strcpy(novo->string, string);
	
	if(*cursor == NULL){  //Caso em que a lista está vazia, e, portanto, insere-se o dado no início.
		novo->ant = NULL;
		*cursor = novo;  //O ponteiro para o primeiro nó quase nunca muda, pois o primeiro quase nunca muda (estamos inserindo nó no final).
	}
	else{  //Caso em que a lista não está vazia.
		if((*cursor)->prox == NULL){  //O cursor está no fim.
			novo->prox = NULL;
			novo->ant = *cursor;
			(*cursor)->prox = novo;
		}
		else{  //O cursor está no meio.
			novo->prox = (*cursor)->prox;
			novo->prox->ant = novo;
			(*cursor)->prox = novo;
			novo->ant = *cursor;
		}
	}
	return;
}

void substitui_atual(PALAVRA** cursor, char string[30]){  //Deu trabalho.
	strcpy((*cursor)->string, string);
	
	return;
}

void busca(PALAVRA** cursor, char string[30]){
	PALAVRA* percorre;  //Percorre no sentido inicio da lista.
	int dist;
	int flag;
	
	dist = 0;
	percorre = *cursor;
	
	
	flag = strcmp(string, percorre->string);
	
	while((percorre != NULL) && flag != 0){
		percorre = percorre->prox;  //Percorrendo até o fim.
		if(percorre == NULL){  //Para não dar segmentation fault.
			break;
		}
		flag = strcmp(string, percorre->string);		
	}
	
	if(percorre == NULL){  //Se o nó não for encontrado.
		return;
	}
	
	while(percorre->ant != NULL){  //Edit: antes era ou
		percorre = percorre->ant;  //Percorrendo até o inicio.
		dist++;
	}

	printf("%d\n", dist);   //Se o nó foi encontrado.

	return;
}

void remove_palavra(PALAVRA** cursor){  //#####Mas para onde "*cursor" vai apontar depois?
	PALAVRA* aux;
	int i;
	char espaco[30];
	
	for(i = 0; i < 30; i++){
		espaco[i] = '\0';
	}
	
	strcpy(espaco, " ");  //Adiciona espaco na string (se não tiver).
	
	aux = *cursor;
	
	if(cursor == NULL){  //A lista não foi inicializada.
		exit(1);
	}
	if(*cursor == NULL){  //A lista foi inicializada, mas está vazia.
		exit(1);
	}
	
	if((*cursor)->prox == NULL){  //A lista foi inicializada e o cursor aponta para um elemento no fim.
		*cursor = aux->ant;  //Ou último
		aux->ant->prox = NULL;
		free(aux);
		
		return;
	}
	
	if((*cursor)->ant == NULL){  //A lista foi inicializada e o cursor aponta para um elemento no inicio.
		*cursor = aux->prox;
		aux->prox->ant = NULL;
		free(aux);
		
		return;
	}
	
	if(((*cursor)->ant != NULL) && ((*cursor)->prox != NULL)){  //A lista foi inicializada e o cursor aponta para um elemento no meio.
		if((*cursor)->prox->string[0] != ' '){
			strcat(espaco, (*cursor)->prox->string);
			strcpy((*cursor)->prox->string, espaco);
		}
		
		*cursor = aux->prox;  //Ou último
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		free(aux);
		
		return;
	}
	
	if(((*cursor)->ant == NULL) && ((*cursor)->prox == NULL)){  //A lista foi inicializada e o cursor aponta para um elemento único.
	    *cursor = NULL;
		free(aux);
		
		return;
	}	
}

void avanca_unitario(PALAVRA** cursor){
	*cursor = (*cursor)->prox;
	
	return;
}

void retrocede_unitario(PALAVRA** cursor){
	*cursor = (*cursor)->ant;
	
	return;
}

void retrocede_ao_zero(PALAVRA** cursor){
	while((*cursor)->ant != NULL){
		*cursor = (*cursor)->ant;
	}
	
	return;
}

void avanca_ao_final(PALAVRA** cursor){
	while((*cursor)->prox != NULL){
		*cursor = (*cursor)->prox;
	}
	
	return;
}

void mover_cursor(PALAVRA** cursor, int numero){
	if(numero > 0){  //O usuário quer avançar.
		while(numero != 0){
			*cursor = (*cursor)->prox;
			numero--;
		}
	}
	
	if(numero < 0){  //O usuário quer retroceder.
		while(numero != 0){
			*cursor = (*cursor)->ant;
			numero++;
		}
	}
	
	return;
}

void imprime(PALAVRA* cursor){
	while(cursor != NULL){
		printf("%s", cursor->string);
	    cursor = cursor->prox;		
	}
	
	return;
}

void grava_arquivo(PALAVRA* cursor, char nome[5]){
	FILE* arquivo;
	
	arquivo = fopen(nome, "w");
	
	if(arquivo == NULL){ //Erro na abertura do arquivo.
	    exit(1);
	}
	
	while(cursor != NULL){
		fprintf(arquivo, "%s", cursor->string);
		cursor = cursor->prox;		
	}
	
	fclose(arquivo);
	return;
}

int main(){
	//Declarações iniciais:
	int gatilho;  //Para manter o programa no loop
	char opcao;  //Recebe os comandos
	char espec[30];  //Recebe as especificações dos comandos.
	PALAVRA* cursor;  //O endereço que esse ponteiro aponta varia durante a execução do programa (o que não aconteceria se fosse uma lista encadeada simples).
	char nome[5];  //Armazena o nome do arquivo
	int numero;  //Armazena quantas posições o usuário deseja mover o cursor (negativo retrocede).
	int i;
	char espec_com_espaco[30]; //Uma versão da espec, mas com espaço no começo.
	char comando[35];
	
	//Atribuições iniciais:
	gatilho = 1;
	
	//Funções iniciais:
	inicializa_lista(&cursor);  //Inicializa a lista duplamente encadeada.
	for(i = 0; i < 5; i++){  //Preenche a string com '\0'.
	    nome[i] = '\0';
	}

	for(i = 0; i < 35; i++){
		comando[i] = '\0';
	}
	
	le_arquivo(&cursor, nome);  //Leitura de um arquivo especificado.
	
	//Principal interação feita pelo usuário:
	while(gatilho == 1){
		for(i = 0; i < 30; i++){  //Preenche com '\0'.
		    espec_com_espaco[i] = '\0';
	    }
		
		setbuf(stdin, NULL);
		
		fgets(comando, 35, stdin); //Capta primeiro opcao, depois espec.
		
		opcao = comando[0]; //recebe a opcao.
		
		for(i = 2; i <= 32; i++){
			espec[i-2] = comando[i];
		}
		
		for(i = 0; i < 30; i++){  //Elimina o '\n'
			if(espec[i+1] == '\0'){
				espec[i] = '\0';
				break;
			}
		}
		
		if(((espec[0] >= 'A') && (espec[0] <= 'Z')) || ((espec[0] >= 'a') && (espec[0] <= 'z')) || ((espec[0] >= '0') && (espec[0] <= '9'))){  //Colocando o espaço (só se a palavra não for especial)
			strcpy(espec_com_espaco, " ");
		} 
		
		strcat(espec_com_espaco, espec);
		
		switch(opcao){ //BP
			case 'i':
				insere_antes(&cursor, espec_com_espaco);  //Insere nó anterior ao cursor.
				
				break;
			case 'a':
				insere_depois(&cursor, espec_com_espaco);  //Insere nó posterior ao cursor.
				
				break;
			case 'r':
				substitui_atual(&cursor, espec_com_espaco);  //Substitui palavra atual.
				
				break;
			case 'f':
				busca(&cursor, espec_com_espaco);  //Busca palavra e diz qual a distância.
				
				break;
			case 'd':
				remove_palavra(&cursor);  //Remove palavra.
				
				break;
			case 'n':
				avanca_unitario(&cursor);  //Avança cursor uma posição.
				
				break;
			case 'p':
				retrocede_unitario(&cursor);  //Retrocede cursor uma posição.
				
				break;
			case 'b':
				retrocede_ao_zero(&cursor);  //Posiciona em 0.
				
				break;
			case 'e':
				avanca_ao_final(&cursor);  //Posiciona no final.
				
				break;
			case 'g':
				numero = atoi(espec_com_espaco);  //Converte para int.
				mover_cursor(&cursor, numero);  //Avança ou retrocede uma certa quantidade de nós.
				
				break;
			case 's':
				retrocede_ao_zero(&cursor);  //Imprime e finaliza.
				imprime(cursor);				
				
				gatilho = 0;
				break;				
		}
		
	}
	
	//Escrita do tal arquivo:
	
	grava_arquivo(cursor, nome);
	
	//Liberando a memória alocada:
	
	//libera_lista();
	
	return 0;
}