import java.io.Serializable;
public class Venda implements IVenda,Serializable{
    private String produto;
    private double preco;
    private int quant;
    private String promo;
    private String cliente;
    private int mes;
    private int filial;
    public Venda(String produto, double preco, int quant, String promo, String cliente, int mes, int filial){
        this.produto = produto;
        this.preco = preco;
        this.quant = quant;
        this.promo = promo;
        this.cliente = cliente;
        this.mes = mes;
        this.filial = filial;
    }
    public Venda(String linhaLida){
        String[] parts = linhaLida.split(" ");
        this.produto = parts[0];
        this.preco = Double.parseDouble(parts[1]);
        this.quant = Integer.parseInt(parts[2]);
        this.promo = parts[3];
        this.cliente = parts[4];
        this.mes = Integer.parseInt(parts[5]);
        this.filial = Integer.parseInt(parts[6]);
    }
    public String getCodProd(){
        return this.produto;
    }
    public String getCodCli(){
        return this.cliente;
    } 
    public int getQuant(){
        return this.quant;
    }
    public double getPreco(){
        return this.preco;   
    }
    public int getMes(){
        return this.mes;
    }
    public String getPromo(){
        return this.promo;
    }
    public int getFilial(){
        return this.filial;
    } 
    public double facturado(){
        return this.quant * this.preco;
    }
    @Override
    public String toString(){
        return this.produto + " " + this.preco + " " + this.quant + " " + this.promo + " " + this.cliente + " " + this.mes + " " + this.filial;
    }
    public boolean valida(ICatProds catp, ICatClientes catc){
        boolean r = true;
        if(this.preco < 0 || this.preco > 999.99) r = false;
        if(r == true && (this.quant < 0 || this.quant > 200)) r = false;
        if(r == true && (this.promo.equals("N") && this.promo.equals("P"))) r = false;
        if(r == true && (this.mes < 0 || this.mes > 12)) r = false;
        if(r == true && (this.filial < 0 || this.filial > 3)) r = false;
        ICliente c = new Cliente(this.cliente); IProduto p = new Produto(this.produto);
        if(r == true &&  (!catc.searchCli(c))) r = false;
        if(r == true && (!catp.searchProd(p))) r = false;
        return r;
    }
}   

