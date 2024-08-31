#include "RepoAdoptedDogs.h"
#include <fstream>
#include <iostream>
#include "../exception/Exception.h"

void RepoAdoptedDogs::addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
    Dog dog = Dog(breed, name, photograph, age);
    this->vectorWithAdoptedDogs.push_back(dog);
}

std::vector<Dog> RepoAdoptedDogs::getAdoption() {
    return this->vectorWithAdoptedDogs;
}

void RepoAdoptedDogs::addAdoption(const Dog &dog) {
    this->vectorWithAdoptedDogs.push_back(dog);
}

// CSV Implementation

RepoAdoptedDogsCSV::RepoAdoptedDogsCSV(const std::string& filePath) : filePath(filePath) {}

void RepoAdoptedDogsCSV::write() {
    std::ofstream writeToCSVFile(filePath);
    for (auto & i : this->getAdoption()){
        writeToCSVFile << i.getName() << "," << i.getBreed() << "," << i.getAge() << "," << i.getPhotograph() << "\n";
    }
    writeToCSVFile.close();
}

void RepoAdoptedDogsCSV::display() {
    system(("start " + filePath).c_str());
}

// HTML Implementation

RepoAdoptedDogsHTML::RepoAdoptedDogsHTML(const std::string& filePath) : filePath(filePath) {}

void RepoAdoptedDogsHTML::write() {
    std::ofstream writeToHTMLFile(filePath);
    writeToHTMLFile << "<!DOCTYPE html>" << std::endl;
    writeToHTMLFile << "<html>" << std::endl;
    writeToHTMLFile << "<head>" << std::endl;
    writeToHTMLFile << "    <title>Adopted Dogs</title>" << std::endl;
    writeToHTMLFile << "</head>" << std::endl;
    writeToHTMLFile << "<body>" << std::endl;
    writeToHTMLFile << "<table border=\"1\">" << std::endl;
    writeToHTMLFile << "    <tr>" << std::endl;
    writeToHTMLFile << "        <td>Name</td>" << std::endl;
    writeToHTMLFile << "        <td>Breed</td>" << std::endl;
    writeToHTMLFile << "        <td>Age</td>" << std::endl;
    writeToHTMLFile << "        <td>Photograph</td>" << std::endl;
    writeToHTMLFile << "    </tr>" << std::endl;

    for (auto & i : this->getAdoption()){
        writeToHTMLFile << "    <tr>" << std::endl;
        writeToHTMLFile << "        <td>" + i.getName() + "</td>" << std::endl;
        writeToHTMLFile << "        <td>" + i.getBreed() + "</td>" << std::endl;
        writeToHTMLFile << "        <td>" << i.getAge() << "</td>" << std::endl;
        writeToHTMLFile << "        <td><img src=\"" + i.getPhotograph() + R"(" alt="Image not found"/></td>)" << std::endl;
        writeToHTMLFile << "    </tr>" << std::endl;
    }

    writeToHTMLFile << "</table>" << std::endl;
    writeToHTMLFile << "</body>" << std::endl;
    writeToHTMLFile << "</html>" << std::endl;
    writeToHTMLFile.close();
}

void RepoAdoptedDogsHTML::display() {
    system(("start " + filePath).c_str());
}