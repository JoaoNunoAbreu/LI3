public class ParClientQuant implements Comparable<ParClientQuant>{
    private ICliente cliente;
    private int quantidade;
    public ParClientQuant(ICliente c, int q){
        this.cliente = c;
        this.quantidade = q;
    }
    public ICliente getCliente(){
        return this.cliente;
    }
    public int getQuantidade(){
        return this.quantidade;
    }
    public void setCliente(ICliente cliente){
        this.cliente = cliente;
    }
    public void setQuantidade(int quantidade){
        this.quantidade = quantidade;
    }
    public int compareTo(ParClientQuant p){
        return this.quantidade > p.getQuantidade() ? -1 :(this.quantidade < p.getQuantidade() ? 1 : 0);
    }
    public String toString(){
        return this.cliente.toString() + " " + this.quantidade;
    }
    public void soma(int quantidade){
        this.quantidade += quantidade;
    }
}
