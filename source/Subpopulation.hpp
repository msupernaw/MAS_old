/* 
 * File:   Subpopulation.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:14 AM
 */

#ifndef SUBPOPULATION_HPP
#define	SUBPOPULATION_HPP

#include <vector>

#include "Object.hpp"
#include "Location.hpp"




namespace mas {

    template<typename REAL_T>
    class Observation;

    /**
     *<br> The subpopulation class follows the well-established premise of conservation of biomass
     *<br> (Russell 1931) within each area of the model. The general model of the time change, indexed by
     *<br>  t , in the biomass ( a,t B ) of the harvested subpopulation in each area, indexed by a , depends on
     *<br>  biomass increases due to somatic growth (G(a,t)), recruitment (R(a,t)), and immigration (I(a,t)) and
     *<br>  depends on biomass decreases due to natural deaths (D(a,t)), fishery yields (Y(a,t)), and emigration
     *<br>  (O(a,t) ) via
     *<br>  
     *<br>   B(a,t+1) = B(a,t) + [G(a,t) + R(a,t) + I(a,t)] - [D(a,t) + Y(a,t) + O(a,t)]
     * 
     *<br> 
     */
    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Subpopulation : public EvaluationObject<REAL_T, EVAL_T> {
        
        public:
            
        enum GrowthModel {
            LOGISISTIC = 0,
            VON_BERTALANFFLY,
            NONE
        };

        enum RecruitmentModel {
            BEVERTON_HOLT = 0,
            HOCKEY_STICK,
            SURVIVAL_BASED,
            NONE
        };

        enum SelectivityModel {
        };

        enum MaturityModel {
        };

        enum FecundityModel {
        };

        enum MortalityModel {
            POPE = 0,
            CONTINUOUS,
            NONE
        };
        private:
        
        uint32_t time_max; // max time dimension
        uint32_t age_max; // max age dimension
        uint32_t genders; // number of genders represented in this subpopulation
        std::vector<EVAL_T> B; // biomass{age x time}
        std::vector<EVAL_T> G; // growth{age x time}
        std::vector<EVAL_T> R; // recruitment{age x time}
        std::vector<EVAL_T> I; // immigration{age x time}
        std::vector<EVAL_T> D; // deaths{age x time}
        std::vector<EVAL_T> Y; // yield{age x time}
        std::vector<EVAL_T> O; // emigration{age x time}
        Observation<REAL_T>* observations; // a pointer to the observed data. 
        Location<REAL_T,EVAL_T>* location;//subpopulations current location
        bool has_fishery_data;
        bool has_survey_data;
        bool has_study_data;
        

        //sub models
        GrowthModel growth_model;
        RecruitmentModel recruitment_model;
        SelectivityModel selectivity_model;
        MaturityModel maturity_model;
        FecundityModel fecundity_model;
        MortalityModel mortality_model;
        
    public:


        const std::vector<EVAL_T>& GetBiomass() const {
            return B;
        }

        void SetBiomass(std::vector<EVAL_T> B) {
            this->B = B;
        }

        const std::vector<EVAL_T>& GetDeaths() const {
            return D;
        }

        void SetDeaths(std::vector<EVAL_T> D) {
            this->D = D;
        }

        const std::vector<EVAL_T>& GetGrowth() const {
            return G;
        }

        void SetGrowth(std::vector<EVAL_T> G) {
            this->G = G;
        }

        const std::vector<EVAL_T>& GetImmigration() const {
            return I;
        }

        void SetImmigration(std::vector<EVAL_T> I) {
            this->I = I;
        }

        const std::vector<EVAL_T>& GetEmigration() const {
            return O;
        }

        void SetEmigration(std::vector<EVAL_T> O) {
            this->O = O;
        }

        const std::vector<EVAL_T>& GetRecruitment() const {
            return R;
        }

        void SetRecruitment(std::vector<EVAL_T> R) {
            this->R = R;
        }

        const std::vector<EVAL_T>& GetYield() const {
            return Y;
        }

        void SetYield(std::vector<EVAL_T> Y) {
            this->Y = Y;
        }

        uint32_t GetAgeMax() const {
            return age_max;
        }

        void SetAgeMax(uint32_t age_max) {
            this->age_max = age_max;
        }

        uint32_t GetGenders() const {
            return genders;
        }

        void SetGenders(uint32_t genders) {
            this->genders = genders;
        }

        Observation<REAL_T>* GetObservations() const {
            return observations;
        }

        void SetObservations(Observation<REAL_T>* observations) {
            this->observations = observations;
        }

        uint32_t GetTimeMax() const {
            return time_max;
        }

        void SetTimeMax(uint32_t time_max) {
            this->time_max = time_max;
        }
        
        FecundityModel GetFecundityModel() const {
            return fecundity_model;
        }

        void SetFecundityModel(FecundityModel fecundity_model) {
            this->fecundity_model = fecundity_model;
        }

        GrowthModel GetGrowthModel() const {
            return growth_model;
        }

        void SetGrowthModel(GrowthModel growth_model) {
            this->growth_model = growth_model;
        }

        MaturityModel GetMaturityModel() const {
            return maturity_model;
        }

        void SetMaturityModel(MaturityModel maturity_model) {
            this->maturity_model = maturity_model;
        }

        MortalityModel GetMortalityModel() const {
            return mortality_model;
        }

        void SetMortalityModel(MortalityModel mortality_model) {
            this->mortality_model = mortality_model;
        }

        RecruitmentModel GetRecruitmentModel() const {
            return recruitment_model;
        }

        void SetRecruitmentModel(RecruitmentModel recruitment_model) {
            this->recruitment_model = recruitment_model;
        }

        SelectivityModel GetSelectivityModel() const {
            return selectivity_model;
        }

        void SetSelectivityModel(SelectivityModel selectivity_model) {
            this->selectivity_model = selectivity_model;
        }


    };

}


#endif	/* SUBPOPULATION_HPP */

