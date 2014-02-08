#ifndef __popup_lab1_intervall__IntervallCoverage__
#define __popup_lab1_intervall__IntervallCoverage__

#include <algorithm>

#define MIN_COV_SUCCESS 0
#define MIN_COV_FAILED 1

template <typename T>
struct Intervall {
    T start;
    T end;
    
    Intervall(T start, T end) : start(start), end(end){}
};

class StringNumber {
    std::string number;
public:
    StringNumber(std::string inputString) {
        if(inputString.find('.') == std::string::npos) {
            inputString.append(".0");
        }
        if(inputString == "-0.0"){
            inputString = "0.0";
        }
        number = inputString;
    }
    
    bool operator<(const StringNumber & otherNumber) {
        bool otherIsNegative = otherNumber.number[0] == '-';
        bool thisIsNegative = number[0] == '-';
        if(thisIsNegative && !otherIsNegative) {
            return true;
        }
        if(!thisIsNegative && otherIsNegative) {
            return false;
        }
        
        if(thisIsNegative) {
            return number > otherNumber.number;
        }
        
        return number < otherNumber.number;
        
        return true;
    }
    
    bool operator>(const StringNumber & otherNumber) {
        return !(*this < otherNumber);
    }
    
    bool operator<=(const StringNumber & otherNumber) {
        if(number == otherNumber.number) {
            return true;
        } else {
            return (*this < otherNumber);
        }
    }
    
    bool operator>=(const StringNumber & otherNumber) {
        if(number == otherNumber.number) {
            return true;
        } else {
            return (*this > otherNumber);
        }
    }
};



/* used within minimalCoverage() so the original indexes of the intervalls are kept even after a sort has been made */
template <typename T>
struct IndexedIntervall {
    IndexedIntervall(Intervall<T> intervall, unsigned int index) : intervall(intervall), index(index){}
    Intervall<T> intervall;
    unsigned int index;
    
    /* always update both values at the same time to avoid user mistakes*/
    void update (Intervall<T> intervall, unsigned int index) {
        this->intervall = intervall;
        this->index = index;
    }
};

static int minimalCoverageResult;

/**
 * 
 * mainIntervall: the Intervall that we are trying to cover fully
 * begin: start of the list of intervalls that we can work with
 * end: end of the list of intervall that we can work with
 * out: should be the beginning of an empty integer list that will be filled with indexes of the found intervalls.
 * However if we fail for some reason, this list will be undefined.
 * exitStatus: will be set to 0 if success, 1 if we could not find a intervall coverage
 */
template <typename InputIterator, typename OutputIterator, typename T>
OutputIterator minimalCoverage(Intervall<T> mainIntervall, InputIterator begin, InputIterator end, OutputIterator out, int & exitStatus = minimalCoverageResult) {
    //TODO: Want to return OutputIterator but cant get it to work
    //we want to sort the input list without altering that list so we create a new vector of the list that we can sort
    std::vector<IndexedIntervall<T>> sortedIntervalls;
    
    unsigned int index = 0;
    for(InputIterator it = begin; it != end; it++, index++) {
        // we keep the original index of each intervall because the output needs it
        sortedIntervalls.push_back(IndexedIntervall<T>(*it, index));
    }
    // We sort each intervall so that the lowest starting values are first
    std::sort (sortedIntervalls.begin(), sortedIntervalls.end(), [](IndexedIntervall<T> first, IndexedIntervall<T> second){return first.intervall.start < second.intervall.start;});
    
    // the mainStart will be altered once we found a optimal intervall covering the mainStart
    T mainStart = mainIntervall.start;
    T mainEnd = mainIntervall.end;
    
    // the chosen intervall is the locally optimal intervall covering as much as possible with start at mainStart
    // when the index is set to -1, no intervall has been found. So setting the intervall to mainIntervall means nothing, its just a starting value since we don't know if T allowed Null values. So index -1 in chosenIntervall means that the intervall "means nothing".
    IndexedIntervall<T> chosenIntervall(mainIntervall, -1);
    
    // we only iterate through our sorted intervall with orignial indexes. Not the original given intervall
    auto it = sortedIntervalls.begin();
    auto sortedEnd = sortedIntervalls.end();
    
    
    // first check is only for first entrence. Second check means that we only search for more intervalls IF we have not yet covered our main endPoint.
    while(chosenIntervall.index == -1 || chosenIntervall.intervall.end < mainEnd) {
        
        //Update the chosen intervall to index -1, indicating that we have no chosen intervall yet.
        chosenIntervall.update(chosenIntervall.intervall, -1);
        for(; it != sortedEnd && it->intervall.start <= mainStart; it++) {

            //if we have not yet chosen a a intervall, we set this intervall to the newest. Otherwise if this intervalls end is further past the other intervalls end we choose this one instead.
            if(chosenIntervall.index == -1 || it->intervall.end > chosenIntervall.intervall.end) {
                chosenIntervall.update(it->intervall, it->index);
            }
        }
        if(chosenIntervall.index == -1) {
            //We never found a intervall that could cover the current mainStart, exit with failed status
            exitStatus = MIN_COV_FAILED;
            return out;
        }
        //update out with the chosen intervalls index
        *out++ = chosenIntervall.index;
        //set the new mainStart to the end of the intervall since we have covered everything up to and including this point.
        mainStart = chosenIntervall.intervall.end;
    }
    // if we leave the while loop, our latest chosen intervall either contains the mainEnd or is the mainEnd
    exitStatus = MIN_COV_SUCCESS;
    return out;
}

#endif
