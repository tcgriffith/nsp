#pragma once

#include "../../etl.hpp"
#include "../JobPredict3D.hpp" 
#include "../../dg/DG.hpp"
#include "BuildTriLoop.hpp"

namespace jian {

class TriAss : public BasicPredict3D, public virtual JobPredict3D {
public:
    using Res = struct {char seq; char ss; int num;};
    using Frag = std::vector<Res>;
    using Module = struct {std::string type; std::list<Frag> frags;};
    using Tree = std::list<Module>;
    using Templates = std::map<const Module *, Model>;

    DG::DistBoundType _dist_bound;
    DG::DihBoundType _dih_bound;
    DG dg;

    BuildTriLoop<Model> build_tri_loop;

    TriAss() {}

    TriAss(Par par) : JobPredict3D(par) {}

//    void operator ()() {
//        log("Start Tri-assemble.\n");
//        for (int i = 0; i < _num; i++) {
//            log("tri-assemble model ", i, '\n');
//            std::string file_name = _name + "-" + boost::lexical_cast<std::string>(i + 1);
//            predict().write(file_name);
//        }
//        log("Finish Tri-assemble.\n");
//    }

    Model predict() {
        auto tree = ss_to_tree();
        for (auto && module : tree) {
            Trace::log(module.type, '\n');
            for (auto && frag : module.frags) {
                for (auto && res : frag) {
                    Trace::log(res.seq, '-', res.ss, '-', res.num, ' ');
                }
                Trace::log('\n');
            }
        }
        auto templates = find_templates(tree);
        position_templates(tree, templates);
        auto model = assemble_templates(tree, templates);
        return build_strands(tree, model);
    }

    Tree ss_to_tree() {
        Tree tree;
        auto res_list = map<std::vector>([&](int i){return Res{_seq[i], _ss[i], i};}, range(0, _seq.size()));
        auto paired_res_list = filter<std::vector>([](const Res &res){return res.ss != '.';}, res_list);
        int len = paired_res_list.size() / 3;

        // hairpin 1
        Module hairpin1; hairpin1.type = "hairpin";
        hairpin1.frags.push_back(map<std::vector>([&](int i){return Res{_seq[i], _ss[i], i};}, range(0, paired_res_list[0].num)));
        hairpin1.frags.push_back(map<std::vector>([&](int i){return Res{_seq[i], _ss[i], i};}, 
            range(paired_res_list[2 * len - 1].num + 1, paired_res_list[2 * len].num - paired_res_list[2 * len - 1].num - 1)));
        tree.push_back(hairpin1);

        // helix 1, loop 1, helix 2, loop 2
        int len_helix = 1;
        std::vector<int> beg {paired_res_list[0].num, paired_res_list[len].num, paired_res_list[2 * len].num};
        for (int i = 1; i < len; i++) {
            if (exists([&](int n){return paired_res_list[n].num - paired_res_list[n - 1].num > 1;}, std::vector<int>{i, len + i, 2 * len + i})) {
                Module helix, loop; helix.type = "helix"; loop.type = "loop";
                for (int j = 0; j < 3; j++) {
                    helix.frags.push_back(map<std::vector>([&](int n){return res_list[n];}, range(beg[j], len_helix)));
                    loop.frags.push_back(map<std::vector>([&](int n){return res_list[n];}, 
                        range(paired_res_list[i + j * len - 1].num + 1, paired_res_list[i + j * len].num - paired_res_list[i + j * len - 1].num - 1)));
                }
                append(tree, std::move(helix), std::move(loop));
                beg = {paired_res_list[i].num, paired_res_list[i + len].num, paired_res_list[i + 2 * len].num};
                len_helix = 1;
            } else {
                len_helix++;
            }
        }

        // helix 3
        Module helix; helix.type = "helix";
        for (int j = 0; j < 3; j++) helix.frags.push_back(map<std::vector>([&](int n){return res_list[n];}, range(beg[j], len_helix)));
        append(tree, std::move(helix));

        // hairpin 2
        Module hairpin2; hairpin2.type = "hairpin";
        hairpin2.frags.push_back(map<std::vector>([&](int i){return Res{_seq[i], _ss[i], i};}, 
            range(paired_res_list[len - 1].num + 1, paired_res_list[len].num - paired_res_list[len - 1].num - 1)));
        hairpin2.frags.push_back(map<std::vector>([&](int i){return Res{_seq[i], _ss[i], i};}, 
            range(paired_res_list[3 * len - 1].num + 1, _seq.size() - paired_res_list[3 * len - 1].num - 1)));
        tree.push_back(hairpin2);

        return tree;
    }

    Templates find_templates(const Tree &tree) {
        Templates templates;
        for (auto && module : tree) {
            if (module.type == "helix") templates[&module] = find_helix_templates(module);
        }
        return templates;
    }

    Model find_helix_templates(const Module &module) {
        std::list<std::string> seqs;
        for (int i = 1; i < ref(module.frags, 0).size(); i++) {
            std::string s; s.reserve(6);
            for (int j = 0; j < 3; j++) append(s, ref(module.frags, j)[i - 1].seq, ref(module.frags, j)[i].seq);
            seqs.push_back(s);
        }
        auto models = map([&](const std::string &s){return load_helix(s);}, seqs);
        return assemble_helices(models);
    }

    Model load_helix(const std::string &s) {
        return Model();
    }

    template<typename LS>
    Model assemble_helices(LS &&ls) {
        return Model();
    }

    void position_templates(const Tree &tree, Templates &templates) {}

    Model assemble_templates(const Tree &tree, const Templates &templates) {
        return Model();
    }

    Model build_strands(const Tree &tree, const Model &model) {
        return Model();
    }

};

} // namespace jian
