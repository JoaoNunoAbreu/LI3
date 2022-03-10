import java.util.Set;
public interface ICatProds{
    public void addProd(IProduto produto);
    public boolean searchProd(IProduto produto);
    public int size();
    public Set<IProduto> getCatProd();
}