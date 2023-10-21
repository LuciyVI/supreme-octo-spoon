#include <iostream>
#include <cmath>
#include <libxml/parser.h>
#include <string>

using namespace std;


struct data {


double x = 0;
double a , b = 0;

};

void calculating_func(struct data *ptr)
{
    double func = (-0.5*cos(0.5*ptr->x)-0.5);
    std::cout<<"Введите 'a' интервал на отрезке"<<std::endl;
    std::cin>>ptr->a;
    std::cout<<"Введите 'b' интервал на отрезке"<<std::endl;
    std::cin>>ptr->b;
};
int open_and_change_config_file(struct data *ptr)
{
    std::string xml_file_name = "./config.xml";
    std::cout << "Parsing " << xml_file_name << std::endl;
    xmlDocPtr doc = xmlParseFile(xml_file_name.c_str());
        if (doc == NULL) 
            {
                std::cerr << "Error parsing file " << std::endl;
                return 1;
            }
    
    std::cout<<doc->name<<std::endl;    

    return 0;
};
int main ()
{
        struct data data;
        struct data  *ptr_on_data = &data;
    
        calculating_func(ptr_on_data);
        std::cout<<data.a<<std::endl;
        std::cout<<data.b<<std::endl;
        open_and_change_config_file(ptr_on_data);
    return 0;

}

