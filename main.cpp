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

#define DEBUG
// using namespace std;
using namespace exprtk;

int calc_extremum(struct data *ptr)
{

    double epsel = calc_epsel(ptr);
    
    std::random_device random_device;
    std::mt19937 generatere(random_device());
    std::uniform_int_distribution<> distribution(ptr->a, ptr->b);
    
 return distribution(generatere);
};





double cycle_calc_for_table(struct data *ptr)
{
        ptr->probability_P = 0.90;
        ptr->probability_Q = 0.005;
        int P = 0;
        for(P;ptr->probability_P<1;)
        {   
        
        for(int q = 0; ptr->probability_Q<0.105;) 
            {
            
                ptr->Global_N_table[P][q] = calc_N(ptr);
                // std::cout<<std::fixed<<"Строки N внутри цикла в цикле = "<<ptr->Global_N_table[P][q]<<std::endl;

                ptr->probability_Q+=0.005;
                // std::cout<<std::fixed<<" итерация  q  = "<<q<<std::endl;
            q++;
            }
            ptr->probability_P+=0.01;
            // std::cout<<std::fixed<<"итерация  P = "<<P<<std::endl;

        P++;
        ptr->probability_Q = 0.005;

        }; 
        ptr->probability_P = 0.90;
        ptr->probability_Q = 0.005;

        return 0;
};
    int paint_table(struct data *ptr)
{
        std::cout<<"+-----+"<<"-----+"<<"-----+"<<"------+"<<"-----+"<<"------+"<<"------+"<<"------+"<<"------+"<<"------+"<<"------+"<<std::endl;
        std::cout<<"| q/P |"<<"0.90"<<" |"<<"0.91"<<" | 0.92"<<" |"<<" 0.93"<<" |"<<"0.94"<<" | 0.95"<<" | 0.96"<<" | 0.97 " <<"| 0.98"<<" | 0.99 |" <<std::endl;
        std::cout<<"+-----+"<<"-----+"<<"-----+"<<"------+"<<"------+"<<"-----+"<<"------+"<<"------+"<<"------+"<<"------+"<<"------+"<<std::endl;
        int j=0;
    
        std::cout<<ptr->Global_N_table[0][0]<<std::endl;
        for(int i=0;i<=10;)
        {
              
            std::cout<<"\n+-----+"<<"-----+"<<"-----+"<<"------+"<<"-----+"<<"------+"<<"------+"<<"------+"<<"------+"<<"------+"<<"------+"<<std::endl;
            std::cout<<"|" <<ptr->probability_Q << "|"<<ptr->Global_N_table[i][j]<<" |"<<ptr->Global_N_table[i][j+1]<<" | "<<ptr->Global_N_table[i][j+2]<<" |"<<ptr->Global_N_table[i][j+3]<<" |"<<ptr->Global_N_table[i][j+4]<<" |"<< ptr->Global_N_table[i][j+5]<<" | "<<ptr->Global_N_table[i][j+6]<<" |"  <<  ptr->Global_N_table[i][j+7]<<" |"<<ptr->Global_N_table[i][j+8] <<"|\n" <<std::endl;
            std::cout<<"+-----+"<<"-----+"<<"-----+"<<"------+"<<"------+"<<"-----+"<<"------+"<<"------+"<<"------+"<<"------+"<<"------+\n"<<std::endl;
            ptr->probability_Q+=0.005;
        
        i++;
        }   
    
            return 0;
};

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
    
    
    // for(i=0;i<10;i++){
    
    //         for(j=0;j<20;j++){
    //         std::cout<<std::fixed<<data.Global_N_table[i][j]<<std::endl;
    //     }
    // }
    paint_table(ptr_on_data);
    return 0;

}
    
