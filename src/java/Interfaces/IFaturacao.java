import java.util.List;
import java.util.Collection;
import java.util.AbstractMap.SimpleEntry;
public interface IFaturacao{
    public void addVenda(IVenda v);
    public boolean containsKey(IProduto produto);
    public int size();
    public int totalSize();
    public double totalFaturacao();
    public int numComprasMes(int mes);
    public List<IProduto> getSortedProds(int x);
    public List<ParProdTabela> totalFaturadoProdutos();
}
