import java.util.*;
import java.io.Serializable;
public class CatProds implements ICatProds,Serializable{
    private Set<IProduto> catProd;
    public CatProds(){
        this.catProd = new HashSet<>();
    }
    public void addProd(IProduto produto){
        this.catProd.add(produto);
    }
    public boolean searchProd(IProduto produto){
        return this.catProd.contains(produto);
    }
    public int size(){
        return this.catProd.size();
    }
    public Set<IProduto> getCatProd(){
        return this.catProd;
    }   
    @Override
    public String toString(){
        return this.catProd.toString();
    }
}