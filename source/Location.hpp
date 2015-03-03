/* 
 * File:   Location.hpp
 * Author: Matthew
 *
 * Created on March 2, 2015, 10:26 AM
 */

#ifndef LOCATION_HPP
#define	LOCATION_HPP

#include <vector>

#include "Object.hpp"
#include "Subpopulation.hpp"

namespace mas {

    template<typename REAL_T>
    struct Point {
        REAL_T x;
        REAL_T y;

        Point() : x(0.0), y(0.0) {

        }

        Point(const REAL_T& x, const REAL_T& y) : x(x), y(y) {

        }

    };

    template<typename REAL_T>
    class Rectangle {
        REAL_T x;
        REAL_T y;
        REAL_T height;
        REAL_T width;
    };

    template<typename REAL_T>
    class Polygon {
    public:

        void AddPoint(const Point<REAL_T>& p) {
            points.push_back(p);
        }

        /**
         * Compute the area of this polygon. points must be entered in 
         * clockwise order.
         * 
         * @return 
         */
        REAL_T ComputeArea() {
            Sort();
            REAL_T area = static_cast<REAL_T> (0.0);
            uint32_t j = points.size() - 1;
            for (uint32_t i = 0; i < points.size(); i++) {
                area += (points[j].x + points[i].x)*(points[j].y - points[i].y);
                j = i;
            }
            return area / static_cast<REAL_T> (2.0);
        }

        Point<REAL_T> Centroid() {
            Point<REAL_T> centroid;
            REAL_T signedArea = 0.0;
            REAL_T x0 = 0.0; // Current vertex X
            REAL_T y0 = 0.0; // Current vertex Y
            REAL_T x1 = 0.0; // Next vertex X
            REAL_T y1 = 0.0; // Next vertex Y
            REAL_T a = 0.0; // Partial signed area

            // For all vertices except last
            int i = 0;
            for (i = 0; i < points.size() - 1; ++i) {
                x0 = points[i].x;
                y0 = points[i].y;
                x1 = points[i + 1].x;
                y1 = points[i + 1].y;
                a = x0 * y1 - x1*y0;
                signedArea += a;
                centroid.x += (x0 + x1) * a;
                centroid.y += (y0 + y1) * a;
            }

            // Do last vertex
            x0 = points[i].x;
            y0 = points[i].y;
            x1 = points[0].x;
            y1 = points[0].y;
            a = x0 * y1 - x1*y0;
            signedArea += a;
            centroid.x += (x0 + x1) * a;
            centroid.y += (y0 + y1) * a;

            signedArea *= 0.5;
            centroid.x /= (6.0 * signedArea);
            centroid.y /= (6.0 * signedArea);

            return centroid;
        }

    private:

        /**
         * Sort the points in this polygon to be in clockwise order.
         */
        void Sort() {
            std::cout << "Warning Polygon.Sort() not yet implemented!\n";
        }

        std::vector<Point<REAL_T> > points;




    };

    template<typename REAL_T, typename EVAL_T = REAL_T>
    class Location : public EvaluationObject<REAL_T,EVAL_T> {
        Polygon<REAL_T> area;
        std::vector<Polygon<REAL_T> > adjacent_areas;
        std::vector<Subpopulation< REAL_T, EVAL_T> > subpopulations;


    };

}
#endif	/* LOCATION_HPP */

