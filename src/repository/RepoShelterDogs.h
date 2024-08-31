#pragma once
#include <vector>
#include "../model/Dog.h"
#include "../../libs/sqlite3.h"


class RepoShelterDogs{
public:
    RepoShelterDogs()= default;
    virtual ~RepoShelterDogs()=default;
    virtual void addDog(const Dog &dog) = 0;
    virtual void updateDog(const Dog &dog) = 0;
    virtual void deleteDog(const std::string &name) = 0;
    [[nodiscard]] virtual std::vector<Dog> getDogs() const = 0;
    virtual int getDogPosition(const Dog& dog) = 0;
    virtual int getDogPositionByName(const std::string &name) = 0;
    virtual Dog getDogByName(const std::string &name) = 0;


};

class FileRepoShelterDogs: public RepoShelterDogs{
private:
    std::vector<Dog> dogs;
    std::string filePath;
public:
    explicit FileRepoShelterDogs(const std::string& filePath = "../data/ShelterDogs.txt");
    ~FileRepoShelterDogs() override =default;
    void addDog(const Dog &dog) override;
    void deleteDog(const std::string &name) override;
    void updateDog(const Dog &dog) override;
    [[nodiscard]] std::vector<Dog> getDogs() const override;
    int getDogPosition(const Dog& dog) override;
    int getDogPositionByName(const std::string &name) override;
    Dog getDogByName(const std::string &name) override;
    void readFromFile();
    void writeToFile() const;
};


class DBRepository : public RepoShelterDogs{
private:
    sqlite3 *databaseWithDogs{};
    std::string filePath;

public:
    explicit DBRepository(const std::string& filePath = "../data/ShelterDogs5.db");
    ~DBRepository() override;
    void addDog(const Dog &dog) override;
    void deleteDog(const std::string &name) override;
    void updateDog(const Dog &dog) override;
    [[nodiscard]] std::vector<Dog> getDogs() const override;
    int getDogPosition(const Dog& dog) override;
    Dog getDogByName(const std::string &name) override;
    int getDogPositionByName(const std::string &name) override;
};