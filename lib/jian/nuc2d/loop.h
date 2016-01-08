#ifndef LOOP_H
#define LOOP_H

#include "helix.h"

namespace jian {
namespace nuc2d {

class loop {
public:
    int type = 0; // -2:pseudoknot
    int len = 0;
    int isPartial = 0;
    res *head = NULL;
    helix s;
    vector<pair<int, int>> hinges;
    deque<loop> sons;
    loop *son = NULL;
    loop *brother = NULL;

    loop() {}
    loop(loop *l) : type(l->type), len(l->len), isPartial(l->isPartial), 
                    head(res::copy(l->head)), s(l->s), hinges(l->hinges), 
                    sons(l->sons), son(l->son), brother(l->brother) {
    }
    loop(const loop &l) : type(l.type), len(l.len), isPartial(l.isPartial), 
                          head(res::copy(l.head)), s(l.s), hinges(l.hinges), 
                          sons(l.sons), son(l.son), brother(l.brother) {
    }
    loop &operator =(const loop &l) {
        type = l.type;
        len = l.len;
        isPartial = l.isPartial;
        res::del(head);
        head = res::copy(l.head);
        s = l.s;
        hinges = l.hinges;
        sons = l.sons;
        son = l.son;
        brother = l.brother;
        return *this;
    }

    template<typename Fn> void each(Fn &&f) {
        int index = 0;
        for (auto r = head; r != NULL; r = r->next) {
            f(r, index);    
            index++;
        }
    }

    template<typename Fn> void each(Fn &&f) const {
        int index = 0;
        for (auto r = head; r != NULL; r = r->next) {
            f(r, index);    
            index++;
        }
    }

    template<typename Fn> void apply(Fn &&f) {
        f(this);
        for (auto l = son; l != NULL; l = l->brother) l->apply(f);
    }

    template<typename Fn> void apply(Fn &&f) const {
        f(this);
        for (auto l = son; l != NULL; l = l->brother) l->apply(f);
    }

    res &at(int n) {
        int index = 0;
        for (auto r = head; r != NULL; r = r->next) {
            if (r->type == '&') continue;
            if (index == n) return *r;
            index++;
        }
        throw "jian::nuc2d::loop::at error! out of range.";
    }

    const res &at(int n) const {
        int index = 0;
        for (auto r = head; r != NULL; r = r->next) {
            if (r->type == '&') continue;
            if (index == n) return *r;
            index++;
        }
        throw "jian::nuc2d::loop::at error! out of range.";
    }


    static loop *copy(loop *l) {
        if (l == NULL) {
            return NULL;
        }

        loop *l_ = new loop(l);
        l_->son = copy(l->son);
        l_->brother = copy(l->brother);
        return l_;
    }
    static void del(loop *l) {
        if (l == NULL) {
            return;
        }

        del(l->son);
        del(l->brother);
        delete l;
        return;
    }
    ~loop() {
        res::del(head);
    }

    inline bool has_helix() {
        return s.head != NULL;
    }

    inline bool has_loop() {
        return head != NULL;
    }

    inline bool has_son() {
        if (son == NULL) {
            return false;
        } else {
            return true;
        }
    }

    inline bool has_brother() {
        if (brother == NULL) {
            return false;
        } else {
            return true;
        }
    }

    inline bool empty() {
        if (head == NULL) {
            return true;
        } else {
            return false;
        }
    }

    int getLen() {
        int temp;
        res *tempRes;

        for (temp = 0, tempRes = head; tempRes != NULL; tempRes = tempRes->next) {
            if (tempRes->type == '(' || tempRes->type == ')' || tempRes->type == '.' || tempRes->type == '[' || tempRes->type == ']') {
                temp++;
            }
        }
        return temp;
    }

    int size() {
        int temp;
        res *tempRes;

        for (temp = 0, tempRes = head; tempRes != NULL; tempRes = tempRes->next) {
            if (tempRes->type != '&') temp++;
        }
        return temp;
    }

    int num_branches() const {
        int len = 0;
        each([&len](auto res, int index){
            if (res->type == ')') len++;
        });
        return len / 2;
    }

    int num_sons() const {
        return hinges.size();
    }

    int getLoopCounts() {
        int counts = 0;
        if (son != NULL) {
            counts += son->getLoopCounts();
        }
        if (brother != NULL) {
            counts += brother->getLoopCounts();
        }
        if (head != NULL) {
            counts++;
        }
        return counts;
    }

    int isVirtual() {
        res *tempRes;
        int flag = 0;

        if (head != NULL) {
            for (tempRes = head; tempRes != NULL; tempRes = tempRes->next) {
                if (tempRes->type == '&') {
                    flag = 1;
                    break;
                }
            }
            return flag;
        } else {
            return -1;
        }
    }

    bool is_open() const {
        return num_branches() == num_sons();
    }

    string getFlag() {
        string flag;
        res *r;
        int n = 0;
        for (r = head; r->next != NULL; r = r->next);
        if (r->type == '&') {
            int temp = 0;
            stringstream ss;
            for (res *tempRes = head; tempRes != NULL; tempRes = tempRes->next) {
                if (tempRes->type == '.' || tempRes->type == '[' || tempRes->type == ']') {
                    temp++;
                } else if (tempRes->type == ')') {
                    if (n % 2 == 1) {
                        ss << temp << '-';
                        temp = 0;
                    }
                    n++;
                }
            }
            ss << temp;
            ss >> flag;
        } else {
            int temp = 0;
            stringstream ss;
            for (res *tempRes = head->next; tempRes->next != NULL; tempRes = tempRes->next) {
                if (tempRes->type == '.' || tempRes->type == '[' || tempRes->type == ']') {
                    temp++;
                } else if (tempRes->type == ')') {
                    if (n % 2 == 1) {
                        ss << temp << '-';
                        temp = 0;
                    }
                    n++;
                }
            }
            ss << temp << '-';
            ss >> flag;
        }
        return flag;
    }

    string ss() const {
        string ss;
        for (res *r = head; r != NULL; r = r->next) {
            ss += r->type;
        }

        return ss;
    }

    string seq() const {
        string seq;
        for (res *r = head; r != NULL; r = r->next) {
            if (r->type != '&') {
                seq += r->name;
            }
        }
        return seq;
    }
    string getSS() const {
        string ss;
        for (res *r = head; r != NULL; r = r->next) {
            ss += r->type;
        }

        return ss;
    }

    string getSeq() const {
        string seq;
        for (res *r = head; r != NULL; r = r->next) {
            if (r->type != '&') {
                seq += r->name;
            }
        }
        return seq;
    }

};

} // namespace nuc2d
} // namespace jian

#endif

