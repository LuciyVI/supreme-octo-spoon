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
#include <boost/format.hpp>
#include <iomanip>

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
                

                ptr->probability_Q+=0.005;
                #ifdef DEBUG
                std::cout<<std::fixed<<"Строки N внутри цикла в цикле = "<<ptr->Global_N_table[P][q]<<std::endl;
                std::cout<<std::fixed<<" итерация  q  = "<<q<<std::endl;
                #endif
            q++;


            }
            ptr->probability_P+=0.01;

            #ifdef DEBUG
            std::cout<<std::fixed<<"итерация  P = "<<P<<std::endl;
            #endif
            
        P++;
        ptr->probability_Q = 0.005;

        }; 
        ptr->probability_P = 0.90;
        ptr->probability_Q = 0.005;

        return 0;
};
   int paint_table(struct data *ptr)
{       

        std::string str1 = "\n +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+ \n";
        std::string str2 = "|     q/P      |     0.90     |      0.91    |     0.92     |      0.93    |     0.94     |      0.95    |      0.96    |    0.97      |     0.98     |     0.99     | ";
 
        std::cout << boost::format("%1$10d %2$10d")% str1 % str2 << std::endl;
        
        
        int j=0;


        for(int i=0;i<20;)
        {

            
            std::cout << boost::format("%1$13d %2$10d %3$13d %4$15d %5$13d %6$15d %7$13d %8$15d %9$15d %10$15d %11$12d %12$13d " ) % str1 % ptr->probability_Q % ptr->Global_N_table[j][i] % ptr->Global_N_table[j+1][i] % ptr->Global_N_table[j+2][i] % ptr->Global_N_table[j+3][i] % ptr->Global_N_table[j+4][i] % ptr->Global_N_table[j+5][i]% ptr->Global_N_table[j+6][i] % ptr->Global_N_table[j+7][i]%  ptr->Global_N_table[j+8][i]% ptr->Global_N_table[j+9][i] << std::endl;
            
            
            ptr->probability_Q+=0.005;
            
        i++;
        }
        std::cout << boost::format("%1$10d")% str1  << std::endl;
    ptr->probability_Q=0.005;
            return 0;
};


   int paint_table_func_x(struct data *ptr)
{       

        std::string str1 = "\n +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+ \n";
        std::string str2 = "|     q/P      |     0.90     |      0.91    |     0.92     |      0.93    |     0.94     |      0.95    |      0.96    |    0.97      |     0.98     |     0.99     | ";
 
        std::cout << boost::format("%1$10d %2$10d ")% str1 % str2  << std::endl;
        
        
        int j=0;


        for(int i=0;i<20;)
        {

            
            std::cout<<std::setprecision(5)<<boost::format("%1$13d %2$13d %3$15d %4$13d %5$15d %6$13d %7$15d %8$13d %9$15d %10$13d %11$15d %12$13d " ) % str1 % ptr->probability_Q % ptr->Global_Fx_table[j][i] % ptr->Global_Fx_table[j+1][i] % ptr->Global_Fx_table[j+2][i] % ptr->Global_Fx_table[j+3][i] % ptr->Global_Fx_table[j+4][i] % ptr->Global_Fx_table[j+5][i]% ptr->Global_Fx_table[j+6][i] % ptr->Global_Fx_table[j+7][i]%  ptr->Global_Fx_table[j+8][i]% ptr->Global_Fx_table[j+9][i] << std::endl;
            
            
            ptr->probability_Q+=0.005;
            
        i++;
        }
    std::cout << boost::format("%1$10d")% str1  << std::endl;    
ptr->probability_Q=0.005;
            return 0;
};

 int paint_table_multi_func(struct data *ptr)
{       

        std::string str1 = "\n +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+ \n";
        std::string str2 = "|     q/P      |     0.90     |      0.91    |     0.92     |      0.93    |     0.94     |      0.95    |      0.96    |    0.97      |     0.98     |     0.99     | ";
 
        std::cout << boost::format("%1$10d %2$10d")% str1 % str2 << std::endl;
        
        
        int j=0;


        for(int i=0;i<20;)
        {

            
            std::cout<<std::setprecision(5)<<boost::format("%1$13d %2$13d %3$15d %4$13d %5$15d %6$13d %7$15d %8$13d %9$15d %10$13d %11$15d %12$13d " ) % str1 % ptr->probability_Q % ptr->Global_Fx_Multi_table[j][i] % ptr->Global_Fx_Multi_table[j+1][i] % ptr->Global_Fx_Multi_table[j+2][i] % ptr->Global_Fx_Multi_table[j+3][i] % ptr->Global_Fx_Multi_table[j+4][i] % ptr->Global_Fx_Multi_table[j+5][i]% ptr->Global_Fx_Multi_table[j+6][i] % ptr->Global_Fx_Multi_table[j+7][i]%  ptr->Global_Fx_Multi_table[j+8][i]% ptr->Global_Fx_Multi_table[j+9][i] << std::endl;
            
            
            ptr->probability_Q+=0.005;
            
        i++;
        }
        std::cout << boost::format("%1$10d")% str1  << std::endl;

ptr->probability_Q=0.005;
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
    
   
    parse_string_for_func_multi(ptr_on_data);

    cycle_calc_for_table(ptr_on_data);
    
    calc_func_y(ptr_on_data);
    std::cout <<"\n Кол-во измерений от вероятностей q/P" <<std::endl;
    paint_table(ptr_on_data);
    std::cout<<"\n ===================================================================================================================================================== \n"<<std::endl;
    
    std::cout <<"\n Таблица унимодальной функции " << data.string_func<<" \n"<<std::endl;
    
    paint_table_func_x(ptr_on_data);
    
    std::cout <<"\n Таблица мультимодальной функции " << data.string_func_multi<<std::endl;
    
    calc_func_multi(ptr_on_data);
    
    paint_table_multi_func(ptr_on_data);

    return 0;
}
    
