#include "TestMC.h"
#include "../util/Par.h"

int main(int argc, char **argv) {
    jian::dg::TestMC test_mc;
    jian::Par par(argc, argv);
    test_mc(std::stoi(par["num"][0]));
    return 0;
}