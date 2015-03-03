/* 
 * File:   Observation.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:57 AM
 */

#ifndef OBSERVATION_HPP
#define	OBSERVATION_HPP

#include <vector>

#include "Location.hpp"

namespace mas {

    template<typename REAL_T>
    class Observation : public Object {
        typedef std::vector<REAL_T> data_vector;
       
    public:
        uint32_t time_max;
        uint32_t number_of_fleets;
        uint32_t number_of_surveys;
        uint32_t number_of_areas;
        uint32_t number_of_age_groups;
        uint32_t number_of_genders;
        //fisheries data
        data_vector fisheries_catch_biomass;
        data_vector fisheries_catch_numbers;
        data_vector fisheries_catch_per_unit_effort;
        data_vector fisheries_selectivity;
        data_vector fisheries_age_composition;
        data_vector fisheries_size_composition;
        data_vector fisheries_sex_composition;
        data_vector fisheries_mean_size;
        data_vector fisheries_tag_recovery;
        //survey data
        data_vector survey_catch_biomass;
        data_vector survey_catch_numbers;
        data_vector survey_catch_per_unit_effort;
        data_vector survey_selectivity;
        data_vector survey_age_composition;
        data_vector survey_size_composition;
        data_vector survey_sex_composition;
        data_vector survey_mean_size;
        data_vector survey_tag_recovery;
        //study data
        data_vector study_size_at_age;
        data_vector study_maturity_data;
        data_vector study_fecundity_data;
        data_vector study_length_weight_data;
        //area definitions
        std::vector<mas::Polygon<REAL_T> > areas;

    };


}



#endif	/* OBSERVATION_HPP */

