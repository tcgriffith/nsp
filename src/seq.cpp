#include <string>
#include "nsp.hpp"
#include <jian/pdb.hpp>

namespace jian {

static std::string seq_chain(const Chain &c) {
    std::string seq(c.size(), 'X');
    for (int i = 0; i < seq.size(); i++) {
        seq[i] = c[i].name.back();
    }
    return seq;
}

REGISTER_NSP_COMPONENT(seq) {
    Model m(par["pdb"][0]);
    if (par.has("chain")) {
        for (auto && chain : m) {
            if (chain.name == par["chain"][0]) {
                std::cout << seq_chain(chain) << std::endl;
                return;
            }
        }
        std::cout << "This molecule has no chain named " << par["chain"][0] << std::endl;
    } else {
        std::vector<std::string> r {"A", "U", "G", "C"};
        std::vector<std::string> d {"DA", "DT", "DG", "DC"};
        std::string seq;
        for (auto && chain : m) {
            for (auto && res : chain) {
                if (std::find(r.begin(), r.end(), res.name) != r.end()) {
                    seq += res.name;
                } else if (std::find(d.begin(), d.end(), res.name) != d.end()) {
                    seq += res.name.back();
                } else {
                    seq += 'X';
                }
            }
        }
        std::cout << seq << std::endl;
    }
}

} // namespace jian

