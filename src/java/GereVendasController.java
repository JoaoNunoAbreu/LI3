import java.util.*;
import java.io.*;
import java.util.AbstractMap.SimpleEntry;
public class GereVendasController implements InterfGereVendasController{
    private InterfGereVendasModel model;
    private InterfGereVendasView view;
    public GereVendasController(){
        this.model = new GereVendasModel();
        this.view = new GereVendasView();
    }
    public void setModel(InterfGereVendasModel model){
        this.model = model;
    } 
    public void setView(InterfGereVendasView view){
        this.view = view;
    }
    public void startController(){
        int op = 0;
        Object obj = null;
        while(op >= 0){
            view.show();
            op = this.readOp();
            if(op > 0){
                obj = resultadoQuery(op);
                if(obj != null){
                    if(op == 1){
                        view.navegador((List) obj);
                        view.printTamanho((List) obj);
                    }
                    else if(op == 2) view.printQ2((List) obj);
                    else if(op == 3 || op == 4) view.printTabela((TwoIntsOneDouble[]) obj);
                    else if(op == 11)view.printCE1((CE1Info) obj);
                    else if(op == 12)view.printCE2((CE2Info) obj);
                    else view.navegador((List) obj);
                }
            }
        }
    }
    public int readOp(){
        Scanner sc = new Scanner(System.in);
        int op = sc.nextInt();
        while(op > 14){
            view.opErrada();
            op = sc.nextInt();
        }
        return op;
    }
    public Object resultadoQuery(int op){
        Scanner sc = new Scanner(System.in);
        Object res = null;
        ICliente c = null;
        IProduto p = null;
        int mes = 0;
        int x = 0; String filename = "gestVendas.dat";;
        switch(op){
            case 1:
                Crono.start();
                res = this.query1();
                view.printTempoQuery(Crono.stop());
                break;
            case 2: 
                view.printMes();
                mes = sc.nextInt();
                if(mes < 1 || mes > 12) view.opErrada();
                else {
                    Crono.start();
                    res = this.query2(mes);
                    view.printTempoQuery(Crono.stop());
                }
                break;
            case 3: 
                view.printCliente();
                c = new Cliente(sc.nextLine());
                if(!this.model.getFilial()[0].containsKey(c) && !this.model.getFilial()[1].containsKey(c) && !this.model.getFilial()[2].containsKey(c))
                    view.clienteNExiste();
                else{
                    Crono.start();
                    res = this.query3(c);
                    view.printTempoQuery(Crono.stop());
                }
                break;
            case 4: 
                view.printProduto();
                p = new Produto(sc.nextLine());
                if(!this.model.getFaturacao().containsKey(p))
                    view.produtoNExiste();
                else{
                    Crono.start();
                    res = this.query4(p);
                    view.printTempoQuery(Crono.stop());
                }
                break;
            case 5: 
                view.printCliente();
                c = new Cliente(sc.nextLine());
                if(!this.model.getFilial()[0].containsKey(c) && !this.model.getFilial()[1].containsKey(c) && !this.model.getFilial()[2].containsKey(c))
                    view.clienteNExiste();
                else{
                    Crono.start();
                    res = this.query5(c);
                    view.printTempoQuery(Crono.stop());
                }
                break;
            case 6: 
                view.printX();
                x = sc.nextInt();
                Crono.start();
                res = this.query6(x);
                view.printTempoQuery(Crono.stop());
                break;
            case 7: 
                Crono.start();
                res = this.query7();
                view.printTempoQuery(Crono.stop());
                break;
            case 8: 
                view.printX();
                x = sc.nextInt();
                Crono.start();
                res = this.query8(x);
                view.printTempoQuery(Crono.stop());
                break;
            case 9: 
                view.printProduto();
                p = new Produto(sc.nextLine());
                view.printX();
                x = sc.nextInt();
                if(!this.model.getFaturacao().containsKey(p))
                    view.produtoNExiste();
                else{
                    Crono.start();
                    res = this.query9(p,x);
                    view.printTempoQuery(Crono.stop());
                }
                break;
            case 10:
                Crono.start();
                res = this.query10();
                view.printTempoQuery(Crono.stop());
                break;
            case 11:
                Crono.start();
                res = ce1();
                view.printTempoQuery(Crono.stop());
                break;
            case 12: 
                Crono.start();
                res = ce2();
                view.printTempoQuery(Crono.stop());
                break;
            case 13:
                try{
                    view.pretendeInserirNome();
                    String opcao = sc.nextLine();
                    if(opcao.equals("s")){
                        view.printNomeFich();
                        filename = sc.nextLine();
                    }
                    Crono.start();
                    this.guardaEstado(filename);
                    view.printTempoQuery(Crono.stop());
                }
                catch(IOException e){e.printStackTrace();}
                break;
            case 14:
                try{
                    Crono.start();
                    this.carregaEstado(filename);
                    view.printTempoQuery(Crono.stop());
                }
                catch(FileNotFoundException e){System.out.println("Ficheiro não encontrado");}
                catch(IOException e){System.out.println("Erro na escrita do ficheiro");}
                catch(ClassNotFoundException e){System.out.println("Classe incorrecta");}
                break;
            default: break;
        }
        return res;
    }
    /**
     * Consultas estatísticas
     */
    public CE1Info ce1(){
        String nome = this.model.getNomeFichVendas();
        int numRegistosErrados = this.model.getNumLinhasVendasTotal() - model.getFaturacao().totalSize();
        int numProdutos = this.model.getCatProds().size();
        int numProdutosDifComprados = this.model.getFaturacao().size();
        int numProdutosNComprados = numProdutos - numProdutosDifComprados;
        Set<ICliente> set = new HashSet<>();
        for(int i = 0; i < 3; i++){
            Set<ICliente> tmp = model.getFilial()[i].getClients();
            for(ICliente c : tmp){ // Para não haver clientes repetidos
                set.add(c);
            }
        }
        int numClientesNCompraram = model.getCatClientes().size() - set.size();
        int numCompras0 = this.model.getNumComprasPreco0();
        double faturacaoTotal = this.model.getFaturacao().totalFaturacao();
        return new CE1Info(nome,numRegistosErrados,numProdutos,numProdutosDifComprados,numProdutosNComprados,numClientesNCompraram,numCompras0,faturacaoTotal);
    }
    public CE2Info ce2(){
        int[] numComprasPorMes = new int[12];
        double[][] faturacaoTotalPorMesEFilial = new double[12][3];
        int[][] numClientesDifPorMesEFilial = new int[12][3];
        
        for(int i = 0; i < 12; i++){
            numComprasPorMes[i] = model.getFaturacao().numComprasMes(i+1);
        }
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 3; j++){ 
                faturacaoTotalPorMesEFilial[i][j] = model.getFilial()[j].totalFacturadoNumMes(i+1);
            }
        }
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 3; j++){
                numClientesDifPorMesEFilial[i][j] = model.getFilial()[j].numClientsDifMes(i+1);
            }
        }
        return new CE2Info(numComprasPorMes,faturacaoTotalPorMesEFilial,numClientesDifPorMesEFilial);
    }
    /**
     * Consultas interactivas
     */
    public List<IProduto> query1(){
        ICatProds catp = model.getCatProds();
        IFaturacao fat = model.getFaturacao();
        Set<IProduto> res = new TreeSet<IProduto>();
        for(IProduto p : catp.getCatProd())
            if(!fat.containsKey(p))
                res.add(p);
        List<IProduto> resLista = new ArrayList<>(res);
        return resLista;
    }
    public List<SimpleEntry<Integer,Integer>> query2(int mes){
        int nvendas = 0; int nclientes = 0;
        List<SimpleEntry<Integer,Integer>> res = new ArrayList<>();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            SimpleEntry<Integer,Integer> temp = f.contaVendasClientes(mes);
            res.add(temp);
            nvendas += temp.getKey();
            nclientes += temp.getValue();
        }
        SimpleEntry<Integer,Integer> res1 = new SimpleEntry(nvendas,nclientes);
        res.add(res1);
        return res; // Será uma lista que nas 3 primeiras posições estarão resultados pelas filiais e na 4ª valores totais
    }
    public TwoIntsOneDouble[] query3(ICliente c){
        TwoIntsOneDouble[] res = new TwoIntsOneDouble[12];
        for(int i = 0; i < 12; i++) res[i] = new TwoIntsOneDouble();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            for(int j = 0; j < 12; j++){
                res[j].soma(f.contaComprasProdutosGasto(c,j+1));
            }
        }
        return res;
    }
    public TwoIntsOneDouble[] query4(IProduto p){
       TwoIntsOneDouble[] res = new TwoIntsOneDouble[12];
       for(int i = 0; i < 12; i++) res[i] = new TwoIntsOneDouble();
       int x,y;
       for(x = 1;x <= 3;x++){
           for(y = 0;y < 12;y++){
               res[y].soma(this.model.getFilial()[x-1].prodInfoMonth(p.getCodProd(),y+1));
            }
       }
       return res;
    }
    public List<ParProdQuant> query5(ICliente c){
        List<ParProdQuant> res = new ArrayList<>();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            res.addAll(f.getQuantComprada(c));
        }
        Collections.sort(res, new ComparatorQuantDecrescente1());
        return res;
    }
    public List<ParProdQuant> query6(int x){
        IFaturacao fat = model.getFaturacao();
        List<IProduto> sorted_prods = fat.getSortedProds(x);
        List<ParProdQuant> tmp = new ArrayList<ParProdQuant>();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            for(IProduto p : sorted_prods){
                tmp.add(new ParProdQuant(p,f.contaClientesQueCompraramP(p)));
            }
        }
        int sum;
        List<ParProdQuant> res = new ArrayList<>();
        for(IProduto p : sorted_prods){
            sum = 0;
            for(ParProdQuant pair : tmp){
                if(p.equals(pair.getProduto()))
                    sum += pair.getQuantidade();
            }
            res.add(new ParProdQuant(p,sum));
        }
        return res;
    }
    public List<List<ICliente>> query7(){
        List<List<ICliente>> res = new ArrayList<>();
        List<ICliente> l1 = new ArrayList<>();
        List<ICliente> l2 = new ArrayList<>();
        List<ICliente> l3 = new ArrayList<>();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            if(i == 0) l1 = f.melhoresCompradores();
            else if(i == 1) l2 = f.melhoresCompradores();
            else if(i == 2) l3 = f.melhoresCompradores();
        }
        res.add(l1);
        res.add(l2);
        res.add(l3);
        return res;
    }
    public List<ParClientQuant> query8(int x){
        List<ParClientQuant> data = new ArrayList<>();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            List<ParClientQuant> temp = f.clientesProdutosDistintos();
            for(ParClientQuant pair : temp){
                // Vai testar se já existe o cliente na lista total (data) e atualizar valor nesse caso
                boolean r = false;
                Iterator<ParClientQuant> it = data.iterator();
                while(it.hasNext() && r == false){
                    ParClientQuant pair_data = it.next();
                    if(pair_data.getCliente().equals(pair.getCliente())){
                        r = true;
                        pair_data.soma(pair.getQuantidade());
                    }
                }
                // Se não existir adicionar novo elemento à lista
                if(!r) data.add(pair);
            }
        }
        // Para ficarem os dados ordenados
        Collections.sort(data);
        if(data.size() < x) return data.subList(0,data.size());
        else return data.subList(0,x);
    }
    public List<ClientFatQuant> query9(IProduto p, int x){
        List<ClientFatQuant> data = new ArrayList<ClientFatQuant>();
        for(int i = 0; i < 3; i++){
            IFilial f = this.model.getFilial()[i];
            List<ClientFatQuant> temp = f.getClientesFaturadoNoProd(p);
            for(ClientFatQuant pair : temp){
                // Vai testar se já existe o cliente na lista total (data) e atualizar valor nesse caso
                boolean r = false;
                Iterator<ClientFatQuant> it = data.iterator();
                while(it.hasNext() && r == false){
                    ClientFatQuant pair_data = it.next();
                    if(pair_data.getCliente().equals(pair.getCliente())){
                        r = true;
                        pair_data.soma(pair.getFaturado());
                    }
                }
                // Se não existir adicionar novo elemento à lista
                if(!r) data.add(pair);
            }
        }
        // Para ficarem os dados ordenados
        Collections.sort(data,new ComparatorQuantDecrescente2());
        if(data.size() < x) return data.subList(0,data.size());
        else return data.subList(0,x);
    }
    public List<ParProdTabela> query10(){
        return model.getFaturacao().totalFaturadoProdutos();
    }
    /**
     * Guarda toda a informação da aplicação
     */
    public void guardaEstado(String fich) throws FileNotFoundException,IOException{
        FileOutputStream fos = new FileOutputStream(fich);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this.model);
        oos.flush();
        oos.close();
    }
    public void carregaEstado(String fich) throws FileNotFoundException,IOException,ClassNotFoundException{
        FileInputStream fis = new FileInputStream(fich);
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.model = (InterfGereVendasModel) ois.readObject();
        ois.close();
    }
}
