import java.util.*;
import java.util.stream.Collectors;
import java.util.AbstractMap.SimpleEntry;
import java.io.Serializable;
public class Faturacao implements IFaturacao,Serializable{
    private Map<IProduto,List<InfoFat>> faturacao;
    public Faturacao(){
        this.faturacao = new HashMap<>();
    }
    public void addVenda(IVenda v){
        IProduto p = new Produto(v.getCodProd());
        InfoFat infofat = new InfoFat(v.getPreco(),v.getQuant(),v.getPromo(),v.getMes(),v.getFilial());
        if(this.faturacao.get(p) == null){
            List<InfoFat> l = new ArrayList<>();
            l.add(infofat);
            this.faturacao.put(p,l);
        }
        else{
            this.faturacao.get(p).add(infofat);
        }
    }
    public boolean containsKey(IProduto produto){
        return this.faturacao.containsKey(produto);
    }
    public int size(){
        return this.faturacao.size();
    }
    public int totalSize(){
        int sum = 0;
        for(List<InfoFat> info : this.faturacao.values())
            sum += info.size();
        return sum;
    }
    public double totalFaturacao(){
        double fat = 0;
        for(List<InfoFat> info : this.faturacao.values())
            for(InfoFat i : info)
                fat += i.getQuant() * i.getPreco();
        return fat;
    }
    public String toString(){
        return this.faturacao.toString();
    }
    /**
     * Função usada na ce2
     */
    public int numComprasMes(int mes){
        int sum = 0;
        for(IProduto p : this.faturacao.keySet()){
            List<InfoFat> list = this.faturacao.get(p);
            for(InfoFat info : list){
                sum += info.correspondeMes(mes);
            }
        }
        return sum;
    }
    /**
     * Função usada na query 6
     */
    public List<IProduto> getSortedProds(int x){
        int quant;
        Map<IProduto,Integer> res = new HashMap<>();
        for(IProduto p : this.faturacao.keySet()){
            quant = this.getQuantidadeTotalProduto(p);
            res.put(p,quant);
        }
        List<IProduto> novo = new ArrayList<>(this.sortByValue(res).keySet()).subList(0,x);
        return novo;
    }
    /**
     * Função usada na query6 (auxiliar)
     */
    public int getQuantidadeTotalProduto(IProduto p){
        int quant = 0;
        List<InfoFat> l = this.faturacao.get(p);
        for(InfoFat info : l)
            quant += info.getQuant();
        return quant;
    }
    /**
     * Função usada na query6 (auxiliar)
     */
    private Map<IProduto,Integer> sortByValue(Map<IProduto,Integer> l) {
        return l.entrySet()
                .stream()
                .sorted((Map.Entry.<IProduto,Integer>comparingByValue().reversed()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));
    }
    /**
     * Função usada na query10
     */
    public List<ParProdTabela> totalFaturadoProdutos(){
        List<TwoIntsOneDouble> l;
        List<ParProdTabela> res = new ArrayList<>();
        for(IProduto p : this.faturacao.keySet()){
            l = this.totalFaturadoProduto(p);
            double[][] tab = new double[12][3];
            for(TwoIntsOneDouble val : l){
                tab[val.getX()-1][val.getY()-1] += val.getZ();
            }
            res.add(new ParProdTabela(p,tab));
        }
        return res;
    }
    /**
     * Função usada na query10 (auxiliar)
     */
    private List<TwoIntsOneDouble> totalFaturadoProduto(IProduto p){
        List<InfoFat> data = this.faturacao.get(p);
        List<TwoIntsOneDouble> res = new ArrayList<>();
        for(InfoFat info : data){
            res.add(new TwoIntsOneDouble(info.getMes(),info.getFilial(), info.getQuant() * info.getPreco()));
        }
        return res;
    }
}
