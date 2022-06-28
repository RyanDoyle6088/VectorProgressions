/*********************************************************************************************
In this project I create 4 functions, the first of which returns the 
* second largest int in a vector, the second of which will return a std::vector<int> containing 
* all the unique ints greater than or equal to a, and less than or equal to b in sorted order,
* te third of which will take in a vector of strngs and return the strings OR return "hidden"
* when encountering a string with non alpha-num chars, and lastly the fourth of which will return
* a std::vector<std::string> containing the reversed string versions of the arithmetic progression 
* starting from a, with an increment of d. 
**********************************************************************************************/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
 
int second_largest ( std::vector<int> in ){
    auto result = std::max_element( in.begin(), in.end() );
    int max_val = *result;
    //Erases all elements from the vector equal to the max element of the vector
    in.erase( std::remove_if( in.begin(), in.end(), [&max_val] ( int val ){return ( val == max_val );} ), in.end() );
    if (in.empty()){
        return max_val;//Returns the max element of the vector, if the vector consisted of the same elements
    }
    else
        result  = std::max_element(in.begin(), in.end());//Searches for the maximum element of the updated vector, which is the second largest element
    return *result;
}
std::vector<int> unique_range ( std::vector<int> in, int a, int b ){
    std::vector<int> new_vec ( in.size() );
    bool is_in = false;
    int new_index = -1;
    std::generate ( new_vec.begin(), new_vec.end(), [&a, &b, &in, &is_in, &new_index](){//Generates a new vector of size n
            static int index = 0;
            //Searches for the unique element, greather than or equal to a and less than or equal to b
            auto search = std::find_if ( in.begin(), in.end(),[&a, &b, &in]( int val ){return ( val >= a && val <=b && std::count ( in.begin(), in.end(), val ) == 1 ) ? true : false;});
            if ( search == in.end() ){//If item was not found, bool set to true to remove this
                is_in = true;         //and next elements from vector
                new_index = index;
            }
            if ( is_in ){
                return 0;
            }
            index++;
            int result = *search;
            in.erase ( search );//Deletes the found element from the given vector in order to find another element in the next iteration
            return result;
        });
    if (is_in){
        new_vec.erase(new_vec.begin() + new_index, new_vec.end());
    }
    std::sort(new_vec.begin(), new_vec.end());
    return new_vec;
}
std::vector<std::string> hide_secret ( std::vector<std::string> in ){// Replaces the non alpha-num strings with the word "hidden"
    std::replace_if( in.begin(), in.end(), [] ( std::string str ){
            // Searches for the non alpha-num symbol in the current string
            auto search = std::find_if( str.begin(), str.end(), [] ( char c ){return !( std::isalpha(c) || std::isdigit(c));});//Returns true if the symbol is not a digit or alpha
            return (search != str.end() ? true : false);}, "hidden");//Returns true if a non alpha-num symbol was found
    return in;
}
std::vector<std::string> ap_reverse ( int a, int d, int n ){
    std::vector<std::string> vec(n);
    //Generates vector of size n
    std::generate( vec.begin(), vec.end(),[&a, &d](){
            static int el = a; //Current element of the progression
            std::string str_el = std::to_string(el); //Converts the number to string
            std::reverse( str_el.begin(), str_el.end() ); //Reverses the string
            el += d;
            return str_el;
        });
    return vec;
}
