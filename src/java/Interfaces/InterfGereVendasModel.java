import java.util.List;
import java.io.FileNotFoundException;
import java.io.IOException;
public interface InterfGereVendasModel{
    public int getNumLinhasVendasTotal();
    public String getNomeFichVendas();
    public int getNumComprasPreco0();
    public void createData();
    public ICatProds getCatProds();
    public ICatClientes getCatClientes();
    public IFaturacao getFaturacao();
    public IFilial[] getFilial();
    /*public void guardaEstado(String fich) throws FileNotFoundException,IOException;
    public void carregaCatProd(String fich) throws FileNotFoundException,IOException,ClassNotFoundException;
    public void carregaCatCli(String fich) throws FileNotFoundException,IOException,ClassNotFoundException;
    public void carregaFaturacao(String fich) throws FileNotFoundException,IOException,ClassNotFoundException;
    public void carregaFiliais(String fich) throws FileNotFoundException,IOException,ClassNotFoundException;*/
}