public class CE2Info{
    private int [] numComprasPorMes;
    private double [][] faturacaoTotalPorMesEFilial;
    private int [][] numClientesDifPorMesEFilial;
    public CE2Info(int [] numComprasPorMes,double [][] faturacaoTotalPorMesEFilial,int [][] numClientesDifPorMesEFilial){
        this.numComprasPorMes = numComprasPorMes;
        this.faturacaoTotalPorMesEFilial = faturacaoTotalPorMesEFilial;
        this.numClientesDifPorMesEFilial = numClientesDifPorMesEFilial;
    }
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nNúmero de compras por mês\n\n");
        for(int i = 0; i < 12; i++) sb.append(numComprasPorMes[i] + " ");
        sb.append("\n\n");
        sb.append("Facturação total por mês e filial\n\n");
        for(int i = 0; i < 12; i++){
            for (int j = 0; j < 3; j++) {
                sb.append(faturacaoTotalPorMesEFilial[i][j] + " ");
            }
            sb.append("\n");
        }
        sb.append("\n");
        sb.append("Número de clientes diferentes por mês e filial\n\n");
        for(int i = 0; i < 12; i++){
            for (int j = 0; j < 3; j++) {
                sb.append(numClientesDifPorMesEFilial[i][j] + " ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }
}
