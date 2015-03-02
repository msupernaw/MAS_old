/* 
 * File:   Subpopulation.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:14 AM
 */

#ifndef SUBPOPULATION_HPP
#define	SUBPOPULATION_HPP

#include <vector>

#include "Object.hpp"
#include "Observation.hpp"



namespace mas {

    /**
     *<br> The subpopulation class follows the well-established premise of conservation of biomass
     *<br> (Russell 1931) within each area of the model. The general model of the time change, indexed by
     *<br>  t , in the biomass ( a,t B ) of the harvested subpopulation in each area, indexed by a , depends on
     *<br>  biomass increases due to somatic growth (G(a,t)), recruitment (R(a,t)), and immigration (I(a,t)) and
     *<br>  depends on biomass decreases due to natural deaths (D(a,t)), fishery yields (Y(a,t)), and emigration
     *<br>  (O(a,t) ) via
     *<br>  
     *<br>   B(a,t+1) = B(a,t) + [G(a,t) + R(a,t) + I(a,t)] - [D(a,t) + Y(a,t) + O(a,t)]
     * 
     *<br> 
     */
    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Subpopulation : public Object {
        uint32_t time_max; // max time dimension
        uint32_t age_max; // max age dimension
        uint32_t genders; // number of genders represented in this subpopulation
        std::vector<EVAL_T> B; // biomass{age x time}
        std::vector<EVAL_T> G; // growth{age x time}
        std::vector<EVAL_T> R; // recruitment{age x time}
        std::vector<EVAL_T> I; // immigration{age x time}
        std::vector<EVAL_T> D; // deaths{age x time}
        std::vector<EVAL_T> Y; // yield{age x time}
        std::vector<EVAL_T> O; // emigration{age x time}
        Observation<REAL_T>* observations;
        
    public:





    };

}


#endif	/* SUBPOPULATION_HPP */

