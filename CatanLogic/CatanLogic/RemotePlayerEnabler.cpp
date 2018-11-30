#include "RemotePlayerEnabler.h"



RemotePlayerEnabler::RemotePlayerEnabler()
{
}

RemotePlayerEnabler::RemotePlayerEnabler(Networking * pkgSender_)
{
	init();
	setPkgSender(pkgSender_);
}


RemotePlayerEnabler::~RemotePlayerEnabler()
{
}
