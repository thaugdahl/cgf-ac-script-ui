#ifndef TASK_HPP
#define TASK_HPP

#include <wx/wx.h>
#include <thread>
#include <string>
#include "FileProcessor.hpp"

class ITask
{
public:
    ITask() {};
    virtual ~ITask() {};

    virtual void run() = 0; 
    virtual void finish() = 0;
};

class IParallelTask : public ITask
{
public:
    virtual bool isFinished() = 0;
};

class ProgressTaskTest : public ITask
{
public:
    ProgressTaskTest();
    virtual ~ProgressTaskTest() {}

    virtual void run() override;
    virtual void finish() override;

    int GetProgress();


private:
    int progress = 0;
    std::thread progressThread;

};

class FileProcessorTask : public IParallelTask
{
public:
    FileProcessorTask() = delete;
    FileProcessorTask(const std::string &input, const std::string &output);
    virtual ~FileProcessorTask();

    virtual void run() override;
    virtual void finish() override;
    virtual bool isFinished() override;

    int GetProgress();

    bool HasFailed();
    bool HasJoined();
    std::string GetLastError();

private:

    int progress = 0;
    std::thread taskThread;

    bool failed = false;
    std::string errorString{};

    bool finished = false;

    std::string input_file;
    std::string output_file;

    FileProcessor *file_processor;


};

#endif

