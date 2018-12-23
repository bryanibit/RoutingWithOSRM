#include "routing.hpp"
#include <stdlib.h>
namespace routing_ns{

        using namespace osrm;

        //routing::routing(){}

        int routing::Config_Routing(std::string osrm_file, bool use_shared_memory, osrm::EngineConfig::Algorithm alg)
        {
            config_.storage_config = {osrm_file};
            config_.use_shared_memory = false;
            config_.algorithm = EngineConfig::Algorithm::MLD;
        }

        int routing::Parameter_Routing(std::string RNDF_File, bool only_normal)
        {
            params_.annotations = true;
            using namespace osrm::engine::api;
            params_.annotations_type = RouteParameters::AnnotationsType::Nodes;
            params_.geometries = RouteParameters::GeometriesType::GeoJSON;
            params_.overview = RouteParameters::OverviewType::Full;
            std::vector<double> Positions;
            if(only_normal)
            {
                Filter_RNDF(RNDF_File, Positions);
            }
            else
            {
                All_RNDF(RNDF_File, Positions);
            }
            for (int i = 0; i < Positions.size(); i = i+2)
            {
                double lon = 0, lat = 0;
                if(i%2 == 0)
                {
                    lon = Positions[i];
                    lat = Positions[i+1];
                }
                else
                {
                    lon = Positions[i+1];
                    lat = Positions[i];
                }

                if(lon*lat != 0)
                    params_.coordinates.push_back({util::FloatLongitude{lon}, util::FloatLatitude{lat}});
            }
        }

        bool routing::Start_Routing()
        {
            const osrm::OSRM osrm_{config_};
            const auto status = osrm_.Route(params_, result_);
            if (status == Status::Ok)
            {
                std::cout << "Routing is successful\n";
                return true;
            }

            else
            {
                std::cout << "Routing fail\n";
                return false;
            }
        }


        int routing::Aquire_points(std::vector<std::vector<double>>& coordinate_vec, std::string result_position)
        {
            auto &routes = result_.values["routes"].get<json::Array>();

            // Let's just use the first route
            auto &route = routes.values.at(0).get<json::Object>();
            const auto distance = route.values["distance"].get<json::Number>().value;
            const auto duration = route.values["duration"].get<json::Number>().value;
            // test-
            const auto &legs = route.values["legs"].get<json::Array>();
            auto coordinates = route.values["geometry"].get<json::Object>().values["coordinates"].get<json::Array>().values;
            //std::vector<std::vector<double>> coordinate_vec;
            for(auto coordinate: coordinates)
            {
                auto co_pair = coordinate.get<json::Array>().values;
                auto longitude = co_pair[0].get<json::Number>().value;
                auto latitude = co_pair[1].get<json::Number>().value;
                std::cout << "Nodes of Longitude: " << std::setprecision(10) << longitude <<
                          " and Latitude: " << latitude << std::endl;
                coordinate_vec.emplace_back(std::vector<double>{longitude, latitude});
            }

            std::ofstream onfile;

            onfile.open(result_position, std::ios::out);

            for(auto c: coordinate_vec)
            {
                onfile << std::setprecision(9) << c[0] << ","  << c[1] << std::endl;
            }


            std::cout << "Successfully write node id to file.\n";
            onfile.close();

            if (distance == 0 || duration == 0)
            {
                std::cout << "Note: distance or duration is zero. ";
                std::cout << "You are probably doing a query outside of the OSM extract.\n\n";
            }

            std::cout << "Distance: " << distance << " meter\n";
            std::cout << "Duration: " << duration << " seconds\n";

            const auto code = result_.values["code"].get<json::String>().value;
            const auto message = result_.values["message"].get<json::String>().value;
            std::cout << "Code: " << code << "\n";
            std::cout << "Message: " << code << "\n";

            return EXIT_SUCCESS;
        }


        template <typename T, typename V>
        int routing::Filter_RNDF(T&& file, V&& position_vec)
        {
            std::ifstream rdfile;
            rdfile.open(file);
            if(!rdfile.is_open())
            {
                std::cerr << "Invalid RNDF\n";
                return EXIT_FAILURE;
            }
            std::string line;
            while(std::getline(rdfile, line))
            {
                std::vector<std::string> lineLL;
                boost::algorithm::split(lineLL, line, boost::algorithm::is_any_of(" "));
                if(std::stoi(lineLL[4]) < 3)
                {
                    position_vec.emplace_back(std::stod(lineLL[1]));
                    position_vec.emplace_back(std::stod(lineLL[2]));
                }
            }
        }

        template <typename T, typename V>
        int routing::All_RNDF(T&& file, V&& position_vec)
        {
            std::ifstream rdfile;
            rdfile.open(file);
            if(!rdfile.is_open())
            {
                std::cerr << "Invalid RNDF\n";
                return EXIT_FAILURE;
            }
            std::string line;
            while(std::getline(rdfile, line))
            {
                std::vector<std::string> lineLL;
                boost::algorithm::split(lineLL, line, boost::algorithm::is_any_of(" "));
                position_vec.emplace_back(std::stod(lineLL[1]));
                position_vec.emplace_back(std::stod(lineLL[2]));
            }
        }

    }