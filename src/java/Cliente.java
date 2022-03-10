import java.util.Arrays;
import java.io.Serializable;
public class Cliente implements ICliente,Comparable<Cliente>,Serializable{
    private String codCli;
    public Cliente(String codCli){
        this.codCli = codCli;
    }
    public Cliente(Cliente c){
        this.codCli = c.getCodCli();
    }
    public String getCodCli(){
        return this.codCli;
    }
    public boolean valida(){
        boolean r = true;
        String linha = this.getCodCli();
        if(linha == null || linha.length() != 5) return false;
        if(!Character.isUpperCase(linha.charAt(0))) r = false;
        else{
            int num1 = Integer.parseInt(linha.substring(1));
            if(num1 < 1000 || num1 > 9999) r = false;
        }
        return r;
    }
    public int compareTo(Cliente c) {
        String cod = c.getCodCli();
        return this.codCli.compareTo(cod);
    }
    @Override
    public Cliente clone(){
        return new Cliente(this);
    }
    @Override
    public String toString(){
        return this.codCli;
    }
    @Override
    public int hashCode(){
        return Arrays.hashCode(new Object[]{this.codCli});
    }
    @Override
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        Cliente p = (Cliente) o;
        return this.codCli.equals(p.getCodCli());
    }
}
