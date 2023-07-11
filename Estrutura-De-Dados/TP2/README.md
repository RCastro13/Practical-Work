# Instruções para compilação e execução

Para compilar e executar o programa basta abrir seu terminal e se movimentar nas pastas até chegar na pasta do TP. Após isso, deve-se utilizar o comando comando “make run” juntamente com um argumento que indica o nome do arquivo “.txt” que contém os pontos de entrada juntamente o texto “fecho”. Segue o formato do comando:
_____________________________________________________________________
make run fecho “arquivo.txt”
_____________________________________________________________________

Sendo que “arquivo.txt” deve ser substituído pelo nome do arquivo “.txt” de entrada, como por exemplo, se esse arquivo se chamar “entrada.txt”, usa-se:
_____________________________________________________________________
	make run fecho entrada.txt
_____________________________________________________________________
	 O arquivo “.txt” deve estar na mesma pasta que o arquivo Makefile e deve conter os pontos de entrada no formato determinado no enunciado do TP:
0 0
0 1
1 0
1 1

Após isso, o arquivo Makefile irá compilar os arquivos .cpp e gerará o executável “.exe” e os objetos “.o”.
A saída do programa será algo do tipo:
_____________________________________________________________________
	FECHO CONVEXO:
(0, 0)
(0, 1)
(1, 0)
(1, 1)

GRAHAM+MERGESORT: 1.200s
GRAHAM+INSERTIONSORT: 1.500s
GRAHAM+LINEAR: 1.004s
JARVIS: 0.992s	
_____________________________________________________________________
