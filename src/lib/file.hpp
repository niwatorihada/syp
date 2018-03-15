#ifndef FILE_HPP
#define FILE_HPP

#include<string>
#include<vector>
#include<fstream>
#include<iostream>

class File {
private:
    // output file stream?
    static std::ofstream ofs;
    // input file stream?
    static std::ifstream ifs;

public:
    static void ofsOpen( const char* const file ) throw(int);
    static void ifsOpen( const char* const file ) throw(int);
    static void ifsClose() throw(int);
    
    void read( std::vector< std::string > &r );
    
    static void write( std::vector< std::string > in );
    static void write( const char* const text );
};

#endif /* FILE_H */
