#ifndef JIAN_PDB_RESIDUE
#define JIAN_PDB_RESIDUE

#include "Atom.h"

namespace jian {

class Residue : public std::deque<Atom> {
public:
    int num = -1;
    std::string name = "X";
    std::string type = "unknown";

    Residue() {}

    Residue(MolFile &pdb_file) {
        if (!pdb_file.eof()) {
            name = format_name(pdb_file.res_name());
            num = pdb_file.res_num();
            int model_num = pdb_file.model_num();
            std::string chain_name = pdb_file.chain_name();
            while (!pdb_file.eof() and model_num == pdb_file.model_num() and chain_name == pdb_file.chain_name() 
                   and num == pdb_file.res_num() and name == format_name(pdb_file.res_name())) {
                this->push_back(Atom(pdb_file));
            }
        }
    }

    std::string format_name(const std::string &s) {
        std::smatch result;
        if (std::regex_match(s, result, std::regex("^(\\w+)\\d+$"))) {
            // tLeap would append a '5' after the name of first residue
            // and '3' after the name of the last residue
            return result[1];
        } else return s;
    }

    Atom &operator [](int n) {
        return std::deque<Atom>::operator [](n);
    }

    const Atom &operator [](int n) const {
        return std::deque<Atom>::operator [](n);
    }

    Atom &operator [](const std::string &s) {
        for (auto &&atom : *this) if (atom.name == s) return atom;
        throw "jian::Residue::operator[] error! Not found atom!";
    }

    const Atom &operator [](const std::string &s) const {
        for (auto &&atom : *this) if (atom.name == s) return atom;
        throw "jian::Residue::operator[] error! Not found atom!";
    }

};

template<typename T>
inline uniform_const_t<Atom, T> &atom(T &&res, const std::string &s) {
    for (auto &&atom : res) if (atom.name == s) return atom;
    throw "jian::pdb::Atom::operator [](const std::string &) error!";
}

template<typename T, template<typename...> class L = std::deque>
inline auto atoms(const Residue &r, T &&ls) {
    L<Atom> v;
    for (auto &&atom : r) if (std::count(ls.begin(), ls.end(), atom.name)) v.push_back(atom);
    return v;
}

template<typename T>
inline bool exists_atom(T &&res, const std::string &s) {
    for (auto &&atom : res) if (atom.name == s) return true;
    return false;
}

inline std::deque<Residue> get_residues_from_file(std::string file_name) {
    std::deque<Residue> residues;
    if (file_name.size() > 4 && file_name.substr(file_name.size() - 4, 4) == ".pdb") {
        PdbFile pdb_file(file_name);
        if (!pdb_file.eof()) {
            while (!pdb_file.eof()) {
                residues.push_back(Residue(pdb_file));
            }
        }
    } else if (file_name.size() > 4 && file_name.substr(file_name.size() - 4, 4) == ".cif") {
        Cif cif(file_name);
        if (!cif.eof()) {
            while (!cif.eof()) {
                residues.push_back(Residue(cif));
            }
        }
    } else {
        throw "JIAN::RESIDUE::get_residues_from_file(std::string) error! Please give me a file ended with '.pdb' or '.cif'!";
    }
    return residues;
}

} // namespace jian

#endif

