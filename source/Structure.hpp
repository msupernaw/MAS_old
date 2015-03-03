/* 
 * File:   Structure.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 12:33 PM
 */

#ifndef STRUCTURE_HPP
#define	STRUCTURE_HPP

#include "Object.hpp"

namespace mas {

    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Structure : public EvaluationObject<REAL_T, EVAL_T> {
    public:

        enum StructureType {
            AGE = 0,
            LENGTH,
            STAGE
        };

        StructureType structure_type;

        /**
         * Default constructor.
         * 
         * The default structure type is age.
         */
        Structure(StructureType type = AGE) : structure_type(type) {

        }

        operator StructureType() {
            return this->structure_type;
        }

        operator StructureType() const {
            return this->structure_type;
        }
    };

}


#endif	/* STRUCTURE_HPP */

