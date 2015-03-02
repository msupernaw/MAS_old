/* 
 * File:   Observation.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:57 AM
 */

#ifndef OBSERVATION_HPP
#define	OBSERVATION_HPP

#include "Object.hpp"

namespace mas {

    template<typename REAL_T>
    class Observation : public Object {
        uint32_t time_max;
        uint32_t number_of_fleets;
        uint32_t number_of_surveys;
        uint32_t number_of_areas;
        uint32_t number_of_age_groups;
        uint32_t number_of_genders;
    };


}



#endif	/* OBSERVATION_HPP */

