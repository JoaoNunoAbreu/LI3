public class ClientFatQuant implements Comparable<ClientFatQuant>{
    private ICliente cliente;
    private double faturado;
    private int quant;
    public ClientFatQuant(ICliente c, double f, int quant){
        this.cliente = c;
        this.faturado = f;
        this.quant = quant;
    }
    public ICliente getCliente(){
        return this.cliente;
    }
    public double getFaturado(){
        return this.faturado;
    }
    public int getQuantidade(){
        return this.quant;
    }
    public void setCliente(ICliente cliente){
        this.cliente = cliente;
    }
    public void setFaturado(double faturado){
        this.faturado = faturado;
    }
    public void setQuantidade(int q){
        this.quant = q;
    }
    public int compareTo(ClientFatQuant p){
        return this.cliente.getCodCli().compareTo(p.getCliente().getCodCli());
    }
    public String toString(){
        return this.cliente.toString() + " " + this.faturado;
    }
    public void soma(double f){
        this.faturado += f;
    }
}
