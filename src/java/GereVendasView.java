import java.util.*;
import java.util.AbstractMap.SimpleEntry;
public class GereVendasView implements InterfGereVendasView{
    public void show(){
        System.out.println();
        System.out.println("-------------------------- MVC --------------------------");
        System.out.println();
        System.out.println("O que pretende executar? (para parar inserir número negativo)");
        System.out.println();
        System.out.println("Consultas Interactivas");
        System.out.println();
        System.out.println("Query 1 - Lista ordenada alfabeticamente com os produtos nunca comprados e o seu respectivo total");
        System.out.println("Query 2 - Mês -> nº de vendas e clientes distintos, com e sem filiais");
        System.out.println("Query 3 - Cliente -> nº compras, produtos distintos, quanto gastou, mês a mês");
        System.out.println("Query 4 - Produto -> nº compras, clientes distintos, facturado total, mês a mês");
        System.out.println("Query 5 - Cliente -> lista de código de produtos mais comprados (e quantos) por ordem decrescente");
        System.out.println("Query 6 - X's produtos mais vendidos indicando nº total de clientes distintos");
        System.out.println("Query 7 - Para cada filial, 3 maiores compradores em termos de dinheiro");
        System.out.println("Query 8 - X's clientes que compraram mais produtos diferentes (quantos) com ordem decrescente");
        System.out.println("Query 9 - Produto -> X clientes que mais o compraram, e qual o valor gasto");
        System.out.println("Query 10 - Mês a mês e filial a filial -> facturação total de cada produto");
        System.out.println();
        System.out.println("Consultas Estatísticas");
        System.out.println();
        System.out.println("11 - Dados referentes ao último ficheiro de vendas lido");
        System.out.println("12 - Números gerais respeitantes aos dados actuais já registados nas estruturas");
        System.out.println();
        System.out.println("Guardar / carregar estado");
        System.out.println();
        System.out.println("13 - Guarda estado da aplicação");
        System.out.println("14 - Carrega estado da aplicação");
        System.out.println();
        System.out.println("---------------------------------------------------------");
    }
    public void opErrada(){
        System.out.println("A opção escolhida não faz parte do intervalo válido!");
    }
    public void clienteNExiste(){
        System.out.println("O cliente não existe!");
    }
    public void produtoNExiste(){
        System.out.println("O produto não existe!");
    }
    public void printMes(){
        System.out.println("Mês:");
    }
    public void printCliente(){
        System.out.println("Cliente:");
    }
    public void printProduto(){
        System.out.println("Produto:");
    }
    public void printX(){
        System.out.println("Valor de X:");
    }
    public void pretendeInserirNome(){
        System.out.println("Pretende inserir nome do ficheiro onde vai set guardado o estado da aplicação? (s/n):");
    }
    public void printNomeFich(){
        System.out.println("Nome do ficheiro:");
    }
    public void printTempoQuery(double time){
        System.out.println("Demorou " + time + " segundos a fazer esta query");
    }
    public void printTabela(TwoIntsOneDouble[] l){
        for(int i = 0; i < l.length; i++)
            System.out.println(l[i].toString());
    }
    public void navegador(List<? extends Object> l){
        Scanner sc = new Scanner(System.in);
        int page = 0;
        int numPaginas = l.size() / 10;
        while(page >= 0){
            System.out.println("Que número de página pretende ler? (para parar inserir número negativo)");
            page = sc.nextInt();
            if(page > numPaginas) System.out.println("Número de página demasiado grande");
            else if(page >= 0){
                int tamanho = l.subList(page * 10,l.size()).size();
                for(int i = 0; i < 10 && i < tamanho ; i++)
                    System.out.println(l.get(page * 10 + i).toString());
            }
        }
    }
    public void printCE1(CE1Info c){
        System.out.println(c.toString());
    }
    public void printCE2(CE2Info c){
        System.out.println(c.toString());
    }
    public void printTamanho(List<? extends Object> l){
        System.out.println("O tamanho desta lista é " + l.size());
    }
    public void printQ2(List<SimpleEntry<Integer,Integer>> l){
        System.out.println("Vendas realizadas para filial 1: " + l.get(0).getKey() + ", número de clientes distintos: " + l.get(0).getValue());
        System.out.println("Vendas realizadas para filial 2: " + l.get(1).getKey() + ", número de clientes distintos: " + l.get(1).getValue());
        System.out.println("Vendas realizadas para filial 3: " + l.get(2).getKey() + ", número de clientes distintos: " + l.get(2).getValue());
        System.out.println("Vendas realizadas globalmente: " + l.get(3).getKey() + ", número de clientes distintos: " + l.get(3).getValue());
    }
}
