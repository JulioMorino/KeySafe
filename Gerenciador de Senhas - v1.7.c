/*  *Criação dos menus
    Problemas corrigidos/adicoes:
        *Consultar senhas passando indices errados foi corrigido
        *Criptografia não devolve mais valores dificeis de lidar na tabela Ascii;
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char gerar_senha(int a, char *b);
char criptografar(char *a, char *b);
void descriptografar(char *a);
void menu1();
int menu2();
int menu3();

int main(){
    int escolha_usuario = 0;
    
    do{
        printf("O que deseja fazer?\n");
        printf("1 - Gerar Senhas.\n2 - Consultar senhas.\n3 - Gerar backup.\n0 - Sair.\n");
        scanf("%d", &escolha_usuario);
        
        switch(escolha_usuario){
            case 1:
            menu1();
            break;
            
            case 2:
            menu2();
            break;
            
            case 3:
            menu3();
            break;
            
            case 0:
            break;
            
            default:
            printf("\nSelecione uma das opcoes possiveis.");
        }
    }while(escolha_usuario != 0);
}

void menu1(){
    int n = 0;
    FILE *file_senha;
    file_senha = fopen("registro.txt", "a");
    
    do{ 
    printf("Insira a quantidade de caracteres que deseja: ");
    scanf("%d", &n);

    if(n < 1 || n > 50)
        printf("Nao foi possivel criar a senha, insira uma quantidade de caracteres entre 1 e 50\n\n");
        fflush (stdin);
    
    } while(n < 1 || n > 50);
    
    struct gerenciar{
        char senha[51]; //variavel n aqui dentro dava problema, talvez pq ela seria local aqui
        char nome[31];
        char cripto[51];
    } ;
    struct gerenciar Senha1;
    printf("Insira o nome da senha: ");
    scanf(" %30[^\n]", Senha1.nome); //comando para scanf ler até um \n
    
    gerar_senha(n, Senha1.senha);
    printf("A senha do(a) %s foi gerada com sucesso:\n%s\n--------------------\n", Senha1.nome, Senha1.senha);
    
    criptografar(Senha1.senha, Senha1.cripto);
    
	fprintf(file_senha, "%s:%s°", Senha1.nome, Senha1.cripto);
	fclose(file_senha);
}

char gerar_senha(int a, char *b){
int i = 0, n = a;
    char minusculo[] = "abcdefghijklmnopqrstuvwxyz";
    char maiusculo[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numeros[] = "0123456789";
    char especiais[] = "!#$&*?@";
    int aleatorio;

    srand(time(NULL));

    while(i < n){
        aleatorio = rand() % 4;
        
        if (aleatorio == 0){
            b[i] = minusculo[rand() % 26];
        }
        
        if (aleatorio == 1){
            b[i] = maiusculo[rand() % 26];
        }
        
        if (aleatorio == 2){
            b[i] = numeros[rand() % 10];
        }
        
        if (aleatorio == 3){
            b[i] = especiais[rand() % 7];
        }
        
        i++;
    }
    b[i] = '\0'; //estava imprimindo lixo quando não coloco '\0' na ultima posição
    
    return *b;
}

char criptografar(char *a, char *b){
	int chave=10, i = 0;
	strcpy(b,a);
    
        while(b[i] != '\0')
        {
            b[i] = b[i] + chave;
            
            i++;
        }
        b[i] = '\0';
        
    
    return *b;	
}

void descriptografar(char *a){
    int chave = 10;
    int i = 0;
 
        i = 0;
        while(a[i] != '\0')
        {
            a[i] = a[i] - chave;
            
            i++;
        }
        a[i] = '\0';
        printf("A senha eh:%s\n--------------------\n", a);
}

int menu2(){
	char registro[5000];
	char busca_nome[31];
	char senha[51];
	int i = 0, j = 0;
	int tam = 0;

	FILE *file_senha;
	file_senha = fopen("registro.txt", "r");
		
		if(file_senha == NULL){
			printf("Não foi possivel abrir o arquivo. Verifique se voce ja gerou alguma senha");
			exit(0);
		}
		
		while(fgets(registro, 5000, file_senha)!= NULL){
		}
		//conteudo do txt salvo no vetor
		
		
	printf("Digite o nome da senha que deseja consultar: ");
	scanf(" %30[^\n]", busca_nome);
    
	char* result = strstr(registro, busca_nome); //busca ocorrencia do nome em todo o txt
	if(result == NULL){
    	printf("Senha nao encontrada, verifique se indicou o nome completo corretamente.\n\n");
    	return 0;
	}
	else{
    printf("Busca desejada: ");
    for (i = 0; i < strlen(busca_nome); i++)
        printf("%c", *(result + i));
        printf("\n");
        
    if((result[i]) != ':'){
    	printf("Senha nao encontrada, verifique se indicou o nome completo corretamente.\n\n");
    	return 0;
	}
    
	
    i = i + 1; // onde a senha comeca, pois sempre esta no formato nome_senha(espaco)senha_correspondente
    			//portanto isso equivale a um i = 0;
    
    while(result[i] != '°'){
    	senha[j] = result[i];
    	i++;
    	j++;
	}
	senha[j] = '\0';
    
    descriptografar(senha);
    //printf("%s\n", senha);
    return 0;
	}
}
int menu3(){
	char registro[5000];
	char registro_backup[5000];
	
	FILE *file_senha;
	file_senha = fopen("registro.txt", "r");
		
		if(file_senha == NULL){
			printf("Não foi possivel abrir o arquivo. Verifique se voce ja gerou alguma senha");
			exit(0);
		}
		
		while(fgets(registro, 5000, file_senha)!= NULL){
		}
		fclose(file_senha);
		
		strcpy(registro_backup, registro);
		
	file_senha = fopen("backup_registro.txt", "w");
	fprintf(file_senha, "%s", registro_backup);
	fclose(file_senha);
	
	printf("Backup realizado com sucesso! Armazene o arquivo criado em um local seguro.\n--------------------\n");
	return 0;
}


