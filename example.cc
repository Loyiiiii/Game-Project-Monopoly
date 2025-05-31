import <string>;



void goo(int x,char c='a',std::string str ="cs") {
    std::cout << "goo l" << std::endl;
}

void goo(int x,int y = 10) {
    std::cout << "goo 2"<< std::endl;
}

int main(int argc,char* argv[]) {
    goo(10);
}