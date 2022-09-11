#include "Task.hpp"

ProgressTaskTest::ProgressTaskTest() {}

void ProgressTaskTest::run()
{
    progressThread = std::thread(
            [&] () {
            for ( int i = 0; i <= 100; i++) {
                usleep(50000);
                progress = i;
    }
            });
}

int ProgressTaskTest::GetProgress()
{
    return progress;
}

void ProgressTaskTest::finish() 
{
    if ( progressThread.joinable() )
        progressThread.join();
}

FileProcessorTask::FileProcessorTask(const std::string &input, const std::string &output) 
{
    file_processor = new FileProcessor(input, output);
}

FileProcessorTask::~FileProcessorTask()
{
    delete file_processor;
}

bool FileProcessorTask::HasFailed()
{
    return failed;
}

void FileProcessorTask::run()
{
    taskThread = std::thread(
            [&] () {
                try {
                    file_processor->process();
                } catch (const std::exception &e)
                {
                    errorString = e.what();
                    failed = true;
                    finished = true;
                }
                finished = true;
            }
    );
}

std::string FileProcessorTask::GetLastError()
{
    std::string lastError = errorString;
    errorString.clear();
    return lastError;
}

int FileProcessorTask::GetProgress()
{
    return file_processor->lines_processed;
}

void FileProcessorTask::finish() 
{
    if ( taskThread.joinable() )
        taskThread.join();

    failed = false;
}

bool FileProcessorTask::HasJoined()
{
    return ! taskThread.joinable();
}

bool FileProcessorTask::isFinished() 
{
    return finished;
}
