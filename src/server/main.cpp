#include <iostream>
#include "server.h"





int main() {
    ChatServer cs(8000,10);
    cs.Run();
}