#include "SampleLogic.h"

void SampleLogic::Init(void)
{
	std::cout << "SanpleLogic Inited\n";
	test = new int;
}

void SampleLogic::Update(void)
{
	std::cout << "SanpleLogic Update\n";
}

void SampleLogic::Shutdown(void)
{
	delete test;
	test = 0;
	std::cout << "SanpleLogic Shutdown\n";
}