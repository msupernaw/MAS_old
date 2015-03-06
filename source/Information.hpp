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
#include "Fleet.hpp"
#include "Survey.hpp"
#include "Study.hpp"
#include "IoStream.hpp"

#include "support/rapidjson/include/rapidjson/document.h"
namespace mas {

    /**
     * Class to hold information about a models 
     * configuration. 
     */
    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Information : public EvaluationObject<REAL_T, EVAL_T> {
        std::string model_type;
        std::string name;
        Structure<REAL_T, EVAL_T> structure; //model structure,ie age-based, length-based, stage-based, etc
        // hold a list of estimable parameters for the population analysis
        std::vector<std::pair<EVAL_T*, int> > estimable_parameters;
        //store areas by name
        std::map<std::string, Location<REAL_T, EVAL_T> > areas;
        //store in comments by name
        std::vector<std::string> model_comments; //additional information, used for report generation
        std::vector<std::string> data_comments; //additional information, used for report generation

        uint32_t number_of_years;
        uint32_t number_of_seasons;
        uint32_t number_of_fleets;
        uint32_t number_of_surveys;
        uint32_t number_of_areas;
        uint32_t number_of_age_groups;
        uint32_t number_of_size_groups;
        uint32_t number_of_stage_groups;
        uint32_t number_of_gender_groups;
        uint32_t number_of_studies;

        std::vector<Fleet<REAL_T, EVAL_T> > fleets;
        std::vector<Survey<REAL_T, EVAL_T> > surveys;
        std::vector<Study<REAL_T, EVAL_T> > studies;
    public:

        Information() :
        number_of_age_groups(0),
        number_of_areas(0),
        number_of_fleets(0),
        number_of_gender_groups(0),
        number_of_seasons(0),
        number_of_size_groups(0),
        number_of_stage_groups(0),
        number_of_studies(0),
        number_of_surveys(0),
        number_of_years(0) {
        }

        uint32_t GetNumberOfAgeGroups() const {
            return number_of_age_groups;
        }

        uint32_t GetNumberOfAreas() const {
            return number_of_areas;
        }

        uint32_t GetNumberOfFleets() const {
            return number_of_fleets;
        }

        uint32_t GetNumberOfGenderGroups() const {
            return number_of_gender_groups;
        }

        uint32_t GetNumberOfSeasons() const {
            return number_of_seasons;
        }

        uint32_t GetNumberOfSizeGroups() const {
            return number_of_size_groups;
        }

        uint32_t GetNumberOfStageGroups() const {
            return number_of_stage_groups;
        }

        uint32_t GetNumber_of_studies() const {
            return number_of_studies;
        }

        uint32_t GetNumberOfSurveys() const {
            return number_of_surveys;
        }

        uint32_t GetNumberOfYears() const {
            return number_of_years;
        }

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
            rapidjson::Document d;
            d.Parse<0>(ss.str().c_str());
            for (rapidjson::Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
                if (std::string(itr->name.GetString()) == "name") {
                    this->name = std::string(itr->value.GetString());
                }
                
                if (std::string(itr->name.GetString()) == "data") {
                    HandleData(itr);
                }
                if (std::string(itr->name.GetString()) == "comment") {
                    this->model_comments.push_back(std::string(itr->value.GetString()));
                }
            }
            this->Prepare();
        }

        std::string ToString()const {
            std::stringstream ss;
            ss<<"Model Name: "<<this->name<<"\n";
            ss << "Model Type: " << this->structure.ToString() << "\n";
            switch (this->structure.structure_type) {

                case Structure<REAL_T, EVAL_T>::AGE:
                    ss << "Number of Age Groups: " << this->number_of_age_groups << "\n";
                    break;
                case Structure<REAL_T, EVAL_T>::LENGTH:
                    ss << "Number of Size Groups: " << this->number_of_size_groups << "\n";
                    break;
                case Structure<REAL_T, EVAL_T>::STAGE:
                    ss << "Number of Stage Groups: " << this->number_of_stage_groups << "\n";
                default:
                    break;

            }

            ss << "Number of Fleets: " << this->number_of_fleets << "\n";
            ss << "Number of Surveys: " << this->number_of_surveys << "\n";
            ss << "Number of Studies: " << this->number_of_studies << "\n";
            typedef typename std::map<std::string, Location<REAL_T, EVAL_T> >::const_iterator location_it;

            for (location_it it = this->areas.begin();
                    it != this->areas.end(); ++it) {
                ss << it->second.ToString();
            }

            if (this->model_comments.size() > 0) {
                ss << "Model Comments:\n";
                for (int i = 0; i < this->model_comments.size(); i++) {
                    ss << " -" << this->model_comments[i] << "\n";
                }
                ss << "\n";
            }

            if (this->data_comments.size() > 0) {
                ss << "Data Comments:\n";
                for (int i = 0; i < this->data_comments.size(); i++) {
                    ss << " -" << this->data_comments[i] << "\n";
                }
                ss << "\n";
            }


            for (int i = 0; i < fleets.size(); i++) {
                ss << fleets[i].ToString() << "\n";
            }

            for (int i = 0; i < surveys.size(); i++) {
                ss << surveys[i].ToString() << "\n";
            }


            return ss.str();
        }

        /**
         * Verify the configuration 
         * of the information class.
         */
        void Verify() {

        }

    private:

        void Prepare() {
            for (int i = 0; i < fleets.size(); i++) {
                fleets[i].LoadData();
            }

            for (int i = 0; i < surveys.size(); i++) {
                surveys[i].LoadData();
            }
        }

        void HandleData(const rapidjson::Value::ConstMemberIterator& itr) {
            for (rapidjson::Value::ConstMemberIterator ditr = itr->value.MemberBegin(); ditr != itr->value.MemberEnd(); ++ditr) {

                if (std::string(ditr->name.GetString()) == "comment") {
                    this->data_comments.push_back(std::string(ditr->value.GetString()));
                }

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
                if (std::string(ditr->name.GetString()) == "observations") {
                    this->HandleObservations(ditr);
                }

                if (std::string(ditr->name.GetString()) == "fleet") {
                    this->HandleFleet(ditr);
                }

                if (std::string(ditr->name.GetString()) == "survey") {
                    this->HandleSurvey(ditr);
                }

                if (std::string(ditr->name.GetString()) == "study") {
                    this->HandleStudy(ditr);
                }


            }

        }

        void HandleArea(const rapidjson::Value::ConstMemberIterator& itr) {
            Location<REAL_T, EVAL_T> area;

            for (rapidjson::Value::ConstMemberIterator aitr = itr->value.MemberBegin(); aitr != itr->value.MemberEnd(); ++aitr) {

                if (std::string(aitr->name.GetString()) == "name") {
                    area.SetName(aitr->value.GetString());
                }

                if (std::string(aitr->name.GetString()) == "polygon") {
                    this->HandlePolygon(aitr, area);
                }

            }

            this->areas[area.GetName()] = area;
        }

        void HandlePolygon(const rapidjson::Value::ConstMemberIterator& itr,
                Location<REAL_T, EVAL_T>& area) {
            Polygon<REAL_T> polygon;

            for (rapidjson::Value::ConstMemberIterator pitr = itr->value.MemberBegin(); pitr != itr->value.MemberEnd(); ++pitr) {
                if (std::string(pitr->name.GetString()) == "point") {
                    this->HandlePoint(pitr, polygon);
                }
            }

            area.SetArea(polygon);

        }

        void HandlePoint(const rapidjson::Value::ConstMemberIterator& itr,
                Polygon<REAL_T>& polygon) {
            REAL_T x = 0.0;
            REAL_T y = 0.0;
            bool has_x = false;
            bool has_y = false;
            for (rapidjson::Value::ConstMemberIterator pitr = itr->value.MemberBegin(); pitr != itr->value.MemberEnd(); ++pitr) {

                if (std::string(pitr->name.GetString()) == "x") {
                    has_x = true;
                    x = static_cast<REAL_T> (pitr->value.GetDouble());
                }

                if (std::string(pitr->name.GetString()) == "x") {
                    has_y = true;
                    y = static_cast<REAL_T> (pitr->value.GetDouble());
                }

            }

            if (has_x && has_y) {
                polygon.AddPoint(Point<REAL_T>(x, y));
            } else {
                std::cout << "invalid point!";
                exit(0);
            }

        }

        void HandleObservations(const rapidjson::Value::ConstMemberIterator & itr) {
            for (rapidjson::Value::ConstMemberIterator ditr = itr->value.MemberBegin(); ditr != itr->value.MemberEnd(); ++ditr) {
                if (std::string(ditr->name.GetString()) == "fleet") {
                    this->HandleFleet(ditr);
                }

                if (std::string(ditr->name.GetString()) == "survey") {
                    this->HandleSurvey(ditr);
                }

                if (std::string(ditr->name.GetString()) == "study") {
                    this->HandleStudy(ditr);
                }
            }
        }

        void HandleFleet(const rapidjson::Value::ConstMemberIterator & itr) {
            this->number_of_fleets++;
            Fleet<REAL_T, EVAL_T> fleet;
            fleet.SetInfo(this);

            for (rapidjson::Value::ConstMemberIterator ditr = itr->value.MemberBegin();
                    ditr != itr->value.MemberEnd(); ++ditr) {

                if (std::string(ditr->name.GetString()) == "name") {
                    fleet.SetName(std::string(ditr->value.GetString()));
                }

                if (std::string(ditr->name.GetString()) == "source") {
                    fleet.SetDataSource(std::string(ditr->value.GetString()));
                }

                if (std::string(ditr->name.GetString()) == "selectivity") {
                    fleet.SetSelectivity(std::string(ditr->value.GetString()));
                }

                if (std::string(ditr->name.GetString()) == "order") {
                    fleet.SetDataOrder(std::string(ditr->value.GetString()));
                }

            }

            fleets.push_back(fleet);
        }

        void HandleSurvey(const rapidjson::Value::ConstMemberIterator & itr) {
            this->number_of_surveys++;
            Survey<REAL_T, EVAL_T> survey;
            survey.SetInfo(this);

            for (rapidjson::Value::ConstMemberIterator ditr = itr->value.MemberBegin();
                    ditr != itr->value.MemberEnd(); ++ditr) {

                if (std::string(ditr->name.GetString()) == "name") {
                    survey.SetName(std::string(ditr->value.GetString()));
                }

                if (std::string(ditr->name.GetString()) == "source") {
                    survey.SetDataSource(std::string(ditr->value.GetString()));
                }

                if (std::string(ditr->name.GetString()) == "selectivity") {
                    survey.SetSelectivity(std::string(ditr->value.GetString()));
                }

                if (std::string(ditr->name.GetString()) == "order") {
                    survey.SetDataOrder(std::string(ditr->value.GetString()));
                }

            }

            surveys.push_back(survey);
        }

        void HandleStudy(const rapidjson::Value::ConstMemberIterator & itr) {
            this->number_of_studies++;
        }

        void HandlePopulationModel(const rapidjson::Value::ConstMemberIterator & itr) {
            for (rapidjson::Value::ConstMemberIterator ditr = itr->value.MemberBegin();
                    ditr != itr->value.MemberEnd(); ++ditr) {


            }
        }



    };

}



#endif	/* INFORMATION_HPP */

