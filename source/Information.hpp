/* 
 * File:   Information.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 12:39 PM
 */

#ifndef INFORMATION_HPP
#define	INFORMATION_HPP

#include <fstream>
#include <sstream>
#include <vector>

#include "Object.hpp"
#include "Location.hpp"
#include "Structure.hpp"
#include "support/rapidjson/include/rapidjson/document.h"
namespace mas {

    /**
     * Class to hold information about a models 
     * configuration. 
     */
    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Information : public EvaluationObject<REAL_T, EVAL_T> {
        // hold a list of estimable parameters for the population analysis
        std::vector<std::pair<EVAL_T*, int> > estimable_parameters;
        std::vector<Location<REAL_T, EVAL_T> > areas;
        std::string model_type;
        Structure<REAL_T, EVAL_T> structure;

    public:

        /**
         * Register a parameter as estimable. Simply adds a pointer to the 
         * parameter to a list along with its phase of optimization. First 
         * phase is 0.  
         * @param parameter
         * @param phase
         */
        void RegisterEstimable(EVAL_T* parameter, int phase = 0) {
            estimable_parameters.push_back(std::pair<EVAL_T*, int>(parameter, phase));
        }

        /**
         * Load a model configuration file in JSON
         * format.
         * @param file
         */
        void LoadModel(const std::string& file) {

            std::ifstream in;
            in.open(file.c_str());

            if (!in.good()) {
                std::cout << file << " not found.";
                exit(0);
            }

            std::stringstream ss;

            std::string line;
            while (in.good()) {
                std::getline(in, line);
                ss << line << "\n";
            }
            std::cout << ss.str() << std::endl;
            rapidjson::Document d;
            d.Parse<0>(ss.str().c_str());
            for (rapidjson::Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
                std::cout << itr->name.GetString() << "\n";
                if (std::string(itr->name.GetString()) == "data") {
                    HandleData(itr);
                }
            }
        }

        std::string ToString()const {
            return this->model_type;
        }

        /**
         * Verify the configuration 
         * of the information class.
         */
        void Verify() {

        }

    private:

        void HandleData(const rapidjson::Value::ConstMemberIterator& itr) {
            for (rapidjson::Value::ConstMemberIterator ditr = itr->value.MemberBegin(); ditr != itr->value.MemberEnd(); ++ditr) {
                if (std::string(ditr->name.GetString()) == "structure") {
                    this->model_type = ditr->value.GetString();

                    if (this->model_type == "age") {
                        this->structure.structure_type = Structure<REAL_T, EVAL_T>::AGE;
                    } else if (this->model_type == "length") {
                        this->structure.structure_type = Structure<REAL_T, EVAL_T>::LENGTH;
                    } else if (this->model_type == "stage") {
                        this->structure.structure_type = Structure<REAL_T, EVAL_T>::STAGE;
                    } else {
                        std::cout << "Unknown model structure type " << this->model_type << "\n";
                        exit(0);
                    }
                }

                if (std::string(ditr->name.GetString()) == "area") {
                    this->HandleArea(ditr);
                }
            }
        }

        void HandleArea(const rapidjson::Value::ConstMemberIterator& itr) {
            for (rapidjson::Value::ConstMemberIterator aitr = itr->value.MemberBegin(); aitr != itr->value.MemberEnd(); ++aitr) {

                std::cout << aitr->name.GetString() << "\n";
            }
        }





    };

}



#endif	/* INFORMATION_HPP */

