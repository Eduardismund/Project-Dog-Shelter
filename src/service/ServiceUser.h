#pragma once
#include <string>
#include "../model/Dog.h"
#include <vector>
#include "../repository/RepoAdoptedDogs.h"
#include "../repository/RepoShelterDogs.h"


class ServiceUser{
private:
    RepoShelterDogs *shelterRepository;
    RepoAdoptedDogs *adoptedRepo;
    std::string shelterFile;
    std::string adoptedFile;
    int currentIndex = 0;
public:
    ServiceUser(RepoShelterDogs *shelterRepository, RepoAdoptedDogs *adoptedRepo, std::string shelterFile_ = "../data/ShelterDogs.txt", std::string adoptedFile_ = "../data/AdoptedDogs.txt");
    ~ServiceUser();

    std::vector<Dog> getDogShelter();
    std::vector<Dog> getDogsAdopted();
    std::vector<Dog> getDogsFiltered(const std::string &breed, int age);

    Dog getCurrentDog();
    void nextDog();

    void adoptDog(const Dog& dog);
    void adoptDog(const std::string &name);


    // read and save shelter dogs from/to file
    void readShelterDogFromFile();
    void saveShelterDogToFile();

    // read and save adopted dogs from/to file
    void readAdoptedDogFromFile();
    void saveAdoptedDogToFile();

    RepoAdoptedDogs *const getRepoAdopted() const {
        return adoptedRepo;
    }

    void setRepoAdopted(RepoAdoptedDogs *repoAdoptedToBeSet) {
        ServiceUser::adoptedRepo = repoAdoptedToBeSet;
        ServiceUser::shelterRepository = new DBRepository;
    }



};