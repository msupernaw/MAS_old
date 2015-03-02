/* 
 * File:   Information.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 12:39 PM
 */

#ifndef INFORMATION_HPP
#define	INFORMATION_HPP


namespace mas {

    /**
     * Class to hold information about a models 
     * configuration. 
     */
    template<typename REAL_T, typename EVAL_T>
    class Information {
        // hold a list of estimable parameters for the population analysis
        std::vector<std::pair<EVAL_T*, int> > estimable_parameters;
        
        
        public:
            
            /**
             * Register a model as estimable. Simply adds pointer to the 
             * parameter to a list along with its phase. First phase is 0.  
             * @param parameter
             * @param phase
             */
            void RegisterEstimable(EVAL_T* parameter, int phase = 0){
                estimable_parameters.push_back(std::pair<EVAL_T*,int>(parameter,phase));
            }




    };

}



#endif	/* INFORMATION_HPP */

