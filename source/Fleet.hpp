/* 
 * File:   Fleet.hpp
 * Author: Matthew
 *
 * Created on March 5, 2015, 10:52 AM
 */

#ifndef FLEET_HPP
#define	FLEET_HPP

#include "Object.hpp"
#include "Observation.hpp"

namespace mas{
    
    template<typename REAL_T, typename EVAL_T>
    class Fleet : public EvaluationObject<REAL_T,EVAL_T>{
        Observation<REAL_T> observation;
    };
    
}


#endif	/* FLEET_HPP */

