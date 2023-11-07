#include <iostream>
#include <cmath>
#include <libxml/parser.h>
#include <string>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <stdlib.h>
#include "exprtk.hpp"
#include <random>


// #define DEBUG
// using namespace std;
using namespace exprtk;


struct data {


    double x = 0;
    double a , b = 0;
    std::string string_func;
    std::string string_func_multi;
    double result_fx;
    double result_func_multi=0; 
    double probability_interval = 0.0;
    double epsel=0.0;
    double probability_P = 0.0;
    double probability_Q = 0.0;
    double Global_N_table[14][24];
};


void open_and_change_config_file(struct data *ptr)
{


xmlDocPtr doc = xmlParseFile("config.xml");
xmlNodePtr cur = xmlDocGetRootElement(doc);
xmlChar*  key;

cur=cur->xmlChildrenNode;

while(cur!=NULL){
/* Найти подузел ключевого слова */

if(!xmlStrcmp(cur->name,(const xmlChar*)"a")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->a=strtod(charString, NULL);
}
if(!xmlStrcmp(cur->name,(const xmlChar*)"b")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->b=strtod(charString, NULL);
}
if(!xmlStrcmp(cur->name,(const xmlChar*)"x")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->x=strtod(charString, NULL);
}    
if(!xmlStrcmp(cur->name,(const xmlChar*)"func")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->string_func = charString;

    
}    

if(!xmlStrcmp(cur->name,(const xmlChar*)"func_multi")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->string_func_multi = charString;

    
}  
if(!xmlStrcmp(cur->name,(const xmlChar*)"q")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->probability_interval = strtod(charString, NULL);

    
}   



cur=cur->next;

}

};


double parse_string_for_func(struct data *ptr)
{
    const std::string expression_string = ptr->string_func;
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;
    
    
    symbol_table_t symbol_table;
    

    symbol_table.add_variable("x",ptr->x);
    symbol_table.add_constants();
    std::cout<<"X in parse_in_func"<<ptr->x<<std::endl;
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_string,expression);

    ptr->result_fx= expression.value();
    
    #ifdef DEBUG
    printf("\n %19.3f Это result F(x) \n",ptr->result_fx);
    std::cout<<"PTR->X"<<ptr->x<<std::endl;
    #endif
    
    return expression.value();
}
double parse_string_for_func_multi(struct data *ptr)
{

    const std::string expression_string = ptr->string_func_multi;
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;
    
    symbol_table_t symbol_table;
    symbol_table.add_variable("x",ptr->x);
    symbol_table.add_variable("func_x",ptr->result_fx);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_string,expression);

    ptr->result_func_multi = expression.value();
#ifdef DEBUG
    printf("%19.3f Это result multimodul Func  \n",ptr->result_func_multi);
#endif

    return expression.value();
}

int calc_epsel(struct data *ptr)
{
    return ptr->epsel=(ptr->b-ptr->a)/ptr->probability_interval;
}

bool _check_value(double N1, double N2 , double N3)
{
bool Condition = false;

    if (N1 == N2 || N2 == N3 || N1 == N3)
    {
        Condition = false;
        std::cout << "condition false" << std::endl;
    }
    else
    {
        Condition = true;
        std::cout << "condition true" << std::endl;

    }
    return Condition;
}   
double calc_N(struct data *ptr)
{
    double N = ceil((std::log(1-ptr->probability_P))/(std::log(1-ptr->probability_Q)));

    #ifdef DEBUG
    // std::cout<<"P точек"<<ptr->probability_P<<std::endl;
    // std::cout<<"Q точек"<<ptr->probability_Q<<std::endl;    
    // std::cout<<"N точек"<<N<<std::endl;
    #endif


    return N;
};
void calc_func_y(struct data *ptr) {
    double x = 10;
    double param = 0;
    double func_x = 0;
    int j = 0;
srand(static_cast<unsigned int>(time(0)));
for(int i =0; i<12;i++){
for(int j=0;j<24; ){
    double param = ptr->Global_N_table[j][i];
    std::cout<<"PARAM : "<<param<<std::endl;
    for(int i = 0; i<param; ++i){
    std::cout<<"iteratition "<<i<<"\n"<<std::endl;
    ptr->x = ptr->a + (ptr->b - ptr->a) * rand() / RAND_MAX;
    // ptr->x = ptr->a + static_cast<double>(rand()) / RAND_MAX * (ptr->b - ptr->a);
    std::cout<<"PARAM : "<<param<<std::endl;
    func_x = parse_string_for_func(ptr);
    std::cout<<std::fixed<<x<<std::endl;
    std::cout<<std::fixed<<func_x<<std::endl;
    if(func_x < x)
    {
        
    x=func_x;


    }
    j++;
    }

}
}
    std::cout<<std::fixed<<"Min :"<<x<<std::endl;
};
