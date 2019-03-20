#pragma once

#include "Patch.h"

#include <fstream>
#include <map>
#include <vector>

class PatchFileLoader
{
private:
	/*
	Creates a Patch object from the data gives in the map argument.

	@param data -> data which will be used to create the patch object
	@returns -> constructed Patch object
	*/
	static Patch createPatchFromData(std::map<std::string, std::string> data);

	/*
	Returns the next line in the file as a string.

	@param file -> file input string which has the patch file opened
	@returns -> line in a file as a string
	*/
	static std::string getLine(std::ifstream& file);

	/*
	Parses the header of the patch file. The header contains general information
	about the patch like the synth engine version it was made for, the name of the
	patch bank etc.

	@param file -> file input string which has the patch file opened
	*/
	static void parseHeader(std::ifstream& file);

	/*
	Parses one instrument from the file and returns a constructed patch object.

	@param file -> file input string which has the patch file opened
	@returns -> constructed patch object
	*/
	static Patch parseInstrument(std::ifstream& file);

	/*
	Starts reading the file and enables loading of mutliple instruments.

	@param file -> file input string which has the patch file opened
	*/
	static std::vector<Patch> parseFile(std::ifstream& file);
public:
	/*
	Opens and loads instruments from the given file. The loaded patches
	are returned as a vector which contains all the parsed patches.
	The patches are indexed depending on the orden in which they were in 
	the file, so the patch that is first in the file will be found at index 0.

	@param filename -> filename of the file which contains the patch data
	@returns -> vector containing all loaded patches
	*/
	static std::vector<Patch> loadPatchData(std::string filename);
};

