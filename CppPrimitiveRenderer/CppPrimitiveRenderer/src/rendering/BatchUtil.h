#pragma once

class BatchUtil
{
public:

	static class Batch* makeBatch(int renderType);
	static void loadAllShaders(class Logger* loggerRef);
	static void deleteAllShaders();
};