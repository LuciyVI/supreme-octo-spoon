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
#include "func.hpp"

// #define DEBUG
// using namespace std;
using namespace exprtk;

int calc_extremum(struct data *ptr)
{

    double epsel = calc_epsel(ptr);
    
    std::random_device random_device;
    std::mt19937 generatere(random_device());
    std::uniform_int_distribution<> distribution(ptr->a, ptr->b);
    
    bool Condition = false;
    double N1 = distribution(generatere);
    double N2 = distribution(generatere);
    double N3 = distribution(generatere);
            std::cout<<"\n>>"<<N1<<"\n "<<std::endl;
            std::cout<<"\n>>"<<N2<<"\n "<<std::endl;
            std::cout<<"\n>>"<<N3<<"\n "<<std::endl;
            std::cout<<"\n>>"<<"Тут цикл"<<"\n "<<std::endl;
for (; Condition == false; )
{
    if (N1 == N2 || N2 == N3 || N1 == N3)
    {
        Condition = false;
        N1 = distribution(generatere);
        N2 = distribution(generatere);
        N3 = distribution(generatere);
        std::cout << "condition false" << std::endl;
    }
    else
    {
        Condition = true;
        std::cout << "condition true" << std::endl;
    }
    
}
            std::cout<<"\n>>После цикла"<<"\n "<<std::endl;
            std::cout<<"\n>>"<<N1<<"\n "<<std::endl;
            std::cout<<"\n>>"<<N2<<"\n "<<std::endl;
            std::cout<<"\n>>"<<N3<<"\n "<<std::endl;
    
    ptr->x=N1;
    
    double y1 = parse_string_for_func(ptr);
    #ifdef DEBUG
    
    std::cout<<"ptr->x=N1 :"<<ptr->x<<std::endl;
    std::cout<<std::fixed<<"Result y1  :"<<y1<<std::endl;
    
    #endif

    ptr->x=N2;
    
    double y2 = parse_string_for_func(ptr);

    #ifdef DEBUG
    
    std::cout<<"ptr->x=N2 :"<<ptr->x<<std::endl;
    std::cout<<std::fixed<<"Result y2  :"<<y1<<std::endl;
    
    #endif

    ptr->x=N3;
    
    double y3 = parse_string_for_func(ptr);

    #ifdef DEBUG
    
    std::cout<<"ptr->x=N3:"<<ptr->x<<std::endl;
    std::cout<<std::fixed<<"Result y3  :"<<y1<<std::endl;
    
    #endif

    bool value = _check_value(y1,y2,y3);
    
    std::cout<<value<<std::endl;
    

    return 0;


};





double cycle_calc_for_table(struct data *ptr)
{
        ptr->probability_P = 0.90;
        ptr->probability_Q = 0.005;
    
       
        return 0;
}
int main()
{

    struct data data;
    struct data  *ptr_on_data = &data;
        
    open_and_change_config_file(ptr_on_data);
        
#ifdef DEBUG        
        std::cout<<"Интервал от А"<<data.a<<"\n"<<std::endl;
        std::cout<<"Интервал от B"<<data.b<<"\n"<<std::endl; 
        std::cout<<"X "<<data.x<<"\n"<<std::endl; 
        std::cout<<"Унимодальная функция -- "<<data.string_func<<"\n"<<std::endl;
        std::cout<<"Мультимодальная функция -- "<<data.string_func_multi<<"\n"<<std::endl;
        std::cout<<"Эпселант -- "<<data.epsel<<"\n"<<std::endl;
        std::cout<<"Q - "<<data.probability_interval<<"\n"<<std::endl;
#endif
    
    parse_string_for_func(ptr_on_data);
    parse_string_for_func_multi(ptr_on_data);
    // calc_extremum(ptr_on_data);
    cycle_calc_for_table(ptr_on_data);

    return 0;

}
    
