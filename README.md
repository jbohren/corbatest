RTT CORBA Test
==============

This is a simple example of CORBA-based remote RTT task browsing. It
demonstrates the minimal requirements for interacting with an RTT deployment
with non-standard types.

Some features of this example:
* The **server** instantiates several TaskContexts and attaches them to a
  DeploymentComponent called the "server\_deployer"
* The TaskContexts on the **server** are attached to TaskContextServers (this
  exposes them to CORBA access)
* The **client**'s DeploymentComponent is a CorbaDeploymentComponent to make it
  easier to create a TaskContextProxy representing the TaskContexts on the
  **server**, but this could also be done with a DeploymentComponent and manual
  creation of TaskContextProxys
* Both the **server** and **client** programs need _actual_
  DeploymentComponents in order to import the external typekits
* Both the **server** and **client** programs need to InitOrb, but the
  **server** uses TaskContextServer and the **client** uses TaskContextProxy.
  Additionally, only the **server** needs to run a CORBA thread.
