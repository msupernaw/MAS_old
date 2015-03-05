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
#include <map>
#include <string>

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
        std::string model_type;
        Structure<REAL_T, EVAL_T> structure; //model structure,ie age-based, length-based, stage-based, etc
        // hold a list of estimable parameters for the population analysis
        std::vector<std::pair<EVAL_T*, int> > estimable_parameters;
        //store areas by name
        std::map<std::string, Location<REAL_T, EVAL_T> > areas;
        //store in comments by name
        std::map<std::string, std::string> comments; //additional information, used for report generation

        uint32_t number_of_years;
        uint32_t number_of_seasons;
        uint32_t number_of_fleets;
        uint32_t number_of_surveys;
        uint32_t number_of_areas;
        uint32_t number_of_age_groups;
        uint32_t number_of_size_groups;
        uint32_t number_of_gender_groups;


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
                if (std::string(ditr->name.GetString()) == "years") {
                    this->number_of_years = ditr->value.GetInt();
                }

                if (std::string(ditr->name.GetString()) == "seasons") {
                    this->number_of_seasons = ditr->value.GetInt();
                }

                if (std::string(ditr->name.GetString()) == "ages") {
                    this->number_of_age_groups = ditr->value.GetInt();
                }

                if (std::string(ditr->name.GetString()) == "sizes") {
                    this->number_of_size_groups = ditr->value.GetInt();
                }

                if (std::string(ditr->name.GetString()) == "genders") {
                    this->number_of_gender_groups = ditr->value.GetInt();
                }

                if (std::string(ditr->name.GetString()) == "area") {
                    this->HandleArea(ditr);
                }
            }

            std::cout << this->structure << "\n";
        }

        void HandleArea(const rapidjson::Value::ConstMemberIterator& itr) {
            Location<REAL_T, EVAL_T> area;

            for (rapidjson::Value::ConstMemberIterator aitr = itr->value.MemberBegin(); aitr != itr->value.MemberEnd(); ++aitr) {

                if (std::string(aitr->name.GetString()) == "name") {
                    area.SetName(aitr->value.GetString());
                }

                if (std::string(aitr->name.GetString()) == "polygon") {
                    this->HandlePolygon(itr, area);
                }

            }
        }

        void HandlePolygon(const rapidjson::Value::ConstMemberIterator& itr,
                Location<REAL_T, EVAL_T>& area) {
            Polygon<REAL_T> polygon;



        }

        void HandlePoint(const rapidjson::Value::ConstMemberIterator& itr,
                Polygon<REAL_T>& polygon) {

        }

        void HandleFleet(const rapidjson::Value::ConstMemberIterator& itr) {

        }

        void HandleSurvey(const rapidjson::Value::ConstMemberIterator& itr) {

        }

        void HandleStudy(const rapidjson::Value::ConstMemberIterator& itr) {

        }

        void HandlePopulationModel(const rapidjson::Value::ConstMemberIterator& itr) {

        }



    };

}



#endif	/* INFORMATION_HPP */

