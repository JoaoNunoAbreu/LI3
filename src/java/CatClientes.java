import java.util.Set;
import java.util.TreeSet;
import java.util.HashSet;
import java.io.Serializable;
public class CatClientes implements ICatClientes,Serializable{
    private Set<ICliente> catCli;
    public CatClientes(){
        this.catCli = new HashSet<>();
    }
    public void addCli(ICliente cliente){
        this.catCli.add(cliente);
    }
    public boolean searchCli(ICliente cliente){
        return this.catCli.contains(cliente);
    }
    public int size(){
        return this.catCli.size();
    }
    @Override
    public String toString(){
        return this.catCli.toString();
    }
}