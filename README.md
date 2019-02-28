# LI3 2018/2019

#### Grupo: 
* João Nuno Abreu
* Hugo Matias
* Jorge Vieira

#### Validade de produtos (AB1234)
* ~~2 letras maiúsculas~~
* ~~4 dígitos entre 1000 e 9999~~

#### Validade de clientes (A1234)
* ~~1 letra maiúscula~~
* ~~4 dígitos entre 1000 e 5000~~

#### Validade de vendas (AB1234 123.12 123 N A1234 1 1)
* Código de produto (tem de estar na lista dos produtos válidos) **cerca de 8min para executar :/**
* ~~Preço por unidade decimal entre 0.0 e 999.99~~
* ~~Número de unidades compradas entre 1 e 200~~
* ~~Compra normal ou promoção (N ou P)~~
* Código do cliente (tem de estar na lista dos clientes válidos) **cerca de 50s para executar :/**
* ~~Mês da compra~~
* ~~Filial entre 1 e 3~~

### Fase 1: Ler e testar valores (pág.4 do BRP)
* Linha mais longa (Venda)
* Produtos envolvidos
* Clientes envolvidos
* Vendas efectivas (válidas)
* Ultimo Cliente
* Numero de Vendas Registadas para este cliente
* Numero de Vendas na Filial 1
* Numero de Vendas na Filial 2
* Numero de Clientes com codigo começado por A, B, …
* Facturação Total registada

## O que falta fazer:
* Arranjar o melhor tamanho para o buffer do fgets()
* ~~Confirmar a validação dos clientes/produtos~~
* Melhorar os tempos de execução da validação das vendas
* ~~Guardar num ficheiro texto apenas as vendas válidas~~
* ~~Colocar linhas válidas de vendas numa struct~~