#ifndef INCLUDED_BSPLINE_CURVE_EVALUATOR_H
#define INCLUDED_BSPLINE_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  

#include "CurveEvaluator.h"

//using namespace std;

class BSplineCurveEvaluator : public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Point>& ctrlPts,
		std::vector<Point>& evalCurvePts,
		const float& aniLength,
		const bool& beWrap) const;
};

#endif