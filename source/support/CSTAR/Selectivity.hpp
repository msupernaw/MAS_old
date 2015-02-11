/* 
 * File:   Selectivity.hpp
 * Author: matthewsupernaw
 *
 * Created on December 16, 2014, 1:46 PM
 */

#ifndef SELECTIVITY_HPP
#define	SELECTIVITY_HPP


/*!
 * Selectivity module for CSTAR. Classes and functions that are in the 
 * namespace cstar::selex can be used in age-based or size-based modeling. 
 * 
 * <br>
 * Classes and functions used for age-based models only are in namespace 
 * cstar::selex::age_based and Classes and functions used for size-based 
 * models only are in namespace cstar::selex::size_based/
 * 
 */
namespace cstar {

    namespace selex {

        template<class T>
        class SelectivityBase {
        };

        template<class T>
        class Constant : public SelectivityBase<T> {
        };

        template<class T>
        class Logistic : public SelectivityBase<T> {
        };

        template<class T>
        const T logistic(const T& li, const T& b1, const T& b2){
            
        }
        
        template<class T>
        class DoubleLogistic : public SelectivityBase<T> {
        };

        template<class T>
        const T double_logistic(){
            
        }
        
        template<class T>
        class DoubleLogisticWithSmoothTransitions : public selex::SelectivityBase<T> {
        };
        
        template<class T>
        const T double_logistic_s_t(){
            
        }

        namespace age_based {

            template<class T>
            class Age : public selex::SelectivityBase<T> {
            };

            template<class T>
            class EachAge : public selex::SelectivityBase<T> {
            };

            template<class T>
            class AccendingGaussian : public selex::SelectivityBase<T> {
            };

            template<class T>
            class AugmentLogistic : public selex::SelectivityBase<T> {
            };



        }

        namespace size_based {

            template<class T>
            class FlatMiddlePowerUpPowerDown : public selex::SelectivityBase<T> {
            };

            template<class T>
            class LinearSegments : public selex::SelectivityBase<T> {
            };



        }


        namespace male {

            template<class T>
            class MalesRelativeToFemales : public selex::SelectivityBase<T> {
            };

        }

        namespace retention {

        }
    }
}

#endif	/* SELECTIVITY_HPP */

