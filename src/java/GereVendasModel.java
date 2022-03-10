import java.util.*;
import java.io.*;
public class GereVendasModel implements InterfGereVendasModel,Serializable{
    private ICatProds catp;
    private ICatClientes catc;
    private IFaturacao fat;
    private IFilial[] fil;
    
    private static int num_linhas_vendas_total = 0;
    private static String nome_fich_vendas = "";
    private static int num_compras_preco_0 = 0;
    public GereVendasModel(){
        this.catp = new CatProds();
        this.catc = new CatClientes();
        this.fat = new Faturacao();
        this.fil = new Filial[3];
        for(int i = 0; i < 3; i++)
            this.fil[i] = new Filial();
    }
    public int getNumLinhasVendasTotal(){
        return this.num_linhas_vendas_total;
    }
    public String getNomeFichVendas(){
        return this.nome_fich_vendas;
    }
    public int getNumComprasPreco0(){
        return this.num_compras_preco_0;
    }
    public void createData(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Pretende carregar os dados da aplicação a partir dos ficheiros de texto? (s/n):");
        String op = sc.nextLine();
        if(op.equals("s")){
            List<String> config = readConfigs();
            Crono.start();
            readProdutos(config.get(0));
            readClientes(config.get(1));
            readVendas(config.get(2));
            System.out.println("Demorou " + Crono.print() + " a carregar todos os ficheiros.");
        }
    }
    public List<String> readConfigs(){
        BufferedReader inStream = null;
        String linha = null;
        List<String> res = new ArrayList<>(3);
        try{
            inStream = new BufferedReader(new FileReader("configs.txt"));
            while((linha = inStream.readLine()) != null){
                res.add(linha);
            }
        }
        catch(IOException e){System.out.println(e);};
        return res;
    }
    private void readProdutos(String fich){
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                IProduto p = new Produto(linha);
                if(p.valida())
                    this.catp.addProd(p);
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    private void readClientes(String fich){
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                ICliente c = new Cliente(linha);
                if(c.valida())
                    this.catc.addCli(c);
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    private void readVendas(String fich){
        BufferedReader inStream = null;
        String linha = null;
        int count = 0;
        num_compras_preco_0 = num_linhas_vendas_total = 0;
        nome_fich_vendas = "";
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                IVenda v = new Venda(linha);
                if(v.valida(this.catp,this.catc)){
                    this.fat.addVenda(v);
                    this.fil[v.getFilial()-1].addVenda(v);
                    if(v.getPreco() == 0) num_compras_preco_0++;
                }
                count++;
            }
            num_linhas_vendas_total = count;
            nome_fich_vendas = fich;
        }
        catch(IOException e){System.out.println(e);};
    }
    public ICatProds getCatProds(){
        return this.catp;
    }
    public ICatClientes getCatClientes(){
        return this.catc;
    }
    public IFaturacao getFaturacao(){
        return this.fat;
    }
    public IFilial[] getFilial(){
        return this.fil;
    }
    /**
     * Carrega o catálogo de produtos
     */
    public void carregaCatProd(String fich) throws FileNotFoundException,IOException,ClassNotFoundException{
        FileInputStream fis = new FileInputStream(fich);
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.catp = (ICatProds) ois.readObject();
        ois.close();
    }
    /**
     * Carrega o catálogo de clientes
     */
    public void carregaCatCli(String fich) throws FileNotFoundException,IOException,ClassNotFoundException{
        FileInputStream fis = new FileInputStream(fich);
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.catc = (ICatClientes) ois.readObject();
        ois.close();
    }
    /**
     * Carrega a faturação
     */
    public void carregaFaturacao(String fich) throws FileNotFoundException,IOException,ClassNotFoundException{
        FileInputStream fis = new FileInputStream(fich);
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.fat = (IFaturacao) ois.readObject();
        ois.close();
    }
    /**
     * Carrega as filiais
     */
    public void carregaFiliais(String fich) throws FileNotFoundException,IOException,ClassNotFoundException{
        FileInputStream fis = new FileInputStream(fich);
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.fil = (IFilial[]) ois.readObject();
        ois.close();
    }
}
