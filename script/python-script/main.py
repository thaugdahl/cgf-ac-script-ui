#!/usr/bin/env python3
import sys
import os

def help_message():
    print("Usage:")
    print("main.py [input_dir] [output_dir]")

class Config():
    def __init__(self):
        self.patterns = []
        self.outPath = ""
        self.mode = False

    def add(self, pattern):
        if ( not isinstance(pattern, tuple) or len(pattern) < 2 ):
            print("Trying to a non-tuple")

        self.patterns.append(pattern)

    def getAll(self):
        return self.patterns

    def setOutPath(self, path):
        self.outPath = path

    def setMode(self, mode):
        self.mode = mode

def handle_file(filename, config):
    if not isinstance(config, Config):
        print("Invalid configuration object passed to handle_file.")
        exit(1)

    cwd = os.getcwd() + "/"

    filename_no_prefix = filename.replace(cwd, "")




    # print(f"Converting {filename}")



def read_patterns(config):
    if ( not isinstance(config, Config) ):
        print("Invalid argument passed to read_patterns. Must be a Config object")

    lines = []
    with open("patterns.txt", "r") as fh:
        lines = fh.readlines()

    for line in lines:
        currentLine = line.strip().split("\t")
        config.add(
                (currentLine[0], currentLine[1], int(currentLine[2])
        ))

def main():
    if ( len(sys.argv) < 3 ):
        help_message()
        exit(1)

    inputPath = sys.argv[1]
    outputPath = sys.argv[2]

    # Check existence of files
    file_exists = os.path.exists(inputPath)
    if ( not file_exists ):
        print("Input Path does not exist!")
        exit(1)


    cwd = os.getcwd()

    cfg = Config()
    cfg.setMode(os.path.isdir(inputPath))
    cfg.setOutPath(outputPath)

    if ( os.path.exists( cwd + "/patterns.txt") ):
        print("Loading configuration from patterns.txt")
        read_patterns(cfg)

    inputFiles = os.listdir(inputPath)

    for inputFile in inputFiles:
        handle_file(cwd + "/" + inputFile, cfg)



if __name__ == '__main__':
    main()
