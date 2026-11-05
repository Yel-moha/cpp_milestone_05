#include "Serializer.hpp"
#include <iostream>

int main(void)
{
    Data *data = new Data;
    data->id = 0;
    data->name = "prima";

    uintptr_t raw = Serializer::serialize(data);
    Data *serialized = Serializer::deserialize(raw);

    std::cout << serialized->name << std::endl;
    std::cout << serialized->id << std::endl;

    delete data;
    return (0);
}
