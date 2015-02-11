/* 
 * File:   MAS.hpp
 * Author: Matthew
 *
 * Created on February 11, 2015, 12:07 PM
 */

#ifndef MAS_HPP
#define	MAS_HPP

#include <vector>

#include "support/CSTAR/CSTAR.hpp"
#include "support/CSTAR/Population.hpp"


namespace mas{
     
    
    template<class T>
    class  MASModel{
        std::vector<cstar::population::PopulationBase<T> > sub_populations;
        cstar::movement::MovementBase<T>* movement_model;
        
        public:
            
            
        
    };
    
    
    
}



#endif	/* MAS_HPP */

