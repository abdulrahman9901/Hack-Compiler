#include "./includes/tokenizer.h"
#include <algorithm>
#include <cctype>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const char kPathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

using namespace std;

namespace fs = std::filesystem;

// bool isComment(std::string& line) {
//     // Check if the line is a comment
//     size_t pos = line.find("//");
//     if (pos != std::string::npos) {
//         line.erase(pos); // Remove the comment portion
//     }

//     return line.empty();
// }

Tokenizer* tokenizer;
// https://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder
std::vector<std::string> get_all(fs::path const& root, std::string const& ext) {
    std::vector<std::string> paths{root.string() + kPathSeparator + "Sys.vm"};

    if (fs::exists(root) && fs::is_directory(root)) {
        for (auto const& entry : fs::recursive_directory_iterator(root)) {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext)
                if (entry.path().filename() != "Sys.vm")
                    paths.emplace_back(entry.path().string());
        }
    }

    return paths;
}

// codeWriter* writer;
/// @brief main Vm translator loop
/// @param argc number of arguments=1
/// @param argv name and path of the file
/// @return 0
int main(int argc, char** argv) {
    cout << "Program Started " << argv[0] << endl;
    if (argc < 2) {
        cout << "Not enough arguments" << endl;
        return 1;
    }
    std::vector<std::string> infiles;
    std::string outfile;
    std::vector<std::string> outfiles;
    if (fs::is_directory(fs::status(argv[1]))) {
        fs::path root = argv[1];
        std::string ext = ".jack";
        infiles = get_all(root, ext);
        for (std::string p : infiles) {
            outfile = p;
            int dotPos = outfile.rfind(".");
            outfile = outfile.substr(0, dotPos);
            outfile += ".xml";
            outfiles.push_back(outfile);
            std::cout << "out file is " << outfile << std::endl;
        }
    } else if (fs::is_regular_file(fs::status(argv[1]))) {
        // getting the input file name and path from input arguments
        infiles = {argv[1]};
        // generating output file name with same name and path but with .xml
        // extension
        int dotPos = infiles[0].rfind(".");
        outfile = infiles[0].substr(0, dotPos);
        outfile += ".xml";
        std::cout << "out file is " << outfile << std::endl;
    } else {
        std::cerr << "something wrong with the input filename or directory "
                  << std::endl;
        return 0;
    }

    for (std::string infile : infiles) {
        // initialize tokenizer
        try {
            tokenizer = new Tokenizer(infile);
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
            return 0;
        }
        // loop through all the lines in the file tokenizer them and
        // extract
        // commands then write corresponding xml tag.
        int c = 1;
        while (tokenizer->hasMoreTokens()) {
            tokenizer->advance();
            auto t = tokenizer->construct_token();
            if (t.type != TOKEN_TYPE::OTHERS) {
                std::cout << "In main loop : "
                          << (t.type == TOKEN_TYPE::SYMBOL    ? "symbol"
                              : t.type == TOKEN_TYPE::KEYWORD ? "keyword"
                              : t.type == TOKEN_TYPE::INT_CONST
                                  ? "integer const"
                              : t.type == TOKEN_TYPE::STRING_CONST
                                  ? "string const"
                              : t.type == TOKEN_TYPE::IDENTIFIER ? "IDENTIFIER"
                                                                 : "others ")
                          << "        " << t.value << "  " << c++ << std::endl;
            }
        }
        tokenizer->close();
    }

    return 0;
}