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
            STAGE,
            UNKNOWN
        };

        StructureType structure_type;

        /**
         * Default constructor.
         * 
         * The default structure type is unknown.
         */
        Structure(StructureType type = UNKNOWN) : structure_type(type) {

        }

        operator StructureType() {
            return this->structure_type;
        }

        operator StructureType() const {
            return this->structure_type;
        }
        
        std::string ToString()const{
            switch(this->structure_type){
                case AGE:
                    return "age structured model";
                case LENGTH:
                    return "length structured model";
                case STAGE:
                    return "stage structured model";
                default:
                    return "model structure unknown";
            }
        }
    };

}


#endif	/* STRUCTURE_HPP */

