/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2007-2008 Vojtech Franc
 * Written (W) 2007-2008 Soeren Sonnenburg
 * Copyright (C) 2007-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _SVMOCAS_H___
#define _SVMOCAS_H___

#include "lib/common.h"
#include "classifier/LinearClassifier.h"
#include "features/DotFeatures.h"
#include "features/Labels.h"

enum E_SVM_TYPE
{
	SVM_OCAS = 0,
	SVM_BMRM = 1
};

/** class SVMOcas */
class CSVMOcas : public CLinearClassifier
{
	public:
		/** constructor
		 *
		 * @param type a E_SVM_TYPE
		 */
		CSVMOcas(E_SVM_TYPE type);

		/** constructor
		 *
		 * @param C constant C
		 * @param traindat training features
		 * @param trainlab labels for training features
		 */
		CSVMOcas(
			float64_t C, CDotFeatures* traindat,
			CLabels* trainlab);
		virtual ~CSVMOcas();

		/** get classifier type
		 *
		 * @return classifier type SVMOCAS
		 */
		virtual inline EClassifierType get_classifier_type() { return CT_SVMOCAS; }

		/** train SVM
		 *
		 * @return true if training was successful
		 */
		virtual bool train();

		/** set C
		 *
		 * @param c1 new C1
		 * @param c2 new C2
		 */
		inline void set_C(float64_t c1, float64_t c2) { C1=c1; C2=c2; }

		/** get C1
		 *
		 * @return C1
		 */
		inline float64_t get_C1() { return C1; }

		/** get C2
		 *
		 * @return C2
		 */
		inline float64_t get_C2() { return C2; }

		/** set epsilon
		 *
		 * @param eps new epsilon
		 */
		inline void set_epsilon(float64_t eps) { epsilon=eps; }

		/** get epsilon
		 *
		 * @return epsilon
		 */
		inline float64_t get_epsilon() { return epsilon; }

		/** set if bias shall be enabled
		 *
		 * @param enable_bias if bias shall be enabled
		 */
		inline void set_bias_enabled(bool enable_bias) { use_bias=enable_bias; }

		/** check if bias is enabled
		 *
		 * @return if bias is enabled
		 */
		inline bool get_bias_enabled() { return use_bias; }

		/** set buffer size
		 *
		 * @param sz buffer size
		 */
		inline void set_bufsize(int32_t sz) { bufsize=sz; }

		/** get buffer size
		 *
		 * @return buffer size
		 */
		inline int32_t get_bufsize() { return bufsize; }

	protected:
		/** compute W
		 *
		 * @param sq_norm_W square normed W
		 * @param dp_WoldW dp W old W
		 * @param alpha alpha
		 * @param nSel nSel
		 * @param ptr ptr
		 */
		static void compute_W(
			float64_t *sq_norm_W, float64_t *dp_WoldW, float64_t *alpha,
			uint32_t nSel, void* ptr);

		/** update W
		 *
		 * @param t t
		 * @param ptr ptr
		 * @return something floaty
		 */
		static float64_t update_W(float64_t t, void* ptr );

		/** add new cut
		 *
		 * @param new_col_H new col H
		 * @param new_cut new cut
		 * @param cut_length length of cut
		 * @param nSel nSel
		 * @param ptr ptr
		 */
		static void add_new_cut(
			float64_t *new_col_H, uint32_t *new_cut, uint32_t cut_length,
			uint32_t nSel, void* ptr );

		/** compute output
		 *
		 * @param output output
		 * @param ptr ptr
		 */
		static void compute_output( float64_t *output, void* ptr );

		/** sort
		 *
		 * @param vals vals
		 * @param idx idx
		 * @param size size
		 */
		static void sort( float64_t* vals, uint32_t* idx, uint32_t size);

		/** @return object name */
		inline virtual const char* get_name() const { return "SVMOcas"; }

	protected:
		/** if bias is used */
		bool use_bias;
		/** buffer size */
		int32_t bufsize;
		/** C1 */
		float64_t C1;
		/** C2 */
		float64_t C2;
		/** epsilon */
		float64_t epsilon;
		/** method */
		E_SVM_TYPE method;

		/** old W */
		float64_t* old_w;
		/** old bias */
		float64_t old_bias;
		/** nDim big */
		float64_t* tmp_a_buf;
		/** labels */
		float64_t* lab;
		
		/** sparse representation of
		 * cutting planes */
		float64_t** cp_value;
		/** cutting plane index */
		uint32_t** cp_index;
		/** cutting plane dimensions */
		uint32_t* cp_nz_dims;
		/** bias dimensions */
		float64_t* cp_bias;
};
#endif
