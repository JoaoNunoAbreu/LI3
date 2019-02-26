# LI3 2018/2019

Grupo : 
* João Nuno Abreu
* Hugo Matias
* Jorge Vieira

    NOTA:

    Validade de produtos (AB1234)
        - 2 letras maiúsculas
        - 4 dígitos entre 1000 e 9999
        - Sem repetidos (acho)

    Validade de clientes (A1234)
        - 1 letra maiúscula
        - 4 dígitos entre 1000 e 5000
        - Sem repetidos (acho)

    Validade de vendas (AB1234 123.12 123 N A1234 1 1)
        - Código de produto
        - Preço por unidade decimal entre 0.0 e 999.99
        - Número de unidades compradas entre 1 e 200
        - Compra normal ou promoção (N ou P)
        - Código do cliente
        - Mês da compra
        - Filial entre 1 e 3
        - Sem repetidos (acho)

    Objetivos:
        - Validar todas as componentes 
        - Armazenar apenas estas
        - Arranjar o melhor tamanho para o buffer do fgets()
        - Para validação das vendas fazer parsing de cada linha usando função strtok()
        - Guardar num ficheiro texto apenas as vendas válidas
        - Contar o total de dados válidos