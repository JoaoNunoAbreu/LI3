public class CE1Info{
    private String nome;
    private int numRegistosErrados;
    private int numProdutos;
    private int numProdutosDifComprados;
    private int numProdutosNComprados;
    private int numClientesNCompraram;
    private int numCompras0;
    private double faturacaoTotal;
    public CE1Info(String nome,int numRegistosErrados,int numProdutos,int numProdutosDifComprados,int numProdutosNComprados,int numClientesNCompraram,int numCompras0,double faturacaoTotal){
        this.nome = nome;
        this.numRegistosErrados = numRegistosErrados;
        this.numProdutos = numProdutos;
        this.numProdutosDifComprados = numProdutosDifComprados;
        this.numProdutosNComprados = numProdutosNComprados;
        this.numClientesNCompraram = numClientesNCompraram;
        this.numCompras0 = numCompras0;
        this.faturacaoTotal = faturacaoTotal;
    }
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Nome do último ficheiro lido: ").append(this.nome).append("\n").
        append("Número de registos errados: ").append(this.numRegistosErrados).append("\n").
        append("Número de produtos: ").append(this.numProdutos).append("\n").
        append("Número de produtos diferentes comprados: ").append(this.numProdutosDifComprados).append("\n").
        append("Número de produtos não comprados: ").append(this.numProdutosNComprados).append("\n").
        append("Número de clientes que não compraram: ").append(this.numClientesNCompraram).append("\n").
        append("Número de compras com preço 0: ").append(this.numCompras0).append("\n").
        append("Facturação total: ").append(this.faturacaoTotal).append("\n");
        return sb.toString();
    }
}
