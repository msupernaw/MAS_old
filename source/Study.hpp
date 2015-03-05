/* 
 * File:   Study.hpp
 * Author: Matthew
 *
 * Created on March 5, 2015, 10:55 AM
 */

#ifndef STUDY_HPP
#define	STUDY_HPP

namespace mas {

    template<typename REAL_T, typename EVAL_T>
    class Study : public EvaluationObject<REAL_T, EVAL_T> {
        Observation<REAL_T> observation;
    };

}


#endif	/* STUDY_HPP */

