Instruções para Execução do Programa:

Requisitos para utilizar o programa:

    - Possuir o python instalado  (pip install python)
    - Possuir as bibliotecas "tkinter" e "pillow" do python instaladas: 
        No linux: sudo apt-get install python3-tk       &&      sudo apt-get install pillow
        No windows: pip install tk      &&      pip install pillow 
    - Possuir o "Ghostscript" instalado:
        No linux: sudo apt-get install ghostscript
        No windows: https://www.ghostscript.com/download/gsdnld.html   //instalação feita pelo link

    As bibliotecas e a dependência são necessárias para a geração da imagem .png do fractal. 

Primeiramente, foi feito um arquivo "Makefile" para execução prática do programa completo, bastando a execução do comando a seguir
dentro do diretório que possui o arquivo Makefile:

    make run

Após isso, será executado primeiro o programa "main.c" e depois do "fractal.py".

Caso queira executar separadamente cada programa, deve seguir os passos:

    g++ main.c -o main
    ./main

Apenas executar esses comandos já é o necessário para avaliar o programa, visto que basta conferir no arquivo arq1.txt o fractal escrito pelo programa.
Além disso, isso gerará o arquivo "main.exe" e é necessário para o python fazer o desenho com o comando:

    python fractal.py

Isso fará o desenho na tela do fractal e gerará o arquivo "fractal.eps" e "fractal.png" gerado a partir do anterior para melhor visualização do desenho.

Lembrando que podem ser executados separadamente, inclusive alterando na mão o arquivo .txt e executando o arquivo "fractal.py" para fazer seu próprio fractal

OBS.: Para melhorar a visualização dos desenhos, pode-se mudar a função "window.setworldcoordinates" para setar as coordenadas fixas do canvas de desenho. Essas
estão por "default" setadas para ver a 4ª iteração de cada fractal. Essa função possui 4 parâmetros(xi, yi, xf, yf):
xi -> coordenada X do canto inferior esquerdo da tela
yi -> coordenada Y do canto inferior esquerdo da tela
xf -> coordenada X do canto superior direito da tela
yf -> coordenada Y do canto superior direito da tela


Instruções de Utilização do programa:

Agora compilado e executado, o programa apresentará a seguinte pergunta:

Escolha o fractal: 
F -> floco de neve de onda quadrada de von Koch
X -> preenchimento de Hilbert
R -> Meu fractal

Deve-se escolher o fractal que será desenvolvido pelo programa e posteriormente informar o axíoma, o ângulo e a(s) regra(s), com exceção do meu fractal que precisa
ser apenas selecionado nessa pergunta inicial