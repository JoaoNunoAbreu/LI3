import java.util.*;
import java.util.AbstractMap.SimpleEntry;
import java.util.stream.Collectors;
import java.io.Serializable;
public class Filial implements IFilial,Serializable{    
    private Map<ICliente,List<InfoFil>> filial;
    public Filial(){
        this.filial = new HashMap<>();
    }
    public void addVenda(IVenda v){
        ICliente c = new Cliente(v.getCodCli());
        IProduto p = new Produto(v.getCodProd());
        InfoFil infofil = new InfoFil(p,v.getPreco(),v.getQuant(),v.getPromo(),v.getMes());
        if(this.filial.get(c) == null){
            List<InfoFil> l = new ArrayList<>();
            l.add(infofil);
            this.filial.put(c,l);
        }
        else{
            this.filial.get(c).add(infofil);
        }
    }
    public int size(){
        return this.filial.values().size();
    }
    public boolean containsKey(ICliente c){
        return this.filial.containsKey(c);
    }
    public Set<ICliente> getClients(){
        return this.filial.keySet();
    }
    /**
     * Função usada na ce2 (1)
     */
    public double totalFacturadoNumMes(int mes){
        double sum = 0;
        for(ICliente c : this.filial.keySet()){
            List<InfoFil> list = this.filial.get(c);
            for(InfoFil info : list){
                if(info.getMes() == mes){
                    sum += info.getFaturado();
                }
            }
        }
        return sum;
    }
    /**
     * Função usada na ce2 (2)
     */
    public int numClientsDifMes(int mes){
        int sum = 0;
        boolean found;
        for(ICliente c : this.filial.keySet()){
            List<InfoFil> list = this.filial.get(c);
            found = false;
            Iterator<InfoFil> it = list.iterator();
            while(it.hasNext() && found == false){
                InfoFil info = it.next();
                if(info.getMes() == mes) found = true;
            }
            if(found) sum++;
        }
        return sum;
    }
    /**
     * Função usada na query2
     */
    public SimpleEntry<Integer,Integer> contaVendasClientes(int mes){
        int nvendas = 0; int nclientes = 0;
        int nvendas_init; // Para ver se houve alteração nesse valor e assim podemos contar +1 cliente
        for(List<InfoFil> info : this.filial.values()){
            nvendas_init = nvendas;
            for(InfoFil i: info){
                nvendas += i.correspondeMes(mes);
            }
            if(nvendas_init != nvendas) nclientes++;
        }
        return new SimpleEntry(nvendas,nclientes);
    }
    /**
     * Função usada na query3
     */
    public TwoIntsOneDouble contaComprasProdutosGasto(ICliente c, int mes){
        int compras = 0; int produtos = 0; double gasto = 0;
        List<InfoFil> l = this.filial.get(c);
        for(InfoFil i : l) 
            compras += i.correspondeMes(mes);
        produtos = this.getProdutosCompradosGasto(c,mes).getKey().size();
        gasto = this.getProdutosCompradosGasto(c,mes).getValue();
        return new TwoIntsOneDouble(compras,produtos,gasto);
    }
    /**
     * Função usada na query3 (auxiliar)
     */
    private SimpleEntry<Set<IProduto>,Double> getProdutosCompradosGasto(ICliente c, int mes){
        Set<IProduto> res = new TreeSet<>();
        List<InfoFil> l = this.filial.get(c);
        double gasto = 0;
        for(InfoFil info : l)
            if(info.getMes() == mes){
                res.add(info.getProduto());
                gasto += info.getQuant() * info.getPreco();
            }
        return new SimpleEntry(res,gasto);
    }
    /**
     * Função usada na query4(auxiliar)
     */
    public List<InfoFil> isMesAndProd(List<InfoFil> info,int mes,String codProd){
        return info.stream().filter(v -> v.valMesAndProd(mes,codProd) == true).collect(Collectors.toList());
    }
    /**
     * Função usada na query4(auxiliar)
     */
    public int totalClientes(int mes,String codProd) {
        return this.filial.entrySet().stream().filter(v -> (isMesAndProd(v.getValue(),mes,codProd)).size() > 0).collect(Collectors.toSet()).size();
    }
    /**
     * Função usada na query4(auxiliar)
     */
    public double totalFactMes(String codProd,int mes){
        Iterator it = this.filial.values().iterator();
         double res = 0;
         while(it.hasNext()){
         List<InfoFil> list = (List<InfoFil>) it.next();
         list = isMesAndProd(list,mes,codProd);
         for(InfoFil info:list){
             res += info.getFacturado();
            }
        }
        return res;
    }
    /**
     * Função usada na query4
     */
    public TwoIntsOneDouble prodInfoMonth(String codProd,int mes){
        TwoIntsOneDouble res = new TwoIntsOneDouble(totalVendMes(codProd,mes),totalClientes(mes,codProd),totalFactMes(codProd,mes));
        return res;
    }
    /**
     * Função usada na query4(auxiliar)
     */
    public int totalVendMes(String codProd,int mes){
        Iterator it = this.filial.values().iterator();
        int res = 0;
        while(it.hasNext()){
            List<InfoFil> list = (List<InfoFil>) it.next();
            list = isMesAndProd(list,mes,codProd);
            for(InfoFil info:list){
                res += info.getQuant();
            }
        }
        return res;
    }
    /**
     * Função usada na query5
     */
    public List<ParProdQuant> getQuantComprada(ICliente c){
        List<ParProdQuant> res = new ArrayList<>();
        List<InfoFil> l = this.filial.get(c);
        if(l != null){
            for(InfoFil info : l){
                ParProdQuant pair = new ParProdQuant(info.getProduto(), info.getQuant());
                if(containsProdutoPar(res,info.getProduto()))
                    this.somaPairs(res,pair);
                    else res.add(pair);
                }
            }
        return res;
    }
    /**
     * Função usada na query5 (auxiliar)
     */
    private boolean containsProdutoPar(List<ParProdQuant> l, IProduto p){
        boolean r = false;
        Iterator<ParProdQuant> it = l.iterator();
        while(it.hasNext() && r == false){
            ParProdQuant pair = it.next();
            if(pair.getProduto().equals(p)) r = true;
        }
        return r;
    }
    /**
     * Função usada na query5 (auxiliar)
     */
    private void somaPairs(List<ParProdQuant> l, ParProdQuant pair_arg){
        Iterator<ParProdQuant> it = l.iterator();
        boolean chegou = false;
        while(it.hasNext() && chegou == false){
            ParProdQuant pair = it.next();
            if(pair.getProduto().equals(pair.getProduto())){
                pair.setQuantidade(pair_arg.getQuantidade() + pair.getQuantidade());
                chegou = true;
            }
        }
    }
    /**
     * Função usada na query6
     */
    public int contaClientesQueCompraramP(IProduto p){
        int num = 0;
        for(ICliente c : this.filial.keySet())
            if(containsProd(c,p)) num++;
        return num;
    }
    /**
     * Função usado na query6 (auxiliar)
     */
    private boolean containsProd(ICliente c, IProduto p){
        List<InfoFil> res = this.filial.get(c);
        Iterator<InfoFil> it = res.iterator();
        boolean found = false;
        while(it.hasNext() && found == false){
            InfoFil info = it.next();
            if(info.getProduto().equals(p)) found = true;
        }
        return found;
    }
    /**
     * Função usada na query7
     */
    public List<ICliente> melhoresCompradores(){
        Map<ICliente,Double> res = new HashMap<>();
        double faturado = 0;
        for(ICliente c : this.filial.keySet()){
            faturado = this.getFacturado(c);
            res.put(c,faturado);
        }
        List<ICliente> novo = new ArrayList<>(this.sortByValue(res).keySet());
        return novo.subList(0,3);
    }
    /**
     * Função usada na query7 (auxiliar)
     */
    private double getFacturado(ICliente c){
        List<InfoFil> l = this.filial.get(c);
        double sum = 0;
        for(InfoFil info : l){
            sum += info.getQuant() * info.getPreco();
        }
        return sum;
    }
    /**
     * Função usada na query7 (auxiliar)
     */
    private Map<ICliente,Double> sortByValue(Map<ICliente,Double> l) {
        return l.entrySet()
                .stream()
                .sorted((Map.Entry.<ICliente,Double>comparingByValue().reversed()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));
    }
    /**
     * Função usada na query8
     */
    public List<ParClientQuant> clientesProdutosDistintos(){
        List<ParClientQuant> res = new ArrayList<>();
        for(ICliente c : this.filial.keySet())
            res.add(new ParClientQuant(c,this.numProdutosDistintosComprados(c)));
        return res;
    }
    /**
     * Função usada na query8 (auxiliar)
     */
    private int numProdutosDistintosComprados(ICliente c){
        List<InfoFil> res = this.filial.get(c);
        Set<IProduto> prods = new TreeSet<IProduto>();
        for(InfoFil info : res)
            prods.add(info.getProduto());
        return prods.size();
    }
    /**
     * Função usada na query9
     */
    public List<ClientFatQuant> getClientesFaturadoNoProd(IProduto p){
        List<ClientFatQuant> res = new ArrayList<>();
        double faturado; int quant;
        for(ICliente c : this.filial.keySet()){
            faturado = quant = 0;
            faturado = this.faturadoClienteProd(c,p);
            quant = this.quantidadeClienteProd(c,p);
            if(quant != 0) res.add(new ClientFatQuant(c,faturado,quant));
        }
        return res;
    }
    /**
     * Função usada na query9 (auxiliar)
     */
    private double faturadoClienteProd(ICliente c, IProduto p){
        List<InfoFil> res = this.filial.get(c);
        double sum = 0;
        for(InfoFil info : res){
            if(info.getProduto().equals(p))
                sum += info.getPreco() * info.getQuant();
        }
        return sum;
    }
    /**
     * Função usada na query9 (auxiliar)
     */
    private int quantidadeClienteProd(ICliente c, IProduto p){
        List<InfoFil> res = this.filial.get(c);
        int sum = 0;
        for(InfoFil info : res){
            if(info.getProduto().equals(p))
                sum += info.getQuant();
        }
        return sum;
    }
}
