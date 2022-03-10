import java.util.*;
import java.io.*;
import java.util.stream.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.charset.StandardCharsets;
public class TestesPerformance{
    public static void readFile1(String fich){
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    public static void readFile2(String fich){
        try{
            Files.readAllLines(Paths.get(fich),StandardCharsets.UTF_8);
        }
        catch(IOException exc){System.out.println(exc.getMessage());}
    }
    public static void readFile3(String fich){
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                IVenda v = new Venda(linha);
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    public static void readFile4(String fich){
        try{
            Stream<String> stream = Files.readAllLines(Paths.get(fich),StandardCharsets.UTF_8).stream();
            stream.map(s -> new Venda(s));
        }
        catch(IOException exc){System.out.println(exc.getMessage());}
    }
    public static void readFile5(String fich, CatProds catp, CatClientes catc){
        List<IVenda> linhas = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                IVenda v = new Venda(linha);
                if(v.valida(catp,catc)){
                    
                }
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    public static void readFile6(String fich, CatProds catp, CatClientes catc){
        List<String> lines = null;
        try(Stream<String> stream = Files.readAllLines(Paths.get(fich),StandardCharsets.UTF_8).stream()){
            stream.map(s -> new Venda(s).valida(catp,catc));
        }
        catch(IOException exc){System.out.println(exc.getMessage());}
    }
    private static void readProdutos(String fich, CatProds catp){
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                IProduto p = new Produto(linha);
                if(p.valida())
                    catp.addProd(p);
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    private static void readClientes(String fich, CatClientes catc){
        BufferedReader inStream = null;
        String linha = null;
        try{
            inStream = new BufferedReader(new FileReader(fich));
            while((linha = inStream.readLine()) != null){
                ICliente c = new Cliente(linha);
                if(c.valida())
                    catc.addCli(c);
            }
        }
        catch(IOException e){System.out.println(e);};
    }
    public static void main(String[] args){
        CatProds catp = new CatProds();
        CatClientes catc = new CatClientes();
        readProdutos("Produtos.txt",catp);
        readClientes("Clientes.txt",catc);
        System.out.println(catp.size());
        System.out.println(catc.size());
        Crono.start();
        readFile5("Vendas_5M.txt",catp,catc);
        System.out.println("Demorou " + Crono.stop() + " segundos a ler o ficheiro");
        Crono.start();
        readFile6("Vendas_5M.txt",catp,catc);
        System.out.println("Demorou " + Crono.stop() + " segundos a ler o ficheiro");
    }
}
