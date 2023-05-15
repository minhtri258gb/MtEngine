#define __MT_FILE_JSON_CPP__

#include <fstream>

#include <nlohmann/json.hpp>

#include "common.h"
#include "FileJson.h"

using namespace std;
using json = nlohmann::json;
using namespace mt::test;

class FileJson::FileJsonImpl
{
public:
	json j;
};

FileJson::FileJson()
{
	// Impliment
	this->impl = new FileJsonImpl();
}

FileJson::FileJson(string filepath)
{
	// Impliment
	this->impl = new FileJsonImpl();

	// Load
	this->load(filepath);
}

FileJson::~FileJson()
{
	// Impliment
	delete this->impl;
}

void FileJson::load(string filepath)
{
	ifstream i(filepath);
	i >> this->impl->j;
}

void FileJson::save(string filepath)
{
	ofstream o(filepath);
	o << std::setw(4) << this->impl->j << endl;
}

void FileJson::run()
{
	// jdEmployees
    json jdEmployees =
    {
        {"firstName","Sean"},
        {"lastName","Brown"},
        {"StudentID",21453},
        {"Department","Computer Sc."}
    };

    // Access the values
    string fName = jdEmployees.value("firstName", "oops");
    string lName = jdEmployees.value("lastName", "oops");
    int sID = jdEmployees.value("StudentID", 0);
    string dept = jdEmployees.value("Department", "oops");
   
    // Print the values
    cout << "First Name: " << fName << endl;
    cout << "Last Name: " << lName << endl;
    cout << "Student ID: " << sID << endl;
    cout << "Department: " << dept << endl;
}
