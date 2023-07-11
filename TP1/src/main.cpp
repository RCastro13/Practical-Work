#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include "pilha.h"

using namespace std;

// Verifica se o caractere é um operador
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// função auxiliar para identificação de precedência dos operadores
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

// Retorna o resultado da operação
double performOperation(char op, double operand1, double operand2) {
    switch(op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if(operand2 == 0){
                throw "Divisão por 0";
            }
            return operand1 / operand2;
        default:
            return 0;
    }
}

bool avaliaExpressao(string expressao, string tipo){
    bool val = true;
    int abre=0, fecha=0;
    if(tipo == "INFIXA"){
        for(int i=0;i<expressao.length();i++){
            if(expressao[i] == '('){
                abre++;
            }
            else if(expressao[i]==')'){
                fecha++;
            }
        }
    }
    else{
        throw "tipo de expressão incorreto.";
    }

    if(abre!=fecha){
        val = false;
    }

    return val;
}

// Função que retorna o resultado da expressão infixa
double evaluateInfixa(string expr){
    
    PilhaDouble operands;
    PilhaChar operators;

    for (int i = 0; i < expr.length(); i++){
        if(expr[i] == ' '){
            continue; // Ignora espaços em branco
        } 
        else if(isdigit(expr[i]) || (i == 0 && expr[i] == '-')){
            // Encontra um número
            int j = i;
            while (isdigit(expr[j]) || expr[j] == '.'){
                j++;
            }
            double operand = stod(expr.substr(i, j-i));
            operands.EmpilhaD(operand);
            i = j-1; // Pula para o próximo caractere após o número
        } 
        else if(expr[i] == '('){
            operators.EmpilhaC(expr[i]);
        } 
        else if(expr[i] == ')'){
            // Resolve as operações dentro do parêntese
            while(operators.getTopoC() != '('){
                double op2 = operands.getTopoD();
                operands.DesempilhaD();
                double op1 = operands.getTopoD();
                operands.DesempilhaD();
                char op = operators.getTopoC();
                operators.DesempilhaC();
                double result;
                result = performOperation(op, op1, op2);
                operands.EmpilhaD(result);
            }
            operators.DesempilhaC();
        } 
        else{
            // Encontra um operador
            while(operators.getTamanho() != 0 && operators.getTopoC() != '(' && 
            ((expr[i] == '*' || expr[i] == '/') || (operators.getTopoC() == '+' || operators.getTopoC() == '-'))){
                double op2 = operands.getTopoD();
                operands.DesempilhaD();
                double op1 = operands.getTopoD();
                operands.DesempilhaD();
                char op = operators.getTopoC();
                operators.DesempilhaC();
                double result = performOperation(op, op1, op2);
                operands.EmpilhaD(result);
            }
            operators.EmpilhaC(expr[i]);
        }
    }

    // Resolve as operações restantes
    while(operators.getTamanho() != 0){
        double op2 = operands.getTopoD();
        operands.DesempilhaD();
        double op1 = operands.getTopoD();
        operands.DesempilhaD();
        char op = operators.getTopoC();
        operators.DesempilhaC();
        double result = performOperation(op, op1, op2);
        operands.EmpilhaD(result);
    }

    double resultado = operands.getTopoD();
    operands.LimpaD();
    operators.LimpaC();

    return resultado; // Retorna o resultado final
}

// Converte uma expressão infixa em posfixa
string infixaToPosfixa(string infixa) {
    
    PilhaChar s;
    string posfixa;

    for(int i = 0; i < infixa.length(); i++){
        if(isdigit(infixa[i]) || infixa[i] == '.') {
            while (i < infixa.length() && (isdigit(infixa[i]) || infixa[i] == '.')) {
                posfixa += infixa[i];
                i++;
            }
            posfixa += ' ';
            i--;
        } 
        else if(infixa[i] == '('){
            s.EmpilhaC(infixa[i]);
        } 
        else if(infixa[i] == ')'){
            while(s.getTamanho() != 0 && s.getTopoC() != '('){
                posfixa += s.getTopoC();
                s.DesempilhaC();
                posfixa += ' ';
            }
            s.DesempilhaC();
        } 
        else if(precedence(infixa[i]) > 0){
            while(s.getTamanho() != 0 && precedence(s.getTopoC()) >= precedence(infixa[i])){
                posfixa += s.getTopoC();
                s.DesempilhaC();
                posfixa += ' ';
            }
            s.EmpilhaC(infixa[i]);
        }
    }

    while(s.getTamanho() != 0){
        posfixa += s.getTopoC();
        s.DesempilhaC();
        posfixa += ' ';
    }

    s.LimpaC();

    return posfixa;
}

//Calcula o resultado de uma expressão posfix
double evaluatePostfix(string postfix){

    PilhaDouble s;
    double conv;
    string termo="";

    for(int i = 0; i < postfix.length(); i++){
        if(postfix[i+1] != ' ' && (isdigit(postfix[i]) || postfix[i]=='.')){
            termo = termo + postfix[i];
        }
        else if(isdigit(postfix[i]) && postfix[i+1] == ' '){
            termo = termo + postfix[i];
            conv = stod(termo);
            s.EmpilhaD(conv);
            termo="";
        }
        else if(postfix[i]=='+' || postfix[i]=='-' || postfix[i]=='*' || postfix[i]=='/'){
            double num1 = s.DesempilhaD();
            double num2 = s.DesempilhaD();
            double resp = performOperation(postfix[i], num2, num1);
            s.EmpilhaD(resp);
        }
    }
    double resultado = s.getTopoD();
    s.LimpaD();
    return resultado;
}

// Converte uma expressão posfix em infixa
string posfixaToInfixa(string postfix){

    Pilha s;

    for(int i = 0; i < postfix.length(); i++){
        if (isdigit(postfix[i]) || postfix[i] == '.'){
            string operand;
            while(i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')){
                operand += postfix[i];
                i++;
            }
            s.Empilha(operand);
            i--;
        } 
        else if(isOperator(postfix[i])){
            string operand2 = s.getTopo();
            s.Desempilha();
            string operand1 = s.getTopo();
            s.Desempilha();
            string expression = "( " + operand1 + " ) " + postfix[i] + " ( " + operand2 + " )";
            s.Empilha(expression);
        }
    }

    string resultado = s.getTopo();
    s.Limpa();

    return resultado;
}

//função que realiza a leitura da linha de entrada e retona a string com a expressão infixa
string leInfixa(string expr, int tam, string tipo){

    string infixa = "";
    infixa = expr.substr(11, tam-11);
    bool ok = avaliaExpressao(infixa, tipo);
    if(ok == false){
        throw "EXP inválida";
    }
    return infixa;
}

//função que realiza a leitura da linha de entrada e retona a string com a expressão posfixa
string lePosfixa(string expr, int tam, string tipo){

    string posfixa = "";
    posfixa = expr.substr(12, tam-12);
    return posfixa;
}

int main() {
    ifstream fin;
    string infixa, posfixa, aux, exp, text;
    int entrada = 0;
    fin.open("entrada.txt");
    
        while(getline(fin, text)){
            
            istringstream iss(text);
            iss>>aux;

            if(aux == "LER"){             //primeira linha da entrada
                iss>>exp;
                if(exp == "INFIXA"){
                    infixa = leInfixa(text, entrada, exp);
                    cout <<"infixa: " << infixa << endl;
                }
                else if(exp == "POSFIXA"){
                    posfixa = lePosfixa(text, entrada, exp);
                    cout <<"posfixa: " << posfixa << endl;
                }
                else{
                    throw "nome da expressão incorreto";
                }
            }
            else if(aux == "INFIXA"){             //segunda linha da entrada
                string expres = "";
                expres = posfixaToInfixa(posfixa);
                cout << "infixa: " << expres << endl;
                
            }
            else if(aux == "POSFIXA"){             //segunda linha da entrada
                string expres = "";
                expres = infixaToPosfixa(infixa);
                cout <<"posfixa: "<< expres << endl;
            }
            else if(aux == "RESOLVE"){             //terceira linha da entrada
                //resolve infixa
                if(exp == "INFIXA"){
                    double resp = evaluateInfixa(infixa);
                    cout << "resp: " << resp << endl;

                }
                //resolve posfixa
                else if(exp == "POSFIXA"){
                    double resp = evaluatePostfix(posfixa); 
                    cout << "resp: " << resp << endl;           
                }
            }
            else{
                throw "nome da expressão incorreto";
            }
        }
    
    fin.close();

    return 0;
}
