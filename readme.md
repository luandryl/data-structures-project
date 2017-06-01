# Data Stuctures Final Project
***

## Importante

Compilador -> gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.4)


## Estrutura do projeto

``` zsh
.
|-libs/ # libs para teste local
|2D_interface.c # interface para lidar com euclidianas 2d
|3D_interface.c # interface para lidar com euclidianas 3d
|explicit_interface.c # interface para lidar com distancias explicitas
|init.c # start da aplicação
```

## Uso

``` zsh
$ git clone git@github.com:luandryl/data-structures-project.git
$ cd data-structures-project/ 
$ gcc init.c -o i
$ ./i [caminho para tsplib] [formato de leitura]
```

## Informações Gerais

Após compilar e executar ```./i [caminho para tsplib] [formato de leitura]``` a aplicação começa a executar, tudo inicia no arquivo ```init.c```, responsável por: 
* Abrir o arquivo (tsplib)
* Encontrar a interface correta para alocar os dados de acordo com as entradas possíveis(EUC_2D, EUC_3D, Explict)
* Fechar o arquivo (tsplib)

As interfaces são responsáveis por: 
* deixar os dados lidos do arquivo disponíveis em formato de uma fila na memoria heap;
* fornecer um meio de visualizar esta fila; 

# TODO
***
* 3D_interface.c
* explicit_interface.c
* definir um método de otimização pra encontrar o menor caminho;