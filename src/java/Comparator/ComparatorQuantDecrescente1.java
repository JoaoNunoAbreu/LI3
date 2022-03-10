import java.util.Comparator;
public class ComparatorQuantDecrescente1 implements Comparator<ParProdQuant>{
    public int compare(ParProdQuant p1, ParProdQuant p2){
        return p1.getQuantidade() > p2.getQuantidade() ? -1 :(p1.getQuantidade() < p2.getQuantidade() ? 1 : (p1.getProduto().getCodProd().compareTo(p2.getProduto().getCodProd())));
    }
}
