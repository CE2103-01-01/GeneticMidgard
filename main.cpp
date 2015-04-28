#include "Data/TreeProof.h"
#include "Interface/Random.h"

using namespace std;
int main() {
    for (int i = 0; i < 100; ++i) {
        cout<<trueRandom::randRange(0.0f, 2.0f)<<endl;
    }
    return 0;
}