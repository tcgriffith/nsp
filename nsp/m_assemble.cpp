#include "nsp.hpp"
#include <jnbio/nuc3d/Assemble.hpp>
#include <jnbio/pdb/utils/cluster_chains.hpp>
#include <jnbio/scoring/Score.hpp>

BEGIN_JN

REGISTER_NSP_COMPONENT(assemble) {
	nuc3d::Assemble ass(par);

	std::ostringstream stream;
	int n;

	int num = 1;
	par.set(num, "n", "num");

	ass.select_templates();
    ass.assemble();

	n = 1;
	mol_write(ass._pred_chain, to_str(ass._name, ".", n, ".pred.pdb"));
	for (n = 2; n <= num; n++) {
		ass.sample_all_templates();
		ass.assemble();
		ass.log << "# Writing sampling structure " << n << std::endl;
		mol_write(ass._pred_chain, to_str(ass._name, ".", n, ".pred.pdb"));
	}

}

END_JN

