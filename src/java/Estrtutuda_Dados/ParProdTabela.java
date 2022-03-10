public class ParProdTabela{
    private IProduto produto;
    private double[][] tabela;
    public ParProdTabela(IProduto p, double[][] tabela){
        this.produto = p;
        this.tabela = tabela;
    }
    public IProduto getProduto(){
        return this.produto;
    }
    public double[][] getTabela(){
        return this.tabela;
    }
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Produto: ").append(this.produto.toString()).append("\n");
        for (int i = 0; i < tabela.length; i++) {
            for (int j = 0; j < tabela[i].length; j++) {
                sb.append(tabela[i][j] + " ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }
}
