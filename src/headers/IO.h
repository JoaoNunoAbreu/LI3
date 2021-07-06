#include "Queries.h"

int runMenu();

void inputQuery1(char** file_nameProds, char** file_nameClient, char** file_nameVendas);
void outputQuery1(char* file_nameProds,char* file_nameClient,char* file_nameVendas,int x,int pLidos,int pTotal,int cLidos,int cTotal, int vLidas,int vTotal);
// ------------------------------------------------------------------------------------------------
char inputQuery2();
void outputQuery2(List_Strings ls);
// ------------------------------------------------------------------------------------------------
void inputQuery3(char* reader, int* mes, char** p);
void outputQuery3(int mes, char* p, char c,float fat1T,float fat1N,float fat1P,float fat2T,float fat2N,float fat2P, float fat3T,float fat3N,float fat3P, int nVendas);
// ------------------------------------------------------------------------------------------------
void inputQuery4(char* c, int* filial);
void outputQuery4(List_Strings ls);
// ------------------------------------------------------------------------------------------------
void outputQuery5(List_Strings ls);
// ------------------------------------------------------------------------------------------------
void outputQuery6(int countC, int countP);
// ------------------------------------------------------------------------------------------------
void inputQuery7(char** reader);
void outputQuery7(int tabela[12][3]);
// ------------------------------------------------------------------------------------------------
void inputQuery8(int* mes1, int* mes2);
void outputQuery8(int mes1, int mes2, int totalVendas, float totalFaturado);
// ------------------------------------------------------------------------------------------------
void inputQuery9(char** produto, int* filial);
void outputQuery9(List_Strings lsN, List_Strings lsP, char* produto, int filial);
// ------------------------------------------------------------------------------------------------
void inputQuery10(char** cliente,int* mes);
void outputQuery10(List_Strings ls);
// ------------------------------------------------------------------------------------------------
int inputQuery11();
void outputQuery11(List_Strings ls1,List_Strings ls2, List_Strings ls3, int count1, int count2, int count3, int N);
// ------------------------------------------------------------------------------------------------
void inputQuery12(char** cliente);
void outputQuery12(List_Strings ls);