#include "routing.hpp"
#include <memory>
int main()
{
    using namespace routing_ns;
    std::shared_ptr<routing_ns::routing> route_plan = std::make_shared<routing_ns::routing>();

    route_plan->Config_Routing("/home/ugv-yu/GPP/osrm-backend/kyxz.osrm", false, osrm::EngineConfig::Algorithm::MLD);
    route_plan->Parameter_Routing("/home/ugv-yu/GPP/osrm-backend/example/plan_file2018.txt", true);
    
    if(route_plan->Start_Routing())
    {
    std::vector<std::vector<double>> V;
    route_plan->Aquire_points(V, "/home/ugv-yu/GPP/position_lib.txt");
    }
}
