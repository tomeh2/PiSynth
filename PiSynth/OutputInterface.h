#pragma once

/*
The OutputInterface class is just a virtual function that all wannabe output streams
must inherit from. It provides a function which should take the samples from the sound engine, encode them
and send them to some output. The function which implements this interface can be given to the sound engine
as the output to which the rendered samples will be written to.
*/
class OutputInterface
{
	virtual void writeOut(float* samples, int size);
};