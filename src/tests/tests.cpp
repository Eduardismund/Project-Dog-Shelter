#include <cassert>
#include "tests.h"
#include <fstream>
#include <iostream>

void Test::testDog() {
    Dog dog("Labrador Retriever", "Max", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 2);
    Dog dog2;
    dog2 = dog;
    assert(dog2 == dog);
    assert(dog.getName() == "Max");
    assert(dog.getAge() == 2);
    assert(dog.getPhotograph() == "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg");
    assert(dog.getBreed() == "Labrador Retriever");

    Dog dog3("Siberian Husky", "Luna", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 3);
    dog3.setAge(dog.getAge());
    dog3.setBreed(dog.getBreed());
    dog3.setName(dog.getName());
    dog3.setPhotograph(dog.getPhotograph());

    assert(dog3 == dog);
    assert(dog3.getName() == "Max");
    assert(dog3.getAge() == 2);
    assert(dog3.getPhotograph() == "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg");
    assert(dog3.getBreed() == "Labrador Retriever");

}

void Test::testFileRepoShelterDogs() {
    const std::string filePath = "test_dogs.txt";

    std::remove(filePath.c_str());

    // 1. Test Constructor and readFromFile()
    {
        std::ofstream file(filePath);
        file << "Max\nLabrador Retriever\n2\nhttps://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg\n";
        file << "Luna\nSiberian Husky\n3\nhttps://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg\n";
        file.close();

        FileRepoShelterDogs repo(filePath);
        std::vector<Dog> dogs = repo.getDogs();
        assert(dogs.size() == 2);
        assert(dogs[0].getName() == "Max");
        assert(dogs[1].getName() == "Luna");
    }

    // 2. Test addDog() and writeToFile()
    {
        FileRepoShelterDogs repo(filePath);
        Dog newDog("Golden Retriever", "Buddy", "https://example.com/buddy.jpg", 4);
        repo.addDog(newDog);

        // Verify the dog is added in the repository
        std::vector<Dog> dogs = repo.getDogs();
        assert(dogs.size() == 3);
        assert(dogs[2].getName() == "Buddy");

        // Verify the dog is added in the file
        std::ifstream file(filePath);
        std::string line;
        bool found = false;
        while (std::getline(file, line)) {
            if (line.find("Buddy") != std::string::npos) {
                found = true;
                break;
            }
        }
        assert(found);
    }

    // 3. Test updateDog()
    {
        FileRepoShelterDogs repo(filePath);
        Dog updatedDog("Golden Retriever", "Buddy", "https://example.com/buddy_updated.jpg", 5);
        repo.updateDog(updatedDog);

        Dog fetchedDog = repo.getDogByName("Buddy");
        assert(fetchedDog.getAge() == 5);
        assert(fetchedDog.getPhotograph() == "https://example.com/buddy_updated.jpg");

        std::ifstream file(filePath);
        std::string line;
        bool found = false;
        while (std::getline(file, line)) {
            if (line.find("Buddy") != std::string::npos) {
                found = true;
                break;
            }
        }
        assert(found);
    }

    // 4. Test deleteDog()
    {
        FileRepoShelterDogs repo(filePath);
        repo.deleteDog("Buddy");

        std::vector<Dog> dogs = repo.getDogs();
        assert(dogs.size() == 2);
        assert(repo.getDogByName("Buddy").getName().empty());

    }

    // 5. Test getDogPosition() and getDogByName()
    {
        FileRepoShelterDogs repo(filePath);
        Dog maxDog = repo.getDogByName("Max");
        int position = repo.getDogPosition(maxDog);
        assert(position != -1);

        Dog nonExistentDog = repo.getDogByName("NonExistent");
        assert(nonExistentDog.getName().empty());

        Dog dog3("Husky", "Lunas", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 2);
        int position1 = repo.getDogPosition(dog3);
        assert(position1 == -1);
    }

    // 6. Test getDogPositionByName()
    {
        FileRepoShelterDogs repo(filePath);
        int position = repo.getDogPositionByName("Luna");
        assert(position != -1);

        int nonExistentPosition = repo.getDogPositionByName("NonExistent");
        assert(nonExistentPosition == -1);
    }

    std::remove(filePath.c_str());
}

void Test::testDBRepository() {

    const std::string dbPath = "test_db.sqlite";

    std::remove(dbPath.c_str());

    DBRepository repo(dbPath);

    Dog dog1("Labrador Retriever", "Max", "https://example.com/max.jpg", 2);
    repo.addDog(dog1);



    auto dogs = repo.getDogs();
    assert(dogs.size() == 1);
    assert(dogs[0] == dog1);

    Dog dog2("German Shepherd", "Rex", "https://example.com/rex.jpg", 3);
    repo.addDog(dog2);
    int p = repo.getDogPosition(dog2);
    assert(p==1);

    Dog dogTest("Labrador Retriever", "Max", "https://example.com/max_new.jpg", 3);
    p = repo.getDogPosition(dogTest);
    assert(p==-1);

    dogs = repo.getDogs();
    assert(dogs.size() == 2);
    assert(dogs[0] == dog1);
    assert(dogs[1] == dog2);

    Dog updatedDog1("Labrador Retriever", "Max", "https://example.com/max_new.jpg", 3);
    repo.updateDog(updatedDog1);

    dogs = repo.getDogs();
    assert(dogs.size() == 2);
    assert(dogs[0] == updatedDog1);
    assert(dogs[1] == dog2);

    assert(repo.getDogPositionByName("Max") == 0);
    assert(repo.getDogPositionByName("Rex") == 1);
    assert(repo.getDogPositionByName("Nonexistent") == -1);
    assert(repo.getDogByName("Max") == updatedDog1);
    assert(repo.getDogByName("Rex") == dog2);
    assert(repo.getDogByName("Nonexistent").getName() == "");

    repo.deleteDog("Rex");

    dogs = repo.getDogs();
    assert(dogs.size() == 1);
    assert(dogs[0] == updatedDog1);

    try {
        repo.deleteDog("Nonexistent");
        assert(true);
    } catch (const Exception &e) {
        assert(false);
    }

    std::remove(dbPath.c_str());
}

void Test::testRepoAdoptedDogs() {
    const std::string csvPath = "test_adopted_dogs.csv";
    const std::string htmlPath = "test_adopted_dogs.html";

    RepoAdoptedDogsCSV csvRepo(csvPath);
    RepoAdoptedDogsHTML htmlRepo(htmlPath);

    Dog dog1("Labrador Retriever", "Max", "https://example.com/max.jpg", 2);
    Dog dog2("German Shepherd", "Rex", "https://example.com/rex.jpg", 3);

    csvRepo.addDog(dog1.getName(), dog1.getBreed(), dog1.getAge(), dog1.getPhotograph());
    htmlRepo.addDog(dog2.getName(), dog2.getBreed(), dog2.getAge(), dog2.getPhotograph());

    assert(csvRepo.getAdoption().size() == 1);
    assert(csvRepo.getAdoption()[0] == dog1);
    assert(htmlRepo.getAdoption().size() == 1);
    assert(htmlRepo.getAdoption()[0] == dog2);

    Dog dog3("Husky", "Lunas", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 2);
    htmlRepo.addAdoption(dog3);
    assert(htmlRepo.getAdoption().size() == 2);

    csvRepo.write();
    htmlRepo.write();

    std::ifstream csvFile(csvPath);

    std::string line;
    std::getline(csvFile, line);
    assert(line == "Max,Labrador Retriever,2,https://example.com/max.jpg");
    csvFile.close();

}

void Test::testAll() {
    testDog();
    testFileRepoShelterDogs();
    testDBRepository();
    testRepoAdoptedDogs();
}