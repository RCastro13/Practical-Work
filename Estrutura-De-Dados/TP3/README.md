# Instruções para compilação e execução

Para compilar e executar o programa basta abrir seu terminal e se movimentar nas pastas até chegar na pasta do TP. Após isso, deve-se utilizar o comando comando “make run” juntamente com os argumentos que indicam o nome dos arquivos de entrada e saída, assim como a flag “c” ou “d” que indica a operação a ser realizada pelo programa, sendo ‘c’ o comando para compactação e ‘d’ o comando para descompactação. Segue o formato dos comandos:
_____________________________________________________________________
make run arg1=entrada.txt arg2=saida.bin arg3=c

make run arg1=entrada.bin arg2=saida.txt arg3=d
_____________________________________________________________________

	Por padrão, na compactação o arquivo é entrada é um “.txt” e o de saída um “.bin”. Quanto à descompactação, a entrada é um “.bin” e a saída um “.txt”, mas qualquer formato escrito no comando, desde que compatível, funcionará.
Além disso, os arquivos “.txt” e “.bin” referentes a entrada devem estar na mesma pasta que o arquivo Makefile, o arquivo de saída não precisa existir, mas caso exista, também deve estar nessa mesma pasta. No diretório enviado os arquivos “entrada.txt”, “compactado.bin” e “descompactado.txt” foram deixados como referência e não necessariamente precisam ser utilizados.

Após a compilação e execução, a saída do programa no terminal, para além do arquivo compactado/descompactado será algo do tipo:
_____________________________________________________________________
O programa irá compactar o arquivo entrada.txt com a saída no arquivo compactado.bin
Arquivo compactado compactado.bin foi criado com sucesso.

O programa irá descompactar o arquivo compactado.bin com a saída no arquivo descompactado.txt
Arquivo descompactado: descompactado.txt foi descompactado com sucesso
_____________________________________________________________________
