#pragma once

#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include "../nuc3d/TSP.hpp"
#include "../nuc3d/BuildHelix.hpp"
#include "../nuc3d/transform.hpp"
#include "../nuc3d/TemplRec.hpp"
#include "../nuc3d/TSP.hpp"
#include "../cg.hpp"
#include "../cg/Frags.hpp"
#include "../utils/Env.hpp"
#include "../utils/file.hpp"
#include "../mc.hpp"
#include "../pdb.hpp"
#include "../geom.hpp"
#include "../nuc2d.hpp"
#include "../pp.hpp"



#define JN_MCXP_PARS1 \
	heat_steps, cool_steps, cycle_steps, write_steps, heat_rate, dec_rate, init_tempr, queue
#define JN_MCXP_PARS2 \
	bond_length_weight, bond_angle_weight, bond_angle_std, bond_dihedral_weight, bond_dihedral_std, \
    pairing_weight, wc_weight, nwc_weight, stacking_weight,  constraints_weight, crash_weight, \
    vdw_weight, max_shift
#define JN_MCXP_DEF_PAR(a) double PP_CAT3(_mc_, a);

namespace jian {

	// MvEl: Moving element
	class MvEl {
	public:
		enum mvel_t {
			MVEL_HL, // helix
			MVEL_HP, // hairpin
			MVEL_IL, // internal loop
			MVEL_FG // fragment
		};
		using frag_t = std::array<int, 2>;
		using range_t = std::vector<frag_t>;

		mvel_t type;
		range_t range;

		MvEl(int a, int b, mvel_t t);

		MvEl(int a, int b, int c, int d, mvel_t t);

		MvEl(const helix &h);

		MvEl(loop *l, mvel_t t);

		int min() const;

		int max() const;

		bool operator ==(const MvEl &el) const;

		bool operator !=(const MvEl &el) const;

		MvEl *operator +(const MvEl &el) const;

		friend std::ostream &operator <<(std::ostream &, const MvEl &el);

		bool contains(const MvEl &el) const;

		bool nips(const MvEl &el) const;

		bool has(int n) const {
			return std::find_if(range.begin(), range.end(), [&n](const frag_t &frag) {
				return frag[0] <= n && n <= frag[1];
			}) != range.end();
		}

		static void merge(std::deque<MvEl *> &dq);
	};

	using fixed_ranges_t = std::list<std::array<int, 2>>;
	using fixed_mvels_t = std::list<MvEl>;

	class MCBase : public TSP, public MC {
	public:
		using item_t = Atom;
		using space_val_t = std::list<int>;
		using space_t = std::map<int, std::map<int, std::map<int, space_val_t>>>;
		using item_space_t = std::vector<space_val_t *>;

		space_t m_space;
		item_space_t m_item_space;
		int m_box = 3;
		double m_box_size = 6;
		std::deque<Atom> _moved_atoms;
		std::string m_traj;
		int mc_num_writing = 1;
		std::vector<int> m_continuous_pts;
		std::vector<int> m_ang_pts;
		std::vector<int> m_dih_pts;
		std::vector<int> m_brk_pts;
		std::string m_par_file;
		MolWriter m_writer;

		std::deque<MvEl *> m_mvels;
		std::vector<MvEl *> m_base_mvels;
		MvEl *m_selected_mvel;
		fixed_mvels_t m_fixed_mvels;

		JN_MAP(JN_MCXP_DEF_PAR, JN_MCXP_PARS2);

		MCBase() = default;

		void init(const Par &par);

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

		item_t &item(int i);

		space_val_t &space_val(int i);

		void space_update_item(int i);

		void run();

		void transform();

		Mat chain_to_coords();

		void print_final_constraints();

		void cg_to_aa(const Mat &c);

		virtual double mc_partial_energy() = 0;
		virtual double dist_two_res(const Residue &, const Residue &) const = 0;
		virtual void write_en() = 0;

		virtual void before_run();
		virtual void finish_run();

		virtual std::string file_parameters() const;

		virtual void save_fixed_ranges();
		virtual void restore_fixed_ranges();

		virtual void mc_select() = 0;
		virtual bool is_selected(const int &i) const = 0;
		virtual Vec rotating_center() const = 0;

	};

} // namespace jian
