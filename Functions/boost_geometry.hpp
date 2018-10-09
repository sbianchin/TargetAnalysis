/* 
 * Created by Jack Hong on 2018-08-10. (jhong@alumni.ubc.ca)
 */
#pragma once 

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point_t;
typedef bg::model::multi_point<point_t> mpoint_t;
typedef bg::model::polygon<point_t> polygon_t;
typedef bg::model::segment<point_t> segment_t;
