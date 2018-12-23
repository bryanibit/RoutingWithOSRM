#ifndef OSRM_LIB_CLASS_LIBRARY_H
#define OSRM_LIB_CLASS_LIBRARY_H

#include "osrm/match_parameters.hpp"
#include "osrm/nearest_parameters.hpp"
#include "osrm/route_parameters.hpp"
#include "osrm/table_parameters.hpp"
#include "osrm/trip_parameters.hpp"

#include "osrm/coordinate.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/json_container.hpp"

#include "osrm/osrm.hpp"
#include "osrm/status.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iomanip>

namespace routing_ns{

    using namespace osrm;
    class routing{

    public:
        //routing():config(){}
        //routing();
        //~routing();

        int Config_Routing(std::string osrm_file, bool use_shared_memory, osrm::EngineConfig::Algorithm alg);

        int Parameter_Routing(std::string RNDF_File, bool only_normal);

        bool Start_Routing();


        int Aquire_points(std::vector<std::vector<double>>& vector, std::string result_position);

        template <typename T, typename V>
        int Filter_RNDF(T&& file, V&& vector);

        template <typename T, typename V>
        int All_RNDF(T&& file, V&& vector);

    private:
        osrm::EngineConfig config_;
        osrm::RouteParameters params_;
        //osrm::OSRM osrm_;
        osrm::json::Object result_;
    };
}

#endif