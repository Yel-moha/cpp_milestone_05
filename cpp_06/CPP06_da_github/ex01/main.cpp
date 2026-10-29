/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:59:09 by cgodecke          #+#    #+#             */
/*   Updated: 2023/11/27 17:24:38 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main(void)
{

	Data *data = new Data;
	data->name = "Peter";
	data->age = 42;
	data->sername = "Meier";

	uintptr_t raw = Serializer::serialize(data);
	Data *serialized = Serializer::deserialize(raw);

	std::cout << serialized->name << std::endl;
	std::cout << serialized->age << std::endl;
	std::cout << serialized->sername << std::endl;

	delete data;
	return (0);
}
