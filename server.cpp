#include <iostream>
#include <rtt/deployment/ComponentLoader.hpp>
#include <rtt/transports/corba/TaskContextServer.hpp>
#include <rtt/transports/corba/TaskContextProxy.hpp>
#include <rtt/plugin/PluginLoader.hpp>
#include <ocl/DeploymentComponent.hpp>
#include <ocl/CorbaDeploymentComponent.hpp>

#include <ocl/TaskBrowser.hpp>
#include <rtt/os/main.h>

using namespace RTT::corba;
using namespace RTT;

class Source : public RTT::TaskContext {
public:
  Source(std::string name) : RTT::TaskContext(name) {
    this->ports()->addPort("test",port_test);
    this->provides("sub1")->addPort("test1",sub_port_test);
    this->provides("sub1")->provides("sub2")->addPort("test12",sub_sub_port_test);
  }
  
  RTT::OutputPort<double> port_test;
  RTT::OutputPort<double> sub_port_test;
  RTT::OutputPort<double> sub_sub_port_test;
};

class Sink : public RTT::TaskContext {
public:
  Sink(std::string name) : RTT::TaskContext(name) {
    this->ports()->addPort("test",port_test);
    this->provides("sub1")->addPort("test1",sub_port_test);
    this->provides("sub1")->provides("sub2")->addPort("test12",sub_sub_port_test);
  }
  
  RTT::InputPort<double> port_test;
  RTT::InputPort<double> sub_port_test;
  RTT::InputPort<double> sub_sub_port_test;
};

int ORO_main(int argc, char** argv)
{
  std::string RTT_COMPONENT_PATH;
  
  // Initialize orb
  int oargc = 0;
  char **oargv = NULL;
  RTT::corba::TaskContextServer::InitOrb(oargc, oargv);
  // Propcess orb requests in a thread
  RTT::corba::TaskContextServer::ThreadOrb();

  // Create the components
  RTT_COMPONENT_PATH = std::string(getenv("RTT_COMPONENT_PATH"));
  RTT::log(RTT::Error) << "RTT_COMPONENT_PATH: " << RTT_COMPONENT_PATH <<std::endl;

  Source source("source"); 
  Sink sink("sink"); 
  OCL::DeploymentComponent server_deployer("server_deployer");
  server_deployer.addPeer(&source);
  server_deployer.addPeer(&sink);

  // Attach the taskcontext server to this component
  RTT::corba::TaskContextServer::Create( &server_deployer );
  RTT::corba::TaskContextServer::Create( &source );
  RTT::corba::TaskContextServer::Create( &sink );

  OCL::TaskBrowser browse( &server_deployer );
  browse.loop();

  return 0;
} 


