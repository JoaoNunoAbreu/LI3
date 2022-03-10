import java.util.Arrays;
import java.io.Serializable;
public class Produto implements IProduto,Comparable<Produto>,Serializable{
    private String codProd;
    public Produto(String codProd){
        this.codProd = codProd;
    }
    public Produto(Produto p){
        this.codProd = p.getCodProd();
    }
    public String getCodProd(){
        return this.codProd;
    }
    public boolean valida(){
        boolean r = true;
        String linha = this.getCodProd();
        if(linha == null || linha.length() != 6) return false;
        if(!Character.isUpperCase(linha.charAt(0)) || !Character.isUpperCase(linha.charAt(1))) r = false;
        else{
            int num1 = Integer.parseInt(linha.substring(2));
            if(num1 < 1000 || num1 > 9999) r = false;
        }
        return r;
    }
    public int compareTo(Produto p) {
        String cod = p.getCodProd();
        return this.codProd.compareTo(cod);
    }
    @Override
    public String toString(){
        return this.codProd;
    }
    @Override
    public int hashCode(){
        return Arrays.hashCode(new Object[]{this.codProd});
    }
    @Override
    public Produto clone(){
        return new Produto(this);
    }
    @Override
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        Produto p = (Produto) o;
        return this.codProd.equals(p.getCodProd());
    }
}
