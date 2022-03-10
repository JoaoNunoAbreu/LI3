import java.util.List;
import java.util.AbstractMap.SimpleEntry;
public interface InterfGereVendasController{
    public void setModel(InterfGereVendasModel model);
    public void setView(InterfGereVendasView view);
    public void startController();
    public CE1Info ce1();
    public CE2Info ce2();
    public List<IProduto> query1();
    public List<SimpleEntry<Integer,Integer>> query2(int mes);
    public TwoIntsOneDouble[] query3(ICliente c);
    public TwoIntsOneDouble[] query4(IProduto p);
    public List<ParProdQuant> query5(ICliente c);
    public List<ParProdQuant> query6(int x);
    public List<List<ICliente>> query7();
    public List<ParClientQuant> query8(int x);
    public List<ClientFatQuant> query9(IProduto p, int x);
    public List<ParProdTabela> query10();
}
