#pragma once
#include <iostream>
#include <vector>

class ROV;
class TURTLE;
class ROCK;
class STRAW;

using namespace std;

class EntityHandler
{
    public:
        EntityHandler();

        ROV *rov;
        TURTLE *turtle;
        vector<ROCK*> rocks;
        vector<STRAW*> straws;
};