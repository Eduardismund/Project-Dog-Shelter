#pragma once
#include <vector>
#include "../exception/Exception.h"
#include "../repository/RepoShelterDogs.h"
#include "../model/Dog.h"
#include "../service/ServiceAdmin.h"
#include "../repository/RepoAdoptedDogs.h"
#include "../service/ServiceUser.h"

class Test{
private:
    static void testDog();
    static void testFileRepoShelterDogs();
    static void testDBRepository();
    static void testRepoAdoptedDogs();
public:
    void testAll();
};