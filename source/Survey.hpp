/* 
 * File:   Survey.hpp
 * Author: Matthew
 *
 * Created on March 5, 2015, 10:54 AM
 */

#ifndef SURVEY_HPP
#define	SURVEY_HPP

namespace mas{
    
    template<typename REAL_T, typename EVAL_T>
    class Survey : public EvaluationObject<REAL_T,EVAL_T>{
        Observation<REAL_T> observation;
    };
    
}

#endif	/* SURVEY_HPP */

