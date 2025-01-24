#pragma once
#include <algorithm>
#include "Tile.hpp"

#include <stdexcept>
#define MAX_HAND_SIZE 14
class Hand {
private:
    Tile* m_tiles[MAX_HAND_SIZE];        // Array of pointers to Tile objects
    size_t m_handSize;       // Current hand size

    void insert_before(size_t index, Tile* new_tile) {
        if (m_handSize >= MAX_HAND_SIZE) {
            throw std::out_of_range("");
        }
        for (size_t i = m_handSize; i > index; --i) {
            m_tiles[i] = m_tiles[i - 1];
        }
        m_tiles[index] = new_tile;
        m_handSize++;
    }

    Tile* pop(size_t index) {
        if (index >= m_handSize) throw std::out_of_range("");
        Tile* removedTile = m_tiles[index];
        for (size_t i = index; i < m_handSize - 1; ++i) {
            m_tiles[i] = m_tiles[i + 1];
        }
        m_tiles[m_handSize - 1] = nullptr;
        m_handSize--;
        return removedTile;
    }
public:
    // Constructors and Destructor
    Hand() {
        m_handSize=0;
    };
    ~Hand() {
        clear();
    };

    // Member Functions
    void clear() {
    for (size_t i = 0; i < m_handSize; ++i) {
        delete m_tiles[i];  // Delete each Tile* individually
        m_tiles[i] = nullptr;
    }
    m_handSize = 0;
    };
    void add_tile(Tile* tile) {
        size_t index = 0;
        while (index < m_handSize && *m_tiles[index] < *tile) {
            ++index;
        }
        insert_before(index, tile);
    }
    Tile* discard_tile() {
        for (size_t i = 0; i < m_handSize - 3; ++i) {
            if (m_tiles[i] == m_tiles[i + 1] &&
                m_tiles[i + 1] == m_tiles[i + 2] &&
                m_tiles[i + 2] == m_tiles[i + 3]) {
                return pop(i);  // Discard one tile from the quadruplet
            }
        }

        for (size_t i = 0; i < m_handSize; ++i) {
            size_t count = 1;
            for (size_t j = i + 1; j < m_handSize; ++j) {
                if (*m_tiles[i] == *m_tiles[j]) count++;
            }
            if (count == 1) {
                return pop(i);  // Discard the single tile
            }
        }

        size_t pairCount = 0;
        for (size_t i = 0; i < m_handSize - 1; ++i) {
            if (*m_tiles[i] == *m_tiles[i + 1]) {
                pairCount++;
                if (pairCount >= 3) {
                    return pop(i);  // Discard from a pair when 3+ pairs exist
                }
                i++;  // Skip the next tile since it's part of the pair
            }
        }

    }


    bool check_win_condition() const {
        if (m_handSize==MAX_HAND_SIZE){
            int counter=0;
            if((m_tiles[-1]==m_tiles[-2])&&(m_tiles[-1]!=m_tiles[-3])){

                for (size_t i = 0; i < m_handSize-5; ++i) {
                Tile* first = m_tiles[i];
                Tile* second = m_tiles[i+1];
                Tile* third = m_tiles[i+2];
                Tile* fourth = m_tiles[i+3];
                if (first==second){
                    if(second==third){
                        if(third==fourth){
                            counter=counter+1;
                        }
                    }
                }

                return (counter==3);

            }

            }else if ((m_tiles[0]==m_tiles[1])&&(m_tiles[1]!=m_tiles[3])){

                for (size_t i = 2; i < m_handSize-3; ++i) {
                Tile* first = m_tiles[i];
                Tile* second = m_tiles[i+1];
                Tile* third = m_tiles[i+2];
                Tile* fourth = m_tiles[i+3];
                if (first==second){
                    if(second==third){
                        if(third==fourth){
                            counter=counter+1;
                        }
                    }
                }

                return (counter==3);
            }
            }
            else if (m_tiles[4]==m_tiles[5]){
                Tile* first = m_tiles[0];
                Tile* second = m_tiles[1];
                Tile* third = m_tiles[2];
                Tile* fourth = m_tiles[3];
                if (first==second){
                    if(second==third){
                        if(third==fourth){
                            counter=counter+1;
                        }
                    }
                }
                for (size_t i = 6; i < m_handSize-3; ++i) {
                    first = m_tiles[i];
                    second = m_tiles[i+1];
                    third = m_tiles[i+2];
                    fourth = m_tiles[i+3];
                    if (first==second){
                        if(second==third){
                            if(third==fourth){
                                counter=counter+1;
                            }
                        }
                    }

                }
                return (counter==3);
            }
            else if (m_tiles[8]==m_tiles[9]){
                Tile* first = m_tiles[10];
                Tile* second = m_tiles[11];
                Tile* third = m_tiles[12];
                Tile* fourth = m_tiles[13];
                if (first==second){
                    if(second==third){
                        if(third==fourth){
                            counter=counter+1;
                        }
                    }
                }
                for (size_t i = 0; i < m_handSize-9; ++i) {
                    first = m_tiles[i];
                    second = m_tiles[i+1];
                    third = m_tiles[i+2];
                    fourth = m_tiles[i+3];
                    if (first==second){
                        if(second==third){
                            if(third==fourth){
                                counter=counter+1;
                            }
                        }
                    }

                }
                return (counter==3);

            }else{
                return false;
            }
        }else{
            return false;
        }
    };

    // Display Function
    void display_hand() const {
        for (size_t i = 0; i < m_handSize; ++i) {
            std::cout <<m_tiles[i];

        }
    };
};
