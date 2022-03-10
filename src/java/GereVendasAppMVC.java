import java.util.List;
public class GereVendasAppMVC{
    public static void main(String [] args){
        InterfGereVendasModel model = new GereVendasModel();
        model.createData();
        if(model == null){System.out.println("ERRO INICIALIZACAO"); System.exit(-1);}
        InterfGereVendasView view = new GereVendasView();
        InterfGereVendasController control = new GereVendasController();
        control.setModel(model);
        control.setView(view); 
        control.startController();
    }
}