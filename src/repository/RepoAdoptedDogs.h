#pragma once
#include "../model/Dog.h"
#include <vector>
#include "../../libs/sqlite3.h"

class RepoAdoptedDogs{
private:
    std::vector<Dog> vectorWithAdoptedDogs;
public:

    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    virtual void addAdoption(const Dog &dog);
    std::vector<Dog> getAdoption();

    virtual void write() = 0;

    virtual void display() = 0;

};

class RepoAdoptedDogsCSV : public RepoAdoptedDogs {
private:
    std::string filePath;

public:
    explicit RepoAdoptedDogsCSV(const std::string& filePath = "../data/AdoptedDogs.csv");
    void write() override;
    void display() override;
};

class RepoAdoptedDogsHTML : public RepoAdoptedDogs {
private:
    std::string filePath;

public:
    explicit RepoAdoptedDogsHTML(const std::string& filePath = "../data/AdoptedDogs.html");
    void write() override;
    void display() override;
};