#include "requestor.h"


Requester::Requester()
{
}

Requester::~Requester()
{
}


SINGLETON_DEFINITION(RequesterManager)

RequesterManager::RequesterManager()
{
}

RequesterManager::~RequesterManager()
{
}

Requester* RequesterManager::create()
{
    return nullptr;
}