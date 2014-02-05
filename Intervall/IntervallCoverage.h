#ifndef __popup_lab1_intervall__IntervallCoverage__
#define __popup_lab1_intervall__IntervallCoverage__

#include <algorithm>

template <typename T>
struct Intervall {
    T start;
    T end;
    
    Intervall(T start, T end) : start(start), end(end){}
};

struct myclass {
    bool operator() (int i,int j) { return (i<j);}
} myobject;


//TODO Wants this inside minimalCoverage but not working cause of strange error...
template <typename T>
struct IndexedIntervalls {
    IndexedIntervalls(Intervall<T> intervall, unsigned int index) : intervall(intervall), index(index){}
    Intervall<T> intervall;
    unsigned int index;
};
/**
 *
 */
template <typename InputIterator, typename OutputIterator, typename T>
bool minimalCoverage(Intervall<T> intervall, InputIterator begin, InputIterator end, OutputIterator out) {
    //TODO: Want to return OutputIterator but cant get it to work
    
    struct BestIntervall {
        BestIntervall(T endPoint, unsigned int index) : endPoint(endPoint), index(index) {}
        void update(T ep, unsigned int i) {
            endPoint = ep;
            index = i;
        }
        unsigned int getIndex() {
            return index;
        }
        T getEndPoint() {
            return endPoint;
        }
    private:
        T endPoint;
        unsigned int index;
    };
    
    
    std::vector<IndexedIntervalls<T>> sortedIntervalls;

    unsigned int index = 0;
    for(InputIterator it = begin; it != end; it++, index++) {
        sortedIntervalls.push_back(IndexedIntervalls<T>(*it, index));
    }
//    
    std::sort (sortedIntervalls.begin(), sortedIntervalls.end(), [](IndexedIntervalls<T> first, IndexedIntervalls<T> second){return first.intervall.start < second.intervall.start;});
    
    T iStart = intervall.start;
    T iEnd = intervall.end;
    
//    OutputIterator failed(out);
    
    BestIntervall bestIntervall(iStart, -1);
    auto it = sortedIntervalls.begin();
    auto sortedEnd = sortedIntervalls.end();
    
    while(bestIntervall.getIndex() == -1 || bestIntervall.getEndPoint() < iEnd) {
        bestIntervall.update(bestIntervall.getEndPoint(), -1);
        for(; it != sortedEnd && it->intervall.start <= iStart; ++it) {
            if(it->intervall.end >= iEnd) {
                // Needed if initial intervall is [x,x]. Also speeds up performance since we do not need to look further
                bestIntervall.update(it->intervall.end, it->index);
                break;
            }
        
            if(it->intervall.end > iStart && (bestIntervall.getIndex() == -1 || it->intervall.end > bestIntervall.getEndPoint())) {
                bestIntervall.update(it->intervall.end, it->index);
            }
        }
        if(bestIntervall.getIndex() == -1) {
            return false;
//            return failed;
        }
        *out++ = bestIntervall.getIndex();
        iStart = bestIntervall.getEndPoint();
    }
    return true;
//    return out;
}

#endif
