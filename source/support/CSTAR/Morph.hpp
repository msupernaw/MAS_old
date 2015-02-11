/* 
 * File:   Morph.hpp
 * Author: matthewsupernaw
 *
 * Created on December 16, 2014, 12:20 PM
 */

#ifndef MORPH_HPP
#define	MORPH_HPP

namespace ss {

    enum MorphType {
        MALE = 0,
        FEMALE,
        COMBINED
    }

    template<class T>
    class Morph {
        MorphType morph_type_m;

        std::vector<T> numbers_at_age_m;
        std::vector<T> observed_catch_m; //t x a x l
        std::vector<T> natural_mortality_m; // by age
        std::vector<T> spawning_biomass_m;
        std::vector<T> recruitment_m;
        std::vector<T> fishing_mortality_m;
        std::vector<T> retainable_biomass_m;
    };
    
   
    template<class T>
    class Selectivity {
    };

    template<class T>
    class Fishery {
        std::vector<Morph<T> > morphs_m;
        std::vector<Selectivity<T> > selectivityies; //
    };

    template<class T>
    class Region {
        std::vector<Fishery<T> > fisheries_m;
    };


}


#endif	/* MORPH_HPP */

