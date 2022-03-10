import java.util.AbstractMap.SimpleEntry;
import java.util.List;
import java.util.Set;
public interface IFilial{
    public void addVenda(IVenda v);
    public Set<ICliente> getClients();
    public int size();
    public boolean containsKey(ICliente c);
    public double totalFacturadoNumMes(int mes);
    public int numClientsDifMes(int mes);
    public TwoIntsOneDouble prodInfoMonth(String codProd,int mes);
    public SimpleEntry<Integer,Integer> contaVendasClientes(int mes);
    public TwoIntsOneDouble contaComprasProdutosGasto(ICliente c, int mes);
    public List<ParProdQuant> getQuantComprada(ICliente c);
    public int contaClientesQueCompraramP(IProduto p);
    public List<ICliente> melhoresCompradores();
    public List<ParClientQuant> clientesProdutosDistintos();
    public List<ClientFatQuant> getClientesFaturadoNoProd(IProduto p);
}
