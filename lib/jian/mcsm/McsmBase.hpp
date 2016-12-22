#pragma once

#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include "../nuc3d/TSP.hpp"
#include "../nuc3d/BuildHelix.hpp"
#include "../nuc3d/transform.hpp"
#include "../nuc3d/TemplRec.hpp"
#include "../cg.hpp"
#include "../cg/ResFrags.hpp"
#include "../utils/Env.hpp"
#include "../utils/file.hpp"
#include "../mc.hpp"
#include "../pdb.hpp"
#include "../geom.hpp"
#include "../nuc2d.hpp"
#include "../pp.hpp"
#include "../nuc3d/BuildChain.hpp"
#include "../scoring/ResConf.hpp"


#define JN_MCXP_PARS1 \
	heat_steps, cool_steps, cycle_steps, write_steps, heat_rate, dec_rate,\
    init_tempr, queue, lowest_rate, lowest_en, lowest_tempr, highest_tempr

#define JN_MCXP_PARS2 \
	bond_length_weight, bond_angle_weight, bond_angle_std, bond_dihedral_weight, bond_dihedral_std, \
    pairing_weight, wc_weight, nwc_weight, stacking_weight,  constraints_weight, crash_weight, \
    vdw_weight, max_shift

#define JN_MCXP_DEF_PAR(a) Num PP_CAT3(_mc_, a);

BEGIN_JN

using Frag = Array<int, 2>;

using Frags = Deque<Frag>;

class MvEl;

using MvEls = Deque<MvEl>;

// MvEl: Moving Element
class MvEl {
public:
	enum Type {
		MVEL_HL, // helix
		MVEL_HP, // hairpin
		MVEL_IL, // internal loop
		MVEL_FG // fragment
	};

	Type type;
	Frags range;

	MvEl(int a, int b, Type t);

	MvEl(int a, int b, int c, int d, Type t);

	MvEl(const Helix &h);

	MvEl(SSTree::El *l, Type t);

	int min() const;

	int max() const;

	bool operator ==(const MvEl &el) const;

	bool operator !=(const MvEl &el) const;

	MvEl *operator +(const MvEl &el) const;

	friend std::ostream &operator <<(std::ostream &, const MvEl &el);

	bool contains(const MvEl &el) const;

	bool nips(const MvEl &el) const;

	bool has(int n) const {
		return std::find_if(range.begin(), range.end(), [&n](const Frag &frag) {
			return frag[0] <= n && n <= frag[1];
		}) != range.end();
	}

	bool minmax_has(int n) const {
		int min = 99999;
		int max = -1;
		for (auto && frag : range) {
			if (min > frag[0]) min = frag[0];
			if (max < frag[1]) max = frag[1];
		}
		return min <= n && n <= max;
	}

	static void merge(Deque<MvEl *> &dq);
};

// MCBase: Base of Monte Carlo Molecule Simulation
class MCBase : public TSP, public MC {
public:
	using SpaceItem = Atom;
	using SpaceVal = List<Int>;
	using Space = Map<Int, Map<Int, Map<Int, SpaceVal>>>;
	using SpaceVals = Vector<SpaceVal *>;

	enum SampleMode {
		SAMPLE_SSE,
		SAMPLE_TREE
	};

	ResConf::MapConfs m_res_confs;
	SampleMode m_sample_mode;
	Bool m_cal_en_constraints;
	Bool m_will_write_traj;
	Space m_space;
	SpaceVals m_item_space;
	Int m_box;
	Num m_box_size;
	Deque<Atom> _moved_atoms;
	Str m_traj;
	Int mc_num_writing = 1;
	Vector<Int> m_continuous_pts;
	Vector<Int> m_ang_pts;
	Vector<Int> m_dih_pts;
	Vector<Int> m_brk_pts;
	Str m_par_file;
	MolWriter m_writer;
	Num m_max_angle;
	Str m_init_sfile;
	Str m_alignfile;
	Deque<Array<Int, 2>> m_align;

	Deque<MvEl *> m_mvels;
	Vector<MvEl *> m_base_mvels;
	MvEl *m_selected_mvel = NULL;
	List<Vector<Bool>> m_fixed_areas;

	JN_MAP(JN_MCXP_DEF_PAR, JN_MCXP_PARS2);

	MCBase() = default;

	void init(const Par &par);

	void set_align();

	void align_to_fixed_areas();

	void restore_raw();

	void set_traj_name();

	void validate_constraints();

	void read_parameters();

	void set_parameters(const Par &par);

	void print_parameters();

	void set_continuous_pts();

	void mc_write();

	void write_traj();

	virtual void mc_sample();

	void mc_sample_res();

	void mc_back();

	void backup();

	void init_space();

	int space_index(double n) const;

	SpaceItem &item(int i);

	SpaceVal &space_val(int i);

	void space_update_item(int i);

	void run();

	void transform();

	void print_final_constraints();

	virtual void mc_next_step();

	virtual double mc_partial_energy() = 0;

	virtual double mc_total_energy() = 0;

	virtual double dist_two_res(const Residue &, const Residue &) const = 0;

	virtual void write_en() = 0;

	virtual void before_run();

	virtual void finish_run();

	virtual S file_parameters() const;

	virtual void save_fixed_ranges();

	virtual void restore_fixed_ranges();

	virtual void mc_select() = 0;

	virtual bool is_selected(const int &i) const = 0;

	virtual Vec rotating_center() const = 0;

};

END_JN

