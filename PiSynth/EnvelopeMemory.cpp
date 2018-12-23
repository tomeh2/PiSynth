#include "EnvelopeMemory.h"
#include "EnvelopeGenerator.h"

EnvelopeMemory::EnvelopeMemory()
{
	EnvelopeGenerator envelopeGenerator;

	envelopeGenerator.addNewState(0.01f, 1.f, 0.f);
	envelopeGenerator.addNewState(0.f, 1.f, 0.05f);
	envelopeGenerator.addNewState(-0.02f, 0.5f, 0.f);
	envelopeGenerator.addNewState(-0.3f, 0.2f, 0.f);
	envelopeGenerator.addNewState(0.f, 0.2f, 0.f);
	envelopeGenerator.addNewState(-0.3f, 0.0f, 0.f);
	envelopeGenerator.trigger();

	do
	{
		this->samples.push_back(envelopeGenerator.getNextValue());


	} while (envelopeGenerator.isActive());
}

EnvelopeMemory::~EnvelopeMemory()
{
}