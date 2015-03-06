/* 
 * File:   Fleet.hpp
 * Author: Matthew
 *
 * Created on March 5, 2015, 10:52 AM
 */

#ifndef FLEET_HPP
#define	FLEET_HPP

#include "Object.hpp"
#include "Observation.hpp"
#include "IoStream.hpp"
#include "Information.hpp"

namespace mas {

    template<typename REAL_T, typename EVAL_T>
    class Fleet : public EvaluationObject<REAL_T, EVAL_T> {
    public:
        std::string name;
        std::string data_source;
        std::string selectivity;
        std::string data_order;
        Observation<REAL_T> observation;

        std::string GetName() const {
            return name;
        }

        void SetName(std::string name) {
            this->name = name;
        }

        std::string GetDataSource() const {
            return data_source;
        }

        void SetDataSource(std::string data_source) {
            this->data_source = data_source;
        }

        Observation<REAL_T> GetObservation() const {
            return observation;
        }

        void SetObservation(Observation<REAL_T> observation) {
            this->observation = observation;
        }

        std::string GetSelectivity() const {
            return selectivity;
        }

        void SetSelectivity(std::string selectivity) {
            this->selectivity = selectivity;
        }

        std::string GetDataOrder() const {
            return data_order;
        }

        void SetDataOrder(std::string data_order) {
            this->data_order = data_order;
        }

        void LoadData() {
            //            std::cout << "Loading data for fleet name \"" << this->GetName() << "\"...\n";
            int years = this->GetInfo()->GetNumberOfYears();
            int seasons = this->GetInfo()->GetNumberOfSeasons();
            int age_groups = this->GetInfo()->GetNumberOfAgeGroups();

            std::vector<std::string> order;
            util::Tokenize(this->data_order, order, ",", true);
            StreamedDataFile<REAL_T> data(this->GetDataSource());
            for (int i = 0; i < order.size(); i++) {
                //                std::cout << order[i] << "\n";

                if (order[i] == "cpue") {

                    this->observation.fisheries_catch_per_unit_effort.resize(years);
                    for (int j = 0; j < this->observation.fisheries_catch_per_unit_effort.size(); j++) {
                        this->observation.fisheries_catch_per_unit_effort[j] = data.Next();
                    }
                    //                    continue;
                }


                if (order[i] == "numbers_at_age") {



                    if (seasons != 0) {
                        this->observation.fisheries_age_composition.resize(years * seasons * age_groups);
                    } else {
                        this->observation.fisheries_age_composition.resize(years * age_groups);
                    }

                    for (int j = 0; j < this->observation.fisheries_age_composition.size(); j++) {
                        this->observation.fisheries_age_composition[j] = data.Next();
                    }


                    //                    continue;
                }



            }


        }

        std::string ToString()const {
            std::stringstream ss;
            ss << "Fleet{\n";
            ss << "  name: " << this->GetName() << "\n";

            int years = this->GetInfo()->GetNumberOfYears();
            int seasons = this->GetInfo()->GetNumberOfSeasons();
            int age_groups = this->GetInfo()->GetNumberOfAgeGroups();

            std::vector<std::string> order;
            util::Tokenize(this->data_order, order, ",");

            ss << "  Data Order: " << this->data_order << "\n";

            for (int i = 0; i < order.size(); i++) {
                //                std::cout << order[i] << "\n";
                if (order[i] == "numbers_at_age") {
                    ss << "  numbers_at_age:\n";


                    if (seasons != 0) {

                        for (int y = 0; y < years; y++) {
                            for (int s = 0; s < seasons; s++) {
                                for (int a = 0; a < age_groups; a++) {
                                    ss << "  " << this->observation.fisheries_age_composition[(y * seasons * age_groups)+(s * age_groups) + a] << " ";
                                }
                            }
                            ss << "\n";
                        }


                    } else {
                        for (int y = 0; y < years; y++) {
                            for (int a = 0; a < age_groups; a++) {
                                ss << "  " << this->observation.fisheries_age_composition[(y * age_groups) + a] << " ";
                            }

                            ss << "\n";
                        }


                    }

                    continue;
                }

                if (order[i] == "cpue") {
                    //
                    ss << "  cpue:\n";
                    for (int j = 0; j < this->observation.fisheries_catch_per_unit_effort.size(); j++) {
                        ss << "  " << this->observation.fisheries_catch_per_unit_effort[j] << " ";
                    }
                    ss << "\n";
                    continue;
                }


            }

            ss << "}";

            return ss.str();
        }


    };

}


#endif	/* FLEET_HPP */

