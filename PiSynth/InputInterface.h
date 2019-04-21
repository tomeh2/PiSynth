#pragma once

#include "MidiEvent.h"

class InputInterface
{
public:
	/*
	Returns the next event which is supposed to be processed by the synthesizer.
	*/
	virtual smf::MidiEvent getNextEvent() = 0;

	/*
	Returns wether the input is active or not (should the synthesis engine expect to recieve anything anymore)
	*/
	virtual bool isActive() = 0;

	/*
	Tells wether there are any MIDI events currently waiting to be processed. Depends on the timestamp if
	the events were read from a file (in this case it returns true if there are any events whose timestamp
	is lower then the given timestamp and have not been already read). If the input stream is from something
	like a keyboard then timestamp should just be set to 0 (don't care variable).
	*/
	virtual bool ready(int timestamp) = 0;
};