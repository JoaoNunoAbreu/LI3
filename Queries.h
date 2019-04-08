#include "SGV.h"

int query1(SGV sgv, char* file_nameProds, char* file_nameClient, char* file_nameVendas, int* pLidos, int* cLidos, int* vLidas);
List_Strings query2(SGV sgv, char c);
void query3(SGV sgv,int mes, Produto p, char c,float* fat1T,float* fat1N,float* fat1P,float* fat2T,float* fat2N,float* fat2P, float* fat3T,float* fat3N,float* fat3P, int* nVendas);
List_Strings query4(SGV sgv,char c, int filial);
List_Strings query5(SGV sgv);
void query6(SGV sgv, int* countC, int* countP);
void query7(SGV sgv, Cliente cliente,int tabela[12][3]);
void query8(SGV sgv, int mes1, int mes2, int* totalVendas, float* totalFaturado);
void query9(SGV sgv, List_Strings lsN, List_Strings lsP, Produto produto, int filial);
List_Strings query10(SGV sgv, Cliente cliente, int mes);
void query11(SGV sgv, int N,List_Strings ls1,List_Strings ls2,List_Strings ls3,int* count1, int* count2, int* count3);
List_Strings query12(SGV sgv, Cliente cliente);