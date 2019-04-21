#pragma once

#include "InputInterface.h"
#include "MidiFile.h"

#include <queue>

class FileIn : public InputInterface
{
private:
	std::queue<smf::MidiEvent> events;
	smf::MidiFile midiFile;

	bool errorStatus;
public:
	FileIn(std::string filename);
	~FileIn();

	bool status();
	smf::MidiEvent getNextEvent();
	void setTimestampPosition(int position);
	bool isActive();
	bool ready(int timestamp);
};

