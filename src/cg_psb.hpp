#pragma once

#include "matrix.hpp"
#include "pdb_chain.hpp"
#include "cg.hpp"

BEGIN_JN

	class CGpsb : public CG {
	public:
		static const std::vector<std::string> m_basic_atoms;

		CGpsb();
		virtual Residue to_cg(const Residue &r) const;
		virtual int res_size() const;
	};

END_JN


