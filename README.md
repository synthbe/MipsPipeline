# MipsPipeline
Repositório reference ao trabalho da primeira unidade de Organização de Computadores (DIM0129)

## Setup

Exporte a variável de ambiente `SYSTEMC_PATH` apontando para onde está instalado o systemc

Exemplos:
```sh
export SYSTEMC_PATH="$HOME/systemc/install"
export SYSTEMC_PATH="$HOME/systemc-install"
```

## Rodando
O processador se encontra em `test/test_cpu.cpp`. Para rodar o teste, execute `make run-test_cpu`