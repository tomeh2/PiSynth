#include "FileIn.h"
#include "Logger.h"

FileIn::FileIn(std::string filename)
{
	this->midiFile = smf::MidiFile();
	midiFile.read(filename);
	this->errorStatus = midiFile.status();

	if (this->errorStatus)
	{
		this->midiFile.joinTracks();
		this->midiFile.sortTracks();
		this->midiFile.absoluteTicks();

		this->setTimestampPosition(0);
	}
}

FileIn::~FileIn()
{
}

//----------------------------- PRIVATE -----------------------------//

//----------------------------- PUBLIC -----------------------------//
bool FileIn::status()
{
	return this->errorStatus;
}

smf::MidiEvent FileIn::getNextEvent()
{
	smf::MidiEvent e = this->events.front();
	this->events.pop();
	return e;
}

void FileIn::setTimestampPosition(int position)
{
	int eventIndex = 0;

	while (this->midiFile[0][eventIndex].tick < position)
		eventIndex++;

	for (int i = position; i < this->midiFile.getEventCount(0); i++)
	{
		this->events.push(midiFile[0][i]);
	}
}

bool FileIn::isActive()
{
	return !this->events.empty();
}

bool FileIn::ready(int timestamp)
{
	if (timestamp >= this->events.front().tick)
		return true;
	return false;
}