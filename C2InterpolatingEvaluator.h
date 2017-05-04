#ifndef C2INTERPOLATING_CURVE_EVALUATOR_H
#define C2INTERPOLATING_CURVE_EVALUATOR_H

#include "curveevaluator.h"

class C2InterpolatingEvaluator : public CurveEvaluator
{
public:
	/*
	* Override to get a bezier curve according to control Points
	*/
	void evaluateCurve(const std::vector<Point>& controlPoints,
		std::vector<Point>& evaluatedPoints,
		const float& animationLength,
		const bool& beWrap) const override;
private:
	/*
	* Helper function, otherwise to long to write together
	*/
	void _evaluate(const int p1, const int p2, const float& animationLength,
		const std::vector<Point>& controlPointsCopy, std::vector<Point>& evaluatedPoints,
		const std::vector<float>& derivativePoints) const;
	void _evaluateDerivative(std::vector<float>& derivative,
		std::vector<Point> controlPointsCopy, int controlN) const;
};

#endif