#include <iostream>
#include "server.h"





int main() {
    // for (int i = 0; i < 1000; i++)
    // {
    //     if (i % 6 == 0) {
    //         cout << i << endl;
    //     }
    // }
    
    ChatServer cs(8000,10);
    cs.Run();
}