#include <iostream>
#include <array>
#include <fstream>


#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

using namespace std;
const int MAX = 243;


int binarySearch ( string SongList[], int first, int last, string aString){
    int loc = 0, mid = last / 2;
    //check if not found
    if (last < first){
        //loc = -1;
        // needs to return otherwise will have infinite loop
        return -1;
    }
        mid = first  + (last - first)/2;
        //cout << " search: " << aString << " first:" << first << " mid:" << mid << " last:" << last << " SongList is " << SongList[mid] << " loc is " << loc << endl;
        if (SongList[mid] == aString) {
            loc = mid + 1; //array starts at 0
        }else if (SongList[mid] > aString){
            loc =  binarySearch(SongList,first, mid - 1,aString);
        } else if (SongList[mid] < aString ){
            loc = binarySearch(SongList, mid + 1, last, aString);
        }
    return loc;
}


int narySearch ( string SongList[], int first, int last, string aString,int n_ary){
    int loc = 0, mdfirst,mdsecond;
    int mdsize = (last - first + 1)/n_ary - 1;
    mdfirst = first + mdsize;
    mdsecond = last - mdsize;

    //check if not found
    if (last < first){
        loc = -1;
        // needs to return otherwise will have infinite loop
        return loc;
    }

    //cout << "search: " << aString << " first:" << first << " mdfirst:" << mdfirst << " mdsecond:" << mdsecond << " last:" << last << "mdfirstSongList:" << SongList[mdfirst] << " loc is " << loc << endl;
    if (SongList[mdfirst] == aString) {
        loc = mdfirst + 1; //array starts at 0
    }else if (SongList[mdfirst] > aString){
        //lower than mdfirst
        loc =  narySearch(SongList,first, mdfirst - 1,aString,n_ary);
    } else if (SongList[mdfirst] < aString ){
        if (SongList[mdsecond] == aString) {
            loc = mdsecond + 1; //array starts at 0
        }else if (SongList[mdsecond] > aString){
            //lower than mdfirst
            loc =  narySearch(SongList,mdfirst + 1, mdsecond-1,aString,n_ary);
        }else if (SongList[mdsecond] < aString){
            loc =  narySearch(SongList,mdsecond + 1, last,aString,n_ary);
        }
    }
    return loc;
}

int main() {

    //Reference powerpoint lecture
    //maximum array size
    string songList[MAX];
    string songs[MAX];

    //set filename
    string filename = "/Users/Shared/tmp/MusicList2.txt";

    string str;

    ifstream inFile;  //Input Filestream name
    int num = 0;

    //open file
    inFile.open(filename);

    if(!inFile){
        //if unable to open input file name
        return -1;
    }

    //process file
    getline(inFile, str);
    while (!inFile.eof() ){
        //read the file to max array
       if( num < MAX) {
           songList[num] = str;
//           cout << "song " << num << " is: " << songList[num] << std::endl;
           getline(inFile, str);
           num++;
       }else{
           break;
       }
    }

    //sort the list just to make sure
    sort(songList,songList + MAX);


    //close the file
    inFile.close();

    //define search string
    string stringToSearch = "Ledisi";
    //get location of the search string
    int location = binarySearch(songList,0,MAX,stringToSearch);
//    std::cout << "location is " << location << " for string: " << stringToSearch<< std::endl;
    //test if location is correct
    ASSERT(location == 190, "Not Matching locaion");

    stringToSearch = "Leona Lewis";
    location = binarySearch(songList,0,MAX,stringToSearch);
//    std::cout << "location is " << location << " for string: " << stringToSearch<< std::endl;
    ASSERT(location == 192, "Not Matching locaion");

    stringToSearch = "Arnold Dajao";
    location = binarySearch(songList,0,MAX,stringToSearch);
//    std::cout << "location is " << location << " for string: " << stringToSearch<< std::endl;
    ASSERT(location == -1, "Not Matching locaion");


    std::cout << "N-Ary search"<< std::endl;
    //N-Ary search
    int n_ary = 3;
    //define search string
    stringToSearch = "Ledisi";
    //get location of the search string
    location = narySearch(songList,0,MAX,stringToSearch,n_ary);
//    std::cout << "location is " << location << " for string: " << stringToSearch<< std::endl;
    //test if location is correct
    ASSERT(location == 190, "Not Matching locaion");


    //define search string
    stringToSearch = "Leona Lewis";
    //get location of the search string
    location = narySearch(songList,0,MAX,stringToSearch,n_ary);
//    std::cout << "location is " << location << " for string: " << stringToSearch<< std::endl;
    //test if location is correct
    ASSERT(location == 192, "Not Matching locaion");

    stringToSearch = "Arnold Dajao";
    location = narySearch(songList,0,MAX,stringToSearch,n_ary);
//    std::cout << "location is " << location << " for string: " << stringToSearch<< std::endl;
    ASSERT(location == -1, "Not Matching locaion");

    std::cout << "All Test Passed"<< std::endl;

    return 0;
}