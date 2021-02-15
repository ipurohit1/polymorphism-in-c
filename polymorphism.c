#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AnimalInterface class that contains pointer to a function called make_Noise that taken in a void pointer and returns void  
typedef struct animal_interface {
    void (*make_noise)(void *instance);
} AnimalInterface;

// Animal class that takes in a void pointer to instance of a Animal 
// Takes in a pointer to a AnimalInterface object (defined above)
typedef struct {
    void *instance;
    const AnimalInterface *interface;
} Animal;


// Takes in a void instance and AnimalInterface and returns a pointer to an Animal
Animal * animal_Create(void *instance, AnimalInterface *interface)
{
    Animal *animal = (Animal *) malloc(sizeof(Animal));
    animal->instance = instance;
    animal->interface = interface;
    return animal;
}

// Takes in Animal pointer and call make noise 
void animal_make_noise(Animal *animal)
{
    // The first term is a pointer to the area function and it takes in an instance of a shape (square )
    (animal->interface->make_noise)(animal->instance);
}

// Dog struct that takes in a str for noise  
typedef struct {
    char noise[6];
} Dog;

// Print out the noise of dog
void make_dog_noise(Dog *dog)
{
    printf("%s\n", dog->noise);
}

// Initialize AnimalInterface for Dog and set its function pointer 
AnimalInterface *DogAsAnimal = &(AnimalInterface) {
    .make_noise = (void (*)(void *)) make_dog_noise
};

// Creates dog obj 
Dog * dog_Create(char noise[6])
{
    Dog *dog = (Dog *) malloc(sizeof(Dog));
    strcpy(dog->noise, noise); 
    return dog;
}

// Cat struct that takes in a str for noise  
typedef struct {
    char noise[6];
} Cat;

// print out noise of cat 
void make_cat_noise(Cat *cat)
{
    printf("%s\n", cat->noise);
}

// Initialize AnimalInterface for Cat and set its function pointer
AnimalInterface *CatAsAnimal = &(AnimalInterface) {
    .make_noise = (void (*)(void *)) make_cat_noise
};

// Creates cat obj 
Cat * cat_Create(char noise[6])
{
    Cat *cat = (Cat *) malloc(sizeof(Cat));
    strcpy(cat->noise, noise); 
    return cat;
}

int main(int argc, char **argv)
{
    // Create concrete types.
    Cat *cat = cat_Create("Meow");
    Dog *dog = dog_Create("Bark");


    // animal_Create takes in object of type cat/dog and type AnimalInterface
    Animal *catAnimal = animal_Create(cat, CatAsAnimal);
    Animal *dogAnimal = animal_Create(dog, DogAsAnimal);

    // Check that Cat object and Animal object of Type Dog output the same noise 
    printf("Noise of Cat Object -> "); 
    make_cat_noise(cat); 
    printf("Noise of Animal Object of Type Cat -> "); 
    animal_make_noise(catAnimal);

    // Check that Dog object and Animal object of Type Dog output the same noise 
    printf("Noise of Dog Object -> "); 
    make_dog_noise(dog); 
    printf("Noise of Animal Object of Type Dog-> "); 
    animal_make_noise(dogAnimal);

    return 0;
}