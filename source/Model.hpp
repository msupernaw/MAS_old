/* 
 * File:   Model.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:13 AM
 */

#ifndef MODEL_HPP
#define	MODEL_HPP

#include "Object.hpp"
#include "Subpopulation.hpp"



namespace mas{
    
    
    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Model: public Object{
        
        uint32_t space_max;//max space dimension
        uint32_t time_max;//max time dimension
        uint32_t age_max;//max age dimension
        uint32_t genders;//max gender dimension
        
        Observation<EVAL_T, REAL_T> observations;
        std::vector<Location<REAL_T, EVAL_T> areas;
        
    };
    
}


#endif	/* MODEL_HPP */

