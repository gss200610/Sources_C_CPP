#pragma once
#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <experimental/filesystem>
#include <string.h>
using namespace std;


	namespace fs = experimental::filesystem::v1;

	static std::string pathApp = fs::current_path().string();




#endif // !CONSTANTES_H

