#include <iostream>
#include <cmath>
#include <libxml/parser.h>
#include <string>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <stdlib.h>
#include "exprtk.hpp"

#define X ptr->x
#define DEBUG
// using namespace std;
using namespace exprtk;


struct data {


double x = 0;
double a , b = 0;
std::string string_func;

};

void calculating_func(struct data *ptr)
{
    double func = (-0.5*cos(0.5*ptr->x)-0.5);
};
int open_and_change_config_file(struct data *ptr)
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
    X=strtod(charString, NULL);
}    
if(!xmlStrcmp(cur->name,(const xmlChar*)"func")){
    key=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    char* charString = (char*)key;
    ptr->string_func = charString;

    
}    


cur=cur->next;

}
    return 0;
};


int parse_string_for_func(struct data *ptr)
{

    const std::string expression_string = ptr->string_func;
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;
    
     double x;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x",ptr->x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_string,expression);

    double y = expression.value();
    printf("%19.3f\t Это X %19.3f\n Это Y",x,y);
    return 0;
}

int main()
{

    struct data data;
    struct data  *ptr_on_data = &data;
    
        calculating_func(ptr_on_data);
        open_and_change_config_file(ptr_on_data);
        
#ifdef DEBUG        
        std::cout<<data.a<<std::endl;
        std::cout<<data.b<<std::endl; 
        std::cout<<data.x<<std::endl; 
        std::cout<<data.string_func<<std::endl; 
#endif
    parse_string_for_func(ptr_on_data);
    return 0;

}

