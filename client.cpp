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

int ORO_main(int argc, char** argv)
{
  // Uncomment to debug RTT_COMPONENT_PATH
  //std::string RTT_COMPONENT_PATH;
  //RTT_COMPONENT_PATH = std::string(getenv("RTT_COMPONENT_PATH"));
  //RTT::log(RTT::Error) << "RTT_COMPONENT_PATH: " << RTT_COMPONENT_PATH <<std::endl;
  //RTT::ComponentLoader::Instance()->setComponentPath(RTT_COMPONENT_PATH);

  // Setup Corba:
  TaskContextProxy::InitOrb(argc, argv);
  //RTT::plugin::PluginLoader::Instance()->loadTypekits("rtt");

  // Get a pointer to the component above
  OCL::CorbaDeploymentComponent client_deployer("client_deployer");
  
  // Load the component using the CORBA factory
  // This is similar to constructing a TaskContextProxy manually like so:
  //    TaskContext* component = TaskContextProxy::Create( "gazebo" );
  //    dc.addPeer(component);
  client_deployer.loadComponent("server_deployer","CORBA");
  
  // Need to import the typekit on the server
  client_deployer.import("kdl_typekit");

  // Interface it:
  OCL::TaskBrowser browse( &client_deployer );
  browse.loop();

  // Cleanup Corba:
  TaskContextProxy::DestroyOrb();
  return 0;
} 


