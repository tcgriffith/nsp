#include "Score6p.hpp"

namespace jian {
	REG_SCORER("6p", Score6p);

	Score6p::Score6p() {
		m_cg = CG::fac_t::create("6p");
	}

	inline double Score6p::en_len(const Residue &r1, const Residue &r2) {
		double d;

		d = geom::distance(r1[2], r2[0]);
		return square(d - m_bond_len_std);
	}

	inline double Score6p::en_ang(const Residue &r1, const Residue &r2, const Residue &r3) {
		double d, e;
		int i;

		e = 0;
		for (i = 0; i < 3; i++) {
			d = geom::angle(r1[i], r2[i], r3[i]);
			e += square(d - m_bond_angle_std[i]);
		}
		return e;
	}

	inline double Score6p::en_dih(const Residue &r1, const Residue &r2, const Residue &r3, const Residue &r4) {
		return 0;
	}

	inline double Score6p::en_crash(const Residue &r1, const Residue &r2) {
		int i, j;
		double d, e;
		const Residue *p1, *p2;
		Residue *temp1, *temp2;

		if (m_cg->is_cg(r1) && m_cg->is_cg(r2)) {
			temp1 = NULL;
			temp2 = NULL;
			p1 = &r1;
			p2 = &r2;
		}
		else {
			temp1 = new Residue(m_cg->to_cg(r1));
			temp2 = new Residue(m_cg->to_cg(r2));
			p1 = temp1;
			p2 = temp2;
		}


		e = 0;
		for (i = 0; i < m_res_size; i++) {
			for (j = 0; j < m_res_size; j++) {
				d = geom::distance(p1->at(i), p2->at(j));
				if (d < 3) {
					e += square(d - 3);
				}
			}
		}

		if (temp1 != NULL) delete temp1;
		if (temp2 != NULL) delete temp2;

		return e;
	}

	bool Score6p::in_base(int n) {
		return n > 2;
	}

} // namespace jian