#ifndef _CPRAC_H_
#define _CPRAC_H_

class pqNode { 
    public: 
        int value;
        map < String, int> hmap;
        pqNode(): value(1) {}
        pqNode(String key, int val) {
            if ( val == value)  
                hmap[key] = value;
        }
};
struct nodeCompare {
    bool operator() (const pqNode& p1, const pqNode& p2) const
    {
        if (p1.value < p2.value) { 
            return true;
        }
        return false;
    }
};
class allOne {
    public: 
        unordered_map < String, int> hmap;
        allOne() : { }
        void incKey(String key);
};

void practise_cprac(int tc, int argc, char * argv[]);

#endif
