/* 
 * File:   Object.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:16 AM
 */

#ifndef OBJECT_HPP
#define	OBJECT_HPP

#include <string>

namespace mas {

    class Object {
    public:

        virtual void Initialize(Information* info){
            
        }
        
        virtual std::string ToString() {
            return "";
        }

    };
}


#endif	/* OBJECT_HPP */

