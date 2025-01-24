#pragma once
#include <iostream>

#include <stdexcept>

// Define your Tile struct
class Tile {
public:
    char m_suit;//C,B,D
    int m_number;//1-9

    // Default constructor; initialized without parameters
    Tile() {
        m_suit=' ';
        m_number=0;
	}

    // Parameterized constructor; initialized with parameters
    Tile(char s, int n) {
        m_suit=s;
        m_number=n;
    }

    // Comparison operator for equality
    bool operator==(const Tile& other) const {
        char currents=this->m_suit;
        char others= other.m_suit;
        int currentn=this->m_number;
        int othern=other.m_number;
        int ascic = currents;
        int ascio = others;
        if ((othern==currentn)&&(ascic==ascio)){
            return true;
        }else{
            return false;
        }
    }
    // Overload less-than operator
    bool operator<(const Tile& other) const {
        char currents=this->m_suit;
        char others= other.m_suit;
        int currentn=this->m_number;
        int othern=other.m_number;
        int ascic = currents;
        int ascio = others;
        if (ascic<ascio){
            return true;
        }else if (ascic==ascio){

            if(currentn<othern){
                return true;
            }
            return false;
        }else{
            return false;
        }
    }

    // Overload greater-than operator
    bool operator>(const Tile& other) const {
        char currents=this->m_suit;
        char others= other.m_suit;
        int currentn=this->m_number;
        int othern=other.m_number;
        int ascic = currents;
        int ascio = others;
        if (ascic>ascio){
            return true;
        }else if (ascic==ascio){

            if(currentn>othern){
                return true;
            }
            return false;
        }else{
            return false;
        }
    }

    bool operator<=(const Tile& other) const {
        char currents=this->m_suit;
        char others= other.m_suit;
        int currentn=this->m_number;
        int othern=other.m_number;
        int ascic = currents;
        int ascio = others;
        if (ascic>ascio){
            return false;
        }else if (ascic==ascio){

            if(currentn>othern){
                return false;
            }
            return true;
        }else{
            return true;
        }
    }

    bool operator>=(const Tile& other) const {
        char currents=this->m_suit;
        char others= other.m_suit;
        int currentn=this->m_number;
        int othern=other.m_number;
        int ascic = currents;
        int ascio = others;
        if (ascic<ascio){
            return false;
        }else if (ascic==ascio){

            if(currentn<othern){
                return false;
            }
            return true;
        }else{
            return true;
        }

    }

    bool operator!=(const Tile& other) const {
        char currents=this->m_suit;
        char others= other.m_suit;
        int currentn=this->m_number;
        int othern=other.m_number;
        int ascic = currents;
        int ascio = others;
        if ((othern==currentn)&&(ascic==ascio)){
            return false;
        }else{
            return true;
        }
    }

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Tile& tile) {
        os << tile.m_suit << tile.m_number;
        return os;
    }
};
