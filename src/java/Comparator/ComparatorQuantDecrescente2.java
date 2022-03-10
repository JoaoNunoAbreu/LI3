import java.util.Comparator;
public class ComparatorQuantDecrescente2 implements Comparator<ClientFatQuant>{
    public int compare(ClientFatQuant p1, ClientFatQuant p2){
        return p1.getQuantidade() > p2.getQuantidade() ? -1 :(p1.getQuantidade() < p2.getQuantidade() ? 1 : (p1.getCliente().getCodCli().compareTo(p2.getCliente().getCodCli())));
    }
}
