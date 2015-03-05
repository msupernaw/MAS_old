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

    
    /**
     *<br> Observation class
     *<br> 
     *<br> The Observation class is the set of observed data for the metapopulation 
     *<br> and fishery system. This includes fisheries data, survey data, and 
     *<br> information from studies like estimates of growth, maturity, or fecundity
     *<br> curves or individual observations of tagging or ageing data. Model 
     *<br> parameters are fit to the observed data through interface with the 
     *<br> subpopulation, environment, and information classes. The observation class
     *<br> is comprised of the basic data and the objects used to store this 
     *<br> information and interface with the subpopulation, environment, and 
     *<br> information classes. 
     */
    template<typename REAL_T>
    class Observation : public Object {
        typedef std::vector<REAL_T> data_vector;
       
    public:
        uint32_t time_max;
        uint32_t number_of_seasons;
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

        

    };


}



#endif	/* OBSERVATION_HPP */

