/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2008 Christian Gehl
 * Copyright (C) 2008 Fraunhofer Institute FIRST
 */

#ifndef _CHISQUAREDISTANCE_H___
#define __CHISQUAREDISTANCE___

#include "lib/common.h"
#include "distance/SimpleDistance.h"
#include "features/RealFeatures.h"

/** class ChiSquareDistance
 *
 * This implementation of \f$\chi^{2}\f$ distance extends the
 * concept of \f$\chi^{2}\f$ metric to negative values.
 *
 * \f[\displaystyle
 *  d(\bf{x},\bf{x'}) = \sum_{i=1}^{n}\frac{(x_{i}-x'_{i})^2}
 *  {|x_{i}|+|x'_{i}|} \quad \bf{x},\bf{x'} \in R^{n}
 * \f]
 *
 * @see K. Rieck, P. Laskov. Linear-Time Computation of Similarity Measures 
 * for Sequential Data. Journal of Machine Learning Research, 9:23--48,2008.
 */
class CChiSquareDistance: public CSimpleDistance<float64_t>
{
	public:
		/** default constructor */
		CChiSquareDistance();

		/** constructor
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 */
		CChiSquareDistance(CRealFeatures* l, CRealFeatures* r);
		virtual ~CChiSquareDistance();

		/** init distance
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @return if init was successful
		 */
		virtual bool init(CFeatures* l, CFeatures* r);

		/** cleanup distance */
		virtual void cleanup();

		/** load init data from file
		 *
		 * @param src file to load from
		 * @return if loading was successful
		 */
		virtual bool load_init(FILE* src);

		/** save init data to file
		 *
		 * @param dest file to save to
		 * @return if saving was successful
		 */
		virtual bool save_init(FILE* dest);

		/** get distance type we are
		 *
		 * @return distance type CHISQUARE
		 */
		virtual EDistanceType get_distance_type() { return D_CHISQUARE; }

		/** get name of the distance
		 *
		 * @return name Chi-square distance 
		 */
		virtual const char* get_name() const { return "Chi-Square-Distance"; }

	protected:
		/// compute distance for features a and b
		/// idx_{a,b} denote the index of the feature vectors
		/// in the corresponding feature object
		virtual float64_t compute(int32_t idx_a, int32_t idx_b);
};

#endif /* _CHISQUAREDISTANCE_H___ */
