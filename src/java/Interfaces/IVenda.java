import java.util.List;
public interface IVenda{
    public String getCodProd();
    public String getCodCli();
    public int getQuant();
    public double getPreco();
    public int getMes();
    public String getPromo();
    public int getFilial();
    public double facturado();
    public String toString();
    public boolean valida(ICatProds catp, ICatClientes catc);
}