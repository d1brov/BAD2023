#include <format>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <sstream>
 
/*
    Finds first unique character in string.
 
    Parameters:
        - String to inspect
 
    Return values:
        - First unique character in word
        - NULL if no unique character found
*/
char FindFirstUniqueChar(const std::string& word) {
 
    size_t word_len{ word.size() };
 
    for (size_t i{}, j{}; i < word_len; i++) {
        for (j = 0; j < word_len; j++) {
            if (i == j) continue;
 
            if (word[i] == word[j]) {
                break;
            }
        }
 
        if (j == word_len) {
            return word[i];
        }
    }
 
    return NULL;
}
 
/*
    Parses word list from string. Delimiters are all characters except 
    uppercase & lowercase letters
 
    Parameters:
        - String to parse
 
    Return value:
        - List of parsed words
*/
std::list<std::string> ParseWordList(const std::string& input) {
 
    std::regex delimiters("\\W+");
 
    std::sregex_token_iterator first( 
        input.begin(), input.end(), delimiters, -1 );
 
    return { first, std::sregex_token_iterator()};
}
 
/*
    Finds first unique letter among first unique letters of input's words
 
    Parameters:
        - String to inspect
 
    Return value:
        - Found char
        - NULL of no unique char found
*/
char FindFirstUniqueLetter(const std::string& input) {
 
    std::string unique_letters{};
    for (const auto& word : ParseWordList(input)) {
        char c{ FindFirstUniqueChar(word) };
        if (c != NULL) {
            unique_letters.push_back(c);
        }
    }
 
    // Find first unique letter
    return FindFirstUniqueChar(unique_letters);
}
 
int main(int argc, char* argv[]) {
 
    // Arguments validation
    if (argc != 2) {
        std::cerr << "Invalid argument amount.\n"
                     "Pass input text filename as second parameter\n";
        return EXIT_FAILURE;
    }
    const std::string input_filename { argv[1] };
 
    // File extension validation
    if (!input_filename.ends_with(".txt")) {
        std::cerr << "Input file must have .txt extension\n";
        return EXIT_FAILURE;
    }
 
    // Open input file stream
    std::ifstream input_stream;
    input_stream.open(input_filename);
    if (!input_stream.is_open()) {
        std::cerr << 
            std::format(
                "Cannot open file [{}] for reading.\n", input_filename);
        return EXIT_FAILURE;
    }
    std::stringstream stream_buffer;
    stream_buffer << input_stream.rdbuf();
    input_stream.close();
 
    // Find first unique symbol of words first unique subsymbols)
    std::cout << FindFirstUniqueLetter(stream_buffer.str()) << '\n';
 
    return EXIT_SUCCESS;
}