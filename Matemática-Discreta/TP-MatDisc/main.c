#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define ITER 4

void resolveVonKoch(char entrada[10000], int teta, char regra[100]){
    FILE *arq1;
    arq1 = fopen("arq1.txt","w");

    //primeira iteração no arquivo
    fprintf(arq1, "%s", entrada);
    fclose(arq1);
    
    for(int i=0;i<ITER;i++){
        arq1 = fopen("arq1.txt", "r");
        fscanf(arq1, "%s", entrada);
        fclose(arq1);

        arq1 = fopen("arq1.txt", "w");
        int num = strlen(entrada);

        for(int j=0;j<num;j++){
            if(entrada[j]=='F'){
                fputs(regra, arq1);  //regra: F-F+F+FF-F-F+F
            }
            else{
                fputc(entrada[j], arq1); 
            }
        }
        
        fclose(arq1);
        printf("%dª Estágio: %s\n", i+1, entrada); //imprimindo iterações menos a última
    }
    arq1 = fopen("arq1.txt", "r");
    fscanf(arq1, "%s", entrada);
    printf("Fractal Final: %s\n", entrada);
    fclose(arq1);
    arq1 = fopen("arq1.txt","w");
    
    fputs(entrada, arq1);
    fputs("\n", arq1);
    fprintf(arq1, "%d", teta);
    fputs("\n", arq1);
    fprintf(arq1, "%d", 1);
    fclose(arq1);

    

    free(entrada);
}

void resolveHilbert(char entrada[10000], int teta, char regra[100], char regra2[100]){
    FILE *arq1;
    arq1 = fopen("arq1.txt","w");

    //primeira iteração no arquivo
    fprintf(arq1, "%s", entrada);
    fclose(arq1);
    for(int i=0;i<ITER;i++){
        arq1 = fopen("arq1.txt", "r");
        fscanf(arq1, "%s", entrada);
        fclose(arq1);

        arq1 = fopen("arq1.txt", "w");
        
        int num = strlen(entrada);
        for(int j=0;j<num;j++){
            if(entrada[j]=='X'){
                fputs(regra, arq1);   //regra: -YF+XFX+FY-
            }
            else if(entrada[j]=='Y'){
                fputs(regra2, arq1);   //regra2: +XF-YFY-FX+
            }
            else{
                fputc(entrada[j], arq1); 
            }
        }
        fclose(arq1);
        printf("%dª Estágio: %s\n", i+1, entrada);
    }
    arq1 = fopen("arq1.txt", "r");
    fscanf(arq1, "%s", entrada);
    printf("Fractal Final: %s\n", entrada);
    fclose(arq1);
    int num1 = strlen(entrada);
    arq1 = fopen("arq1.txt","w");
    for(int k=0;k<num1;k++){
        if(entrada[k]!='Y' && entrada[k]!='X'){
            fputc(entrada[k], arq1);
        }
    }
    fputs("\n", arq1);
    fprintf(arq1, "%d", teta);
    fputs("\n", arq1);
    fprintf(arq1, "%d", 2);
    fclose(arq1);

    free(entrada);
}

void resolveMeuFractal(char entrada[10000], int teta){
    FILE *arq1;
    arq1 = fopen("arq1.txt","w");
    //primeira iteração no arquivo
    fputs("R+R+S", arq1);
    fclose(arq1);
    for(int i=0;i<ITER;i++){
        arq1 = fopen("arq1.txt", "r");
        fscanf(arq1, "%s", entrada);
        fclose(arq1);

        arq1 = fopen("arq1.txt", "w");
        
        int num = strlen(entrada);
        for(int j=0;j<num;j++){
            if(entrada[j]=='R'){
                fputs("RR", arq1);
            }
            else if(entrada[j]=='S'){
                fputs("S+R-S-R+S", arq1);
            }
            else{
                fputc(entrada[j], arq1); 
            }
        }
        fclose(arq1);
        printf("%dª Estágio: %s\n", i+1, entrada);
    }
    arq1 = fopen("arq1.txt", "r");
    fscanf(arq1, "%s", entrada);
    printf("Fractal Final: %s\n", entrada);
    fclose(arq1);
    int num1 = strlen(entrada);
    arq1 = fopen("arq1.txt","w");
    for(int k=0;k<num1;k++){
        fputc(entrada[k], arq1); 
    }
    fputs("\n", arq1);
    fprintf(arq1, "%d", teta);
    fputs("\n", arq1);
    fprintf(arq1, "%d", 3);
    fclose(arq1);

    free(entrada);
}

int main(){
    FILE *arq1, *arq2;
    char entrada[10000], regra[100], regra2[100], axioma[100];
    int n=4, teta=90;

    printf("Escolha o fractal: \nF -> floco de neve de onda quadrada de von Koch\nX -> preenchimento de Hilbert\nR -> Meu fractal\n");
    scanf("%s", &entrada);  //seleção do fractal
    
    if(entrada[0]=='F' || entrada[0]=='X'){
        printf("Digite o axíoma: \n");
        scanf("%s", &axioma); //axioma de entrada
        printf("Digite o ângulo teta: \n");
        scanf("%d", &teta); //angulo 
    }

    if(teta==90 && entrada[0]=='F'){ //verifico se é o floco de neve de onda quadrada de von Koch
        printf("Digite a regra: \n");
        scanf("%s", &regra);

        resolveVonKoch(entrada, teta, regra);
    }
    else if(teta==90 && entrada[0]=='X'){ //verifico se é o preenchimento de espaço de Hilbert
        printf("Digite a regra 1: \n");
        scanf("%s", &regra);
        printf("Digite a regra 2: \n");
        scanf("%s", &regra2);

        resolveHilbert(entrada, teta, regra, regra2);
    }
    else if(entrada[0]=='R'){ //verifico se é o meu fractal
        //regra do meu fractal:  R->RR  // S->S+R-S-R+S
        teta=120;
        resolveMeuFractal(entrada, teta);
    }
    else{
        printf("Entrada Inválida para o fractal determinado.\n");
    }
        
    free(entrada);
    free(regra);
    free(regra2);
    free(axioma);

    return 0;
}