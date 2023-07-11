# Instruções para compilação e execução
Esta seção deve ser colocada em um apêndice ao fim do documento e em uma página exclusiva (não divide página com outras seções).

Para compilar e executar o programa basta abrir seu terminal e se movimentar nas pastas até chegar na pasta do TP. Após isso, basta digitar o comando “make run” que o arquivo Makefile irá compilar os arquivos .cpp e gerará o executável.

As entradas deverão ser adicionadas ao arquivo “entrada.txt” no seguinte formato:
_____________________________________________________________________
LER X EXPRESSAO
Y
RESOLVER
--------------------------------------------------------------------------------------------------------

	Sendo X=”INFIXA” ou “POSFIXA” referente ao tipo da expressão de entrada, EXPRESSAO = expressão de entrada e Y= “INFIXA ou “POSFIXA” referentes ao tipo oposto à expressão de entrada.

	Exemplo:
_____________________________________________________________________
LER INFIXA ( ( ( 20.555121 ) + ( 4.765412 ) ) * ( 8.987123 ) )
POSFIXA
RESOLVE
--------------------------------------------------------------------------------------------------------
