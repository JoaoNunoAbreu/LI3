import java.io.Serializable;
public class InfoFat implements Serializable{
    private double preco;
    private int quant;
    private String promo;
    private int mes;
    private int filial;
    public InfoFat(double p, int q, String promo, int mes, int filial){
        this.preco = p;
        this.quant = q;
        this.promo = promo;
        this.mes = mes;
        this.filial = filial;
    }
    public int correspondeMes(int mes){
        if(this.mes == mes) return 1;
        return 0;
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
    public int getFilial(){
        return this.filial;
    }
    public String toString(){
        return this.preco + " " + this.quant + " " + this.promo + " " + this.mes + " " + this.filial;
    }
}
