public class ParProdQuant implements Comparable<ParProdQuant>{
    private IProduto produto;
    private int quantidade;
    public ParProdQuant(IProduto p, int q){
        this.produto = p;
        this.quantidade = q;
    }
    public IProduto getProduto(){
        return this.produto;
    }
    public int getQuantidade(){
        return this.quantidade;
    }
    public void setProduto(IProduto produto){
        this.produto = produto;
    }
    public void setQuantidade(int quantidade){
        this.quantidade = quantidade;
    }
    public int compareTo(ParProdQuant p){
        return this.produto.getCodProd().compareTo(p.getProduto().getCodProd());
    }
    public String toString(){
        return this.produto.toString() + " " + this.quantidade;
    }
}
