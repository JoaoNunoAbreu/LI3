import java.io.Serializable;
public class InfoFil implements Comparable<InfoFil>,Serializable{
    private IProduto produto;
    private double preco;
    private int quant;
    private String promo;
    private int mes;
    public InfoFil(IProduto p,double preco, int q, String promo, int mes){
        this.produto = p;
        this.preco = preco;
        this.quant = q;
        this.promo = promo;
        this.mes = mes;
    }
    public int correspondeMes(int mes){
        if(this.mes == mes) return 1;
        return 0;
    }
    public double getFaturado(){
        return this.preco * this.quant;
    }
    public IProduto getProduto(){
        return this.produto;
    }
    public double getPreco(){
        return this.preco;
    }
    public int getQuant(){
        return this.quant;
    }
    public String getPromo(){
        return this.promo;
    }
    public int getMes(){
        return this.mes;
    }
    public int compareTo(InfoFil i){
        return i.getProduto().getCodProd().compareTo(this.produto.getCodProd());
    }
    public String toString(){
        return this.produto.toString() + " " + this.preco + " " + this.quant + " " + this.promo + " " + this.mes;
    }
    public double getFacturado(){
        return quant*preco;
    }
    public boolean valMesAndProd(int mes,String codProd){
        if(this.getMes() == mes && this.getProduto().getCodProd().equals(codProd)) return true;
        return false;
    }
}
