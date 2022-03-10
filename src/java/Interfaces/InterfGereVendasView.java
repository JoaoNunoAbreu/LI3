import java.util.List;
import java.util.AbstractMap.SimpleEntry;
public interface InterfGereVendasView{
    public void show();
    public void opErrada();
    public void clienteNExiste();
    public void produtoNExiste();
    public void printMes();
    public void printCliente();
    public void printProduto();
    public void printX();
    public void printNomeFich();
    public void pretendeInserirNome();
    public void printTempoQuery(double time);
    public void printTabela(TwoIntsOneDouble[] l);
    public void navegador(List<? extends Object> l);
    public void printCE1(CE1Info c);
    public void printCE2(CE2Info c);
    public void printTamanho(List<? extends Object> l);
    public void printQ2(List<SimpleEntry<Integer,Integer>> l);
}
